#include "mex.h"

#include "math_const.h"
#include "tm_prop_turb.h"

#define NINPUTS 4 
/**
* alt, vel, manete, Rcm 
**/
#define NOUTPUTS 3
/**
* thurst, Mturb, Hturb
**/

/**
* [thurst, Mturb, Hturb] = turb_mx(alt, vel, manete, Rcm)
**/

void mexFunction(int nlhs, mxArray *plhs[],         /* Output variables */
                int nrhs, const mxArray *prhs[])    /* Input variables */
{
	prop_turb_param prop_turb_p;
	prop_turb_data prop_turb;

	float64_t dt, t;
	
	float64_t *alt;
	float64_t *vel;
	float64_t *manete;
	float64_t *R_cm;
	
    float64_t *thurst;
	float64_t *Mturb;
	float64_t *Hturb;

    if (nrhs != NINPUTS)
        mexErrMsgTxt("A função deve ter 4 argumentos de entrada ");
    
	if (nlhs != NOUTPUTS)
        mexErrMsgTxt("A função deve ter 3 argumentos de saída");
    
    if ( mxGetN(prhs[0]) != 1 || mxGetN(prhs[1]) != 1 || mxGetN(prhs[2]) != 1 ||
		 mxGetM(prhs[0]) != 1 || mxGetM(prhs[1]) != 1 || mxGetM(prhs[2]) != 1 )
        mexErrMsgTxt("Os 3 primeiros argumentos de entrada devem ser escalares");
    if ( mxGetN(prhs[3]) != 3 || mxGetM(prhs[3]) != 3 )
        mexErrMsgTxt("O último argumento de entrada deve ser um vetor 3x1");
  
    plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    plhs[1] = mxCreateDoubleMatrix(3,1,mxREAL);
    plhs[2] = mxCreateDoubleMatrix(3,1,mxREAL);
    

    /* Entradas */
	alt = mxGetPr(prhs[0]);
    vel = mxGetPr(prhs[1]);
    manete = mxGetPr(prhs[2]);
    R_cm = mxGetPr(prhs[3]);

     /* Saídas Escalares */
	thurst = mxGetPr(plhs[0]);
	
	/* 3x1 */
    Mturb = mxGetPr(plhs[1]);
    Hturb = mxGetPr(plhs[2]);

    AV_Vector R_turb, T_turb;
    AV_Vector R;
    AV_Vector N_turb = AV_VectorZero();

    float64_t theta_turb = 0.*TM_D2R;
    float64_t psi_turb = 0.*TM_D2R;

    R_turb.x = -4.261;
    R_turb.y = 0.;
    R_turb.z = 0.;

	/** Infelizmente, tem que chamar aqui**/
	prop_turb_init(&prop_turb_p, &prop_turb);
	
	turbojato(&prop_turb_p, &prop_turb, alt[0], vel[0], manete[0]);
	prop_turb.thurst = prop_turb.E;
    
	N_turb.x = (TM_PI/30.)* prop_turb.N;
    AV_MatrixMultVector(&(prop_turb_p.J),&N_turb,&(prop_turb.H));
	
    T_turb.x = cos(theta_turb)*cos(psi_turb)*prop_turb.thurst;
    T_turb.y = cos(theta_turb)*sin(psi_turb)*prop_turb.thurst;
    T_turb.z = sin(theta_turb)*prop_turb.thurst;

    R.x = R_turb.x - R_cm[0];
    R.y = R_turb.y - R_cm[1];
    R.z = R_turb.z - R_cm[2];

    AV_VectorCross(&R,&T_turb, &(prop_turb.Mom));

	thurst[0] = prop_turb.thurst;
	
	Mturb[0] = prop_turb.Mom.x;
	Mturb[1] = prop_turb.Mom.y;
	Mturb[2] = prop_turb.Mom.z;
	
	Hturb[0] = prop_turb.H.x;
	Hturb[1] = prop_turb.H.y;
	Hturb[2] = prop_turb.H.z;
   	
    return;
	
}