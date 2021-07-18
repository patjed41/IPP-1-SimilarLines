CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -O2

.PHONY: all clean

all: similar_lines

similar_lines: conversion.o cmpfloats.o input.o \
main.o mset.o mmset.o pair.o safefunctions.o
	$(CC) $(CFLAGS) -g -o similar_lines conversion.o cmpfloats.o \
	input.o main.o mset.o mmset.o pair.o safefunctions.o
cmpfloats.o: cmpfloats.c cmpfloats.h
	$(CC) $(CFLAGS) -g -c cmpfloats.c
conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) -g -c conversion.c
input.o: input.c input.h
	$(CC) $(CFLAGS) -g -c input.c
main.o: main.c conversion.h input.h mmset.h mset.h
	$(CC) $(CFLAGS) -g -c main.c
mmset.o: mmset.c mmset.h mset.h safefunctions.h cmpfloats.h pair.h
	$(CC) $(CFLAGS) -g -c mmset.c
mset.o: mset.c mset.h safefunctions.h cmpfloats.h
	$(CC) $(CFLAGS) -g -c mset.c
pair.o: pair.c pair.h safefunctions.h
	$(CC) $(CFLAGS) -g -c pair.c
safefunctions.o: safefunctions.c safefunctions.h
	$(CC) $(CFLAGS) -g -c safefunctions.c

clean:
	@rm -f *.o similar_lines