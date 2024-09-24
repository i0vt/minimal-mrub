CPP      = g++
CC       = gcc
MM       = ./mruby
MBU      = $(MM)/build/host
OPCJE99  = -Wall -O0 -std=c99 -pedantic -pedantic-errors
PROG     = przyk

./$(PROG): $(PROG).c Makefile
	$(CC) $(OPCJE99) -g -I $(MM)/include/ -I$(MM)/include/mruby $< \
	  -o $(PROG) $(MBU)/lib/libmruby.a -lm
	./$(PROG)

mem: ./$(PROG)
	valgrind --leak-check=full --show-reachable=yes -s --track-origins=yes ./$(PROG)

.PHONY: clean

clean:
	rm -f ./$(PROG) ./wynik.bin
