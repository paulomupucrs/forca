data.o: lib/data.h lib/data.c
	cc -c lib/data.c -o data.o

forca.out: data.o forca.c lib/data.h lib/data.c
	cc data.o forca.c -o forca.out

clear:
	rm -f data.o forca.out log.txt
