#include "../../includes/complex/krylov_complex.h"
#include "../../includes/constant_data.h"

void linear_least_squares(matrix * H, matrix * omega, matrix * matR, vector * y, complex * beta){
	complex * c, * s, * ro, * sigma;
	vector v1, v2, vg;
	matrix newR, in_newR, newomega;
	//calcul for given rotation: c, s
	c = (complex *)malloc(sizeof(complex));
	s = (complex *)malloc(sizeof(complex));
	ro = (complex *)malloc(sizeof(complex));
	sigma = (complex *)malloc(sizeof(complex));

	matrix_get_vector(omega, &v1, matrix_get_ligne(omega) - 1);
	matrix_get_vector(H, &v2, matrix_get_ligne(H) - 1);
	vector_delete(&v2, vector_total(&v2) - 1);
	vector_inner_produit(&v1, &v2, ro);
	complex_copy(sigma, (complex *)matrix_get(H, matrix_get_ligne(H) - 1, matrix_get_colone(H) - 1));
	givens(c, s, ro, sigma);
	vector_free(&v2);
	//printf("c: %f, s: %f, ro: %f, sigma: %f\n", * c, * s, * ro, * sigma);
	//calcul for new omega
	complex * flag = (complex *)malloc(sizeof(complex));
	complex_init(flag, -1, 0); complex_multiple(flag, s);
	vector_multiple(&v1, c);
	stock_vector_in_matrix(omega, &v1, matrix_get_ligne(omega) - 1);
	vector_divid(&v1, c); vector_multiple(&v1, flag);
	stock_vector_in_matrix(omega, &v1, matrix_get_ligne(omega));
	matrix_add_duplicate(omega, matrix_get_ligne(omega) - 2, (void *)s);
	matrix_add_duplicate(omega, matrix_get_ligne(omega) - 1, (void *)c);
	matrix_complete_ligne(omega);
	vector_free(&v1);
	free(c); free(s); free(ro); free(sigma), free(flag);
	//calcul for new matR
	matrix_free(matR); 
	matrix_multiple_matrix(omega, H, matR);
	//matrix_show(omega); matrix_show(H); matrix_show(matR);
	//calcul for yn
	matrix_delete_ligne(matR, &newR, matR->ligne - 1);
	matrix_transpose(omega, &newomega);
	matrix_get_vector(&newomega, &vg, 0);
	vector_multiple(&vg, beta);
	vector_delete(&vg, vector_total(&vg) - 1);
	upper_triangle_matrix_inverse(&newR, &in_newR);
	matrix_multiple_vector(&in_newR, &vg, y);
	matrix_free(&newR); matrix_free(&in_newR); matrix_free(&newomega);
	vector_free(&vg);
}

void hessenberg_qr(matrix * matH, matrix * matU, int num_iteration){
	complex * c, * s, * m, * n, * l1, * l2;
	c = (complex *)malloc(sizeof(complex));
	s = (complex *)malloc(sizeof(complex));
	m = (complex *)malloc(sizeof(complex));
	n = (complex *)malloc(sizeof(complex));
	l1 = (complex *)malloc(sizeof(complex));
	l2 = (complex *)malloc(sizeof(complex));
	matrix_transpose(matH, matU);

	for(int k=1; k<=num_iteration; k++){
		for(int i=0; i<matrix_get_ligne(matU) - 1; i++){
			givens(c, s, (complex *)matrix_get(matU, i, i), (complex *)matrix_get(matU, i + 1, i));
			for(int j=i; j<matrix_get_ligne(matU); j++){
				complex_copy(l1, s); complex_copy(m, c);
				complex_copy(l2, s); complex_copy(n, c);
				//* m = ((* c) * (*(double *)matrix_get(matU, i, j))) + ((* s) * (*(double *)matrix_get(matU, i + 1, j)));
				complex_multiple(m, (complex *)matrix_get(matU, i, j));
				complex_multiple(l1, (complex *)matrix_get(matU, i + 1, j));
				complex_add(m, l1);
				//* n = ((* c) * (*(double *)matrix_get(matU, i + 1, j))) - ((* s) * (*(double *)matrix_get(matU, i, j)));
				complex_multiple(n, (complex *)matrix_get(matU, i + 1, j));
				complex_multiple(l2, (complex *)matrix_get(matU, i, j));
				complex_reduce(n, l2);
				
				matrix_set(matU, i, j, (void *)m);
				matrix_set(matU, i + 1, j, (void *)n);
			}
		}
		for(int i=0; i<matrix_get_ligne(matU) - 1; i++){
			givens(c, s, (complex *)matrix_get(matU, i, i), (complex *)matrix_get(matU, i + 1, i));
			for(int j=0; j<=i + 1; j++){
				complex_copy(l1, s); complex_copy(m, c);
				complex_copy(l2, s); complex_copy(n, c);
				//* m = (* c) * (*(double *)matrix_get(matU, j, i)) + (* s) * (*(double *)matrix_get(matU, j, i + 1));
				complex_multiple(m, (complex *)matrix_get(matU, j, i));
				complex_multiple(l1, (complex *)matrix_get(matU, j, i + 1));
				complex_add(m, l1);
				//* n = (* c) * (*(double *)matrix_get(matU, j, i + 1)) - (* s) * (*(double *)matrix_get(matU, j, i));
				complex_multiple(n, (complex *)matrix_get(matU, j, i + 1));
				complex_multiple(l2, (complex *)matrix_get(matU, j, i));
				complex_reduce(n, l2);
				
				matrix_set(matU, j, i, (void *)m);
				matrix_set(matU, j, i + 1, (void *)n);
			}
		}
	}
	free(c); free(s); free(m); free(n); free(l1); free(l2);
}

static void givens(complex * c, complex * s, complex * a, complex * b){
	complex * n1 = (complex *)malloc(sizeof(complex));
	complex * n2 = (complex *)malloc(sizeof(complex));

	//* c = (* a) / sqrt((* a) * (* a) + (* b) * (* b));
	complex_copy(n1, a); complex_multiple(n1, a);
	complex_copy(n2, b); complex_multiple(n2, b);
	complex_add(n1, n2); complex_copy(n2, a);
	complex_sqrt(n1); complex_divid(n2, n1);
	complex_copy(c, n2);

	//* s = (* b) / sqrt((* a) * (* a) + (* b) * (* b));
	complex_copy(n2, b); complex_divid(n2, n1);
	complex_copy(s, n2);
}