#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "mod_foggui_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#ifndef SS_INT64
#define SS_INT64                       45
#endif

#ifndef SS_UINT64
#define SS_UINT64                      46
#endif

#else
#include "builtin_typeid_types.h"
#include "mod_foggui.h"
#include "mod_foggui_capi.h"
#include "mod_foggui_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif

static rtwCAPI_Signals rtBlockSignals[] = {

  { 0, 6, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 1, 6, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING(""), 1, 1, 1, 0, 0 },

  { 2, 6, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING(""), 2, 0, 0, 0, 0 },

  { 3, 5, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING("tempo_ejecao"), 9, 2, 0, 0, 1 },

  { 4, 5, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING("nro_timeout"), 11, 2, 0, 0, 1 },

  { 5, 5, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING("pulso_flag_voo"), 12, 2, 0, 0, 1 },

  { 6, 5, TARGET_STRING("mod_foggui/Controle"),
    TARGET_STRING("ssv_fimdequeima"), 13, 2, 0, 0, 1 },

  { 7, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 8, 4, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS"),
    TARGET_STRING(""), 2, 0, 0, 0, 1 },

  { 9, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS"),
    TARGET_STRING("tejec"), 9, 2, 0, 0, 1 },

  { 10, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS"),
    TARGET_STRING(""), 11, 2, 0, 0, 1 },

  { 11, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS"),
    TARGET_STRING(""), 12, 2, 0, 0, 1 },

  { 12, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS"),
    TARGET_STRING(""), 13, 2, 0, 0, 1 },

  { 13, 6, TARGET_STRING("mod_foggui/Controle/Rate Transition12"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 14, 6, TARGET_STRING("mod_foggui/Controle/Rate Transition13"),
    TARGET_STRING(""), 0, 1, 1, 0, 0 },

  { 15, 6, TARGET_STRING("mod_foggui/Controle/Rate Transition3"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 16, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 1, 3, 2, 0, 1 },

  { 17, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 2, 3, 2, 0, 1 },

  { 18, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 3, 3, 2, 0, 1 },

  { 19, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 4, 3, 2, 0, 1 },

  { 20, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 5, 3, 2, 0, 1 },

  { 21, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 6, 3, 2, 0, 1 },

  { 22, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 7, 3, 2, 0, 1 },

  { 23, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 8, 3, 2, 0, 1 },

  { 24, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 9, 3, 0, 0, 1 },

  { 25, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 10, 3, 0, 0, 1 },

  { 26, 2, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/ajusteEntradas "),
    TARGET_STRING(""), 11, 3, 0, 0, 1 },

  { 27, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion1"),
    TARGET_STRING(""), 0, 3, 3, 0, 1 },

  { 28, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion12"),
    TARGET_STRING("fom"), 0, 0, 2, 0, 1 },

  { 29, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion13"),
    TARGET_STRING(""), 0, 3, 3, 0, 1 },

  { 30, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion14"),
    TARGET_STRING(""), 0, 3, 3, 0, 1 },

  { 31, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion15"),
    TARGET_STRING(""), 0, 3, 3, 0, 1 },

  { 32, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion16"),
    TARGET_STRING(""), 0, 3, 3, 0, 1 },

  { 33, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion2"),
    TARGET_STRING(""), 0, 3, 3, 0, 1 },

  { 34, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Data Type Conversion8"),
    TARGET_STRING(""), 0, 3, 0, 0, 0 },

  { 35, 6, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Rate Transition"),
    TARGET_STRING(""), 0, 1, 2, 0, 0 },

  { 36, 6, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Rate Transition1"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 37, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition12"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 38, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition13"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 39, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition15"),
    TARGET_STRING(""), 0, 3, 4, 0, 1 },

  { 40, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition16"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 41, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition17"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 42, 6, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Rate Transition2"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 43, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition25"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 44, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition26"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 45, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition27"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 46, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition28"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 47, 6, TARGET_STRING(
    "mod_foggui/Controle/LEITURA_SENSORES/Rate Transition29"),
    TARGET_STRING(""), 0, 3, 0, 0, 1 },

  { 48, 6, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Rate Transition3"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 49, 6, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Rate Transition4"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 50, 4, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/alijaSb"),
    TARGET_STRING("flag_ejecao"), 0, 0, 0, 0, 1 },

  { 51, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 52, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV"),
    TARGET_STRING(""), 1, 2, 0, 0, 1 },

  { 53, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV"),
    TARGET_STRING("flag_sb"), 2, 0, 0, 0, 1 },

  { 54, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV"),
    TARGET_STRING(""), 3, 2, 0, 0, 1 },

  { 55, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV"),
    TARGET_STRING(""), 4, 2, 0, 0, 1 },

  { 56, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV"),
    TARGET_STRING(""), 5, 2, 0, 0, 1 },

  { 57, 5, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/Unit Delay1"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static rtwCAPI_BlockParameters rtBlockParameters[] = {

  { 58, TARGET_STRING("mod_foggui/Gain"),
    TARGET_STRING("Gain"), 0, 0, 1 },

  { 59, TARGET_STRING("mod_foggui/Unit Delay"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 60, TARGET_STRING("mod_foggui/Unit Delay1"),
    TARGET_STRING("InitialCondition"), 1, 0, 0 },

  { 61, TARGET_STRING("mod_foggui/Unit Delay2"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 62, TARGET_STRING("mod_foggui/Controle/Rate Transition12"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 63, TARGET_STRING("mod_foggui/Controle/Rate Transition13"),
    TARGET_STRING("InitialCondition"), 1, 0, 0 },

  { 64, TARGET_STRING("mod_foggui/Controle/Rate Transition3"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 65, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Constant"),
    TARGET_STRING("Value"), 1, 0, 0 },

  { 66, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Unit Delay"),
    TARGET_STRING("InitialCondition"), 1, 0, 0 },

  { 67, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Unit Delay1"),
    TARGET_STRING("InitialCondition"), 1, 0, 0 },

  { 68, TARGET_STRING("mod_foggui/Controle/controleJATOSeCANARDS/Unit Delay1"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 69, TARGET_STRING("mod_foggui/traj/dinCanards/Rate Limiter"),
    TARGET_STRING("RisingSlewLimit"), 1, 0, 0 },

  { 70, TARGET_STRING("mod_foggui/traj/dinCanards/Rate Limiter"),
    TARGET_STRING("FallingSlewLimit"), 1, 0, 0 },

  { 71, TARGET_STRING("mod_foggui/traj/dinCanards/Rate Limiter"),
    TARGET_STRING("InitialCondition"), 1, 0, 0 },

  { 72, TARGET_STRING("mod_foggui/traj/dinCanards/Saturation"),
    TARGET_STRING("UpperLimit"), 1, 0, 0 },

  { 73, TARGET_STRING("mod_foggui/traj/dinCanards/Saturation"),
    TARGET_STRING("LowerLimit"), 1, 0, 0 },

  { 74, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete Transfer Fcn1"),
    TARGET_STRING("Numerator"), 1, 0, 0 },

  { 75, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete Transfer Fcn1"),
    TARGET_STRING("Denominator"), 1, 5, 0 },

  { 76, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete Transfer Fcn1"),
    TARGET_STRING("InitialStates"), 1, 0, 0 },

  { 77, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete Transfer Fcn3"),
    TARGET_STRING("Numerator"), 1, 0, 0 },

  { 78, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete Transfer Fcn3"),
    TARGET_STRING("Denominator"), 1, 5, 0 },

  { 79, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete Transfer Fcn3"),
    TARGET_STRING("InitialStates"), 1, 0, 0 },

  { 80, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/rho2pressao/kelvin"),
    TARGET_STRING("Value"), 1, 0, 0 },

  { 81, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/rho2pressao/Gain"),
    TARGET_STRING("Gain"), 1, 0, 0 },

  { 82, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/rho2pressao/R"),
    TARGET_STRING("Gain"), 1, 0, 0 },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

static rtwCAPI_States rtBlockStates[] = {

  { 83, -1, TARGET_STRING("mod_foggui/Unit Delay"),
    TARGET_STRING(""), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 84, -1, TARGET_STRING("mod_foggui/Unit Delay1"),
    TARGET_STRING(""), "", 0, 1, 1, 0, 0, 0, -1, 0 },

  { 85, -1, TARGET_STRING("mod_foggui/Unit Delay2"),
    TARGET_STRING(""), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 86, -1, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Unit Delay"),
    TARGET_STRING(""), "", 0, 1, 0, 0, 0, 0, -1, 0 },

  { 87, -1, TARGET_STRING("mod_foggui/Controle/LEITURA_SENSORES/Unit Delay1"),
    TARGET_STRING(""), "", 0, 1, 0, 0, 0, 0, -1, 0 },

  { 88, -1, TARGET_STRING(
    "mod_foggui/Controle/controleJATOSeCANARDS/Unit Delay1"),
    TARGET_STRING(""), "", 0, 0, 0, 0, 1, 0, -1, 0 },

  { 89, -1, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete\nTransfer Fcn1"),
    TARGET_STRING(""), "", 0, 1, 0, 0, 0, 0, -1, 0 },

  { 90, -1, TARGET_STRING("mod_foggui/traj/dinCanards/Discrete\nTransfer Fcn3"),
    TARGET_STRING(""), "", 0, 1, 0, 0, 0, 0, -1, 0 },

  {
    0, -1, (NULL), (NULL), (NULL), 0, 0, 0, 0, 0, 0, -1, 0
  }
};

static rtwCAPI_ModelParameters rtModelParameters[] = {

  { 91, TARGET_STRING("state"), 17, 0, 0 },

  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

static void mod_foggui_InitializeDataAddr(void* dataAddr[], B_mod_foggui_T
  *mod_foggui_B, P_mod_foggui_T *mod_foggui_P, DW_mod_foggui_T *mod_foggui_DW)
{
  dataAddr[0] = (void*) (&mod_foggui_B->RateTransition12_mwuhtr5lwn);
  dataAddr[1] = (void*) (&mod_foggui_B->RateTransition13[0]);
  dataAddr[2] = (void*) (&mod_foggui_B->RateTransition3_jscxuhpmkl);
  dataAddr[3] = (void*) (&mod_foggui_B->sfunSSV_o2);
  dataAddr[4] = (void*) (&mod_foggui_B->sfunSSV_o4);
  dataAddr[5] = (void*) (&mod_foggui_B->sfunSSV_o5);
  dataAddr[6] = (void*) (&mod_foggui_B->sfunSSV_o6);
  dataAddr[7] = (void*) (&mod_foggui_B->sfunSSV_o1);
  dataAddr[8] = (void*) (&mod_foggui_B->flag_ejecao);
  dataAddr[9] = (void*) (&mod_foggui_B->sfunSSV_o2);
  dataAddr[10] = (void*) (&mod_foggui_B->sfunSSV_o4);
  dataAddr[11] = (void*) (&mod_foggui_B->sfunSSV_o5);
  dataAddr[12] = (void*) (&mod_foggui_B->sfunSSV_o6);
  dataAddr[13] = (void*) (&mod_foggui_B->RateTransition12_mwuhtr5lwn);
  dataAddr[14] = (void*) (&mod_foggui_B->RateTransition13[0]);
  dataAddr[15] = (void*) (&mod_foggui_B->RateTransition3_jscxuhpmkl);
  dataAddr[16] = (void*) (&mod_foggui_B->Bank[0]);
  dataAddr[17] = (void*) (&mod_foggui_B->Elevation[0]);
  dataAddr[18] = (void*) (&mod_foggui_B->Ve[0]);
  dataAddr[19] = (void*) (&mod_foggui_B->Vn[0]);
  dataAddr[20] = (void*) (&mod_foggui_B->Vd[0]);
  dataAddr[21] = (void*) (&mod_foggui_B->Lat[0]);
  dataAddr[22] = (void*) (&mod_foggui_B->Lon[0]);
  dataAddr[23] = (void*) (&mod_foggui_B->Alt[0]);
  dataAddr[24] = (void*) (&mod_foggui_B->lat_targ);
  dataAddr[25] = (void*) (&mod_foggui_B->lon_targ);
  dataAddr[26] = (void*) (&mod_foggui_B->alt_targ);
  dataAddr[27] = (void*) (&mod_foggui_B->DataTypeConversion1[0]);
  dataAddr[28] = (void*) (&mod_foggui_B->fom[0]);
  dataAddr[29] = (void*) (&mod_foggui_B->DataTypeConversion13[0]);
  dataAddr[30] = (void*) (&mod_foggui_B->DataTypeConversion14[0]);
  dataAddr[31] = (void*) (&mod_foggui_B->DataTypeConversion15[0]);
  dataAddr[32] = (void*) (&mod_foggui_B->DataTypeConversion16[0]);
  dataAddr[33] = (void*) (&mod_foggui_B->DataTypeConversion2[0]);
  dataAddr[34] = (void*) (&mod_foggui_B->DataTypeConversion8);
  dataAddr[35] = (void*) (&mod_foggui_B->RateTransition[0]);
  dataAddr[36] = (void*) (&mod_foggui_B->RateTransition1);
  dataAddr[37] = (void*) (&mod_foggui_B->RateTransition12);
  dataAddr[38] = (void*) (&mod_foggui_B->RateTransition13_fhpnmvyjeu);
  dataAddr[39] = (void*) (&mod_foggui_B->RateTransition15[0]);
  dataAddr[40] = (void*) (&mod_foggui_B->RateTransition16);
  dataAddr[41] = (void*) (&mod_foggui_B->RateTransition17);
  dataAddr[42] = (void*) (&mod_foggui_B->RateTransition2);
  dataAddr[43] = (void*) (&mod_foggui_B->RateTransition25);
  dataAddr[44] = (void*) (&mod_foggui_B->RateTransition26);
  dataAddr[45] = (void*) (&mod_foggui_B->RateTransition27);
  dataAddr[46] = (void*) (&mod_foggui_B->RateTransition28);
  dataAddr[47] = (void*) (&mod_foggui_B->RateTransition29);
  dataAddr[48] = (void*) (&mod_foggui_B->RateTransition3);
  dataAddr[49] = (void*) (&mod_foggui_B->RateTransition4);
  dataAddr[50] = (void*) (&mod_foggui_B->flag_ejecao);
  dataAddr[51] = (void*) (&mod_foggui_B->sfunSSV_o1);
  dataAddr[52] = (void*) (&mod_foggui_B->sfunSSV_o2);
  dataAddr[53] = (void*) (&mod_foggui_B->flag_sb);
  dataAddr[54] = (void*) (&mod_foggui_B->sfunSSV_o4);
  dataAddr[55] = (void*) (&mod_foggui_B->sfunSSV_o5);
  dataAddr[56] = (void*) (&mod_foggui_B->sfunSSV_o6);
  dataAddr[57] = (void*) (&mod_foggui_B->UnitDelay1_fvkxsdqnex);
  dataAddr[58] = (void*) (&mod_foggui_P->Gain_Gain_o4w1mvc04r);
  dataAddr[59] = (void*) (&mod_foggui_P->UnitDelay_InitialCondition_ixzxscpueh);
  dataAddr[60] = (void*) (&mod_foggui_P->UnitDelay1_InitialCondition_ev2gupt1pg);
  dataAddr[61] = (void*) (&mod_foggui_P->UnitDelay2_InitialCondition);
  dataAddr[62] = (void*) (&mod_foggui_P->RateTransition12_InitialCondition);
  dataAddr[63] = (void*) (&mod_foggui_P->RateTransition13_InitialCondition);
  dataAddr[64] = (void*) (&mod_foggui_P->RateTransition3_InitialCondition);
  dataAddr[65] = (void*) (&mod_foggui_P->Constant_Value);
  dataAddr[66] = (void*) (&mod_foggui_P->UnitDelay_InitialCondition);
  dataAddr[67] = (void*) (&mod_foggui_P->UnitDelay1_InitialCondition);
  dataAddr[68] = (void*) (&mod_foggui_P->UnitDelay1_InitialCondition_fywu2qaory);
  dataAddr[69] = (void*) (&mod_foggui_P->RateLimiter_RisingLim);
  dataAddr[70] = (void*) (&mod_foggui_P->RateLimiter_FallingLim);
  dataAddr[71] = (void*) (&mod_foggui_P->RateLimiter_IC);
  dataAddr[72] = (void*) (&mod_foggui_P->Saturation_UpperSat);
  dataAddr[73] = (void*) (&mod_foggui_P->Saturation_LowerSat);
  dataAddr[74] = (void*) (&mod_foggui_P->DiscreteTransferFcn1_NumCoef);
  dataAddr[75] = (void*) (&mod_foggui_P->DiscreteTransferFcn1_DenCoef[0]);
  dataAddr[76] = (void*) (&mod_foggui_P->DiscreteTransferFcn1_InitialStates);
  dataAddr[77] = (void*) (&mod_foggui_P->DiscreteTransferFcn3_NumCoef);
  dataAddr[78] = (void*) (&mod_foggui_P->DiscreteTransferFcn3_DenCoef[0]);
  dataAddr[79] = (void*) (&mod_foggui_P->DiscreteTransferFcn3_InitialStates);
  dataAddr[80] = (void*) (&mod_foggui_P->kelvin_Value);
  dataAddr[81] = (void*) (&mod_foggui_P->Gain_Gain);
  dataAddr[82] = (void*) (&mod_foggui_P->R_Gain);
  dataAddr[83] = (void*) (&mod_foggui_DW->UnitDelay_DSTATE_gupgjp1fb1);
  dataAddr[84] = (void*) (&mod_foggui_DW->UnitDelay1_DSTATE[0]);
  dataAddr[85] = (void*) (&mod_foggui_DW->UnitDelay2_DSTATE);
  dataAddr[86] = (void*) (&mod_foggui_DW->UnitDelay_DSTATE);
  dataAddr[87] = (void*) (&mod_foggui_DW->UnitDelay1_DSTATE_mtu4iijmx1);
  dataAddr[88] = (void*) (&mod_foggui_DW->UnitDelay1_DSTATE_jwmvbzzmma);
  dataAddr[89] = (void*) (&mod_foggui_DW->DiscreteTransferFcn1_states);
  dataAddr[90] = (void*) (&mod_foggui_DW->DiscreteTransferFcn3_states);
  dataAddr[91] = (void*) (&mod_foggui_P->state);
}

#endif

#ifndef HOST_CAPI_BUILD

static void mod_foggui_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

#ifndef HOST_CAPI_BUILD

static void mod_foggui_InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
{
  loggingPtrs[0] = (NULL);
  loggingPtrs[1] = (NULL);
  loggingPtrs[2] = (NULL);
  loggingPtrs[3] = (NULL);
  loggingPtrs[4] = (NULL);
  loggingPtrs[5] = (NULL);
  loggingPtrs[6] = (NULL);
  loggingPtrs[7] = (NULL);
  loggingPtrs[8] = (NULL);
  loggingPtrs[9] = (NULL);
  loggingPtrs[10] = (NULL);
  loggingPtrs[11] = (NULL);
  loggingPtrs[12] = (NULL);
  loggingPtrs[13] = (NULL);
  loggingPtrs[14] = (NULL);
  loggingPtrs[15] = (NULL);
  loggingPtrs[16] = (NULL);
  loggingPtrs[17] = (NULL);
  loggingPtrs[18] = (NULL);
  loggingPtrs[19] = (NULL);
  loggingPtrs[20] = (NULL);
  loggingPtrs[21] = (NULL);
  loggingPtrs[22] = (NULL);
  loggingPtrs[23] = (NULL);
  loggingPtrs[24] = (NULL);
  loggingPtrs[25] = (NULL);
  loggingPtrs[26] = (NULL);
  loggingPtrs[27] = (NULL);
  loggingPtrs[28] = (NULL);
  loggingPtrs[29] = (NULL);
  loggingPtrs[30] = (NULL);
  loggingPtrs[31] = (NULL);
  loggingPtrs[32] = (NULL);
  loggingPtrs[33] = (NULL);
  loggingPtrs[34] = (NULL);
  loggingPtrs[35] = (NULL);
  loggingPtrs[36] = (NULL);
  loggingPtrs[37] = (NULL);
  loggingPtrs[38] = (NULL);
  loggingPtrs[39] = (NULL);
  loggingPtrs[40] = (NULL);
  loggingPtrs[41] = (NULL);
  loggingPtrs[42] = (NULL);
  loggingPtrs[43] = (NULL);
  loggingPtrs[44] = (NULL);
  loggingPtrs[45] = (NULL);
  loggingPtrs[46] = (NULL);
  loggingPtrs[47] = (NULL);
  loggingPtrs[48] = (NULL);
  loggingPtrs[49] = (NULL);
  loggingPtrs[50] = (NULL);
  loggingPtrs[51] = (NULL);
  loggingPtrs[52] = (NULL);
  loggingPtrs[53] = (NULL);
  loggingPtrs[54] = (NULL);
  loggingPtrs[55] = (NULL);
  loggingPtrs[56] = (NULL);
  loggingPtrs[57] = (NULL);
  loggingPtrs[58] = (NULL);
  loggingPtrs[59] = (NULL);
  loggingPtrs[60] = (NULL);
  loggingPtrs[61] = (NULL);
  loggingPtrs[62] = (NULL);
  loggingPtrs[63] = (NULL);
  loggingPtrs[64] = (NULL);
  loggingPtrs[65] = (NULL);
  loggingPtrs[66] = (NULL);
  loggingPtrs[67] = (NULL);
  loggingPtrs[68] = (NULL);
  loggingPtrs[69] = (NULL);
  loggingPtrs[70] = (NULL);
  loggingPtrs[71] = (NULL);
  loggingPtrs[72] = (NULL);
  loggingPtrs[73] = (NULL);
  loggingPtrs[74] = (NULL);
  loggingPtrs[75] = (NULL);
  loggingPtrs[76] = (NULL);
  loggingPtrs[77] = (NULL);
  loggingPtrs[78] = (NULL);
  loggingPtrs[79] = (NULL);
  loggingPtrs[80] = (NULL);
  loggingPtrs[81] = (NULL);
  loggingPtrs[82] = (NULL);
  loggingPtrs[83] = (NULL);
  loggingPtrs[84] = (NULL);
  loggingPtrs[85] = (NULL);
  loggingPtrs[86] = (NULL);
  loggingPtrs[87] = (NULL);
  loggingPtrs[88] = (NULL);
  loggingPtrs[89] = (NULL);
  loggingPtrs[90] = (NULL);
  loggingPtrs[91] = (NULL);
}

#endif

static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {

  { "int", "int32_T", 0, 0, sizeof(int32_T), SS_INT32, 0, 0, 0 },

  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0, 0 },

  { "unsigned short", "uint16_T", 0, 0, sizeof(uint16_T), SS_UINT16, 0, 0, 0 },

  { "float", "real32_T", 0, 0, sizeof(real32_T), SS_SINGLE, 0, 0, 0 },

  { "struct", "b_config_lancamento", 15, 1, sizeof(b_config_lancamento),
    SS_STRUCT, 0, 0, 0 },

  { "struct", "b_config_inercia", 20, 16, sizeof(b_config_inercia), SS_STRUCT, 0,
    0, 0 },

  { "struct", "b_config_propelente", 20, 36, sizeof(b_config_propelente),
    SS_STRUCT, 0, 0, 0 },

  { "struct", "b_config_geometria", 11, 56, sizeof(b_config_geometria),
    SS_STRUCT, 0, 0, 0 },

  { "struct", "b_config_dados_part", 25, 67, sizeof(b_config_dados_part),
    SS_STRUCT, 0, 0, 0 },

  { "struct", "b_config_empuxo", 3, 92, sizeof(b_config_empuxo), SS_STRUCT, 0, 0,
    0 },

  { "struct", "b_config_vento", 3, 95, sizeof(b_config_vento), SS_STRUCT, 0, 0,
    0 },

  { "struct", "b_coef_canard", 5, 98, sizeof(b_coef_canard), SS_STRUCT, 0, 0, 0
  },

  { "struct", "b_config_erros", 3, 103, sizeof(b_config_erros), SS_STRUCT, 0, 0,
    0 },

  { "struct", "b_config_flags", 1, 106, sizeof(b_config_flags), SS_STRUCT, 0, 0,
    0 },

  { "struct", "b_config_controle_z", 4, 107, sizeof(b_config_controle_z),
    SS_STRUCT, 0, 0, 0 },

  { "struct", "b_config", 13, 111, sizeof(b_config), SS_STRUCT, 0, 0, 0 },

  { "struct", "b_config_controle", 5, 124, sizeof(b_config_controle), SS_STRUCT,
    0, 0, 0 },

  { "struct", "struct_K8JPS3rkFE223YguxJpwYD", 2, 129, sizeof
    (struct_K8JPS3rkFE223YguxJpwYD), SS_STRUCT, 0, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {

  { (NULL), 0, 0, 0, 0 },

  { "Elev", rt_offsetof(b_config_lancamento, Elev), 1, 6, 0 },

  { "Rlat", rt_offsetof(b_config_lancamento, Rlat), 1, 6, 0 },

  { "Rlong", rt_offsetof(b_config_lancamento, Rlong), 1, 6, 0 },

  { "Ralt", rt_offsetof(b_config_lancamento, Ralt), 1, 6, 0 },

  { "Azi", rt_offsetof(b_config_lancamento, Azi), 1, 6, 0 },

  { "Talt", rt_offsetof(b_config_lancamento, Talt), 1, 0, 0 },

  { "Tesp", rt_offsetof(b_config_lancamento, Tesp), 1, 0, 0 },

  { "Hsub", rt_offsetof(b_config_lancamento, Hsub), 1, 0, 0 },

  { "Hmet", rt_offsetof(b_config_lancamento, Hmet), 1, 0, 0 },

  { "Rtemp", rt_offsetof(b_config_lancamento, Rtemp), 1, 0, 0 },

  { "Rde", rt_offsetof(b_config_lancamento, Rde), 1, 0, 0 },

  { "Dbal", rt_offsetof(b_config_lancamento, Dbal), 1, 6, 0 },

  { "Tbal", rt_offsetof(b_config_lancamento, Tbal), 1, 6, 0 },

  { "Pbal", rt_offsetof(b_config_lancamento, Pbal), 1, 6, 0 },

  { "Phi0", rt_offsetof(b_config_lancamento, Phi0), 1, 6, 0 },

  { "Mf", rt_offsetof(b_config_inercia, Mf), 1, 6, 0 },

  { "Xf", rt_offsetof(b_config_inercia, Xf), 1, 6, 0 },

  { "Yf", rt_offsetof(b_config_inercia, Yf), 1, 6, 0 },

  { "Zf", rt_offsetof(b_config_inercia, Zf), 1, 6, 0 },

  { "Ixf", rt_offsetof(b_config_inercia, Ixf), 1, 6, 0 },

  { "Iyf", rt_offsetof(b_config_inercia, Iyf), 1, 6, 0 },

  { "Izf", rt_offsetof(b_config_inercia, Izf), 1, 6, 0 },

  { "Ixyf", rt_offsetof(b_config_inercia, Ixyf), 1, 6, 0 },

  { "Ixzf", rt_offsetof(b_config_inercia, Ixzf), 1, 6, 0 },

  { "Iyzf", rt_offsetof(b_config_inercia, Iyzf), 1, 6, 0 },

  { "Fgrot", rt_offsetof(b_config_inercia, Fgrot), 1, 6, 0 },

  { "Fog", rt_offsetof(b_config_inercia, Fog), 1, 6, 0 },

  { "Ixemp_fech", rt_offsetof(b_config_inercia, Ixemp_fech), 1, 6, 0 },

  { "Kc", rt_offsetof(b_config_inercia, Kc), 1, 6, 0 },

  { "Tabin", rt_offsetof(b_config_inercia, Tabin), 1, 6, 0 },

  { "Tabre", rt_offsetof(b_config_inercia, Tabre), 1, 6, 0 },

  { "A2", rt_offsetof(b_config_inercia, A2), 1, 6, 0 },

  { "A5", rt_offsetof(b_config_inercia, A5), 1, 6, 0 },

  { "A9", rt_offsetof(b_config_inercia, A9), 1, 6, 0 },

  { "A10", rt_offsetof(b_config_inercia, A10), 1, 6, 0 },

  { "Mp0", rt_offsetof(b_config_propelente, Mp0), 1, 6, 0 },

  { "Xp", rt_offsetof(b_config_propelente, Xp), 1, 6, 0 },

  { "Yp", rt_offsetof(b_config_propelente, Yp), 1, 6, 0 },

  { "Zp", rt_offsetof(b_config_propelente, Zp), 1, 6, 0 },

  { "Ixyp", rt_offsetof(b_config_propelente, Ixyp), 1, 0, 0 },

  { "Ixzp", rt_offsetof(b_config_propelente, Ixzp), 1, 0, 0 },

  { "Iyzp", rt_offsetof(b_config_propelente, Iyzp), 1, 0, 0 },

  { "Dp", rt_offsetof(b_config_propelente, Dp), 1, 0, 0 },

  { "Lp", rt_offsetof(b_config_propelente, Lp), 1, 0, 0 },

  { "Rop", rt_offsetof(b_config_propelente, Rop), 1, 0, 0 },

  { "Tb0", rt_offsetof(b_config_propelente, Tb0), 1, 0, 0 },

  { "T_trans", rt_offsetof(b_config_propelente, T_trans), 1, 6, 0 },

  { "E0", rt_offsetof(b_config_propelente, E0), 1, 6, 0 },

  { "Ye", rt_offsetof(b_config_propelente, Ye), 1, 6, 0 },

  { "Ze", rt_offsetof(b_config_propelente, Ze), 1, 6, 0 },

  { "Alfaj", rt_offsetof(b_config_propelente, Alfaj), 1, 0, 0 },

  { "Betaj", rt_offsetof(b_config_propelente, Betaj), 1, 0, 0 },

  { "Ae", rt_offsetof(b_config_propelente, Ae), 1, 6, 0 },

  { "Grot0", rt_offsetof(b_config_propelente, Grot0), 1, 6, 0 },

  { "Kcan", rt_offsetof(b_config_propelente, Kcan), 1, 0, 0 },

  { "Dr", rt_offsetof(b_config_geometria, Dr), 1, 6, 0 },

  { "Lb", rt_offsetof(b_config_geometria, Lb), 1, 6, 0 },

  { "Be", rt_offsetof(b_config_geometria, Be), 1, 0, 0 },

  { "Ce", rt_offsetof(b_config_geometria, Ce), 1, 6, 0 },

  { "Fe", rt_offsetof(b_config_geometria, Fe), 1, 6, 0 },

  { "De0", rt_offsetof(b_config_geometria, De0), 1, 6, 0 },

  { "Flat", rt_offsetof(b_config_geometria, Flat), 1, 0, 0 },

  { "Fnor", rt_offsetof(b_config_geometria, Fnor), 1, 6, 0 },

  { "Retemp", rt_offsetof(b_config_geometria, Retemp), 1, 0, 0 },

  { "Wabre", rt_offsetof(b_config_geometria, Wabre), 1, 0, 0 },

  { "Dalfog0", rt_offsetof(b_config_geometria, Dalfog0), 1, 6, 0 },

  { "Xt1", rt_offsetof(b_config_dados_part, Xt1), 1, 6, 0 },

  { "Xt2", rt_offsetof(b_config_dados_part, Xt2), 1, 6, 0 },

  { "Xt3", rt_offsetof(b_config_dados_part, Xt3), 1, 6, 0 },

  { "Xfim", rt_offsetof(b_config_dados_part, Xfim), 1, 6, 0 },

  { "Dlan", rt_offsetof(b_config_dados_part, Dlan), 1, 6, 0 },

  { "Ktubo", rt_offsetof(b_config_dados_part, Ktubo), 1, 6, 0 },

  { "Rt", rt_offsetof(b_config_dados_part, Rt), 1, 6, 0 },

  { "Lr", rt_offsetof(b_config_dados_part, Lr), 1, 6, 0 },

  { "Mir", rt_offsetof(b_config_dados_part, Mir), 1, 6, 0 },

  { "Xboca", rt_offsetof(b_config_dados_part, Xboca), 1, 6, 0 },

  { "Memp", rt_offsetof(b_config_dados_part, Memp), 1, 6, 0 },

  { "Cemp", rt_offsetof(b_config_dados_part, Cemp), 1, 6, 0 },

  { "Demp", rt_offsetof(b_config_dados_part, Demp), 1, 6, 0 },

  { "Aemp", rt_offsetof(b_config_dados_part, Aemp), 1, 6, 0 },

  { "Cemp0", rt_offsetof(b_config_dados_part, Cemp0), 1, 6, 0 },

  { "Cemp1", rt_offsetof(b_config_dados_part, Cemp1), 1, 6, 0 },

  { "Cemp2", rt_offsetof(b_config_dados_part, Cemp2), 1, 6, 0 },

  { "Cemp3", rt_offsetof(b_config_dados_part, Cemp3), 1, 6, 0 },

  { "Ixemp", rt_offsetof(b_config_dados_part, Ixemp), 1, 6, 0 },

  { "Fcdsub", rt_offsetof(b_config_dados_part, Fcdsub), 1, 6, 0 },

  { "Dsub", rt_offsetof(b_config_dados_part, Dsub), 1, 6, 0 },

  { "Msub", rt_offsetof(b_config_dados_part, Msub), 1, 6, 0 },

  { "Xac", rt_offsetof(b_config_dados_part, Xac), 1, 6, 0 },

  { "Yac", rt_offsetof(b_config_dados_part, Yac), 1, 6, 0 },

  { "Zac", rt_offsetof(b_config_dados_part, Zac), 1, 6, 0 },

  { "Tempo", rt_offsetof(b_config_empuxo, Tempo), 1, 7, 0 },

  { "Empuxo", rt_offsetof(b_config_empuxo, Empuxo), 1, 7, 0 },

  { "Grot", rt_offsetof(b_config_empuxo, Grot), 1, 7, 0 },

  { "altitude", rt_offsetof(b_config_vento, altitude), 1, 8, 0 },

  { "azimute", rt_offsetof(b_config_vento, azimute), 1, 8, 0 },

  { "velocidade", rt_offsetof(b_config_vento, velocidade), 1, 8, 0 },

  { "Mo", rt_offsetof(b_coef_canard, Mo), 1, 10, 0 },

  { "CNa", rt_offsetof(b_coef_canard, CNa), 1, 10, 0 },

  { "CMa", rt_offsetof(b_coef_canard, CMa), 1, 10, 0 },

  { "CA", rt_offsetof(b_coef_canard, CA), 1, 10, 0 },

  { "xCP", rt_offsetof(b_coef_canard, xCP), 1, 10, 0 },

  { "bias_phi", rt_offsetof(b_config_erros, bias_phi), 1, 0, 0 },

  { "bias_theta", rt_offsetof(b_config_erros, bias_theta), 1, 0, 0 },

  { "bias_psi", rt_offsetof(b_config_erros, bias_psi), 1, 0, 0 },

  { "controle_on", rt_offsetof(b_config_flags, controle_on), 1, 0, 0 },

  { "t0", rt_offsetof(b_config_controle_z, t0), 1, 0, 0 },

  { "roll_on", rt_offsetof(b_config_controle_z, roll_on), 1, 0, 0 },

  { "rollrate_on", rt_offsetof(b_config_controle_z, rollrate_on), 1, 0, 0 },

  { "rollrate_ref", rt_offsetof(b_config_controle_z, rollrate_ref), 1, 0, 0 },

  { "lancamento", rt_offsetof(b_config, lancamento), 4, 0, 0 },

  { "inercia", rt_offsetof(b_config, inercia), 5, 0, 0 },

  { "propelente", rt_offsetof(b_config, propelente), 6, 0, 0 },

  { "geometria", rt_offsetof(b_config, geometria), 7, 0, 0 },

  { "dados_part", rt_offsetof(b_config, dados_part), 8, 0, 0 },

  { "dados_empuxo", rt_offsetof(b_config, dados_empuxo), 9, 0, 0 },

  { "dados_vento", rt_offsetof(b_config, dados_vento), 10, 0, 0 },

  { "tabaer", rt_offsetof(b_config, tabaer), 1, 9, 0 },

  { "coef_canard", rt_offsetof(b_config, coef_canard), 11, 0, 0 },

  { "k_canard", rt_offsetof(b_config, k_canard), 1, 0, 0 },

  { "erros", rt_offsetof(b_config, erros), 12, 0, 0 },

  { "flags", rt_offsetof(b_config, flags), 13, 0, 0 },

  { "controle_z", rt_offsetof(b_config, controle_z), 14, 0, 0 },

  { "alvo", rt_offsetof(b_config_controle, alvo), 1, 2, 0 },

  { "dh_alvo", rt_offsetof(b_config_controle, dh_alvo), 1, 0, 0 },

  { "t_canard", rt_offsetof(b_config_controle, t_canard), 1, 0, 0 },

  { "cd_subm", rt_offsetof(b_config_controle, cd_subm), 1, 0, 0 },

  { "ganhos", rt_offsetof(b_config_controle, ganhos), 1, 4, 0 },

  { "config", rt_offsetof(struct_K8JPS3rkFE223YguxJpwYD, config), 15, 6, 0 },

  { "controle", rt_offsetof(struct_K8JPS3rkFE223YguxJpwYD, controle), 16, 6, 0 }
};

static rtwCAPI_DimensionMap rtDimensionMap[] = {

  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 },

  { rtwCAPI_VECTOR, 6, 2, 0 },

  { rtwCAPI_VECTOR, 8, 2, 0 },

  { rtwCAPI_VECTOR, 10, 2, 0 },

  { rtwCAPI_MATRIX_COL_MAJOR, 0, 2, 0 },

  { rtwCAPI_MATRIX_COL_MAJOR, 12, 2, 0 },

  { rtwCAPI_MATRIX_COL_MAJOR, 14, 2, 0 },

  { rtwCAPI_MATRIX_COL_MAJOR, 16, 2, 0 },

  { rtwCAPI_VECTOR, 18, 2, 0 }
};

static uint_T rtDimensionArray[] = {
  1,
  1,
  2,
  1,
  3,
  1,
  6,
  1,
  10,
  1,
  1,
  2,
  1,
  41,
  48,
  1,
  25,
  41,
  40,
  1
};

static const real_T rtcapiStoredFloats[] = {
  0.00083333333333333339, 0.0, 0.02, 1.0
};

static rtwCAPI_FixPtMap rtFixPtMap[] = {

  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0 },

  { static_cast<const void *>(&rtcapiStoredFloats[3]), static_cast<const void *>
    (&rtcapiStoredFloats[1]), rtwCAPI_FIX_UNIFORM_SCALING, 32, -30, 1 }
};

static rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {

  { static_cast<const void *>(&rtcapiStoredFloats[0]), static_cast<const void *>
    (&rtcapiStoredFloats[1]), 0, 0 },

  { static_cast<const void *>(&rtcapiStoredFloats[2]), static_cast<const void *>
    (&rtcapiStoredFloats[1]), 1, 0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {

  { rtBlockSignals, 58,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 25,
    rtModelParameters, 1 },

  { rtBlockStates, 8 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 324667875U,
    654425810U,
    1811968447U,
    3031874926U },
  (NULL), 0,
  0
};

const rtwCAPI_ModelMappingStaticInfo*
  mod_foggui_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

#ifndef HOST_CAPI_BUILD

void mod_foggui_InitializeDataMapInfo(RT_MODEL_mod_foggui_T *const mod_foggui_M,
  B_mod_foggui_T *mod_foggui_B, P_mod_foggui_T *mod_foggui_P, DW_mod_foggui_T
  *mod_foggui_DW)
{
  rtwCAPI_SetVersion(mod_foggui_M->DataMapInfo.mmi, 1);
  rtwCAPI_SetStaticMap(mod_foggui_M->DataMapInfo.mmi, &mmiStatic);
  rtwCAPI_SetLoggingStaticMap(mod_foggui_M->DataMapInfo.mmi, (NULL));
  mod_foggui_InitializeDataAddr(mod_foggui_M->DataMapInfo.dataAddress,
    mod_foggui_B, mod_foggui_P, mod_foggui_DW);
  rtwCAPI_SetDataAddressMap(mod_foggui_M->DataMapInfo.mmi,
    mod_foggui_M->DataMapInfo.dataAddress);
  mod_foggui_InitializeVarDimsAddr(mod_foggui_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(mod_foggui_M->DataMapInfo.mmi,
    mod_foggui_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetPath(mod_foggui_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(mod_foggui_M->DataMapInfo.mmi, (NULL));
  mod_foggui_InitializeLoggingFunctions(mod_foggui_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(mod_foggui_M->DataMapInfo.mmi,
    mod_foggui_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetInstanceLoggingInfo(mod_foggui_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArray(mod_foggui_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(mod_foggui_M->DataMapInfo.mmi, 0);
}

#else
#ifdef __cplusplus

extern "C" {

#endif

  void mod_foggui_host_InitializeDataMapInfo(mod_foggui_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    rtwCAPI_SetVersion(dataMap->mmi, 1);
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}
#endif
#endif

