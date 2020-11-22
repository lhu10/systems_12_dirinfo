all: main.o
	gcc -o work12 main.o

main.o: main.c
	gcc -c main.c

run: 
	./work12

clean: 
	rm *.o
