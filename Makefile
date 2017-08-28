
bin/run : ./src/main.cpp
	mkdir bin 2>/dev/null || true
	./build.sh

run : bin/run
	./bin/run

clean :
	-rm -rf bin
