all: calc.out

calc.out: libadd.so libsub.so libmul.so libdiv.so calc.c
	gcc calc.c -o calc.out -L . -ladd -lsub -lmul -ldiv

libadd.so: add.o
	gcc -shared add.o -o libadd.so

libsub.so: sub.o
	gcc -shared sub.o -o libsub.so

libmul.so: mul.o
	gcc -shared mul.o -o libmul.so

libdiv.so: div.o
	gcc -shared div.o -o libdiv.so

add.o: add.c
	gcc add.c -fPIC -c

sub.o: sub.c
	gcc sub.c -fPIC -c

mul.o: mul.c
	gcc mul.c -fPIC -c

div.o: div.c
	gcc div.c -fPIC -c

clean:
	rm -rf *.o *.out *.so

exec:
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD) ./calc.out
