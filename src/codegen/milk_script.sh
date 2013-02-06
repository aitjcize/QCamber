#!/bin/bash
SYMBOL_NAME=hexagon_l
./codegen_milk.py -t symbol.h.tmpl -C ../symbol ${SYMBOL_NAME}.xml 
./codegen_milk.py -t symbol.cpp.tmpl -C ../symbol ${SYMBOL_NAME}.xml
