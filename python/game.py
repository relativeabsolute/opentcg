# MIT License
#
# Copyright (c) 2017 Johan Burke
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
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
    def read_card(self, setfile, cardfilename):
        print("Card = " + cardfilename)
        card_doc = dom.parse(os.path.join(setfile, cardfilename))
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
    def read_set(self, setfilename):
        for filename in [item for item in os.listdir(setfilename)
            if item.endswith('.xml')]:
            self.read_card(setfilename, filename)

    def read_game(self, filename):
        document = dom.parse(filename)
        setsfilename = xmlutil.get_element_text(document, 'SetFile')

        create_command = "CREATE TABLE cards\n(name text, setcode text"
        create_command += ", setname text, cardtext text, typealias text"
        create_command += ", params text)"
        self.cursor.execute(create_command)

        # read into a list so we don't have to have multiple files open at once
        sets = open(setsfilename).readlines()
        for set_name in sets:
            self.read_set(set_name.strip())
        self.conn.commit()
        self.conn.close()

    def __init__(self):
        self.conn = sqlite3.connect('example.db')
        self.cursor = self.conn.cursor()
