CC = gcc
MAKE = make

.PHONY = all read write lib
IO_LIB_DIR = ./mmIO_Utils
IO_LIB = ${IO_LIB_DIR}/libmmIO.a
 
all: lib read write

lib:
	@echo "===Building libs==="
	${MAKE} -C ${IO_LIB_DIR}
	@echo "===Completed======"

read:
	@echo "====Read====="
	${CC} -o read mmRead.c ${IO_LIB}

write:
	@echo "====Write==="
	${CC} -o write mmWrite.c ${IO_LIB}	

distclean:
	@echo "====Clean==="
	rm -rf mmRead.o mmWrite.o read write
