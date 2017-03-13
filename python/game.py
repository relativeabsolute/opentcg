# MIT License
#
# Copyright (c) 2017 Johan Burke
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated self.documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import xml.dom.minidom as dom
import os
import os.path

import xmlutil
import sqlite3

class Game:

    # reads the given xml file into a dictionary structure
    # which will be converted into SQL
    def read_card(self, set_file, card_filename):
        print("Card = " + card_filename)
        card_doc = dom.parse(os.path.join(set_file, card_filename))
        result = {}
        result['name'] = xmlutil.get_element_text(card_doc, 'Name')
        result['setcode'] = xmlutil.get_element_text(card_doc, 'SetCode')
        result['setname'] = xmlutil.get_element_text(card_doc, 'SetName')
        result['cardtext'] = xmlutil.get_element_text(card_doc, 'CardText')
        result['typealias'] = xmlutil.get_element_text(card_doc, 'TypeAlias')
        result['params'] = ""
        for param_node in card_doc.getElementsByTagName('Parameter'):
            key_node = xmlutil.get_first_child_element(param_node)
            val_node = xmlutil.get_first_sibling_element(key_node)
            result['params'] += 'key=' + xmlutil.get_text(key_node) +\
                ',val=' + xmlutil.get_text(val_node) + ';'
        insert_statement = "INSERT INTO cards\n"
        insert_statement += "VALUES (:name, :setcode, :setname, :cardtext"
        insert_statement += ", :typealias, :params)"
        self.cursor.execute(insert_statement, result)

    # convert all the xml files found in the given set directory
    # into dictionary structures and then into SQL
    def read_set(self, set_filename):
        for filename in [item for item in os.listdir(set_filename)
            if item.endswith('.xml')]:
            self.read_card(set_filename, filename)

    def read_type(self, type_dir, type_filename):
        type_doc = dom.parse(os.path.join(type_dir, type_filename))
        name = xmlutil.get_element_text(type_doc, 'Name')
        for alias_node in type_doc.getElementsByTagName('Alias'):
            alias_name = xmlutil.get_text(alias_node)
            insert_statement = "INSERT INTO types (alias, name)\n"
            insert_statement += "VALUES (:alias, :name)"
            self.cursor.execute(insert_statement, {"alias":alias_name,"name":name})
        for param_node in type_doc.getElementsByTagName('Parameter'):
            param_name = xmlutil.get_text(param_node)
            insert_statement = "INSERT INTO types (param, of)\n"
            insert_statement += "VALUES (:param, :of)"
            self.cursor.execute(insert_statement, {"param":param_name,"of":name})

    def read_types(self, card_types_filename):
        for filename in [item for item in os.listdir(card_types_filename)
            if item.endswith('.xml')]:
            self.read_type(card_types_filename, filename)

    def read_subsections(self):
        for section_node in self.document.getElementsByTagName('Subsection'):
            result = {}
            name_node = xmlutil.get_first_child_element(section_node)
            result['name'] = xmlutil.get_text(name_node)

            group_node = xmlutil.get_first_sibling_element(name_node)
            result['groupname'] = int(xmlutil.get_text(group_node))

            min_size_node = xmlutil.get_first_sibling_element(group_node)
            result['minsize'] = int(xmlutil.get_text(min_size_node))

            max_size_node = xmlutil.get_first_sibling_element(min_size_node)
            result['maxsize'] = int(xmlutil.get_text(max_size_node))

            rows_node = xmlutil.get_first_sibling_element(max_size_node)
            result['rows'] = int(xmlutil.get_text(rows_node))

            cols_node = xmlutil.get_first_sibling_element(rows_node)
            result['columns'] = int(xmlutil.get_text(cols_node))

            insert_statement = "INSERT INTO sections\n"
            insert_statement += "VALUES (:name, :groupname, :minsize"
            insert_statement += ", :maxsize, :rows, :columns)"
            self.cursor.execute(insert_statement, result)

    def create_tables(self):
        create_command = "CREATE TABLE cards\n(name text, setcode text"
        create_command += ", setname text, cardtext text, typealias text"
        create_command += ", params text)"
        self.cursor.execute(create_command)

        # types table consists of the following:
        # alias | name | param | of
        # alias refers to a type alias name
        # name refers to the type the corresponding alias refers to
        # param refers to a parameter name
        # of refers to the type name the parameter belongs to
        create_command = "CREATE TABLE types\n(alias text, name text"
        create_command += ", param text, of text)"
        self.cursor.execute(create_command)

        create_command = "CREATE TABLE sections\n(name text, groupname integer"
        create_command += ", minsize integer, maxsize integer, rows integer"
        create_command += ", columns integer)"
        self.cursor.execute(create_command)

    def read_game(self, filename):
        self.document = dom.parse(filename)

        card_types_filename = xmlutil.get_element_text(self.document, 'TypeDirectory')

        sets_filename = xmlutil.get_element_text(self.document, 'SetFile')
 
        self.create_tables()
       
        self.read_types(card_types_filename)

        self.read_subsections()

        # read into a list so we don't have to have multiple files open at once
        sets = open(sets_filename).readlines()
        for set_name in sets:
            self.read_set(set_name.strip())
        self.conn.commit()
        self.conn.close()

    def __init__(self):
        self.conn = sqlite3.connect('example.db')
        self.cursor = self.conn.cursor()
