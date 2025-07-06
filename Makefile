both: 
	gcc -c strutils.c     -o strutils.o
	gcc -c strutils_adv.c -o strutils_adv.o
	ar rsc strutils.a strutils.o strutils_adv.o
	rm -rf *.o
	gcc -c -fPIC strutils.c -o strutils.o
	gcc -c -fPIC strutils_adv.c -o strutils_adv.o
	gcc -shared -o strutils.so strutils.o strutils_adv.o
	rm -rf *.o
	gcc -o baitap1_a baitap1.c strutils.a
	gcc -o baitap1_so baitap1.c strutils.so

static:
	gcc -c strutils.c     -o strutils.o
	gcc -c strutils_adv.c -o strutils_adv.o
	ar rsc strutils.a strutils.o strutils_adv.o
	gcc -o baitap1_a baitap1.c strutils.a
	rm -rf *.o baitap1_so

shared:
	gcc -c strutils.c      -o strutils.o
	gcc -c -fPIC strutils_adv.c  -o strutils_adv.o
	gcc -shared -o strutils.so strutils.o  strutils_adv.o
	gcc -o baitap1_so baitap1.c strutils.so
	rm -rf *.o
	rm -rf baitap1_a

xoa:
	rm baitap1_so baitap1_a *.o *.a *.so