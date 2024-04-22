#include "mex.h"

#include "tm_aer.h"
#include "math_const.h"
#include "tm_atmos.h"
#include "math_util.h"

#define NINPUTS 8 
/**
* V, W, CM, alt,
* d1, d2, d3, d4 
**/
#define NOUTPUTS 6
/**
* alfa, beta, mach, rho, Faer, Maer
**/

/**
* [alfa_rad, beta_rad, mach, rho, Faer, Maer] = 
* 	aer_cruz_mx(V, W, CM, alt, d1_rad, d2_rad, d3_rad, d4_rad)
**/

/******************************************************************/
void mexFunction(int nlhs, mxArray *plhs[],         /* Output variables */
                int nrhs, const mxArray *prhs[])    /* Input variables */
{           
    aer_param aer_p;
	aer_data aer;
	AV_Vector Vt, Wt, R_cm;
	
	float64_t *V;
	float64_t *W;
	float64_t *CM;
	float64_t *alt;
	float64_t *d1_rad;
	float64_t *d2_rad;
	float64_t *d3_rad;
	float64_t *d4_rad;

    float64_t *alfa_rad;
	float64_t *beta_rad;
	float64_t *mach;
	float64_t *rho;
	float64_t *Faer;
	float64_t *Maer;
	
    inicializacaoSIM inicSIM;
    atmos_data atmos;

    inicSIM.aer_dref = 0.45;
    inicSIM.aer_cmp  = -49.564;          /** = Clp [1/rad] **/
    inicSIM.aer_cmq  = -340.837;         /** [1/rad] **/
    inicSIM.aer_cmr  = -324.257;         /** = Cnr [1/rad] **/

    if (nrhs != NINPUTS)
        mexErrMsgTxt("A função deve ter 8 argumentos de entrada ");
    
	if (nlhs != NOUTPUTS)
        mexErrMsgTxt("A função deve ter 6 argumentos de saída");
    
    if ( mxGetN(prhs[3]) != 1 || mxGetN(prhs[4]) != 1 || mxGetN(prhs[5]) != 1 ||
		 mxGetN(prhs[6]) != 1 || mxGetN(prhs[7]) != 1 ||
		 mxGetM(prhs[3]) != 1 || mxGetM(prhs[4]) != 1 || mxGetM(prhs[5]) != 1 ||
		 mxGetM(prhs[6]) != 1 || mxGetM(prhs[7]) != 1 )
        mexErrMsgTxt("Os argumentos de entrada 4,5,6,7,8 devem ser escalares");

	if ( mxGetM(prhs[0]) != 3 || mxGetM(prhs[1]) != 3 || mxGetM(prhs[2]) != 3 ||
		 mxGetN(prhs[0]) != 1 || mxGetN(prhs[1]) != 1 || mxGetN(prhs[2]) != 1)
		mexErrMsgTxt("Os 3 primeiros argumentos de entrada devem ser vetores coluna de 3 elementos");
   
    plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
    plhs[2] = mxCreateDoubleMatrix(1,1,mxREAL);
    plhs[3] = mxCreateDoubleMatrix(1,1,mxREAL);
    plhs[4] = mxCreateDoubleMatrix(3,1,mxREAL);
    plhs[5] = mxCreateDoubleMatrix(3,1,mxREAL);
    
    V = mxGetPr(prhs[0]);	/* 3x1 */
    W = mxGetPr(prhs[1]);	/* 3x1 */
    CM = mxGetPr(prhs[2]);	/* 3x1 */

    /* Entradas Escalares */
	alt = mxGetPr(prhs[3]);
    d1_rad = mxGetPr(prhs[4]);
    d2_rad = mxGetPr(prhs[5]);
    d3_rad = mxGetPr(prhs[6]);
    d4_rad = mxGetPr(prhs[7]);

     /* Saídas Escalares */
	alfa_rad = mxGetPr(plhs[0]);
    beta_rad = mxGetPr(plhs[1]);
    mach = mxGetPr(plhs[2]);
    rho = mxGetPr(plhs[3]);
	
	/* 3x1 */
    Faer = mxGetPr(plhs[4]);
    Maer = mxGetPr(plhs[5]);
	
	Vt.x = V[0];
	Vt.y = V[1];
	Vt.z = V[2];
	Wt.x = W[0];
	Wt.y = W[1];
	Wt.z = W[2];
	R_cm.x = CM[0];
	R_cm.y = CM[1];
	R_cm.z = CM[2];
       
    aer_init(&aer_p, &aer, &inicSIM);
	
	aer_update(&aer_p, &aer,  alt[0], Vt, Wt, R_cm,
				d1_rad[0], d2_rad[0], d3_rad[0], d4_rad[0] , 1, 1);
	
    alfa_rad[0] = aer.alfa;
    beta_rad[0] = aer.beta;
	mach[0] = aer.mach;

    atmos_update(&atmos, alt[0]);
	rho[0] = atmos.rho;
	
	Faer[0] = aer.Faer.x;
	Faer[1] = aer.Faer.y;
	Faer[2] = aer.Faer.z;

 	Maer[0] = aer.Maer.x;
	Maer[1] = aer.Maer.y;
	Maer[2] = aer.Maer.z;
   	
    return;
}
