#ifndef RTW_HEADER_mod_foggui_types_h_
#define RTW_HEADER_mod_foggui_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_b_config_lancamento_
#define DEFINED_TYPEDEF_FOR_b_config_lancamento_

typedef struct {
  real_T Elev;
  real_T Rlat;
  real_T Rlong;
  real_T Ralt;
  real_T Azi;
  real_T Talt;
  real_T Tesp;
  real_T Hsub;
  real_T Hmet;
  real_T Rtemp;
  real_T Rde;
  real_T Dbal;
  real_T Tbal;
  real_T Pbal;
  real_T Phi0;
} b_config_lancamento;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_controle_
#define DEFINED_TYPEDEF_FOR_b_config_controle_

typedef struct {
  real_T alvo[3];
  real_T dh_alvo;
  real_T t_canard;
  real_T cd_subm;
  real_T ganhos[10];
} b_config_controle;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_inercia_
#define DEFINED_TYPEDEF_FOR_b_config_inercia_

typedef struct {
  real_T Mf;
  real_T Xf;
  real_T Yf;
  real_T Zf;
  real_T Ixf;
  real_T Iyf;
  real_T Izf;
  real_T Ixyf;
  real_T Ixzf;
  real_T Iyzf;
  real_T Fgrot;
  real_T Fog;
  real_T Ixemp_fech;
  real_T Kc;
  real_T Tabin;
  real_T Tabre;
  real_T A2;
  real_T A5;
  real_T A9;
  real_T A10;
} b_config_inercia;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_propelente_
#define DEFINED_TYPEDEF_FOR_b_config_propelente_

typedef struct {
  real_T Mp0;
  real_T Xp;
  real_T Yp;
  real_T Zp;
  real_T Ixyp;
  real_T Ixzp;
  real_T Iyzp;
  real_T Dp;
  real_T Lp;
  real_T Rop;
  real_T Tb0;
  real_T T_trans;
  real_T E0;
  real_T Ye;
  real_T Ze;
  real_T Alfaj;
  real_T Betaj;
  real_T Ae;
  real_T Grot0;
  real_T Kcan;
} b_config_propelente;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_geometria_
#define DEFINED_TYPEDEF_FOR_b_config_geometria_

typedef struct {
  real_T Dr;
  real_T Lb;
  real_T Be;
  real_T Ce;
  real_T Fe;
  real_T De0;
  real_T Flat;
  real_T Fnor;
  real_T Retemp;
  real_T Wabre;
  real_T Dalfog0;
} b_config_geometria;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_dados_part_
#define DEFINED_TYPEDEF_FOR_b_config_dados_part_

typedef struct {
  real_T Xt1;
  real_T Xt2;
  real_T Xt3;
  real_T Xfim;
  real_T Dlan;
  real_T Ktubo;
  real_T Rt;
  real_T Lr;
  real_T Mir;
  real_T Xboca;
  real_T Memp;
  real_T Cemp;
  real_T Demp;
  real_T Aemp;
  real_T Cemp0;
  real_T Cemp1;
  real_T Cemp2;
  real_T Cemp3;
  real_T Ixemp;
  real_T Fcdsub;
  real_T Dsub;
  real_T Msub;
  real_T Xac;
  real_T Yac;
  real_T Zac;
} b_config_dados_part;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_empuxo_
#define DEFINED_TYPEDEF_FOR_b_config_empuxo_

typedef struct {
  real_T Tempo[41];
  real_T Empuxo[41];
  real_T Grot[41];
} b_config_empuxo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_vento_
#define DEFINED_TYPEDEF_FOR_b_config_vento_

typedef struct {
  real_T altitude[48];
  real_T azimute[48];
  real_T velocidade[48];
} b_config_vento;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_coef_canard_
#define DEFINED_TYPEDEF_FOR_b_coef_canard_

typedef struct {
  real_T Mo[40];
  real_T CNa[40];
  real_T CMa[40];
  real_T CA[40];
  real_T xCP[40];
} b_coef_canard;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_erros_
#define DEFINED_TYPEDEF_FOR_b_config_erros_

typedef struct {
  real_T bias_phi;
  real_T bias_theta;
  real_T bias_psi;
} b_config_erros;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_flags_
#define DEFINED_TYPEDEF_FOR_b_config_flags_

typedef struct {
  real_T controle_on;
} b_config_flags;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_controle_z_
#define DEFINED_TYPEDEF_FOR_b_config_controle_z_

typedef struct {
  real_T t0;
  real_T roll_on;
  real_T rollrate_on;
  real_T rollrate_ref;
} b_config_controle_z;

#endif

#ifndef DEFINED_TYPEDEF_FOR_b_config_
#define DEFINED_TYPEDEF_FOR_b_config_

typedef struct {
  b_config_lancamento lancamento;
  b_config_inercia inercia;
  b_config_propelente propelente;
  b_config_geometria geometria;
  b_config_dados_part dados_part;
  b_config_empuxo dados_empuxo;
  b_config_vento dados_vento;
  real_T tabaer[1025];
  b_coef_canard coef_canard;
  real_T k_canard;
  b_config_erros erros;
  b_config_flags flags;
  b_config_controle_z controle_z;
} b_config;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_K8JPS3rkFE223YguxJpwYD_
#define DEFINED_TYPEDEF_FOR_struct_K8JPS3rkFE223YguxJpwYD_

typedef struct {
  b_config config;
  b_config_controle controle;
} struct_K8JPS3rkFE223YguxJpwYD;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_nEeapCAtEjbC8LadNjeTbF_
#define DEFINED_TYPEDEF_FOR_struct_nEeapCAtEjbC8LadNjeTbF_

typedef struct {
  real_T dt;
  real_T dt_controle;
} struct_nEeapCAtEjbC8LadNjeTbF;

#endif

#ifndef struct_tag_skA4KFEZ4HPkJJBOYCrevdH
#define struct_tag_skA4KFEZ4HPkJJBOYCrevdH

struct tag_skA4KFEZ4HPkJJBOYCrevdH
{
  uint32_T SafeEq;
  uint32_T Absolute;
  uint32_T NaNBias;
  uint32_T NaNWithFinite;
  uint32_T FiniteWithNaN;
  uint32_T NaNWithNaN;
};

#endif

#ifndef typedef_skA4KFEZ4HPkJJBOYCrevdH_mod_foggui_T
#define typedef_skA4KFEZ4HPkJJBOYCrevdH_mod_foggui_T

typedef struct tag_skA4KFEZ4HPkJJBOYCrevdH skA4KFEZ4HPkJJBOYCrevdH_mod_foggui_T;

#endif

#ifndef struct_tag_srPvjfcx7mpxeOt6SLi9kSE
#define struct_tag_srPvjfcx7mpxeOt6SLi9kSE

struct tag_srPvjfcx7mpxeOt6SLi9kSE
{
  real32_T step_ini;
  real32_T step_mid;
  real32_T step_fim;
  real32_T tempo_step_ini;
  real32_T tempo_step_mid;
  real32_T epsilon_step;
  real32_T epsilon_altura;
  real32_T max_iteracoes;
};

#endif

#ifndef typedef_srPvjfcx7mpxeOt6SLi9kSE_mod_foggui_T
#define typedef_srPvjfcx7mpxeOt6SLi9kSE_mod_foggui_T

typedef struct tag_srPvjfcx7mpxeOt6SLi9kSE srPvjfcx7mpxeOt6SLi9kSE_mod_foggui_T;

#endif

#ifndef struct_tag_s8zZSU4DcwnDyW5HgyKzKEG
#define struct_tag_s8zZSU4DcwnDyW5HgyKzKEG

struct tag_s8zZSU4DcwnDyW5HgyKzKEG
{
  real32_T S;
  real32_T Cwss[41];
  real32_T Massa;
  real32_T Cdadjsm;
  real32_T Cd_fac_eng;
  real32_T Delta_ejec;
};

#endif

#ifndef typedef_s8zZSU4DcwnDyW5HgyKzKEG_mod_foggui_T
#define typedef_s8zZSU4DcwnDyW5HgyKzKEG_mod_foggui_T

typedef struct tag_s8zZSU4DcwnDyW5HgyKzKEG s8zZSU4DcwnDyW5HgyKzKEG_mod_foggui_T;

#endif

#ifndef struct_tag_sEVXbkLo0N9NSyeYRxwQseC
#define struct_tag_sEVXbkLo0N9NSyeYRxwQseC

struct tag_sEVXbkLo0N9NSyeYRxwQseC
{
  real_T Ateps;
  real_T Dmach;
  real_T Fcd;
  real_T G0;
  real_T Ldel;
  real_T P0;
  real_T Rg;
  real_T Rgas;
  real_T Wg;
};

#endif

#ifndef typedef_sEVXbkLo0N9NSyeYRxwQseC_mod_foggui_T
#define typedef_sEVXbkLo0N9NSyeYRxwQseC_mod_foggui_T

typedef struct tag_sEVXbkLo0N9NSyeYRxwQseC sEVXbkLo0N9NSyeYRxwQseC_mod_foggui_T;

#endif

#ifndef struct_tag_sq1Qru32xi5xJTo6FdWoaIC
#define struct_tag_sq1Qru32xi5xJTo6FdWoaIC

struct tag_sq1Qru32xi5xJTo6FdWoaIC
{
  real_T A1;
  real_T A11;
  real_T A3;
  real_T A6;
  real_T A8;
  real_T Ar;
  real_T Atlin0;
  real_T Dcdsep;
  int8_T Fesp;
  real_T Ltab;
  real_T Msep;
  real_T Nova_trans;
  int8_T Pit0;
  real_T Tfq;
  real_T Tsep;
};

#endif

#ifndef typedef_sq1Qru32xi5xJTo6FdWoaIC_mod_foggui_T
#define typedef_sq1Qru32xi5xJTo6FdWoaIC_mod_foggui_T

typedef struct tag_sq1Qru32xi5xJTo6FdWoaIC sq1Qru32xi5xJTo6FdWoaIC_mod_foggui_T;

#endif

#ifndef struct_tag_sPym3pucFKRcIQmClJIeg
#define struct_tag_sPym3pucFKRcIQmClJIeg

struct tag_sPym3pucFKRcIQmClJIeg
{
  real_T Dtemp4;
  real_T Gfi;
  real_T Hstrat0;
  real_T Hstrat1;
  real_T Hstrat2;
  real_T Hstrat3;
  real_T Hstrat4;
  real_T Hstrat5;
  real_T Htrop;
  real_T Rfi;
  real_T Ro0;
  real_T Rostrat0;
  real_T Rotrop0;
  real_T T0;
  real_T Tatm;
  real_T Tstrat0;
  real_T Ttrop;
};

#endif

#ifndef typedef_sPym3pucFKRcIQmClJIeg_mod_foggui_T
#define typedef_sPym3pucFKRcIQmClJIeg_mod_foggui_T

typedef struct tag_sPym3pucFKRcIQmClJIeg sPym3pucFKRcIQmClJIeg_mod_foggui_T;

#endif

#ifndef struct_tag_sjTpbHoFvn1bLMMDbtjcivH
#define struct_tag_sjTpbHoFvn1bLMMDbtjcivH

struct tag_sjTpbHoFvn1bLMMDbtjcivH
{
  real_T Crlat;
  real_T Srlat;
};

#endif

#ifndef typedef_sjTpbHoFvn1bLMMDbtjcivH_mod_foggui_T
#define typedef_sjTpbHoFvn1bLMMDbtjcivH_mod_foggui_T

typedef struct tag_sjTpbHoFvn1bLMMDbtjcivH sjTpbHoFvn1bLMMDbtjcivH_mod_foggui_T;

#endif

#ifndef struct_tag_sHahOnMXbvRg70ubtDVo2tE
#define struct_tag_sHahOnMXbvRg70ubtDVo2tE

struct tag_sHahOnMXbvRg70ubtDVo2tE
{
  real_T altitudes[48];
  real_T norte[48];
  real_T leste[48];
};

#endif

#ifndef typedef_sHahOnMXbvRg70ubtDVo2tE_mod_foggui_T
#define typedef_sHahOnMXbvRg70ubtDVo2tE_mod_foggui_T

typedef struct tag_sHahOnMXbvRg70ubtDVo2tE sHahOnMXbvRg70ubtDVo2tE_mod_foggui_T;

#endif

#ifndef struct_tag_sJCxfmxS8gBOONUZjbjUd9E
#define struct_tag_sJCxfmxS8gBOONUZjbjUd9E

struct tag_sJCxfmxS8gBOONUZjbjUd9E
{
  boolean_T CaseSensitivity;
  boolean_T StructExpand;
  char_T PartialMatching[6];
  boolean_T IgnoreNulls;
};

#endif

#ifndef typedef_sJCxfmxS8gBOONUZjbjUd9E_mod_foggui_T
#define typedef_sJCxfmxS8gBOONUZjbjUd9E_mod_foggui_T

typedef struct tag_sJCxfmxS8gBOONUZjbjUd9E sJCxfmxS8gBOONUZjbjUd9E_mod_foggui_T;

#endif

#ifndef struct_tag_sqGkV3LOf3ZeiqHmG7NW6GD
#define struct_tag_sqGkV3LOf3ZeiqHmG7NW6GD

struct tag_sqGkV3LOf3ZeiqHmG7NW6GD
{
  b_config_lancamento lancamento;
  b_config_inercia inercia;
  b_config_propelente propelente;
  b_config_geometria geometria;
  b_config_dados_part dados_part;
  sEVXbkLo0N9NSyeYRxwQseC_mod_foggui_T cte;
  sq1Qru32xi5xJTo6FdWoaIC_mod_foggui_T aero;
  sPym3pucFKRcIQmClJIeg_mod_foggui_T atmosf;
  sjTpbHoFvn1bLMMDbtjcivH_mod_foggui_T tip_off;
  sHahOnMXbvRg70ubtDVo2tE_mod_foggui_T ventos;
  real_T Dbat[101];
  real_T Hbat[101];
  real_T Lbat[101];
  real_T Tbat[101];
  real_T E1[41];
  real_T Tb[41];
  real_T E2[41];
  real_T Eb[41];
  real_T G1[41];
  real_T Ib[41];
  real_T Gbv[41];
  real_T b_I[20];
  real_T Ab[2];
  real_T Ac1[2];
  real_T Tc[2];
  real_T C[1025];
};

#endif

#ifndef typedef_sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T
#define typedef_sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T

typedef struct tag_sqGkV3LOf3ZeiqHmG7NW6GD sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T;

#endif

#ifndef typedef_Traj_mod_foggui_T
#define typedef_Traj_mod_foggui_T

typedef struct {
  sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T modelo;
  real_T Fase_fim;
  real_T Apo;
  real_T Pit0;
  real_T Maxv;
  real_T H;
  real_T Htabv;
  real_T Flw;
  real_T Refcam;
  real_T Retrot;
  real_T Vhor[2];
  real_T Tfim;
  real_T Vwx;
  real_T Vwy;
  real_T Vwz;
  real_T T_emp;
  real_T Phi;
  real_T Teta;
  real_T Psi;
  real_T Qt1;
  real_T Qt2;
  real_T Qt3;
  real_T Qt4;
  real_T Wx;
  real_T Wy;
  real_T Wz;
  real_T Wx_p;
  real_T Wy_p;
  real_T Wz_p;
  real_T Vx;
  real_T Vy;
  real_T Vz;
  real_T Vx_p;
  real_T Vy_p;
  real_T Vz_p;
  real_T Vax;
  real_T Vay;
  real_T Vaz;
  real_T Vxh;
  real_T Vyh;
  real_T Vzh;
  real_T Dlat;
  real_T Dlong;
  real_T Dalt;
  real_T Fax;
  real_T Fay;
  real_T Faz;
  real_T Max;
  real_T May;
  real_T Maz;
  real_T Z;
  real_T Tant;
  real_T Kb;
  real_T Kc;
  real_T Rot0;
  real_T Gir0;
  real_T Cphia;
  real_T Fgrot;
  real_T Tempo;
  real_T Dkw;
  real_T Kw;
  real_T Kh;
  real_T Ksub;
  real_T Vxfmr;
  real_T Hkeep;
  real_T Van;
  real_T Alfap;
  real_T Alfa1;
  real_T Alfa2;
  real_T Alfa3;
  real_T Alfa4;
  real_T Alfab;
  real_T Dkh;
  real_T Fesp;
  real_T Alfat;
  real_T Betat;
  real_T Tetap;
  real_T Psip;
  real_T Wytp;
  real_T Wztp;
  real_T Vytp;
  real_T Vztp;
  real_T Wla;
  real_T Wno;
  real_T Cno;
  real_T Cla;
  real_T Cmno;
  real_T Cmla;
  real_T Cnow;
  real_T Cnoap;
  real_T Sphia;
  real_T Cmlas;
  real_T Cmlaw;
  real_T Cmlaap;
  real_T Root;
  real_T Cna;
  real_T Cnq;
  real_T Cnap;
  real_T Cma;
  real_T Cmq;
  real_T Cmap;
  real_T Cnae;
  real_T Lcpb;
  real_T Lcpe;
  real_T Tgrot;
  real_T Tabin;
  real_T Tabre;
  real_T Ttubo;
  real_T Vx_pmin;
  real_T Wtubo;
  real_T Vmax;
  real_T Hapo;
  real_T Hejec;
  real_T Vx_pmax;
  real_T Al11;
  real_T Al21;
  real_T Al31;
  real_T Al12;
  real_T Al22;
  real_T Al32;
  real_T Sreta;
  real_T Creta;
  real_T Slat;
  real_T Clat;
  real_T Rb;
  real_T T;
  real_T Massa;
  real_T Ix;
  real_T Iy;
  real_T Iz;
  real_T Ixy;
  real_T Ixz;
  real_T Iyz;
  real_T Jxx;
  real_T Jyy;
  real_T Jzz;
  real_T Jxy;
  real_T Jxz;
  real_T Jyz;
  real_T Km0;
  real_T Km1;
  real_T Km2;
  real_T Xcm;
  real_T Ycm;
  real_T Zcm;
  real_T Xcmp;
  real_T Ycmp;
  real_T Zcmp;
  real_T Grot;
  real_T Roex;
  real_T Roey;
  real_T Roez;
  real_T Vm;
  real_T Ixd;
  real_T Iyd;
  real_T Izd;
  real_T Tx;
  real_T Acontr;
  real_T Linf;
  real_T Lsup;
  real_T Crgama;
  real_T Gb;
  real_T Sgamal;
  real_T Ll;
  real_T L11;
  real_T L12;
  real_T L13;
  real_T L21;
  real_T L22;
  real_T L23;
  real_T L31;
  real_T L32;
  real_T L33;
  real_T Eps;
  real_T F;
  real_T R;
  real_T Q;
  real_T M;
  real_T Rxr;
  real_T Ryr;
  real_T Rzr;
  real_T Delr;
  real_T Sp;
  real_T Sdlong;
  real_T Cdlong;
  real_T R13;
  real_T R23;
  real_T R33;
  real_T Hl;
  real_T Hmax;
  real_T Fat;
  real_T Rot;
  real_T Pit;
  real_T Gir;
  real_T Mod;
  real_T U;
  real_T List;
  real_T Parada;
  real_T Fdist;
  real_T Fang;
  real_T Fder;
  real_T Fcoef;
  real_T Fataq;
  boolean_T Fpf;
  real_T Rwx;
  real_T Rwy;
  real_T Rwz;
  real_T Az1;
  real_T Awz;
  real_T Nw;
  real_T Rsul[48];
  real_T Rles[48];
  real_T Ws0;
  real_T Wl0;
  real_T Wv0;
  real_T Hven;
  real_T Rzw;
  real_T Vwexp;
  real_T Vw1;
  real_T Alfaw;
  real_T Ta;
  real_T Ro;
  real_T Pa;
  real_T Vsom;
  real_T Wxl;
  real_T Wyl;
  real_T Wzl;
  real_T Kquat0;
  real_T Qt1_p;
  real_T Qt2_p;
  real_T Qt3_p;
  real_T Qt4_p;
  real_T Wbhx;
  real_T Wbhy;
  real_T Wbhz;
  real_T Wgxb;
  real_T Wgyb;
  real_T Wgzb;
  real_T Wgx;
  real_T Wgz;
  real_T Vwxb;
  real_T Vwyb;
  real_T Vwzb;
  real_T Dlat_p;
  real_T Dlong_p;
  real_T Dalt_p;
  real_T Frx;
  real_T Fry;
  real_T Frz;
  real_T Mrx;
  real_T Mry;
  real_T Mrz;
  real_T Matr;
  real_T Ll11;
  real_T Ll12;
  real_T Ll13;
  real_T Ll21;
  real_T Ll22;
  real_T Ll23;
  real_T Ll31;
  real_T Ll32;
  real_T Ll33;
  real_T A[9];
  real_T Rti;
  real_T Li;
  real_T Di;
  real_T Xi;
  real_T Zci;
  real_T Zcip;
  real_T Cgamai;
  real_T Sgamai;
  real_T Gamai;
  real_T Rcxi;
  real_T Rcyi;
  real_T Rczi;
  real_T Rocxip;
  real_T Rocyip;
  real_T Roczip;
  real_T Dicx;
  real_T Dicy;
  real_T Dicz;
  real_T Dipcx;
  real_T Dipcy;
  real_T Dipcz;
  real_T Frxi;
  real_T Fryi;
  real_T Frzi;
  real_T Mrxi;
  real_T Mryi;
  real_T Mrzi;
  real_T Kk;
  real_T Pf;
  real_T Qsi;
  real_T Sm;
  real_T Claw;
  real_T Lcp0;
  real_T Rot1;
  real_T Pit1;
  real_T Gir1;
  real_T Asm;
  real_T Acel;
  real_T Frot;
  real_T Cnab;
  real_T Xcp0;
  real_T Va;
  real_T Arpd;
  real_T Pd;
  real_T Fcdsep;
  real_T Whxb;
  real_T Cfx;
  real_T Cfy;
  real_T Cfz;
  real_T Cmx;
  real_T Cmy;
  real_T Cmz;
  real_T F_trans;
  real_T Rcpe;
  real_T Mach;
  real_T Contador;
  real_T Contador_aux;
  int32_T CanardON;
  real_T CanardAng1;
  real_T CanardAng2;
  real_T CanardAng3;
  real_T CanardAng4;
  real_T Cfx_c;
  real_T Cfy_c;
  real_T Cfz_c;
  real_T Cmx_c;
  real_T Cmz_c;
  real_T Cmy_c;
  real_T k_canard;
  b_coef_canard Coef_canard;
  real_T cfx_b;
  real_T cfy_b;
  real_T cfz_b;
  real_T cmx_b;
  real_T cmz_b;
  real_T cmy_b;
  real_T cfx_e;
  real_T cfy_e;
  real_T cfz_e;
  real_T cmx_e;
  real_T cmz_e;
  real_T cmy_e;
  real_T controle_z_t0;
  real_T controle_z_roll_on;
  real_T controle_z_rollrate_on;
  real_T controle_z_rollrate_ref;
} Traj_mod_foggui_T;

#endif

#ifndef struct_tag_syf7A5HdRUQxXfDjUTEKnuC
#define struct_tag_syf7A5HdRUQxXfDjUTEKnuC

struct tag_syf7A5HdRUQxXfDjUTEKnuC
{
  real_T Pi180;
  real_T Pis2;
  real_T Pi2;
  real_T Href;
  real_T Hdel;
  real_T Dpit0;
  real_T Wdel;
  real_T Wpdel;
  real_T Romin;
  real_T Atmin;
  real_T Kquat;
  real_T P0;
  real_T Smax;
  real_T Fase_fim;
  real_T Apo;
  real_T Pit0;
  real_T Maxv;
  real_T H;
  real_T Htabv;
  real_T Flw;
  real_T Refcam;
  real_T Retrot;
  real_T Vhor[2];
  real_T Tfim;
  real_T Vwx;
  real_T Vwy;
  real_T Vwz;
  real_T T_emp;
  sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T modelo;
  real_T Phi;
  real_T Teta;
  real_T Psi;
  real_T Qt1;
  real_T Qt2;
  real_T Qt3;
  real_T Qt4;
  real_T Wx;
  real_T Wy;
  real_T Wz;
  real_T Wx_p;
  real_T Wy_p;
  real_T Wz_p;
  real_T Vx;
  real_T Vy;
  real_T Vz;
  real_T Vx_p;
  real_T Vy_p;
  real_T Vz_p;
  real_T Vax;
  real_T Vay;
  real_T Vaz;
  real_T Vxh;
  real_T Vyh;
  real_T Vzh;
  real_T Dlat;
  real_T Dlong;
  real_T Dalt;
  real_T Fax;
  real_T Fay;
  real_T Faz;
  real_T Max;
  real_T May;
  real_T Maz;
  real_T Z;
  real_T Tant;
  real_T Kb;
  real_T Kc;
  real_T Rot0;
  real_T Gir0;
  real_T Cphia;
  real_T Fgrot;
  real_T Tempo;
  real_T Dkw;
  real_T Kw;
  real_T Kh;
  real_T Ksub;
  real_T Vxfmr;
  real_T Hkeep;
  real_T Van;
  real_T Alfap;
  real_T Alfa1;
  real_T Alfa2;
  real_T Alfa3;
  real_T Alfa4;
  real_T Alfab;
  real_T Dkh;
  real_T Fesp;
  real_T Alfat;
  real_T Betat;
  real_T Tetap;
  real_T Psip;
  real_T Wytp;
  real_T Wztp;
  real_T Vytp;
  real_T Vztp;
  real_T Wla;
  real_T Wno;
  real_T Cno;
  real_T Cla;
  real_T Cmno;
  real_T Cmla;
  real_T Cnow;
  real_T Cnoap;
  real_T Sphia;
  real_T Cmlas;
  real_T Cmlaw;
  real_T Cmlaap;
  real_T Root;
  real_T Cna;
  real_T Cnq;
  real_T Cnap;
  real_T Cma;
  real_T Cmq;
  real_T Cmap;
  real_T Cnae;
  real_T Lcpb;
  real_T Lcpe;
  real_T Tgrot;
  real_T Tabin;
  real_T Tabre;
  real_T Ttubo;
  real_T Vx_pmin;
  real_T Wtubo;
  real_T Vmax;
  real_T Hapo;
  real_T Hejec;
  real_T Vx_pmax;
  real_T Al11;
  real_T Al21;
  real_T Al31;
  real_T Al12;
  real_T Al22;
  real_T Al32;
  real_T Sreta;
  real_T Creta;
  real_T Slat;
  real_T Clat;
  real_T Rb;
  real_T T;
  real_T Massa;
  real_T Ix;
  real_T Iy;
  real_T Iz;
  real_T Ixy;
  real_T Ixz;
  real_T Iyz;
  real_T Jxx;
  real_T Jyy;
  real_T Jzz;
  real_T Jxy;
  real_T Jxz;
  real_T Jyz;
  real_T Km0;
  real_T Km1;
  real_T Km2;
  real_T Xcm;
  real_T Ycm;
  real_T Zcm;
  real_T Xcmp;
  real_T Ycmp;
  real_T Zcmp;
  real_T Grot;
  real_T Roex;
  real_T Roey;
  real_T Roez;
  real_T Vm;
  real_T Ixd;
  real_T Iyd;
  real_T Izd;
  real_T Tx;
  real_T Acontr;
  real_T Linf;
  real_T Lsup;
  real_T Crgama;
  real_T Gb;
  real_T Sgamal;
  real_T Ll;
  real_T L11;
  real_T L12;
  real_T L13;
  real_T L21;
  real_T L22;
  real_T L23;
  real_T L31;
  real_T L32;
  real_T L33;
  real_T Eps;
  real_T F;
  real_T R;
  real_T Q;
  real_T M;
  real_T Rxr;
  real_T Ryr;
  real_T Rzr;
  real_T Delr;
  real_T Sp;
  real_T Sdlong;
  real_T Cdlong;
  real_T R13;
  real_T R23;
  real_T R33;
  real_T Hl;
  real_T Hmax;
  real_T Fat;
  real_T Rot;
  real_T Pit;
  real_T Gir;
  real_T Mod;
  real_T U;
  real_T List;
  real_T Parada;
  real_T Fdist;
  real_T Fang;
  real_T Fder;
  real_T Fcoef;
  real_T Fataq;
  boolean_T Fpf;
  real_T Rwx;
  real_T Rwy;
  real_T Rwz;
  real_T Az1;
  real_T Awz;
  real_T Nw;
  real_T Rsul[48];
  real_T Rles[48];
  real_T Ws0;
  real_T Wl0;
  real_T Wv0;
  real_T Hven;
  real_T Rzw;
  real_T Vwexp;
  real_T Vw1;
  real_T Alfaw;
  real_T Ta;
  real_T Ro;
  real_T Pa;
  real_T Vsom;
  real_T Wxl;
  real_T Wyl;
  real_T Wzl;
  real_T Kquat0;
  real_T Qt1_p;
  real_T Qt2_p;
  real_T Qt3_p;
  real_T Qt4_p;
  real_T Wbhx;
  real_T Wbhy;
  real_T Wbhz;
  real_T Wgxb;
  real_T Wgyb;
  real_T Wgzb;
  real_T Wgx;
  real_T Wgz;
  real_T Vwxb;
  real_T Vwyb;
  real_T Vwzb;
  real_T Dlat_p;
  real_T Dlong_p;
  real_T Dalt_p;
  real_T Frx;
  real_T Fry;
  real_T Frz;
  real_T Mrx;
  real_T Mry;
  real_T Mrz;
  real_T Matr;
  real_T Ll11;
  real_T Ll12;
  real_T Ll13;
  real_T Ll21;
  real_T Ll22;
  real_T Ll23;
  real_T Ll31;
  real_T Ll32;
  real_T Ll33;
  real_T A[9];
  real_T Rti;
  real_T Li;
  real_T Di;
  real_T Xi;
  real_T Zci;
  real_T Zcip;
  real_T Cgamai;
  real_T Sgamai;
  real_T Gamai;
  real_T Rcxi;
  real_T Rcyi;
  real_T Rczi;
  real_T Rocxip;
  real_T Rocyip;
  real_T Roczip;
  real_T Dicx;
  real_T Dicy;
  real_T Dicz;
  real_T Dipcx;
  real_T Dipcy;
  real_T Dipcz;
  real_T Frxi;
  real_T Fryi;
  real_T Frzi;
  real_T Mrxi;
  real_T Mryi;
  real_T Mrzi;
  real_T Kk;
  real_T Pf;
  real_T Qsi;
  real_T Sm;
  real_T Claw;
  real_T Lcp0;
  real_T Rot1;
  real_T Pit1;
  real_T Gir1;
  real_T Asm;
  real_T Acel;
  real_T Frot;
  real_T Cnab;
  real_T Xcp0;
  real_T Va;
  real_T Arpd;
  real_T Pd;
  real_T Fcdsep;
  real_T Whxb;
  real_T Cfx;
  real_T Cfy;
  real_T Cfz;
  real_T Cmx;
  real_T Cmy;
  real_T Cmz;
  real_T F_trans;
  real_T Rcpe;
  real_T Contador;
  real_T Contador_aux;
  int32_T CanardON;
  real_T CanardAng1;
  real_T CanardAng2;
  real_T CanardAng3;
  real_T CanardAng4;
  real_T Cfx_c;
  real_T Cfy_c;
  real_T Cfz_c;
  real_T Cmx_c;
  real_T Cmz_c;
  real_T Cmy_c;
  real_T controle_z_roll_on;
  real_T controle_z_rollrate_on;
  real_T controle_z_rollrate_ref;
};

#endif

#ifndef typedef_syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T
#define typedef_syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T

typedef struct tag_syf7A5HdRUQxXfDjUTEKnuC syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T;

#endif

#ifndef SS_INT64
#define SS_INT64                       45
#endif

#ifndef SS_UINT64
#define SS_UINT64                      46
#endif

typedef struct P_mod_foggui_T_ P_mod_foggui_T;
typedef struct tag_RTM_mod_foggui_T RT_MODEL_mod_foggui_T;

#endif
