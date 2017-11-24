#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmp.h>
#include "../../includes/arnoldi_gmres.h"
//#include "../../includes/constant_data.h"
#include "../../includes/matrix.h"
#include "../../includes/vector.h"

#define NPES = 1
#define ROWS_NUM = 4
#define NNZ = 9
#pragma xmp nodes p(NPES)
#pragma xmp template t(0:ROWS_NUM-1)
#pragma xmp distribute t(block) onto p

//matrix and vector for parallel computing
double (*mat_val);
int (*cind);
int (*offset);
double * V;
double *product;

//double * vT;
//double * idx;

#pragma xmp align mat_val[*] with t(i)
#pragma xmp align cind[*] with t(i)
#pragma xmp align offset[*] with t(i)
#pragma xmp align product[*] with t(i)

int main(){

/*initialize Vector*/
	V = (double *)xmp_malloc(xmp_desc_of(V), ROWS_NUM);
        product = (double *)xmp_malloc(xmp_desc_of(product), ROWS_NUM);       
	#pragma xmp loop on t(i)
{
        for(int i=0; i<ROWS_NUM; i++){
                V[i] = 1;
		product[i] = 0; 
       }
}

/*initialize matrix*/
        mat_val = (double *)xmp_malloc(xmp_desc_of(mat_val), NNZ);
	cind = (int *)xmp_malloc(xmp_des_of(cind), NNZ);
        offset = (int *)xmp_malloc(xmp_des_of(offset), ROWS_NUM+1);

        double val[NNZ] = [1,7,2,8,5,3,9,6,4];
        int ind[NNZ] = [0,1,1,2,0,2,3,1,3];
        int ofst[ROWS_NUM+1] = [0,2,4,7,9];

	#pragma xmp loop on t(i)
{
	for(int i = 0; i < NNZ; i++){
		mat_val[i] = val[i];
		cind[i] = ind[i];
	}
}

	#pragma xmp loop on t(i)
{
	for(int i = 0; i < ROWS_NUM+1; i++){
		offset[i] = ofst[j];
	}
}
/*SpMV*/
	#pragma xmp loop on t(i)
{
	for(int i=0; i<ROWS_NUM,i++){
		for(int j=offset[i], j<offset[i+i];j++){
			product[i]+ = V[j]*mat_val[cind[j]]; 			
		}
	}
}
	#pragma xmp task on p(1)
{
	for(int i=0; i<NNZ; i++){
		printf("product[%d] = %f\n",i, product[i]);
	}
}

 	 return 0;
}
