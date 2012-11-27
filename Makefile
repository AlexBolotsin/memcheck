all: sources
	g++ main.cpp -std=c++0x -o run
lib: sources
	g++ -shared -Wl,-soname,libleak_check.so -o libleak_check.so allocation_hooks.o
sources:
	g++ -std=c++0x -fPIC -c allocation_hooks.cpp -o allocation_hooks.o
clean:
	rm *.o *.so