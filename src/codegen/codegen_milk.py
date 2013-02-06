#!/usr/bin/env python2
#-*- coding: utf-8 -*-
# 
# codegen.py
#
# Copyright (C) 2013 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
# All Rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

import re
import sys
import os.path

from xml.etree import ElementTree
from optparse import OptionParser, make_option

class TemplateEngine(object):
    def __init__(self, template_file, target_dir=None):
        with open(template_file, 'r') as f:
            self.template = f.read()
        self.target_dir = target_dir
        self.outfile_suffix = template_file.split('.')[-2]

    def interpolate(self, matchobj):
        expr = matchobj.group(1)
        ops = expr.split('|')

        target = ops[0]
        attrib = None
        
        if '#' in target:
            target, attrib = target.split('#')

        target_node = self.root.find(target)
        if target_node is None:
            return ''

        result = target_node.text if not attrib else target_node.attrib[attrib]

        for op in ops[1:]:
            result = eval('result.%s()' % op)

        result = result.strip('\n ').rstrip(' ')

        if matchobj.group(0).endswith('\n'):
            result += '\n'
        
        return result

    def render(self, dataxml):
        tree = ElementTree.parse(dataxml)
        self.root = tree.getroot()

        filename = '%s.%s' % (self.root.find('.').attrib['name'].lower(),
                              self.outfile_suffix)
        if self.target_dir:
            filename = os.path.join(self.target_dir, filename)

        print 'GEN %s'  % filename

        result = re.sub(r'{{([^{}]+?)}}\n?', self.interpolate, self.template,
                        flags=re.S).strip() + '\n'

        # remove whitespace only line
        result = re.sub(r'\n +\n', r'\n\n', result, flags=re.S)

        with open(filename, 'w') as f:
            f.write(result)

def main():
    option_list = [
        make_option('-C', '--change-target-dir', action='store', type='string',
                    dest='target_dir', default=None,
                    help='change output directory'),
        make_option('-t', '--template', action='store', type='string',
                    dest='template', default=None,
                    help='name of template'),
    ]
    parser = OptionParser(usage='Usage: %s [OPTION...] xml1 xml2 ...' %sys.argv,
                          option_list=option_list)

    options, args = parser.parse_args()

    if not options.template:
        raise RuntimeError("no template specified.")

    e = TemplateEngine(options.template, options.target_dir)

    for xml in args:
        e.render(xml)

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print 'error:', str(e)
