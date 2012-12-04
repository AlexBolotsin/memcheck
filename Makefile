all:
	g++ main.cpp -o run
memcheck: sources liblogger libmemcheck
	g++ main.cpp -DMEMCHECK -std=c++0x -o run -L. -lmemcheck -llogger
libmemcheck: sources
	g++ -shared -Wl,-soname,libmemcheck.so -o libmemcheck.so allocation_hooks.o info_storage.o
liblogger:
	g++ -shared -Wl,-soname,liblogger.so -o liblogger.so logger.o
sources:
	g++ -std=c++0x -fPIC -c allocation_hooks.cpp -o allocation_hooks.o
	g++ -std=c++0x -fPIC -c info_storage.cpp -o info_storage.o
	g++ -std=c++0x -fPIC -c logger.cpp -o logger.o
clean:
	rm *.o *.so run