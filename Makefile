.PHONY: all clean run

all:
	cmake -B build
	cmake --build build

run: all
	./build/SpaceInvaders.exe

clean:
	rm -rf build
