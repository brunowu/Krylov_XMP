All:all

XCC = xmpcc
CFLAGS =
AR = ar
ARFLAGS = cr
REAL_LIB = libreal.a
CPLX_LIB = libcomplex.a
REAL_SRCS = matrix.c vector.c mVecMatrix.c basic_operation.c basicKrylov.c
CPLX_SRCS = complex_scalar.c matrix_complex.c vector_complex.c mVecMatrix_complex.c basic_operation_complex.c basicCplxKrylov.c
REAL_OBJS = matrix.o vector.o mVecMatrix.o basic_operation.o basicKrylov.o
CPLX_OBJS = complex_scalar.o matrix_complex.o vector_complex.o mVecMatrix_complex.o basic_operation_complex.o basicKrylov.o

%.o:%.c
	@${XCC} ${CFLAGS} -c $< -o ./$@

${REAL_LIB}:${REAL_OBJS}
	@echo "Building real library ${REAL_LIB}"
	${AR} ${ARFLAGS} $@ ${REAL_OBJS}

${CPLX_LIB}:${CPLX_OBJS}
	@echo "Building complex library ${CPLX_LIB}"
	${AR} ${ARFLAGS} $@ ${CPLX_OBJS}

all:${REAL_OBJS} ${CPLX_OBJS} ${REAL_LIB} ${CPLX_LIB}

clean:
	rm -rf ${REAL_OBJS} ${CPLX_OBJS} ${REAL_LIB} ${CPLX_LIB}
