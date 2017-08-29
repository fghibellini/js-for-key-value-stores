#!/usr/bin/env bash

g++ -I"${v8}/include"\
    -O0 \
    src/main.cpp\
    -o bin/run\
    -Wl,--start-group \
	${v8}/lib/libv8_{base,libbase,snapshot,libplatform,libsampler}.a\
    ${icu}/lib/libicu{uc,i18n}.so\
	-Wl,--end-group\
    -pthread\
    -std=c++0x
