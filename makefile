SHELL=/bin/bash

CC = xmpcc
CFLAGS = 
SRC = src
LIB = libs
TESTDIR = test
.PHONY = all test distclean exec rarnoldi carnoldi rgmres cgmres
MAKE = make
REAL_LIB = ${LIB}/libreal.a
CPLX_LIB = ${LIB}/libcomplex.a
OFILES = ${wildcard ./libs/*.o} ${wildcard ./src/*/*.o} ${wildcard ./test/*.o}
EXEC = rarnoldi carnoldi rgmres cgmres

BIN = bin

all: blib exec

test: blib tests


blib:
	@echo "=======Buildng Library======="
	${MAKE} -C ${LIB}
	@echo "=======Building Completed====" 

tests:
	@echo "=======Building test apps===="
	${MAKE} -C ${TESTDIR}
	@echo "=======Test Builded=========="

exec:
	@echo "======Compile apps==========="
	${MAKE} -C ${SRC}
	@echo "======appd completed=========="

distclean:
	@echo "======cleaning apps and libs=="
	rm -rf ${OFILES} ${BIN}/* ${REAL_LIB} ${CPLX_LIB}
	@echo "======Cleaned================="

rarnoldi:
	@echo "=======Building real arnoldi="
	cd ${SRC}/ERAM; \
	make rarnoldi;
	@echo "=======Real Arnoldi built===="

carnoldi:
	@echo "=======Building Complex arnoldi="
	cd ${SRC}/ERAM; \
	make carnoldi;
	@echo "=======Complex Arnoldi built===="

rgmres:
	@echo "=======Building real GMRES="
	cd ${SRC}/GMRES; \
	make rgmres;
	@echo "=======Complex built===="

#cgmres:
#	@echo "=======Building compex GMRES="
#	${CC} ${SRC}/GMRES/gmres_malloc_run_complex.c -o ${BIN}/cgmres.exe ${CPLX_LIB}
#	@echo "=======Compex GMRES built===="
