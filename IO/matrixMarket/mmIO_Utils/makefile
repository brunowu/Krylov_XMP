SHELL=/bin/bash

All: all

CC = gcc 
CFLAGS = 
AR = ar
ARFLAGS = cr

SRCS = mmIO_Utils.c utils.c mm2Csr.c 
OBJS = mmIO_Utils.o utils.o mm2Csr.o

.PHONY = all

LIB = libmmIO.a

all: ${LIB}

%.o:%.c
	@${CC} ${CFLAGS} -c $< -o ./$@

${LIB}:${OBJS}
	@echo "Bulding Matrix Market IO library"
	${AR} ${ARFLAGS} $@ ${OBJS}

clean: 
	rm -rf *.o *.a
