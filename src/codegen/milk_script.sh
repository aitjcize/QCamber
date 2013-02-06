#!/bin/bash
SYMBOL_NAME=triangle
./codegen.py -t symbol.h.tmpl -C ../symbol ${SYMBOL_NAME}.xml 
./codegen.py -t symbol.cpp.tmpl -C ../symbol ${SYMBOL_NAME}.xml
