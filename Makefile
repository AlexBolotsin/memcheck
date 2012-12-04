all: sources lib
	g++ main.cpp -std=c++0x -o run -L. -lmemcheck
lib: sources
	g++ -shared -Wl,-soname,libmemcheck.so -o libmemcheck.so allocation_hooks.o info_storage.o \
		logger.o
sources:
	g++ -std=c++0x -fPIC -c allocation_hooks.cpp -o allocation_hooks.o
	g++ -std=c++0x -fPIC -c info_storage.cpp -o info_storage.o
	g++ -std=c++0x -fPIC -c logger.cpp -o logger.o
clean:
	rm *.o *.so run