All:all

XCC = xmpcc
CFLAGS =
SOURCEC = matrix.c vector.c mVecMatrix.c complex_scalar.c matrix_complex.c vector_complex.c mVecMatrix_complex.c basic_operation_complex.c
SOURCEH =
CLEANFILE = matrix.o vector.o mVecMatrix.o complex_scalar.o matrix_complex.o vector_complex.o mVecMatrix_complex.o basic_operation_complex.o

%.o:%.c
	@${XCC} ${CFLAGS} -c $< -o ./$@

all:${CLEANFILE}

clean:
	rm -rf ${CLEANFILE}
