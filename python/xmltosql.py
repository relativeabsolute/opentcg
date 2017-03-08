'''
MIT License

Copyright (c) 2017 Johan Burke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
'''

import xml.dom.minidom as dom
import sys
import os
import os.path

def read_card_info(filename):
    doc = dom.parse(filename)
    result = {}
    for node in doc.documentElement.childNodes:
        if node.hasChildNodes():
            result[node.nodeName] = node.firstChild.nodeValue
    print(str(result))

def convert_to_sql(dirName):
    for filename in os.listdir(dirName):
        (_, ext) = os.path.splitext(filename)
        if ext == '.xml':
            read_card_info(os.path.join(dirName, filename))

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print("Usage: python xmltosql.py [directoryname]")
    else:
        convert_to_sql(sys.argv[1])
