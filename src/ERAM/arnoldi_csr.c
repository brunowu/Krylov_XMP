#define P 3
#define ROWS_NUM 4
#define NNZ 9

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmp.h>
#include "../../includes/arnoldi_gmres.h"
//#include "../../includes/constant_data.h"
#include "../../includes/matrix.h"
#include "../../includes/vector.h"

#pragma xmp nodes p(P)
#pragma xmp template t(0:ROWS_NUM-1)
#pragma xmp template t1(0:NNZ-1)
//#pragma xmp template t2(0:ROWS_NUM)
#pragma xmp distribute t(block) onto p
#pragma xmp distribute t1(block) onto p
//#pragma xmp distribute t2(block) onto p

//matrix and vector for parallel computing
double *mat_val;
int *cind;
int *offset;
double * V;
double *product;


//#pragma xmp align mat_val[i] with t1(i)
//#pragma xmp align cind[i] with t1(i)
//#pragma xmp align offset[i] with t2(i)
#pragma xmp align product[i] with t(i)
#pragma xmp align V[i] with t(i)

int main(void){

/*initialize Vector*/

	V = (double *)xmp_malloc(xmp_desc_of(V), ROWS_NUM);
        product = (double *)xmp_malloc(xmp_desc_of(product), ROWS_NUM);       

//        mat_val = (double *)xmp_malloc(xmp_desc_of(mat_val), NNZ);
//        cind = (int *)xmp_malloc(xmp_desc_of(cind), NNZ);
//        offset = (int *)xmp_malloc(xmp_desc_of(offset), ROWS_NUM+1);
	offset = malloc(sizeof(int)*(ROWS_NUM+1));

	#pragma xmp loop on t(i)
{
        for(int i=0; i<ROWS_NUM; i++){
                V[i] = 1;
		product[i] = 0; 
       }
}


/*initialize matrix*/

        double val[NNZ] = {1,7,2,8,5,3,9,6,4};
        int ind[NNZ] = {0,1,1,2,0,2,3,1,3};
        int ofst[ROWS_NUM+1] = {0,2,4,7,9};

/*
	#pragma xmp loop on t1(i)
{
	for(int i = 0; i < NNZ; i++){
		mat_val[i] = val[i];
		cind[i] = ind[i];
//		printf("mat[%d] == %f \n", i, mat_val[i]);
	}
}
*/
#pragma xmp barrier

//	#pragma xmp loop on t2(i)

{
	for(int i = 0; i < ROWS_NUM+1; i++){
		offset[i] = ofst[i];
//		#pragma xmp task on p(1)
//		printf("offset[%d] = %d \n", i, offset[i]);
	}
}

	int num = xmpc_node_num();
	int size = xmp_num_nodes();

//	printf("Procs = %d, total num = %d \n", num, size);

	int dist = ROWS_NUM/size;

//	printf("Dist = %d \n", dist);

	int indx;
	
	if(num == P-1){
		indx = ROWS_NUM-dist*(P-1);
	}
	else{
		indx = dist;
	}

	int buf = offset[indx+num] - offset[num];
	printf("Indx %d on Procs %d buff allocated is: %d \n", num, indx, buf);

	mat_val = malloc(sizeof(double)*buf);
	cind = malloc(sizeof(int)*buf);

//	int m = sizeof(mat_val)/sizeof(mat_val[0]);

//	printf("m = %d\n", m);	

	for(int i = 0; i < buf; i++){
		mat_val[i] = val[offset[num]+i];
		cind[i] = ind[offset[num]+i];		
	}

	for(int i = 0; i < buf; i++){
		printf("On proc %d: mat_val[%d] =: %f; Col index is: %d \n",num, i, mat_val[i],cind[i]);
	}

#pragma xmp barrier

/*SpMV*/
/*
	#pragma xmp loop on t(i)
{
	for(int i=0; i<ROWS_NUM;i++){

		for(int j=offset[i];j<offset[i+1];j++){
			printf("mat[%d] = %f \n",j, mat_val[j]);
			product[i] = product[i]+V[cind[j]]*mat_val[j]; 			
		}
	}
}
*/

#pragma xmp barrier

/*
	#pragma xmp loop on t(i)
{
	for(int i=0; i<ROWS_NUM; i++){
		printf("product[%d] = %f\n",i, product[i]);
	}
}
*/

 	 return 0;
}
