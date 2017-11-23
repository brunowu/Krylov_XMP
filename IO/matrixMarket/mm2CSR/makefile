CC = gcc
MAKE = make

.PHONY = all
IO_LIB_DIR = ../mmIO_Utils
IO_LIB = ${IO_LIB_DIR}/libmmIO.a
SRCS = mm2Csr.c utils.c 
EXEC = mm2Csr.exe
 
all: ${EXEC}

${EXEC}:${SRCS}
	@echo "====MAKE====="
	${CC} -o ${EXEC} $^ ${IO_LIB}

clean:
	@echo "====Clean==="
	rm -rf *.o *.exe
