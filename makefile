all: client server

client: wcclient.o
	gcc -o wcc wcclient.o

wcclient.o: wcclient.c
	gcc -c wcclient.c

server: wcserver.o
	gcc -o wcs wcserver.o

wcserver.o: wcserver.c
	gcc -c wcserver.c

clean:
	rm *.o
	rm wcc
	rm wcs
