#include "../includes/basic_operation_complex.h"
#include "../includes/constant_data.h"

void arnoldi(matrix * mat, vector * v, matrix * matQ, matrix * matH){
	
	vector r, r1;
	complex * h = (complex *)malloc(sizeof(complex));
	//calcul and stock of q1
	vector q1, q;
	vector_copy(v, &q1);
	vector_abs(v, h);
	vector_divid(&q1, h);
	stock_vector_in_matrix(matQ, &q1, 0);
	vector_free(&q1);
	for(int j=1; j<=restart_max; j++){
		matrix_get_vector(matQ, &q, j - 1);
		matrix_multiple_vector(mat, &q, &r);
		vector_free(&q);
		// Gram-Schmidt orthogonalization
		for(int i=1; i<=j; i++){
			matrix_get_vector(matQ, &q, i - 1);
			vector_inner_produit(&q, &r, h);
			matrix_add_duplicate(matH, j - 1, (void *)h);
			vector_multiple(&q, h);
			vector_reduce_vector(&r, &q, &r1);
			vector_free(&r);
			vector_duplicate(&r1, &r);
			vector_free(&q); vector_free(&r1);
		}
		vector_abs(&r, h);
		vector_divid(&r, h);
		if(j == restart_max){
			vector_free(&r); vector_free(v);
			free(h);
			matrix_complete_ligne(matH);
			return;
		}else{
			matrix_add_duplicate(matH, j - 1, (void *)h);
			stock_vector_in_matrix(matQ, &r, j);
			vector_free(&r);
		}
	}
}

void gmres(matrix * mat, vector * vx, vector * vb, matrix * matQ, matrix * matH, matrix * omega, matrix * matR, int index_ligne, complex * beta){
	printf("Tour %d\n", index_ligne + 1);
	vector r, r1, rp, q, y, newx;
	matrix qT;
	complex * h = (complex *)malloc(sizeof(complex));

	vector_init(&y, 1);
	matrix_multiple_vector(mat, vx, &q);
	vector_reduce_vector(vb, &q, &r);
	vector_free(&q);

	vector_abs(&r, h);
	complex_copy(beta, h);

	vector_divid(&r, h);
	stock_vector_in_matrix(matQ, &r, 0);
	vector_free(&r);

	for(int j=1; j<=restart_max; j++){
		matrix_get_vector(matQ, &q, j - 1);
		matrix_multiple_vector(mat, &q, &r);
		vector_duplicate(&r, &rp);
		vector_free(&q); 
		// Gram-Schmidt orthogonalization
		for(int i=1; i<=j; i++){
			matrix_get_vector(matQ, &q, i - 1);
			vector_inner_produit(&q, &r, h);
			matrix_add_duplicate(matH, j - 1, (void *)h);
			vector_multiple(&q, h);
			vector_reduce_vector(&rp, &q, &r1);
			vector_free(&rp);
			vector_duplicate(&r1, &rp);
			vector_free(&q); vector_free(&r1);
		}
		vector_abs(&rp, h);
		matrix_add_duplicate(matH, j - 1, (void *)h);
		vector_divid(&rp, h);
		vector_free(&r);
		matrix_complete_ligne(matH);

		//linear_least_squares
		linear_least_squares(matH, omega, matR, &y, beta);

		matrix_transpose(matQ, &qT);
		matrix_multiple_vector(&qT, &y, &q);
		//matrix_show(&qT); vector_show(&q);
		matrix_free(&qT);
		vector_add_vector(vx, &q, &newx);
		vector_free(&q); vector_free(&y);
		matrix_multiple_vector(mat, &newx, &q);
		vector_reduce_vector(vb, &q, &r1);
		vector_abs(&r1, h);
		vector_free(&q); vector_free(&r1); 
		printf("The residual is %f\n", complex_abs(h));
		if( complex_abs(h) < 1e-1){
			vector_free(&rp);
			vector_free(vx);
		    vector_duplicate(&newx, vx);
		    vector_free(&newx);
			free(h); free(beta);
			return;
		}
		if(j == restart_max){
			complex * A = malloc(sizeof(complex));
			complex_init(A, 1, 0);
			index_ligne++;
			vector_free(&rp);
			free(h); free(beta);
			beta = (complex *)malloc(sizeof(complex));
			vector_free(vx); vector_duplicate(&newx, vx); vector_free(&newx);
		    matrix_free(matQ); matrix_free(matH); matrix_free(omega); matrix_free(matR);
		    matrix_init(matQ, 1, 1); matrix_init(matH, 1, 1); matrix_init(matR, 1, 1); matrix_init(omega, 1, 1);
		    matrix_add_duplicate(omega, 0, (void *)A); free(A);
			gmres(mat, vx, vb, matQ, matH, omega, matR, index_ligne, beta);
		}
		stock_vector_in_matrix(matQ, &rp, j);
		vector_free(&rp); vector_free(&newx);
	}
}
