CC=g++

BINARY_NAME=out
CFLAGS=-o bin/$(BINARY_NAME) -I lib/ -Wfatal-errors
LDFLAGS=lib/glad/src/glad.o lib/glfw/src/libglfw3.a lib/glm/build/glm/libglm.a

SRC=src/*.cpp src/**/*.cpp

.PHONY=all compile debug libs clean run

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS); #./bin/$(BINARY_NAME)

debug:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -g; gdb ./bin/$(BINARY_NAME)

libs:
	pushd lib/glad/; $(CC) -o src/glad.o -I include/ -c src/glad.c; popd;
	pushd lib/glfw/; cmake .; make; popd;
	pushd lib/glm; cmake -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -B build .; cmake --build build -- all; popd;

clean:
	rm -rf bin/*; rm lib/glfw/CMakeCache.txt;

run:
	@./bin/$(BINARY_NAME)
