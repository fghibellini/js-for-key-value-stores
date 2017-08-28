
g++ -I"${v8}" -I"${v8}/include" \
    hello-world.cc\
    -o hello-world\
    -Wl,--start-group \
	${v8}/lib/libv8_{base,libbase,snapshot,libplatform,libsampler}.a\
    ${icu}/lib/libicu{uc,i18n}.so\
	-Wl,--end-group\
    -lrt\
    -ldl\
    -pthread\
    -std=c++0x
