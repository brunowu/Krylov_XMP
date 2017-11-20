all: ell_gen mat_gen rndmat_gen complex rnd_get shadow cplx_mat_gen

OFILES = ../libs/complex_scalar.o
ell_gen:
	xmpcc ellpack_generator.c -o ell_gen.exe

mat_gen:
	xmpcc matrix_generator.c -o mat_gen.exe

rndmat_gen:
	xmpcc random_matrix_generator.c -o rndmat_gen.exe

complex:
	xmpcc test_complex.c ${OFILES} -o complex.exe

rnd_get:
	xmpcc test_random_get.c -o rnd_get.exe

shadow:
	xmpcc test_shadow_xmp.c -o shadow,exe

cplx_mat_gen:
	xmpcc complex_matrix_generator.c -o cplx_mat_gen.exe

clean:
	rm -rf *.o *.exe
