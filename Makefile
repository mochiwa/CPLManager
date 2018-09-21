CC=gcc -W -I header
VALGRIND=valgrind --leak-check=yes ./main
EXE=main
FILE=sources/$*.c

all: main clean

memory-leak: main
	$(VALGRIND)

main: main.o
	$(CC) -o $(EXE) *.o
main.o: sources/main.c own.o menu.o
	$(CC) -o $@ -c $(FILE)
own.o : sources/own.c
	$(CC) -o $@ -c $(FILE)
menu.o: sources/menu.c  customer.o order.o
	$(CC) -o $@ -c $(FILE)
customer.o: sources/customer.c address.o date.o entity.o 
	$(CC) -o $@ -c $(FILE)
address.o: sources/address.c
	$(CC) -o $@ -c $(FILE)
date.o: sources/date.c
	$(CC) -o $@ -c $(FILE)
entity.o: sources/entity.c
	$(CC) -o $@ -c $(FILE)
order.o: sources/order.c line.o product.o 
	$(CC) -o $@ -c $(FILE)
line.o: sources/line.c 
	$(CC) -o $@ -c $(FILE)
product.o: sources/product.c
	$(CC) -o $@ -c $(FILE)


clean:
	rm -f *.o
