CC = xmpcc
CFLAGS = 
LIB = ../../libs
.PHONY = all rarnoldi carnoldi
MAKE = make
REAL_LIB = ${LIB}/libreal.a
CPLX_LIB = ${LIB}/libcomplex.a
SOURCE = $(wildcard *.c)
DIR = $(notdir $(SOURCE))
#DIR = $(SOURCE)
OBJ = $(patsubst %.c,%.o,$(DIR))
BIN = ../../bin

all: rarnoldi carnoldi

rarnoldi:
	@echo "======Compile real arnoldi=="
	${CC} ${CFLAGS} arnoldi_malloc_run.c -o ${BIN}/rarnoldi ${REAL_LIB}
	@echo "======Compile completed====="

carnoldi:
	@echo "======Compile complex arnoldi=="
	${CC} ${CFLAGS} arnoldi_malloc_run_complex.c -o ${BIN}/carnoldi ${CPLX_LIB}
	@echo "======Compile completed====="

clean:
	@echo "======Cleaning=============="
	rm -rf *.o
#rarnoldi:
#	@echo "=======Building real arnoldi="
#	${CC} ${SRC}/ERAM/arnoldi_malloc_run.c -o rarnoldi.exe ${REAL_LIB}
#	@echo "=======Real Arnoldi built===="
