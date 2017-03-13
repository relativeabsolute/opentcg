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

# concatenates all text children of the given node
def get_text(node):
    rc = []
    for child in node.childNodes:
        if child.nodeType == child.TEXT_NODE:
            rc.append(child.data.strip())
    return ''.join(rc)

# returns the text of the first node in the document by the given name
def get_element_text(doc, name):
    return get_text(doc.getElementsByTagName(name)[0])

# get the first element among the children of the given node
# returns the first child element or None if there are None
def get_first_child_element(node):
    result = None
    for child in node.childNodes:
        if child.nodeType == child.ELEMENT_NODE:
            result = child
            break
    return result

# get the first element among the siblings of the given node
# returns the first sibling element or None if there are none
def get_first_sibling_element(node):
    sibling = node.nextSibling
    while sibling != None:
        if sibling.nodeType == sibling.ELEMENT_NODE:
            return sibling
        sibling = sibling.nextSibling
    return None
