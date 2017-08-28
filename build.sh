#!/usr/bin/env bash

g++ -I"${v8}/include"\
    src/main.cpp\
    -o bin/run\
    -Wl,--start-group \
	${v8}/lib/libv8_{base,libbase,snapshot,libplatform,libsampler}.a\
    ${icu}/lib/libicu{uc,i18n}.so\
	-Wl,--end-group\
    -lrt\
    -ldl\
    -pthread\
    -std=c++0x
