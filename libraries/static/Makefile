all: calc

calc: libfcalc.a calc.c
	gcc calc.c -o calc -L. -lfcalc

libfcalc.a: add.o sub.o mul.o div.o
	ar rc libfcalc.a add.o sub.o mul.o div.o

add.o: add.c
	gcc add.c -c

sub.o: sub.c
	gcc sub.c -c

mul.o: mul.c
	gcc mul.c -c

div.o: div.c
	gcc div.c -c

clean:
	rm -rf *.o libfcalc.a calc

