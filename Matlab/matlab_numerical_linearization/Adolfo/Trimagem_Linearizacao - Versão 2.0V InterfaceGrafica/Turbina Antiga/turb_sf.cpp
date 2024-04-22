#define S_FUNCTION_NAME turb_sf /* Defines and Includes */
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"

#include "tm_prop_turb.h"
#include "math_const.h"

#define NINPUTS 4
// alt, vel, manete, Rcm 

#define NOUTPUTS 3
// thurst, Mturb, Hturb

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
	
	for (i=0; i<NINPUTS-1; i++) 
	{
		ssSetInputPortWidth(S, i, 1);
		ssSetInputPortDirectFeedThrough(S, i, 1);
	}
	ssSetInputPortWidth(S, 3, 3);
	ssSetInputPortDirectFeedThrough(S, i, 1);
	
	if (!ssSetNumOutputPorts(S,NOUTPUTS)) return;
	
	ssSetOutputPortWidth(S, 0, 1);
	ssSetOutputPortWidth(S, 1, 3);
	ssSetOutputPortWidth(S, 2, 3);

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
	ssGetPWork(S)[0] = (void *) new prop_turb_param; 
	ssGetPWork(S)[1] = (void *) new prop_turb_data;

	prop_turb_param* prop_turb_p = (prop_turb_param *) ssGetPWork(S)[0];
	prop_turb_data* prop_turb = (prop_turb_data *) ssGetPWork(S)[1];
      
	prop_turb_init(prop_turb_p, prop_turb);
    
} 
#endif /* MDL_START */
/*=====================================================================*/
static void mdlOutputs(SimStruct *S, int_T tid)
{

	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
	InputRealPtrsType u1Ptrs = ssGetInputPortRealSignalPtrs(S,1);
	InputRealPtrsType u2Ptrs = ssGetInputPortRealSignalPtrs(S,2);
	InputRealPtrsType u3Ptrs = ssGetInputPortRealSignalPtrs(S,3);

	real_T *yPtrs = ssGetOutputPortRealSignal(S,0);
	real_T *yPtrs1 = ssGetOutputPortRealSignal(S,1);
	real_T *yPtrs2 = ssGetOutputPortRealSignal(S,2);
	
    float64_t alt;
    float64_t vel;
	float64_t manete;
    AV_Vector R_cm;
		
    AV_Vector R_turb, T_turb;
    AV_Vector R;
    AV_Vector N_turb = AV_VectorZero();

    R_turb.x = -4.261;
    R_turb.y = 0.;
    R_turb.z = 0.;

    float64_t theta_turb = 0.*TM_D2R;
    float64_t psi_turb = 0.*TM_D2R;
    
	prop_turb_param* prop_turb_p = (prop_turb_param *) ssGetPWork(S)[0];
	prop_turb_data* prop_turb = (prop_turb_data *) ssGetPWork(S)[1];

	alt = (*uPtrs[0]);
	vel = (*u1Ptrs[0]);
	manete = (*u2Ptrs[0]);
	
	R_cm.x = (*u3Ptrs[0]);
	R_cm.y = (*u3Ptrs[1]);
	R_cm.z = (*u3Ptrs[2]);

	turbojato(prop_turb_p, prop_turb, alt, vel, manete);
	prop_turb->thurst = prop_turb->E;
    
	N_turb.x = (TM_PI/30.)* prop_turb->N;
    AV_MatrixMultVector(&(prop_turb_p->J),&N_turb,&(prop_turb->H));
	
    T_turb.x = cos(theta_turb)*cos(psi_turb)*prop_turb->thurst;
    T_turb.y = cos(theta_turb)*sin(psi_turb)*prop_turb->thurst;
    T_turb.z = sin(theta_turb)*prop_turb->thurst;

    R.x = R_turb.x - R_cm.x;
    R.y = R_turb.y - R_cm.y;
    R.z = R_turb.z - R_cm.z;

    AV_VectorCross(&R,&T_turb, &(prop_turb->Mom));
	
	yPtrs[0] = prop_turb->thurst;
	yPtrs1[0] = prop_turb->Mom.x;
	yPtrs1[1] = prop_turb->Mom.y;
	yPtrs1[2] = prop_turb->Mom.z;
	yPtrs2[0] = prop_turb->H.x;
	yPtrs2[1] = prop_turb->H.y;
	yPtrs2[2] = prop_turb->H.z;
	
}
/* Function: mdlTerminate =====================================================
* Abstract:
* In this function, you should perform any actions that are necessary
* at the termination of a simulation. For example, if memory was
* allocated in mdlStart, this is the place to free it.
*/
static void mdlTerminate(SimStruct *S)
{
	prop_turb_param* prop_turb_p = (prop_turb_param *) ssGetPWork(S)[0];
	prop_turb_data* prop_turb = (prop_turb_data *) ssGetPWork(S)[1];
	
	delete prop_turb;
	delete prop_turb_p;
}
#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
	#include "simulink.c" /* MEX-file interface mechanism */
#else
	#include "cg_sfun.h" /* Code generation registration function */
#endif