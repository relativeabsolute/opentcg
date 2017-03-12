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

def read_card(setfile, cardfilename):
    print("Card = " + cardfilename)
    card_doc = dom.parse(os.path.join(setfile, cardfilename))
    result = {}
    result['Name'] = xmlutil.get_element_text(card_doc, 'Name')
    result['SetCode'] = xmlutil.get_element_text(card_doc, 'SetCode')
    result['SetName'] = xmlutil.get_element_text(card_doc, 'SetName')
    result['CardText'] = xmlutil.get_element_text(card_doc, 'CardText')
    print(str(result))

def read_set(setfilename):
    for filename in [item for item in os.listdir(setfilename)
        if item.endswith('.xml')]:
        read_card(setfilename, filename)

def read_class(filename):
    document = dom.parse(filename)
    print("Name = " + xmlutil.get_element_text(document, 'Name'))
    setsfilename = xmlutil.get_element_text(document, 'SetFile')
    print("Set filename = " + setsfilename)

    # read into a list so we don't have to have multiple files open at once
    sets = open(setsfilename).readlines()
    for set_name in sets:
        read_set(set_name.strip())
