/*  File    : sfunSSV.cpp
 *  Abstract:
 *
 *      S-function para executar o Software de Supervisao de Voo (SSV)
 *      no programa de simulacao Traj_m
 *
 */

#include <iostream>
#include "ssv.h"
#include <cstdio>

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  sfunSSV
#define NUM_INPUTS 12
#define NUM_OUTPUTS 6

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include <cstdlib>

#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal))

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    // contador i
    unsigned int i;

    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;
    

    for (i = 0; i < NUM_INPUTS; ++i) {
        ssSetInputPortComplexSignal(S, i, COMPLEX_NO);
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1); /*direct input signal access*/
        ssSetInputPortDataType(S, i, SS_SINGLE);
    }
    
    // inicializando flag_ejecao
    // Input 0
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType(S, 0, SS_INT32);
    
    ssSetInputPortWidth(S, 1, 6); // ax
    ssSetInputPortWidth(S, 2, 6); // ay
    ssSetInputPortWidth(S, 3, 6); // az

    ssSetInputPortWidth(S, 4, 3); // vx
    ssSetInputPortWidth(S, 5, 3); // vy
    ssSetInputPortWidth(S, 6, 3); // vz
    ssSetInputPortWidth(S, 7, 3); // altitude

    ssSetInputPortWidth(S, 8, 1);  // altitude_alvo
    ssSetInputPortWidth(S, 9, 1);  // perc_gps
    ssSetInputPortWidth(S, 10, 1); // tempo

    ssSetInputPortWidth(S, 11, 3); // FoM
    ssSetInputPortDataType(S, 11, SS_INT32);
    
    // OUTPUTS

    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    
    // canard
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_INT32);

    // tejec
    ssSetOutputPortWidth(S, 1, 1);
    ssSetOutputPortDataType(S, 1, SS_UINT16);
    
    // fsb (flag_sb)
    ssSetOutputPortWidth(S, 2, 1);
    ssSetOutputPortDataType(S, 2, SS_INT32);

    // timeout
    ssSetOutputPortWidth(S, 3, 1);
    ssSetOutputPortDataType(S, 3, SS_UINT16);

    // flag voo
    ssSetOutputPortWidth(S, 4, 1);
    ssSetOutputPortDataType(S, 4, SS_UINT16);

    // fim de queima
    ssSetOutputPortWidth(S, 5, 1);
    ssSetOutputPortDataType(S, 5, SS_UINT16);
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 2); // reserve element in the pointers vector
    ssSetNumModes(S, 0); // to store a C++ object
    ssSetNumNonsampledZCs(S, 0);

    ssSetSimStateCompliance(S, USE_CUSTOM_SIM_STATE);
    
    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
}

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
      ssGetPWork(S)[0] = (void *) new ssv(50,3); // store new C++ object in the pointers vector
  }                                            
#endif /*  MDL_START */

/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid) {

    ssv *s = (ssv *) ssGetPWork(S)[0]; // retrieve C++ object from

    // declarando step
    ssv_step_in_fg step_in;

    // INPUTS
    const int16_T *flag_ejecao    = (const int16_T *) ssGetInputPortSignal(S, 0);
    const real32_T *ax            = (const real32_T *) ssGetInputPortSignal(S, 1);
    const real32_T *ay            = (const real32_T *) ssGetInputPortSignal(S, 2);
    const real32_T *az            = (const real32_T *) ssGetInputPortSignal(S, 3);
    const real32_T *vx            = (const real32_T *) ssGetInputPortSignal(S, 4);
    const real32_T *vy            = (const real32_T *) ssGetInputPortSignal(S, 5);
    const real32_T *vz            = (const real32_T *) ssGetInputPortSignal(S, 6);
    const real32_T *altitude      = (const real32_T *) ssGetInputPortSignal(S, 7);
    const real32_T *altitude_alvo = (const real32_T *) ssGetInputPortSignal(S, 8);
    const real32_T *perc_gps        = (const real32_T *) ssGetInputPortSignal(S, 9);
    const real32_T *tempo         = (const real32_T *) ssGetInputPortSignal(S, 10);
    const uint16_T *fom           = (const uint16_T *) ssGetInputPortSignal(S, 11);
    
    // OUTPUTS
    int16_T  *y_canard            = (int16_T *)ssGetOutputPortSignal(S,0);  // canard_on
    uint16_T *y_tejec             = (uint16_T *)ssGetOutputPortSignal(S,1); // tempo_ejecao
    int16_T  *y_fsb               = (int16_T *)ssGetOutputPortSignal(S,2);  // flag_sb
    int16_T  *y_timeout           = (int16_T *)ssGetOutputPortSignal(S,3);  // timeout
    int16_T  *y_flag_voo          = (int16_T *)ssGetOutputPortSignal(S,4);  // flag_voo
    int16_T  *y_fimdequeima       = (int16_T *)ssGetOutputPortSignal(S,5);  // fimdequeima
    
    // ESTRUTURA DE DADOS SSV
    step_in.flag_ejecao   = flag_ejecao[0];
    step_in.ax[5]         = ax[5];
    step_in.ay[5]         = ay[5];
    step_in.az[5]         = az[5];
    step_in.vx[2]         = vx[2];
    step_in.vy[2]         = vy[2];
    step_in.vz[2]         = vz[2];
    step_in.altitude[2]   = altitude[2];
    step_in.altitude_alvo = altitude_alvo[0];
    step_in.perc_gps      = perc_gps[0];
    step_in.tempo         = tempo[0];
    step_in.fom[2]        = fom[2];

    // CALCULOS SSV
    s->step(step_in);

    // if (s->fg_canard_on <= 1) {
        // printf("tempo    : %.1f\n", step_in.tempo);
        // printf("canard_on: %d\n", s->fg_canard_on);
    // }

    // printf("tempo : %.1f\n", step_in.tempo);
    // printf("vz    : %.1f\n", step_in.vz[2u]);
    // printf("ejecao: %d\n", step_in.flag_ejecao);
    // printf("h     : %.1f\n", step_in.altitude[2u]);
    // printf("\n");

    // saida
    y_canard[0U]      = s->fg_canard_on;
    y_tejec[0U]       = s->fg_tempo_ejecao;
    y_fsb[0U]         = s->fg_flag_sb;
    y_timeout[0U]     = s->fg_timeout;
    y_flag_voo[0U]    = s->flag_voo;
    y_fimdequeima[0U] = s->flag_fim_de_queima;
}                                                

#ifdef MATLAB_MEX_FILE
/* For now mdlG[S]etSimState are only supported in normal simulation */

/* Define to indicate that this S-Function has the mdlG[S]etSimState mothods */
#define MDL_SIM_STATE

/* Function: mdlGetSimState =====================================================
 * Abstract:
 *
 */
static mxArray* mdlGetSimState(SimStruct* S)
{
    ssv* c = (ssv*) ssGetPWork(S)[0];
    mxArray* outSS = mxCreateDoubleMatrix(1,1,mxREAL);
    mxGetPr(outSS)[0] = c->flag_voo;
    return outSS;
}
/* Function: mdlGetSimState =====================================================
 * Abstract:
 *
 */
static void mdlSetSimState(SimStruct* S, const mxArray* ma)
{
    // counter* c = (counter*) ssGetPWork(S)[0];
    // c->setX(mxGetPr(ma)[0]);
    
    // ssv* s = (ssv*) ssGetPWork(S)[1];	
    // b->setX(1.0);
}

#endif


/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    // counter *c = (counter *) ssGetPWork(S)[0]; // retrieve and destroy C++
    // delete c;                                  // object in the termination
    
    ssv *s = (ssv *) ssGetPWork(S)[0]; // retrieve and destroy C++
    delete s;                          // object in the termination
}                                      // function
/*======================================================*
 * See sfuntmpl.doc for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

