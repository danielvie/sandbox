#define S_FUNCTION_NAME aer_cruz_sf /* Defines and Includes */
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"

#include "tm_aer.h"
#include "math_const.h"
#include "tm_atmos.h"
#include "math_util.h"

#define NINPUTS 8
/**
* V, W, CM, alt
* d1, d2, d3, d4 
**/
#define NOUTPUTS 6
/**
* alfa, beta, mach, rho, Faer, Maer
**/
#define NPARAMS 0
/*=====================================================================*/
static void mdlInitializeSizes(SimStruct *S)
{
	int_T i;

	ssSetNumSFcnParams(S, NPARAMS);
	
	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) 
	{
		return; /* Parameter mismatch reported by the Simulink engine*/
	}
	
	ssSetNumContStates(S, 0);
	ssSetNumDiscStates(S, 0);

	/* reserve element in the pointers vector to store objects (structures) */
	ssSetNumPWork(S, 2); 
	
	if (!ssSetNumInputPorts(S, NINPUTS)) return;
	
	for (i=0; i<3; i++) 
	{
		ssSetInputPortWidth(S, i, 3);
		ssSetInputPortDirectFeedThrough(S, i, 1);
	}
	for (i=3; i<NINPUTS; i++) 
	{
		ssSetInputPortWidth(S, i, 1);
		ssSetInputPortDirectFeedThrough(S, i, 1);
	}
	
	if (!ssSetNumOutputPorts(S,NOUTPUTS)) return;
	
	for (i=0; i<4; i++) 
	{
		ssSetOutputPortWidth(S, i, 1);
	}
	
	ssSetOutputPortWidth(S, 4, 3);
	ssSetOutputPortWidth(S, 5, 3);

	ssSetNumSampleTimes(S, 1);
	
	/* Take care when specifying exception free code - see sfuntmpl.doc */
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}
/*=====================================================================*/
static void mdlInitializeSampleTimes(SimStruct *S)
{
	ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
	ssSetOffsetTime(S, 0, 0.0);
}
/*=====================================================================*/
#define MDL_START /* Change to #undef to remove function */
#if defined(MDL_START)
/* Function: mdlStart ==================================================
* Abstract:
* This function is called once at start of model execution. If you
* have states that should be initialized once, this is the place to do it.
*/
static void mdlStart(SimStruct *S)
{
	/* store structures in the pointers vector */
	ssGetPWork(S)[0] = (void *) new aer_param; 
	ssGetPWork(S)[1] = (void *) new aer_data;

	aer_param* aer_p = (aer_param *) ssGetPWork(S)[0];
	aer_data* aer = (aer_data *) ssGetPWork(S)[1];
    
	inicializacaoSIM inicSIM;
    inicSIM.aer_dref = 0.45;
    inicSIM.aer_cmp  = -49.564;          /** = Clp [1/rad] **/
    inicSIM.aer_cmq  = -340.837;         /** [1/rad] **/
    inicSIM.aer_cmr  = -324.257;         /** = Cnr [1/rad] **/
      
    aer_init(aer_p, aer, &inicSIM);
} 
#endif /* MDL_START */
/*=====================================================================*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
	int_T i = 0;
	int_T width = ssGetOutputPortWidth(S,0);

	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
	InputRealPtrsType u1Ptrs = ssGetInputPortRealSignalPtrs(S,1);
	InputRealPtrsType u2Ptrs = ssGetInputPortRealSignalPtrs(S,2);
	InputRealPtrsType u3Ptrs = ssGetInputPortRealSignalPtrs(S,3);
	InputRealPtrsType u4Ptrs = ssGetInputPortRealSignalPtrs(S,4);
	InputRealPtrsType u5Ptrs = ssGetInputPortRealSignalPtrs(S,5);
	InputRealPtrsType u6Ptrs = ssGetInputPortRealSignalPtrs(S,6);
	InputRealPtrsType u7Ptrs = ssGetInputPortRealSignalPtrs(S,7);

	real_T *yPtrs = ssGetOutputPortRealSignal(S,0);
	real_T *yPtrs1 = ssGetOutputPortRealSignal(S,1);
	real_T *yPtrs2 = ssGetOutputPortRealSignal(S,2);
	real_T *yPtrs3 = ssGetOutputPortRealSignal(S,3);
	real_T *yPtrs4 = ssGetOutputPortRealSignal(S,4);
	real_T *yPtrs5 = ssGetOutputPortRealSignal(S,5);
	
	aer_param* aer_p = (aer_param *) ssGetPWork(S)[0];
	aer_data* aer = (aer_data *) ssGetPWork(S)[1];

	AV_Vector V, W, R_cm;
	float64_t alt, d1, d2, d3, d4;

    float64_t alfa_rad, beta_rad, mach;
	AV_Vector Faer, Maer;

    atmos_data atmos;

	V.x = (*uPtrs[0]);
	V.y = (*uPtrs[1]);
	V.z = (*uPtrs[2]);
	W.x = (*u1Ptrs[0]);
	W.y = (*u1Ptrs[1]);
	W.z = (*u1Ptrs[2]);
	R_cm.x = (*u2Ptrs[0]);
	R_cm.y = (*u2Ptrs[1]);
	R_cm.z = (*u2Ptrs[2]);
	alt = (*u3Ptrs[0]);
	d1 = (*u4Ptrs[0]);
	d2 = (*u5Ptrs[0]);
	d3 = (*u6Ptrs[0]);
	d4 = (*u7Ptrs[0]);
		
	aer_update(aer_p, aer, alt, V, W, R_cm,
				d1, d2, d3, d4, 1, 1);  

    atmos_update(&atmos, alt);
	
	yPtrs[0] = aer->alfa;
	yPtrs1[0] = aer->beta;
	yPtrs2[0] = aer->mach;
	yPtrs3[0] = atmos.rho;
	yPtrs4[0] = aer->Faer.x;
	yPtrs4[1] = aer->Faer.y;
	yPtrs4[2] = aer->Faer.z;
	yPtrs5[0] = aer->Maer.x;
	yPtrs5[1] = aer->Maer.y;
	yPtrs5[2] = aer->Maer.z;
	
}
/* Function: mdlTerminate =====================================================
* Abstract:
* In this function, you should perform any actions that are necessary
* at the termination of a simulation. For example, if memory was
* allocated in mdlStart, this is the place to free it.
*/
static void mdlTerminate(SimStruct *S)
{
	aer_param* aer_p = (aer_param *) ssGetPWork(S)[0];
	aer_data* aer = (aer_data *) ssGetPWork(S)[1];
	
	delete aer;
	delete aer_p;
}
#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
	#include "simulink.c" /* MEX-file interface mechanism */
#else
	#include "cg_sfun.h" /* Code generation registration function */
#endif