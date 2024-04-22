#ifndef RTW_HEADER_mod_foggui_h_
#define RTW_HEADER_mod_foggui_h_
#include <stddef.h>
#include <cstring>
#include <cfloat>
#include <cmath>
#include <math.h>
#include "rtw_modelmap.h"
#ifndef mod_foggui_COMMON_INCLUDES_
# define mod_foggui_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif

#include "mod_foggui_types.h"

#include "multiword_types.h"
#include <stddef.h>
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

typedef struct {
  syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T unusedExpr;
  syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T unusedExpr_mbvzarwird;
  sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T modelo;
  real_T C[1025];
  real_T C_cl54gopm0x[1025];
  real32_T a_tmp[1500];
  real_T RateTransition[3];
  real_T RateTransition1;
  real_T RateTransition2;
  real_T RateTransition3;
  real_T RateTransition4;
  real_T RateTransition16;
  real_T RateTransition17;
  real_T RateTransition13[2];
  real32_T RateTransition29;
  real32_T DataTypeConversion1[6];
  real32_T DataTypeConversion13[6];
  real32_T DataTypeConversion14[6];
  real32_T DataTypeConversion15[6];
  real32_T DataTypeConversion16[6];
  real32_T DataTypeConversion2[6];
  real32_T DataTypeConversion8;
  real32_T RateTransition12;
  real32_T RateTransition13_fhpnmvyjeu;
  real32_T RateTransition15[10];
  real32_T RateTransition25;
  real32_T RateTransition26;
  real32_T RateTransition27;
  real32_T RateTransition28;
  real32_T Bank[3];
  real32_T Elevation[3];
  real32_T Ve[3];
  real32_T Vn[3];
  real32_T Vd[3];
  real32_T Lat[3];
  real32_T Lon[3];
  real32_T Alt[3];
  real32_T lat_targ;
  real32_T lon_targ;
  real32_T alt_targ;
  int32_T fom[3];
  int32_T RateTransition12_mwuhtr5lwn;
  int32_T RateTransition3_jscxuhpmkl;
  int32_T UnitDelay1_fvkxsdqnex;
  int32_T sfunSSV_o1;
  int32_T flag_sb;
  int32_T flag_ejecao;
  uint16_T sfunSSV_o2;
  uint16_T sfunSSV_o4;
  uint16_T sfunSSV_o5;
  uint16_T sfunSSV_o6;
} B_mod_foggui_T;

typedef struct {
  Traj_mod_foggui_T o;
  real_T UnitDelay1_DSTATE[2];
  real_T DiscreteTransferFcn1_states;
  real_T DiscreteTransferFcn3_states;
  real_T UnitDelay_DSTATE;
  real_T UnitDelay1_DSTATE_mtu4iijmx1;
  real_T PrevY[2];
  real_T cont;
  real_T F_aux;
  real_T Salfab;
  real_T Dalfa;
  real_T Dalfa_c;
  real_T cont_kimmltz2iq;
  real_T err_;
  real_T erroint;
  real_T RateTransition5_Buffer[3];
  real_T RateTransition18_Buffer[6];
  real_T RateTransition20_Buffer[6];
  real_T RateTransition21_Buffer[6];
  real_T RateTransition6_Buffer[6];
  real_T RateTransition7_Buffer[6];
  real_T RateTransition22_Buffer[3];
  real_T RateTransition23_Buffer[3];
  real_T RateTransition19_Buffer[6];
  real_T RateTransition11_Buffer[3];
  real_T RateTransition13_Buffer0[2];
  real_T m3[9];
  real_T m6[36];
  real_T i3;
  real_T i6;
  void *sfunSSV_PWORK[2];
  int32_T UnitDelay_DSTATE_gupgjp1fb1;
  int32_T UnitDelay2_DSTATE;
  int32_T UnitDelay1_DSTATE_jwmvbzzmma;
  real32_T RateTransition29_Buffer;
  real32_T RateTransition10_Buffer[3];
  real32_T RateTransition12_Buffer;
  real32_T RateTransition13_Buffer;
  real32_T RateTransition15_Buffer[10];
  real32_T RateTransition24_Buffer[3];
  real32_T RateTransition30_Buffer[3];
  real32_T RateTransition8_Buffer[2];
  real32_T RateTransition9_Buffer[3];
  real32_T RateTransition25_Buffer;
  real32_T RateTransition26_Buffer;
  real32_T RateTransition27_Buffer;
  real32_T RateTransition28_Buffer;
  real32_T moduloERRO_;
  real32_T vetorPOS[20];
  real32_T x[10];
  real32_T lista_circular[6];
  real32_T pos_buffer[1000];
  real32_T ang13_;
  real32_T ang24_;
  real32_T theta0[3];
  real32_T pontos[10];
  real32_T y_;
  real32_T x_bio4k4d4zb[10];
  real32_T buffer[27];
  int32_T RateTransition12_Buffer0;
  int32_T RateTransition3_Buffer0;
  int16_T cont_fpqdtmbzoo;
  int8_T flag_wx;
  int8_T flag_gui_lat;
  int8_T flag_gui_lon;
  boolean_T o_not_empty;
  boolean_T flagLoopFases1;
  boolean_T flagLoopFases2;
  boolean_T mantem_ejecao;
  boolean_T pontos_not_empty;
} DW_mod_foggui_T;

typedef struct {
  int32_T tiro;
} ExtU_mod_foggui_T;

typedef struct {
  real_T tempo;
  real_T vel[3];
  real_T pqr[3];
  real_T uvw[3];
  real_T ang[3];
  real_T pos[3];
  real_T latlong[2];
  boolean_T fim;
  real_T canard_y[2];
  real_T log_anmk3tusmu[29];
  real_T fm[7];
  real_T canard_on;
  real_T canard_u[2];
  real_T erro_lat;
  real_T erro_lon;
  real_T sigma_lat;
  real_T sigma_lon;
  real32_T pontos_traj[10];
  real32_T modulo_erro;
  uint16_T tempo_ejecao;
  int32_T nro_iteracoes;
  uint16_T nro_timeout;
  uint16_T pulso_flag_voo;
  uint16_T ssv_fimdequeima;
  real_T flag_ejecao;
} ExtY_mod_foggui_T;

struct P_mod_foggui_T_ {
  struct_K8JPS3rkFE223YguxJpwYD state;
  real_T R_Gain;
  real_T kelvin_Value;
  real_T Gain_Gain;
  real_T Constant_Value;
  real_T UnitDelay_InitialCondition;
  real_T UnitDelay1_InitialCondition;
  real_T RateTransition13_InitialCondition;
  real_T DiscreteTransferFcn1_NumCoef;
  real_T DiscreteTransferFcn1_DenCoef[2];
  real_T DiscreteTransferFcn1_InitialStates;
  real_T DiscreteTransferFcn3_NumCoef;
  real_T DiscreteTransferFcn3_DenCoef[2];
  real_T DiscreteTransferFcn3_InitialStates;
  real_T Saturation_UpperSat;
  real_T Saturation_LowerSat;
  real_T RateLimiter_RisingLim;
  real_T RateLimiter_FallingLim;
  real_T RateLimiter_IC;
  real_T UnitDelay1_InitialCondition_ev2gupt1pg;
  int32_T UnitDelay1_InitialCondition_fywu2qaory;
  int32_T RateTransition12_InitialCondition;
  int32_T RateTransition3_InitialCondition;
  int32_T UnitDelay_InitialCondition_ixzxscpueh;
  int32_T UnitDelay2_InitialCondition;
  int32_T Gain_Gain_o4w1mvc04r;
};

struct tag_RTM_mod_foggui_T {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[2];
    SimStruct childSFunctions[1];
    SimStruct *childSFunctionPtrs[1];
    struct _ssBlkInfo2 blkInfo2[1];
    struct _ssSFcnModelMethods2 methods2[1];
    struct _ssSFcnModelMethods3 methods3[1];
    struct _ssSFcnModelMethods4 methods4[1];
    struct _ssStatesInfo2 statesInfo2[1];
    ssPeriodicStatesInfo periodicStatesInfo[1];
    struct _ssPortInfo2 inputOutputPortInfo2[1];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[12];
      struct _ssInPortUnit inputPortUnits[12];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[12];
      struct _ssPortOutputs outputPortInfo[6];
      struct _ssOutPortUnit outputPortUnits[6];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[6];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn0;
  } NonInlinedSFcns;

  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[92];
    int32_T* vardimsAddress[92];
    RTWLoggingFcnPtr loggingPtrs[92];
  } DataMapInfo;

  struct {
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  struct {
    time_T stepSize;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[2];
    time_T offsetTimesArray[2];
    int_T sampleTimeTaskIDArray[2];
    int_T sampleHitArray[2];
    int_T perTaskSampleHitsArray[4];
    time_T tArray[2];
  } Timing;
};

extern const rtwCAPI_ModelMappingStaticInfo*
  mod_foggui_GetCAPIStaticMap(void);
class mod_fogguiModelClass {
 public:
  ExtU_mod_foggui_T mod_foggui_U;
  ExtY_mod_foggui_T mod_foggui_Y;
  void initialize();
  void step();
  void terminate();
  mod_fogguiModelClass();
  ~mod_fogguiModelClass();
  RT_MODEL_mod_foggui_T * getRTM();
  static P_mod_foggui_T mod_foggui_P;
 private:
  B_mod_foggui_T mod_foggui_B;
  DW_mod_foggui_T mod_foggui_DW;
  RT_MODEL_mod_foggui_T mod_foggui_M;
  void mod_foggui_cosd_dln4qkicsy(real_T *x);
  void mod_foggui_sind_nfvntbsefa(real_T *x);
  void mod_foggui_circshift_ad3ayr23dy(real_T a[41]);
  void mod_foggui_circshift_ad3ayr23dys(real_T a[41]);
  void mod_foggui_cosd_dln4qkicsyc(real_T x[48]);
  void mod_foggui_sind_nfvntbsefaa(real_T x[48]);
  void mod_foggui_Traj_Update_modelo(real_T config_lancamento_Elev, real_T
    config_lancamento_Rlat, real_T config_lancamento_Rlong, real_T
    config_lancamento_Ralt, real_T config_lancamento_Azi, real_T
    config_lancamento_Talt, real_T config_lancamento_Tesp, real_T
    config_lancamento_Hsub, real_T config_lancamento_Hmet, real_T
    config_lancamento_Rtemp, real_T config_lancamento_Rde, real_T
    config_lancamento_Dbal, real_T config_lancamento_Tbal, real_T
    config_lancamento_Pbal, real_T config_lancamento_Phi0, const
    b_config_inercia *config_inercia, const b_config_propelente
    *config_propelente, const b_config_geometria *config_geometria, const
    b_config_dados_part *config_dados_part, const b_config_empuxo
    *config_dados_empuxo, const b_config_vento *config_dados_vento, const real_T
    config_tabaer[1025], sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T *modelo);
  void mod_foggui_hypot(const real_T x[48], const real_T y[48], real_T r[48]);
  void mod_foggui_eye(real_T b_I[9]);
  void mod_foggui_Traj_Inicializa_traj(Traj_mod_foggui_T *o, real_T
    config_lancamento_Elev, real_T config_lancamento_Rlat, real_T
    config_lancamento_Rlong, real_T config_lancamento_Ralt, real_T
    config_lancamento_Azi, real_T config_lancamento_Talt, real_T
    config_lancamento_Tesp, real_T config_lancamento_Hsub, real_T
    config_lancamento_Hmet, real_T config_lancamento_Rtemp, real_T
    config_lancamento_Rde, real_T config_lancamento_Dbal, real_T
    config_lancamento_Tbal, real_T config_lancamento_Pbal, real_T
    config_lancamento_Phi0, const b_config_inercia *config_inercia, const
    b_config_propelente *config_propelente, const b_config_geometria
    *config_geometria, const b_config_dados_part *config_dados_part, const
    b_config_empuxo *config_dados_empuxo, const b_config_vento
    *config_dados_vento, const real_T config_tabaer[1025], const b_coef_canard
    *config_coef_canard, const b_config_controle_z config_controle_z);
  void mod_foggui_Traj_Inercia(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Quat(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Lbh(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_R_inic(Traj_mod_foggui_T *o, const real_T L[4]);
  void mod_foggui_Traj_Tabre_(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Iniciar(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Padrao(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Vento(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Pa_vsom(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Atmosf(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Cdist(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Cp_contato(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Cr_tubo(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Tip_off(Traj_mod_foggui_T *o);
  real_T mod_foggui_Traj_Cnemp(const Traj_mod_foggui_T *o, real_T Alf, real_T
    *Dcna, real_T Cna2e, real_T Cna3e);
  void mod_foggui_Traj_Empena_canard(Traj_mod_foggui_T *o, real_T Im, real_T Ym);
  void mod_foggui_Traj_Comb(Traj_mod_foggui_T *o);
  real_T mod_foggui_interp1(const real_T varargin_1[40], const real_T
    varargin_2[40], real_T varargin_3);
  void mod_foggui_Traj_debug(const Traj_mod_foggui_T *o,
    syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T *o_);
  void mod_foggui_Traj_Forca_canard(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Empena(Traj_mod_foggui_T *o, real_T Im, real_T Ym, real_T
    Clind);
  void mod_foggui_Traj_Aero(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Cpf(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Deriv(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Degree(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Newstate(Traj_mod_foggui_T *o, const real_T
    estadoAnterior[13], real_T Hfat);
  void mod_foggui_Traj_Runge(Traj_mod_foggui_T *o, const real_T P_[13]);
  void mod_foggui_Traj_Apogeu(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Fase(Traj_mod_foggui_T *o);
  void mod_foggui_Traj_Flag(Traj_mod_foggui_T *o);
  void mod_foggui_circshift(real32_T a[1000]);
  void mod_foggui_mldivide(const real32_T A[9], const real32_T B[1500], real32_T
    Y[1500]);
  real32_T mod_foggui_calculoRaioCurvatura(const real32_T d[1000]);
  real32_T mod_foggui_norm(const real32_T x[2]);
  void mod_foggui_guiamentoLongitudinal(const real32_T vh[3], const real32_T
    pos[3], const real32_T pos_a[3], const real32_T pos_buffer[1000], real32_T
    Dgui, real32_T fator_curvatura, real32_T *vc, real32_T *lambda_dot, real32_T
    pontos_out[10], int8_T *modo);
  void mod_foggui_cosd(real32_T *x);
  void mod_foggui_sind(real32_T *x);
  int32_T mod_foggui_thirdOfFive(const real32_T v[10], int32_T ia, int32_T ib);
  void mod_foggui_quickselect(real32_T v[10], int32_T n, int32_T idx0, int32_T
    vlen, real32_T *vn, int32_T *nfirst, int32_T *nlast);
  real_T mod_foggui_norm_hmux2c0tmp(const real_T x[3]);
  void mod_foggui_dynamicEquations3DoF(const real_T entrada[6], real_T g, real_T
    Fa, real_T Xp[6]);
  void mod_foggui_calculaTrajetoria(const real32_T LLA[3], const real32_T VEL[3],
    const real32_T ALVO[3], real32_T config_step_ini, real32_T config_step_mid,
    real32_T config_step_fim, real32_T config_tempo_step_ini, real32_T
    config_tempo_step_mid, real32_T config_epsilon_step, real32_T
    config_epsilon_altura, real32_T config_max_iteracoes, const
    s8zZSU4DcwnDyW5HgyKzKEG_mod_foggui_T *fog, real32_T Tref, real32_T P0,
    real32_T lla[3], int32_T *nro_iteracoes, int32_T *flag_caiu);
  void mod_foggui_calculaErro(const real32_T lla[3], const real32_T lla_targ[3],
    int32_T flag_caiu, int32_T *flag_ejecao, real32_T *modulo_erro);
};

#endif
