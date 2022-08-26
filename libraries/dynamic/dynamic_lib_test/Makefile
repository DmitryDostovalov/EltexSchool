all: dynamic_lib_test.out

dynamic_lib_test.out: libdynamic_lib.so dynamic_lib.h dynamic_lib_test.c
	gcc dynamic_lib_test.c -o dynamic_lib_test.out -L . -ldynamic_lib

libdynamic_lib.so: dynamic_lib.o
	gcc -shared dynamic_lib.o -o libdynamic_lib.so

dynamic_lib.o: dynamic_lib.c
	gcc dynamic_lib.c -fPIC -c

clean:
	rm -rf *.o *.out *.so

exec:
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD) ./dynamic_lib_test.out
