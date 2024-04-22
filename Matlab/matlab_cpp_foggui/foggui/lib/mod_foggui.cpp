#include "mod_foggui_capi.h"
#include "mod_foggui.h"
#include "mod_foggui_private.h"

static void rate_scheduler(RT_MODEL_mod_foggui_T *const mod_foggui_M);
static void rate_scheduler(RT_MODEL_mod_foggui_T *const mod_foggui_M)
{
  (mod_foggui_M->Timing.TaskCounters.TID[1])++;
  if ((mod_foggui_M->Timing.TaskCounters.TID[1]) > 23) {
    mod_foggui_M->Timing.TaskCounters.TID[1] = 0;
  }

  mod_foggui_M->Timing.sampleHits[1] = (mod_foggui_M->Timing.TaskCounters.TID[1]
    == 0);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      u1_0 = std::ceil(u1);
    } else {
      u1_0 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = std::abs(u0 / u1);
      if (std::abs(u1_0 - std::floor(u1_0 + 0.5)) <= DBL_EPSILON * u1_0) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

void mod_fogguiModelClass::mod_foggui_cosd_dln4qkicsy(real_T *x)
{
  int8_T n;
  real_T b_x;
  real_T absx;
  if (rtIsInf(*x) || rtIsNaN(*x)) {
    *x = (rtNaN);
  } else {
    b_x = rt_remd_snf(*x, 360.0);
    absx = std::abs(b_x);
    if (absx > 180.0) {
      if (b_x > 0.0) {
        b_x -= 360.0;
      } else {
        b_x += 360.0;
      }

      absx = std::abs(b_x);
    }

    if (absx <= 45.0) {
      b_x *= 0.017453292519943295;
      *x = std::cos(b_x);
    } else {
      if (absx <= 135.0) {
        if (b_x > 0.0) {
          b_x = (b_x - 90.0) * 0.017453292519943295;
          n = 1;
        } else {
          b_x = (b_x + 90.0) * 0.017453292519943295;
          n = -1;
        }
      } else if (b_x > 0.0) {
        b_x = (b_x - 180.0) * 0.017453292519943295;
        n = 2;
      } else {
        b_x = (b_x + 180.0) * 0.017453292519943295;
        n = -2;
      }

      if (n == 1) {
        *x = -std::sin(b_x);
      } else if (n == -1) {
        *x = std::sin(b_x);
      } else {
        *x = -std::cos(b_x);
      }
    }
  }
}

void mod_fogguiModelClass::mod_foggui_sind_nfvntbsefa(real_T *x)
{
  int8_T n;
  real_T c_x;
  real_T absx;
  if (rtIsInf(*x) || rtIsNaN(*x)) {
    *x = (rtNaN);
  } else {
    c_x = rt_remd_snf(*x, 360.0);
    absx = std::abs(c_x);
    if (absx > 180.0) {
      if (c_x > 0.0) {
        c_x -= 360.0;
      } else {
        c_x += 360.0;
      }

      absx = std::abs(c_x);
    }

    if (absx <= 45.0) {
      c_x *= 0.017453292519943295;
      *x = std::sin(c_x);
    } else {
      if (absx <= 135.0) {
        if (c_x > 0.0) {
          c_x = (c_x - 90.0) * 0.017453292519943295;
          n = 1;
        } else {
          c_x = (c_x + 90.0) * 0.017453292519943295;
          n = -1;
        }
      } else if (c_x > 0.0) {
        c_x = (c_x - 180.0) * 0.017453292519943295;
        n = 2;
      } else {
        c_x = (c_x + 180.0) * 0.017453292519943295;
        n = -2;
      }

      if (n == 1) {
        *x = std::cos(c_x);
      } else if (n == -1) {
        *x = -std::cos(c_x);
      } else {
        *x = -std::sin(c_x);
      }
    }
  }
}

void mod_fogguiModelClass::mod_foggui_circshift_ad3ayr23dy(real_T a[41])
{
  real_T buffer;
  int32_T k;
  buffer = a[40];
  for (k = 41; k > 1; k--) {
    a[k - 1] = a[k - 2];
  }

  a[0] = buffer;
}

void mod_fogguiModelClass::mod_foggui_circshift_ad3ayr23dys(real_T a[41])
{
  real_T buffer;
  int32_T b_k;
  buffer = a[0];
  for (b_k = 0; b_k < 40; b_k++) {
    a[b_k] = a[b_k + 1];
  }

  a[40] = buffer;
}

void mod_fogguiModelClass::mod_foggui_cosd_dln4qkicsyc(real_T x[48])
{
  int32_T k;
  int8_T n;
  real_T b_x;
  real_T absx;
  for (k = 0; k < 48; k++) {
    if (rtIsInf(x[k]) || rtIsNaN(x[k])) {
      b_x = (rtNaN);
    } else {
      b_x = rt_remd_snf(x[k], 360.0);
      absx = std::abs(b_x);
      if (absx > 180.0) {
        if (b_x > 0.0) {
          b_x -= 360.0;
        } else {
          b_x += 360.0;
        }

        absx = std::abs(b_x);
      }

      if (absx <= 45.0) {
        b_x *= 0.017453292519943295;
        b_x = std::cos(b_x);
      } else {
        if (absx <= 135.0) {
          if (b_x > 0.0) {
            b_x = (b_x - 90.0) * 0.017453292519943295;
            n = 1;
          } else {
            b_x = (b_x + 90.0) * 0.017453292519943295;
            n = -1;
          }
        } else if (b_x > 0.0) {
          b_x = (b_x - 180.0) * 0.017453292519943295;
          n = 2;
        } else {
          b_x = (b_x + 180.0) * 0.017453292519943295;
          n = -2;
        }

        if (n == 1) {
          b_x = -std::sin(b_x);
        } else if (n == -1) {
          b_x = std::sin(b_x);
        } else {
          b_x = -std::cos(b_x);
        }
      }
    }

    x[k] = b_x;
  }
}

void mod_fogguiModelClass::mod_foggui_sind_nfvntbsefaa(real_T x[48])
{
  int32_T k;
  int8_T n;
  real_T c_x;
  real_T absx;
  for (k = 0; k < 48; k++) {
    if (rtIsInf(x[k]) || rtIsNaN(x[k])) {
      c_x = (rtNaN);
    } else {
      c_x = rt_remd_snf(x[k], 360.0);
      absx = std::abs(c_x);
      if (absx > 180.0) {
        if (c_x > 0.0) {
          c_x -= 360.0;
        } else {
          c_x += 360.0;
        }

        absx = std::abs(c_x);
      }

      if (absx <= 45.0) {
        c_x *= 0.017453292519943295;
        c_x = std::sin(c_x);
      } else {
        if (absx <= 135.0) {
          if (c_x > 0.0) {
            c_x = (c_x - 90.0) * 0.017453292519943295;
            n = 1;
          } else {
            c_x = (c_x + 90.0) * 0.017453292519943295;
            n = -1;
          }
        } else if (c_x > 0.0) {
          c_x = (c_x - 180.0) * 0.017453292519943295;
          n = 2;
        } else {
          c_x = (c_x + 180.0) * 0.017453292519943295;
          n = -2;
        }

        if (n == 1) {
          c_x = std::cos(c_x);
        } else if (n == -1) {
          c_x = -std::cos(c_x);
        } else {
          c_x = -std::sin(c_x);
        }
      }
    }

    x[k] = c_x;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Update_modelo(real_T
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
  b_config_empuxo *config_dados_empuxo, const b_config_vento *config_dados_vento,
  const real_T config_tabaer[1025], sqGkV3LOf3ZeiqHmG7NW6GD_mod_foggui_T *modelo)
{
  b_config_inercia b_config_inercia_0;
  real_T A6;
  real_T A9;
  real_T Ro0;
  real_T Rotrop0;
  real_T E1[41];
  real_T G1[41];
  real_T G2[41];
  real_T E2[41];
  real_T Eb[41];
  real_T Gbv[41];
  real_T Ib[41];
  int32_T i;
  int8_T b_data[41];
  int8_T c_data[41];
  boolean_T x[41];
  int32_T idx;
  int32_T b_ii;
  real_T e[48];
  boolean_T x_0;
  int8_T ii_data_idx_0;
  int32_T b_size_idx_1;
  real_T A6_tmp;
  real_T b_a_tmp;
  real_T d_a_tmp;
  real_T c_a_tmp;
  real_T Eb_tmp;
  real_T A9_tmp;
  static const int32_T Dbat[101] = { 0, 100, 350, 750, 1250, 1750, 2250, 2750,
    3250, 3750, 4250, 4750, 5500, 6500, 7500, 8500, 9500, 14023, 15023, 15523,
    20023, 21023, 31023, 46023, 50023, 58023, 80023, 88023, 99023, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const real_T Hbat[101] = { -0.0385, -0.0008, -0.00675, -0.0084, -0.0082,
    -0.0078, -0.006, -0.0056, -0.0042, -0.0048, -0.0064, -0.0068, -0.0058,
    -0.0069, -0.0079, -0.0042, -0.006711462, -0.00644401533333,
    -0.00635996066667, 0.003931228, 0.00392358666667, 0.00219235866667,
    0.00220764133333, 0.0, -0.002, -0.003511462, 0.0, 0.00201528266667, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  boolean_T exitg1;
  int32_T exitg2;
  b_config_inercia_0 = *config_inercia;
  b_config_inercia_0.Fgrot = 1.0;
  b_config_inercia_0.Fog = 1.0;
  b_config_inercia_0.Ixemp_fech = config_dados_part->Memp * config_geometria->Dr
    * config_geometria->Dr;
  b_config_inercia_0.Kc = 1.0;
  b_config_inercia_0.Tabin = 1.0E+98;
  b_config_inercia_0.Tabre = 1.0E+98;
  A6_tmp = 2.0 * config_geometria->Dr + config_geometria->Be;
  A6 = A6_tmp / (4.0 * config_geometria->Dr);
  A9_tmp = config_geometria->Lb / config_geometria->Dr;
  A9 = A9_tmp * 2.0;
  b_config_inercia_0.A2 = 0.925;
  b_config_inercia_0.A5 = 0.538;
  b_config_inercia_0.A9 = A9;
  b_config_inercia_0.A10 = 0.925 * A9;
  A9 = (config_lancamento_Rtemp + 273.16) + 0.0065 * config_lancamento_Hmet;
  Ro0 = rt_powd_snf((config_lancamento_Rtemp + 273.16) / A9, -4.2561) *
    config_lancamento_Rde;
  Rotrop0 = rt_powd_snf((A9 - 71.5) / A9, 4.2561) * Ro0;
  modelo->tip_off.Crlat = config_lancamento_Rlat;
  mod_foggui_cosd_dln4qkicsy(&modelo->tip_off.Crlat);
  modelo->tip_off.Srlat = config_lancamento_Rlat;
  mod_foggui_sind_nfvntbsefa(&modelo->tip_off.Srlat);
  b_a_tmp = config_inercia->Yf - config_propelente->Yp;
  c_a_tmp = config_inercia->Zf - config_propelente->Zp;
  d_a_tmp = config_propelente->Xp - config_inercia->Xf;
  std::memcpy(&E1[0], &config_dados_empuxo->Empuxo[0], 41U * sizeof(real_T));
  mod_foggui_circshift_ad3ayr23dy(E1);
  std::memcpy(&G1[0], &config_dados_empuxo->Grot[0], 41U * sizeof(real_T));
  mod_foggui_circshift_ad3ayr23dy(G1);
  std::memcpy(&G2[0], &G1[0], 41U * sizeof(real_T));
  mod_foggui_circshift_ad3ayr23dys(G2);
  G2[0] = 0.0;
  b_ii = 0;
  exitg1 = false;
  while ((!exitg1) && (b_ii < 41)) {
    if (config_dados_empuxo->Tempo[b_ii] > 1.0E+10) {
      ii_data_idx_0 = static_cast<int8_T>((b_ii + 1));
      exitg1 = true;
    } else {
      b_ii++;
    }
  }

  std::memcpy(&E2[0], &E1[0], 41U * sizeof(real_T));
  mod_foggui_circshift_ad3ayr23dys(E2);
  std::memset(&Eb[0], 0, 41U * sizeof(real_T));
  std::memset(&Gbv[0], 0, 41U * sizeof(real_T));
  std::memset(&Ib[0], 0, 41U * sizeof(real_T));
  b_ii = 0;
  do {
    exitg2 = 0;
    i = ii_data_idx_0 - 1;
    if (b_ii <= i) {
      i = ii_data_idx_0 - b_ii;
      Ib[i - 1] = (config_dados_empuxo->Tempo[i] - config_dados_empuxo->Tempo[i
                   - 1]) * (E1[i] + E2[i]) / 2.0 + Ib[i];
      b_ii++;
    } else {
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  for (idx = 1; idx - 1 <= i; idx++) {
    Eb_tmp = config_dados_empuxo->Tempo[idx] - config_dados_empuxo->Tempo[idx -
      1];
    Eb[idx] = (E2[idx] - E1[idx]) / Eb_tmp;
    Gbv[idx] = (G2[idx] - G1[idx]) / Eb_tmp;
  }

  idx = 0;
  for (b_ii = 0; b_ii < 41; b_ii++) {
    x_0 = rtIsNaN(Eb[b_ii]);
    if (x_0) {
      idx++;
    }

    x[b_ii] = x_0;
  }

  b_size_idx_1 = idx;
  idx = 0;
  for (b_ii = 0; b_ii < 41; b_ii++) {
    if (x[b_ii]) {
      b_data[idx] = static_cast<int8_T>((b_ii + 1));
      idx++;
    }
  }

  for (i = 0; i < b_size_idx_1; i++) {
    Eb[b_data[i] - 1] = 0.0;
  }

  idx = 0;
  for (b_ii = 0; b_ii < 41; b_ii++) {
    x_0 = rtIsNaN(Gbv[b_ii]);
    if (x_0) {
      idx++;
    }

    x[b_ii] = x_0;
  }

  b_size_idx_1 = idx;
  idx = 0;
  for (b_ii = 0; b_ii < 41; b_ii++) {
    if (x[b_ii]) {
      c_data[idx] = static_cast<int8_T>((b_ii + 1));
      idx++;
    }
  }

  for (i = 0; i < b_size_idx_1; i++) {
    Gbv[c_data[i] - 1] = 0.0;
  }

  std::memcpy(&e[0], &config_dados_vento->azimute[0], 48U * sizeof(real_T));
  mod_foggui_cosd_dln4qkicsyc(e);
  for (i = 0; i < 48; i++) {
    modelo->ventos.norte[i] = config_dados_vento->velocidade[i] * e[i];
    e[i] = config_dados_vento->azimute[i];
  }

  mod_foggui_sind_nfvntbsefaa(e);
  modelo->lancamento.Elev = config_lancamento_Elev;
  modelo->lancamento.Rlat = config_lancamento_Rlat;
  modelo->lancamento.Rlong = config_lancamento_Rlong;
  modelo->lancamento.Ralt = config_lancamento_Ralt;
  modelo->lancamento.Azi = config_lancamento_Azi;
  modelo->lancamento.Talt = config_lancamento_Talt;
  modelo->lancamento.Tesp = config_lancamento_Tesp;
  modelo->lancamento.Hsub = config_lancamento_Hsub;
  modelo->lancamento.Hmet = config_lancamento_Hmet;
  modelo->lancamento.Rtemp = config_lancamento_Rtemp;
  modelo->lancamento.Rde = config_lancamento_Rde;
  modelo->lancamento.Dbal = config_lancamento_Dbal;
  modelo->lancamento.Tbal = config_lancamento_Tbal;
  modelo->lancamento.Pbal = config_lancamento_Pbal;
  modelo->lancamento.Phi0 = config_lancamento_Phi0;
  modelo->inercia = b_config_inercia_0;
  modelo->propelente = *config_propelente;
  modelo->geometria = *config_geometria;
  modelo->dados_part = *config_dados_part;
  modelo->cte.Ateps = 1.0E-6;
  modelo->cte.Dmach = 0.1;
  modelo->cte.Fcd = 1.0;
  modelo->cte.G0 = 9.80665;
  modelo->cte.Ldel = 0.0001;
  modelo->cte.P0 = 94540.0;
  modelo->cte.Rg = 6.371E+6;
  modelo->cte.Rgas = 287.043;
  modelo->cte.Wg = 7.292E-5;
  modelo->aero.A1 = A9_tmp;
  if (config_geometria->Fe < 0.0) {
    A9_tmp = -1.0;
  } else if (config_geometria->Fe > 0.0) {
    A9_tmp = 1.0;
  } else if (config_geometria->Fe == 0.0) {
    A9_tmp = 0.0;
  } else {
    A9_tmp = (rtNaN);
  }

  modelo->aero.A11 = config_geometria->Flat * A9_tmp;
  modelo->aero.A3 = config_geometria->Lb / config_geometria->Dr * 2.0 * 0.925;
  modelo->aero.A6 = A6;
  modelo->aero.A8 = (config_geometria->Be * config_geometria->Be / (A6_tmp *
    A6_tmp * 3.0) + 1.0) * A6;
  modelo->aero.Ar = config_geometria->Dr * config_geometria->Dr *
    3.1415926535897931 / 4.0;
  modelo->aero.Atlin0 = 0.034906585039886591;
  modelo->aero.Dcdsep = 0.0;
  modelo->aero.Fesp = 0;
  modelo->aero.Ltab = 41.0;
  modelo->aero.Msep = config_inercia->Mf;
  modelo->aero.Nova_trans = 0.0;
  modelo->aero.Pit0 = 1;
  modelo->aero.Tfq = config_propelente->Tb0;
  modelo->aero.Tsep = 1.0E+99;
  modelo->atmosf.Dtemp4 = 0.75178452339776136 * A9 - (A9 - 71.5);
  modelo->atmosf.Gfi = 9.80665;
  modelo->atmosf.Hstrat0 = 20000.0;
  modelo->atmosf.Hstrat1 = 24384.0;
  modelo->atmosf.Hstrat2 = 51816.0;
  modelo->atmosf.Hstrat3 = 82296.0;
  modelo->atmosf.Hstrat4 = 96012.0;
  modelo->atmosf.Hstrat5 = 198120.0;
  modelo->atmosf.Htrop = 11000.0;
  modelo->atmosf.Rfi = 6.337838E+6;
  modelo->atmosf.Ro0 = Ro0;
  modelo->atmosf.Rostrat0 = std::exp(9.80665 / ((A9 - 71.5) * 287.043) * -9000.0)
    * Rotrop0;
  modelo->atmosf.Rotrop0 = Rotrop0;
  modelo->atmosf.T0 = A9;
  modelo->atmosf.Tatm = 0.0;
  modelo->atmosf.Tstrat0 = A9 - 71.5;
  modelo->atmosf.Ttrop = A9 - 71.5;
  for (i = 0; i < 48; i++) {
    modelo->ventos.altitudes[i] = config_dados_vento->altitude[i] +
      config_lancamento_Hmet;
    modelo->ventos.leste[i] = config_dados_vento->velocidade[i] * e[i];
  }

  for (i = 0; i < 101; i++) {
    modelo->Dbat[i] = Dbat[i];
    modelo->Hbat[i] = Hbat[i];
    modelo->Lbat[i] = Hbat[i];
    modelo->Tbat[i] = Hbat[i];
  }

  std::memcpy(&modelo->E1[0], &E1[0], 41U * sizeof(real_T));
  std::memcpy(&modelo->Tb[0], &config_dados_empuxo->Tempo[0], 41U * sizeof
              (real_T));
  std::memcpy(&modelo->E2[0], &E2[0], 41U * sizeof(real_T));
  std::memcpy(&modelo->Eb[0], &Eb[0], 41U * sizeof(real_T));
  std::memcpy(&modelo->G1[0], &G1[0], 41U * sizeof(real_T));
  std::memcpy(&modelo->Ib[0], &Ib[0], 41U * sizeof(real_T));
  std::memcpy(&modelo->Gbv[0], &Gbv[0], 41U * sizeof(real_T));
  modelo->b_I[0] = 6.2831853071795862 * config_propelente->Rop *
    config_propelente->Lp;
  modelo->b_I[1] = config_propelente->Dp * config_propelente->Dp / 4.0;
  modelo->b_I[2] = config_propelente->Lp * config_propelente->Lp / 12.0;
  modelo->b_I[3] = 0.0;
  modelo->b_I[4] = 0.0;
  modelo->b_I[5] = config_inercia->Xf * config_inercia->Mf;
  modelo->b_I[6] = config_inercia->Yf * config_inercia->Mf;
  modelo->b_I[7] = config_inercia->Zf * config_inercia->Mf;
  modelo->b_I[8] = (b_a_tmp * b_a_tmp + c_a_tmp * c_a_tmp) * config_inercia->Mf;
  modelo->b_I[9] = (d_a_tmp * d_a_tmp + b_a_tmp * b_a_tmp) * config_inercia->Mf;
  modelo->b_I[10] = (d_a_tmp * d_a_tmp + c_a_tmp * c_a_tmp) * config_inercia->Mf;
  A6_tmp = b_a_tmp * config_inercia->Mf;
  modelo->b_I[11] = A6_tmp * d_a_tmp;
  modelo->b_I[12] = c_a_tmp * config_inercia->Mf * d_a_tmp;
  modelo->b_I[13] = A6_tmp * c_a_tmp;
  A6_tmp = config_inercia->Mf * config_inercia->Mf;
  modelo->b_I[14] = (b_a_tmp * b_a_tmp + c_a_tmp * c_a_tmp) * A6_tmp;
  modelo->b_I[15] = (b_a_tmp * b_a_tmp + d_a_tmp * d_a_tmp) * A6_tmp;
  modelo->b_I[16] = (c_a_tmp * c_a_tmp + d_a_tmp * d_a_tmp) * A6_tmp;
  modelo->b_I[17] = config_propelente->Ixyp / config_propelente->Mp0;
  modelo->b_I[18] = config_propelente->Ixzp / config_propelente->Mp0;
  modelo->b_I[19] = config_propelente->Iyzp / config_propelente->Mp0;
  modelo->Ab[0] = 0.0;
  modelo->Ac1[0] = 0.0;
  modelo->Tc[0] = 0.0;
  modelo->Ab[1] = 0.0;
  modelo->Ac1[1] = 0.0;
  modelo->Tc[1] = 1.0E+99;
  std::memcpy(&modelo->C[0], &config_tabaer[0], 1025U * sizeof(real_T));
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = std::sqrt(y * y + 1.0) * a;
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

void mod_fogguiModelClass::mod_foggui_hypot(const real_T x[48], const real_T y
  [48], real_T r[48])
{
  int32_T k;
  for (k = 0; k < 48; k++) {
    r[k] = rt_hypotd_snf(x[k], y[k]);
  }
}

void mod_fogguiModelClass::mod_foggui_eye(real_T b_I[9])
{
  std::memset(&b_I[0], 0, 9U * sizeof(real_T));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
}

void mod_fogguiModelClass::mod_foggui_Traj_Inicializa_traj(Traj_mod_foggui_T *o,
  real_T config_lancamento_Elev, real_T config_lancamento_Rlat, real_T
  config_lancamento_Rlong, real_T config_lancamento_Ralt, real_T
  config_lancamento_Azi, real_T config_lancamento_Talt, real_T
  config_lancamento_Tesp, real_T config_lancamento_Hsub, real_T
  config_lancamento_Hmet, real_T config_lancamento_Rtemp, real_T
  config_lancamento_Rde, real_T config_lancamento_Dbal, real_T
  config_lancamento_Tbal, real_T config_lancamento_Pbal, real_T
  config_lancamento_Phi0, const b_config_inercia *config_inercia, const
  b_config_propelente *config_propelente, const b_config_geometria
  *config_geometria, const b_config_dados_part *config_dados_part, const
  b_config_empuxo *config_dados_empuxo, const b_config_vento *config_dados_vento,
  const real_T config_tabaer[1025], const b_coef_canard *config_coef_canard,
  const b_config_controle_z config_controle_z)
{
  real_T Wsul[48];
  real_T Rsul_[48];
  real_T Rles_[48];
  real_T Rg;
  int32_T i;
  int32_T i_0;
  int8_T ii_data_idx_0;
  int32_T tmp;
  boolean_T exitg1;
  mod_foggui_Traj_Update_modelo(config_lancamento_Elev, config_lancamento_Rlat,
    config_lancamento_Rlong, config_lancamento_Ralt, config_lancamento_Azi,
    config_lancamento_Talt, config_lancamento_Tesp, config_lancamento_Hsub,
    config_lancamento_Hmet, config_lancamento_Rtemp, config_lancamento_Rde,
    config_lancamento_Dbal, config_lancamento_Tbal, config_lancamento_Pbal,
    config_lancamento_Phi0, config_inercia, config_propelente, config_geometria,
    config_dados_part, config_dados_empuxo, config_dados_vento, config_tabaer,
    &mod_foggui_B.modelo);
  o->Vxfmr = 0.0;
  mod_foggui_hypot(mod_foggui_B.modelo.ventos.norte,
                   mod_foggui_B.modelo.ventos.leste, Wsul);
  i = 48;
  exitg1 = false;
  while ((!exitg1) && (i > 0)) {
    if (Wsul[i - 1] < 9000.0) {
      ii_data_idx_0 = static_cast<int8_T>(i);
      exitg1 = true;
    } else {
      i--;
    }
  }

  if (ii_data_idx_0 < 48) {
    i = ii_data_idx_0 - 1;
    Rg = mod_foggui_B.modelo.ventos.leste[i];
    tmp = 49 - ii_data_idx_0;
    for (i_0 = 0; i_0 < tmp; i_0++) {
      mod_foggui_B.modelo.ventos.leste[(ii_data_idx_0 + i_0) - 1] = Rg;
    }

    Rg = mod_foggui_B.modelo.ventos.norte[i];
    for (i_0 = 0; i_0 < tmp; i_0++) {
      mod_foggui_B.modelo.ventos.norte[(ii_data_idx_0 + i_0) - 1] = Rg;
    }

    Rg = mod_foggui_B.modelo.ventos.altitudes[i];
    for (i = 0; i < tmp; i++) {
      mod_foggui_B.modelo.ventos.altitudes[(ii_data_idx_0 + i) - 1] = Rg;
    }
  }

  o->modelo = mod_foggui_B.modelo;
  o->Fase_fim = 8.0;
  o->M = 1.0;
  o->R = 0.0;
  o->Q = 0.0;
  o->H = 0.0;
  o->Htabv = 0.0;
  o->Flw = -1.0;
  o->Refcam = 0.0;
  o->Retrot = 1.0E+98;
  o->Ws0 = 1.0;
  o->Wl0 = 1.0;
  o->Wv0 = 0.0;
  o->Vhor[0] = 0.0;
  o->Vhor[1] = 1.0E+99;
  o->Tfim = 1.0E+98;
  o->Vwx = 0.0;
  o->Vwy = 0.0;
  o->Vwz = 0.0;
  o->F = 1.0;
  o->T_emp = 0.0;
  o->Z = 0.0;
  o->Tant = -1.0;
  o->Kb = 1.0;
  o->Kc = 1.0;
  o->Apo = 1.0;
  o->Rot0 = 1.0;
  o->Pit0 = 1.0;
  o->Gir0 = 1.0;
  o->Asm = 1.0;
  o->Cphia = 1.0;
  o->Maxv = 1.0;
  o->Fgrot = 1.0;
  o->Tempo = 0.0;
  o->Wx = 0.0;
  o->Wy = 0.0;
  o->Wz = 0.0;
  o->Wy_p = 0.0;
  o->Wz_p = 0.0;
  o->Vx = 0.0;
  o->Vy = 0.0;
  o->Vz = 0.0;
  o->Vy_p = 0.0;
  o->Vz_p = 0.0;
  o->Dkw = 0.0;
  o->Kw = 0.0;
  o->Kh = 0.0;
  o->Ksub = 0.0;
  o->Hkeep = 0.0;
  o->Van = 0.0;
  o->Alfap = 0.0;
  o->Alfa1 = 0.0;
  o->Alfa2 = 0.0;
  o->Alfa3 = 0.0;
  o->Alfa4 = 0.0;
  o->Alfab = 0.0;
  o->Dkh = 0.0;
  o->Fesp = 0.0;
  o->Fax = 0.0;
  o->Fay = 0.0;
  o->Faz = 0.0;
  o->Max = 0.0;
  o->May = 0.0;
  o->Maz = 0.0;
  o->Vay = 0.0;
  o->Vaz = 0.0;
  o->Alfat = 0.0;
  o->Betat = 0.0;
  o->Tetap = 0.0;
  o->Psip = 0.0;
  o->Wytp = 0.0;
  o->Wztp = 0.0;
  o->Vytp = 0.0;
  o->Vztp = 0.0;
  o->Wla = 0.0;
  o->Wno = 0.0;
  o->Cno = 0.0;
  o->Cla = 0.0;
  o->Cmno = 0.0;
  o->Cmla = 0.0;
  o->Cnow = 0.0;
  o->Cnoap = 0.0;
  o->Sphia = 0.0;
  o->Cmlas = 0.0;
  o->Cmlaw = 0.0;
  o->Cmlaap = 0.0;
  o->Pf = 0.0;
  o->Qsi = 0.0;
  o->Sm = 0.0;
  o->Root = 0.0;
  o->Cna = 0.0;
  o->Cnq = 0.0;
  o->Cnap = 0.0;
  o->Cma = 0.0;
  o->Cmq = 0.0;
  o->Cmap = 0.0;
  o->Cnae = 0.0;
  o->Lcpb = 0.0;
  o->Lcpe = 0.0;
  o->Wtubo = 0.0;
  o->Vmax = 0.0;
  o->Hapo = 0.0;
  o->Hejec = 0.0;
  o->Vx_pmax = 0.0;
  o->List = 0.0;
  o->Mach = 0.0;
  o->Tgrot = 1.0E+98;
  o->Tabin = 1.0E+98;
  o->Tabre = 1.0E+98;
  o->Ttubo = 1.0E+98;
  o->Vx_pmin = 1.0E+98;
  o->T = 0.0;
  o->Vx_p = 0.0;
  o->Wx_p = 0.0;
  o->Wy_p = 0.0;
  o->Vax = 0.0;
  o->Vay = 0.0;
  o->Vaz = 0.0;
  o->Vxh = 0.0;
  o->Vyh = 0.0;
  o->Vzh = 0.0;
  o->Phi = 0.0;
  o->Teta = 0.0;
  o->Psi = 0.0;
  o->Rxr = 0.0;
  o->Ryr = 0.0;
  o->Rzr = 0.0;
  o->Mod = 1.0;
  o->U = 1.0E+98;
  o->Parada = 0.0;
  o->Fdist = 1.0;
  o->Fang = 1.0;
  o->Fder = 1.0;
  o->Fcoef = 1.0;
  o->Fataq = 1.0;
  o->Linf = 0.0;
  o->Lsup = 0.0;
  o->Crgama = 0.0;
  o->Gb = 9.80665;
  o->Sgamal = 0.0;
  o->Ll = 0.0;
  o->L11 = 0.0;
  o->L12 = 0.0;
  o->L13 = 0.0;
  o->L21 = 0.0;
  o->L22 = 0.0;
  o->L23 = 0.0;
  o->L31 = 0.0;
  o->L32 = 0.0;
  o->L33 = 0.0;
  o->Eps = 0.0;
  o->Delr = 0.0;
  o->Sdlong = 0.0;
  o->Cdlong = 0.0;
  o->R13 = 0.0;
  o->R23 = 0.0;
  o->R33 = 0.0;
  o->Hl = 0.0;
  o->Fpf = false;
  o->Rwx = 0.0;
  o->Rwy = 0.0;
  o->Rwz = 0.0;
  o->Ta = 0.0;
  o->Ro = 0.0;
  o->Pa = 0.0;
  o->Vsom = 0.0;
  o->Wbhx = 0.0;
  o->Wbhy = 0.0;
  o->Wbhz = 0.0;
  o->Wgxb = 0.0;
  o->Wgyb = 0.0;
  o->Wgzb = 0.0;
  o->Wgx = 0.0;
  o->Wgz = 0.0;
  o->Vwxb = 0.0;
  o->Vwyb = 0.0;
  o->Vwzb = 0.0;
  o->Dlat_p = 0.0;
  o->Dlong_p = 0.0;
  o->Dalt_p = 0.0;
  o->Ll11 = 0.0;
  o->Ll12 = 0.0;
  o->Ll13 = 0.0;
  o->Rti = 0.0;
  o->Li = 0.0;
  o->Xi = 0.0;
  o->Zci = 0.0;
  o->Zcip = 0.0;
  o->Cgamai = 0.0;
  o->Sgamai = 0.0;
  o->Gamai = 0.0;
  o->Rcxi = 0.0;
  o->Rcyi = 0.0;
  o->Rczi = 0.0;
  o->Rocxip = 0.0;
  o->Rocyip = 0.0;
  o->Roczip = 0.0;
  o->Dicx = 0.0;
  o->Dicy = 0.0;
  o->Dicz = 0.0;
  o->Dipcx = 0.0;
  o->Dipcy = 0.0;
  o->Dipcz = 0.0;
  o->Frxi = 0.0;
  o->Fryi = 0.0;
  o->Frzi = 0.0;
  o->Mrxi = 0.0;
  o->Mryi = 0.0;
  o->Mrzi = 0.0;
  o->Kk = 0.0;
  o->Rot1 = 0.0;
  o->Pit1 = 0.0;
  o->Gir1 = 0.0;
  o->Whxb = 0.0;
  o->Alfaw = 1.0;
  o->Nw = ii_data_idx_0;
  for (i = 0; i < 48; i++) {
    Wsul[i] = -mod_foggui_B.modelo.ventos.norte[i];
    Rsul_[i] = 0.0;
    Rles_[i] = 0.0;
  }

  for (i = 0; i < static_cast<int32_T>((o->Nw - 1.0)); i++) {
    Rg = mod_foggui_B.modelo.ventos.altitudes[i + 1] -
      mod_foggui_B.modelo.ventos.altitudes[i];
    Rsul_[i] = (Wsul[i + 1] - Wsul[i]) / Rg;
    Rles_[i] = (mod_foggui_B.modelo.ventos.leste[i + 1] -
                mod_foggui_B.modelo.ventos.leste[i]) / Rg;
  }

  std::memcpy(&o->Rsul[0], &Rsul_[0], 48U * sizeof(real_T));
  std::memcpy(&o->Rles[0], &Rles_[0], 48U * sizeof(real_T));
  Rg = o->modelo.cte.Rg;
  o->Wxl = 0.0;
  o->Wyl = 0.0;
  o->Wzl = 0.0;
  o->Kquat0 = 1.0;
  o->Qt1 = 0.0;
  o->Qt2 = 0.0;
  o->Qt3 = 0.0;
  o->Qt4 = 0.0;
  o->Dalt = 0.0;
  o->Dlat = 0.0;
  o->Clat = 0.0;
  o->Creta = 0.0;
  o->Sreta = 0.0;
  o->Dlong = 0.0;
  o->Rb = Rg;
  o->Qt1_p = 0.0;
  o->Qt2_p = 0.0;
  o->Qt3_p = 0.0;
  o->Qt4_p = 0.0;
  mod_foggui_eye(o->A);
  o->Frx = 0.0;
  o->Fry = 0.0;
  o->Frz = 0.0;
  o->Mrx = 0.0;
  o->Mry = 0.0;
  o->Mrz = 0.0;
  o->Matr = 0.0;
  o->Acel = 0.0;
  o->Frot = 1.0;
  o->Cnab = 0.0;
  o->Xcp0 = 0.0;
  o->Va = 0.0;
  o->Arpd = 0.0;
  o->Pd = 0.0;
  o->Fcdsep = 1.0;
  o->F_trans = 0.0;
  o->Rcpe = 0.0;
  o->Cfx = 0.0;
  o->Cfy = 0.0;
  o->Cfz = 0.0;
  o->Cmx = 0.0;
  o->Cmy = 0.0;
  o->Cmz = 0.0;
  o->CanardON = 0;
  o->CanardAng1 = 0.0;
  o->CanardAng2 = 0.0;
  o->CanardAng3 = 0.0;
  o->CanardAng4 = 0.0;
  o->Cfx_c = 0.0;
  o->Cfy_c = 0.0;
  o->Cfz_c = 0.0;
  o->Cmx_c = 0.0;
  o->Cmz_c = 0.0;
  o->Cmy_c = 0.0;
  o->k_canard = 1.0;
  o->Coef_canard = *config_coef_canard;
  o->cfx_b = 0.0;
  o->cfy_b = 0.0;
  o->cfz_b = 0.0;
  o->cmx_b = 0.0;
  o->cmz_b = 0.0;
  o->cmy_b = 0.0;
  o->cfx_e = 0.0;
  o->cfy_e = 0.0;
  o->cfz_e = 0.0;
  o->cmx_e = 0.0;
  o->cmz_e = 0.0;
  o->cmy_e = 0.0;
  o->Vwexp = 1.0;
  o->Az1 = 0.0;
  o->Hven = 6.0;
  o->Awz = 0.0;
  o->Vw1 = 0.0;
  o->Rzw = 0.0;
  o->Sp = 0.0;
  o->Al11 = 0.0;
  o->Al21 = 0.0;
  o->Al31 = 0.0;
  o->Al12 = 0.0;
  o->Al22 = 0.0;
  o->Al32 = 0.0;
  o->Ll21 = 0.0;
  o->Ll31 = 0.0;
  o->Ll22 = 0.0;
  o->Ll32 = 0.0;
  o->Ll23 = 0.0;
  o->Ll33 = 0.0;
  o->Xcm = 0.0;
  o->Xcmp = 0.0;
  o->Ycm = 0.0;
  o->Ycmp = 0.0;
  o->Zcm = 0.0;
  o->Zcmp = 0.0;
  o->Di = 0.0;
  o->Massa = 0.0;
  o->Crgama = 0.0;
  o->Km0 = 0.0;
  o->Km1 = 0.0;
  o->Km2 = 0.0;
  o->Tx = 0.0;
  o->Grot = 1.0;
  o->Claw = 0.0;
  o->Lcp0 = 0.0;
  o->Ixd = 0.0;
  o->Ix = 0.0;
  o->Iy = 0.0;
  o->Iz = 0.0;
  o->Iyd = 0.0;
  o->Izd = 0.0;
  o->Vm = 0.0;
  o->Roex = 0.0;
  o->Roey = 0.0;
  o->Roez = 0.0;
  o->Jxx = 0.0;
  o->Jyy = 0.0;
  o->Jzz = 0.0;
  o->Jxy = 0.0;
  o->Jxz = 0.0;
  o->Jyz = 0.0;
  o->Ixy = 0.0;
  o->Ixz = 0.0;
  o->Iyz = 0.0;
  o->Rot = 1.0;
  o->Pit = 1.0;
  o->Gir = 1.0;
  o->Q = 1.0;
  o->Hmax = 1.0;
  o->Fat = 1.0;
  o->Sgamal = 1.0;
  o->Slat = 1.0;
  o->Acontr = 0.0;
  o->Contador = 0.0;
  o->Contador_aux = 0.0;
  o->controle_z_t0 = config_controle_z.t0;
  o->controle_z_roll_on = config_controle_z.roll_on;
  o->controle_z_rollrate_on = config_controle_z.rollrate_on;
  o->controle_z_rollrate_ref = config_controle_z.rollrate_ref;
}

void mod_fogguiModelClass::mod_foggui_Traj_Inercia(Traj_mod_foggui_T *o)
{
  real_T Ab[2];
  real_T Ac1[2];
  real_T Ixemp;
  real_T E2[41];
  real_T G1[41];
  real_T Gbv[41];
  real_T Lb;
  real_T I1;
  real_T I10;
  real_T I11;
  real_T I12;
  real_T I13;
  real_T I14;
  real_T I15;
  real_T I16;
  real_T I17;
  real_T I18;
  real_T I19;
  real_T I2;
  real_T I20;
  real_T I3;
  real_T I6;
  real_T I7;
  real_T I8;
  real_T I9;
  real_T Ib[41];
  real_T A10;
  real_T A2;
  real_T A5;
  real_T A9;
  real_T Fog;
  real_T Ixemp_fech;
  real_T Ixf;
  real_T Ixyf;
  real_T Ixzf;
  real_T Iyf;
  real_T Iyzf;
  real_T Izf;
  real_T Mf;
  real_T Xf;
  real_T Yf;
  real_T Zf;
  real_T E0;
  real_T Grot0;
  real_T Mp0;
  real_T Tb0;
  real_T Xp;
  real_T Ye;
  real_T Yp;
  real_T Ze;
  real_T Zp;
  real_T Tb[41];
  real_T Tc[2];
  real_T Kb_;
  real_T Kc_;
  real_T Ax;
  real_T Mp;
  int32_T tmp;
  Ab[0] = o->modelo.Ab[0];
  Ac1[0] = o->modelo.Ac1[0];
  Ab[1] = o->modelo.Ab[1];
  Ac1[1] = o->modelo.Ac1[1];
  Ixemp = o->modelo.dados_part.Ixemp;
  Lb = o->modelo.geometria.Lb;
  I1 = o->modelo.b_I[0];
  I10 = o->modelo.b_I[9];
  I11 = o->modelo.b_I[10];
  I12 = o->modelo.b_I[11];
  I13 = o->modelo.b_I[12];
  I14 = o->modelo.b_I[13];
  I15 = o->modelo.b_I[14];
  I16 = o->modelo.b_I[15];
  I17 = o->modelo.b_I[16];
  I18 = o->modelo.b_I[17];
  I19 = o->modelo.b_I[18];
  I2 = o->modelo.b_I[1];
  I20 = o->modelo.b_I[19];
  I3 = o->modelo.b_I[2];
  I6 = o->modelo.b_I[5];
  I7 = o->modelo.b_I[6];
  I8 = o->modelo.b_I[7];
  I9 = o->modelo.b_I[8];
  A10 = o->modelo.inercia.A10;
  A2 = o->modelo.inercia.A2;
  A5 = o->modelo.inercia.A5;
  A9 = o->modelo.inercia.A9;
  Fog = o->modelo.inercia.Fog;
  Ixemp_fech = o->modelo.inercia.Ixemp_fech;
  Ixf = o->modelo.inercia.Ixf;
  Ixyf = o->modelo.inercia.Ixyf;
  Ixzf = o->modelo.inercia.Ixzf;
  Iyf = o->modelo.inercia.Iyf;
  Iyzf = o->modelo.inercia.Iyzf;
  Izf = o->modelo.inercia.Izf;
  Mf = o->modelo.inercia.Mf;
  Xf = o->modelo.inercia.Xf;
  Yf = o->modelo.inercia.Yf;
  Zf = o->modelo.inercia.Zf;
  E0 = o->modelo.propelente.E0;
  Grot0 = o->modelo.propelente.Grot0;
  Mp0 = o->modelo.propelente.Mp0;
  Tb0 = o->modelo.propelente.Tb0;
  Xp = o->modelo.propelente.Xp;
  Ye = o->modelo.propelente.Ye;
  Yp = o->modelo.propelente.Yp;
  Ze = o->modelo.propelente.Ze;
  Zp = o->modelo.propelente.Zp;
  std::memcpy(&E2[0], &o->modelo.E2[0], 41U * sizeof(real_T));
  std::memcpy(&G1[0], &o->modelo.G1[0], 41U * sizeof(real_T));
  std::memcpy(&Gbv[0], &o->modelo.Gbv[0], 41U * sizeof(real_T));
  std::memcpy(&Ib[0], &o->modelo.Ib[0], 41U * sizeof(real_T));
  std::memcpy(&Tb[0], &o->modelo.Tb[0], 41U * sizeof(real_T));
  Tc[0] = o->modelo.Tc[0];
  Tc[1] = o->modelo.Tc[1];
  Kb_ = o->Kb + 1.0;
  Kc_ = o->Kc + 1.0;
  Ax = o->Tempo / o->modelo.propelente.Tb0;
  tmp = static_cast<int32_T>((o->Kb + 1.0)) - 1;
  o->Tx = (Ax - o->modelo.Tb[static_cast<int32_T>(((o->Kb + 1.0) - 1.0)) - 1]) *
    o->modelo.Eb[tmp] + o->modelo.E1[tmp];
  Mp = ((E2[static_cast<int32_T>(Kb_) - 1] + o->Tx) * (Tb[static_cast<int32_T>
         (Kb_) - 1] - Ax) / 2.0 + Ib[static_cast<int32_T>(Kb_) - 1]) * Mp0 / Ib
    [0];
  o->Vm = Mp0 * o->Tx / (Tb0 * Ib[0]);
  o->Tx *= E0;
  o->Grot = ((Ax - Tb[static_cast<int32_T>((Kb_ - 1.0)) - 1]) * Gbv
             [static_cast<int32_T>(Kb_) - 1] + G1[static_cast<int32_T>(Kb_) - 1])
    * Grot0 * o->Fgrot;
  o->Massa = Mp + Mf;
  tmp = static_cast<int32_T>(Kc_) - 1;
  o->Acontr = ((o->Tempo - Tc[static_cast<int32_T>((Kc_ - 1.0)) - 1]) * Ab[tmp]
               + Ac1[tmp]) * 0.017453292519943295;
  o->Xcm = (Xp * Mp + I6) / o->Massa;
  o->Ycm = (Yp * Mp + I7) / o->Massa;
  o->Zcm = (Zp * Mp + I8) / o->Massa;
  I6 = o->Massa * o->Massa;
  Ax = o->Vm * Mf / I6;
  o->Xcmp = (Xf - Xp) * Ax;
  o->Ycmp = (Yf - Yp) * Ax;
  o->Zcmp = (Zf - Zp) * Ax;
  o->Roex = o->Xcm - Lb;
  o->Roey = Ye - o->Ycm;
  o->Roez = Ze - o->Zcm;
  I1 = I2 - Mp / I1;
  Xf = Mp * I1;
  Yf = Xf / 2.0 + Mp * I3;
  Ax = Mp / o->Massa;
  Zf = 0.0;
  if (Fog == 1.0) {
    if (o->F < 6.0) {
      Zf = Ixemp_fech - Ixemp;
    }

    if ((o->F == 6.0) && (o->T_emp != 0.0)) {
      Zf = (Ixemp_fech - Ixemp) * (o->Tabre - o->Tempo) / o->T_emp;
    }
  }

  o->Ix = ((Xf + Ixf) + Ax * I9) + Zf;
  o->Iy = (Yf + Iyf) + Ax * I11;
  o->Iz = (Yf + Izf) + Ax * I10;
  I10 = (I2 - 2.0 * I1) * o->Vm;
  o->Ixd = I10 - o->Vm * I15 / I6;
  I15 = I10 / 2.0 - o->Vm * I3;
  o->Iyd = I15 - o->Vm * I17 / I6;
  o->Izd = I15 - o->Vm * I16 / I6;
  if ((o->Tempo > o->Tabin) && (o->Tempo < o->Tabre) && (o->F == 6.0)) {
    o->Ixd -= (Ixemp_fech - Ixemp) / o->T_emp;
  }

  Ax = (Mp - Mf) * Mp / I6;
  o->Km0 = o->Xcm / Lb;
  I6 = 1.0 - o->Km0;
  I1 = A5 - o->Km0;
  Ixemp = (1.0 - o->Km0) - A2;
  o->Km1 = ((1.0 - o->Km0) * (1.0 - o->Km0) - A2 * I1) * A9 / Ixemp;
  o->Km2 = A10 * I1 / Ixemp;
  o->Km0 = 2.0 * I6;
  o->Ixy = (Ax * I12 + Ixyf) + I18 * Mp;
  o->Ixz = (Ax * I13 + Ixzf) + I19 * Mp;
  o->Iyz = (Ax * I14 + Iyzf) + I20 * Mp;
  Ax = (((o->Ix * o->Iy * o->Iz - o->Ix * o->Iyz * o->Iyz) - o->Iy * o->Ixz *
         o->Ixz) - o->Iz * o->Ixy * o->Ixy) - 2.0 * o->Ixy * o->Ixz * o->Iyz;
  o->Jxx = (o->Iy * o->Iz - o->Iyz * o->Iyz) / Ax;
  o->Jyy = (o->Iz * o->Ix - o->Ixz * o->Ixz) / Ax;
  o->Jzz = (o->Ix * o->Iy - o->Ixy * o->Ixy) / Ax;
  o->Jxy = (o->Ixz * o->Iyz + o->Ixy * o->Iz) / Ax;
  o->Jxz = (o->Ixy * o->Iyz + o->Ixz * o->Iy) / Ax;
  o->Jyz = (o->Ixz * o->Ixy + o->Iyz * o->Ix) / Ax;
}

void mod_fogguiModelClass::mod_foggui_Traj_Quat(Traj_mod_foggui_T *o)
{
  real_T Ax;
  real_T Ay;
  real_T Az;
  real_T Bx;
  real_T By;
  real_T Bz;
  real_T Ay_tmp;
  real_T tmp;
  Bx = o->Psi / 2.0;
  Ax = std::cos(Bx);
  Ay_tmp = o->Teta / 2.0;
  Ay = std::cos(Ay_tmp);
  Bz = o->Phi / 2.0;
  Az = std::cos(Bz);
  Bx = std::sin(Bx);
  By = std::sin(Ay_tmp);
  Bz = std::sin(Bz);
  Ay_tmp = Ax * Ay;
  tmp = Bx * By;
  o->Qt1 = Ay_tmp * Az + tmp * Bz;
  Ax *= By;
  Ay *= Bx;
  o->Qt2 = Ay * Az - Ax * Bz;
  o->Qt3 = Ax * Az + Ay * Bz;
  o->Qt4 = Ay_tmp * Bz - tmp * Az;
}

void mod_fogguiModelClass::mod_foggui_Traj_Lbh(Traj_mod_foggui_T *o)
{
  real_T Ax;
  real_T Ay;
  real_T Az;
  real_T Aw;
  real_T tmp;
  Ax = o->Qt1 * o->Qt1;
  Ay = o->Qt2 * o->Qt2;
  Az = o->Qt3 * o->Qt3;
  Aw = o->Qt4 * o->Qt4;
  tmp = Ax - Ay;
  o->L11 = (tmp - Az) + Aw;
  o->L12 = (o->Qt3 * o->Qt4 + o->Qt1 * o->Qt2) * 2.0;
  o->L13 = (o->Qt2 * o->Qt4 - o->Qt1 * o->Qt3) * 2.0;
  o->L21 = (o->Qt3 * o->Qt4 - o->Qt1 * o->Qt2) * 2.0;
  o->L22 = (tmp + Az) - Aw;
  o->L23 = (o->Qt2 * o->Qt3 + o->Qt1 * o->Qt4) * 2.0;
  o->L31 = (o->Qt2 * o->Qt4 + o->Qt1 * o->Qt3) * 2.0;
  o->L32 = (o->Qt2 * o->Qt3 - o->Qt1 * o->Qt4) * 2.0;
  o->L33 = ((Ax + Ay) - Az) - Aw;
  o->Eps = (((1.0 - Ax) - Ay) - Az) - Aw;
}

void mod_fogguiModelClass::mod_foggui_Traj_R_inic(Traj_mod_foggui_T *o, const
  real_T L[4])
{
  real_T Ktubo;
  real_T B2;
  real_T B3;
  int32_T i;
  int32_T d;
  int32_T b_j;
  real_T tmp;
  int32_T B2_tmp;
  boolean_T exitg1;
  Ktubo = o->modelo.dados_part.Ktubo;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 5)) {
    B2 = 0.0;
    B3 = 0.0;
    d = static_cast<int32_T>(((1.0 - o->Linf) + o->Lsup));
    for (b_j = 0; b_j < d; b_j++) {
      B2_tmp = static_cast<int32_T>((o->Linf + static_cast<real_T>(b_j))) - 1;
      B2 += L[B2_tmp];
      B3 += L[B2_tmp] * L[B2_tmp];
    }

    tmp = B2 * B2 - ((o->Lsup - o->Linf) + 1.0) * B3;
    o->Ll = o->Massa * o->Gb * o->Crgama * (L[0] * B2 - B3) / Ktubo / tmp;
    if (o->Ll < 0.0) {
      o->Linf++;
      i++;
    } else {
      o->Sgamal = -o->Massa * o->Gb * o->Crgama * B2 / Ktubo / tmp;
      if ((L[static_cast<int32_T>(o->Linf) - 1] - L[static_cast<int32_T>(o->Lsup)
           - 1]) * o->Sgamal + o->Ll < 0.0) {
        o->Lsup--;
        i++;
      } else {
        exitg1 = true;
      }
    }
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Tabre_(Traj_mod_foggui_T *o)
{
  real_T Ax;
  switch (static_cast<int32_T>(o->modelo.inercia.Fog)) {
   case 1:
    if (!(o->Frot != 0.0)) {
      o->T_emp = 0.0;
    } else {
      Ax = 1.0 / (o->Wx / 2.0 / 3.1415926535897931 + o->modelo.dados_part.Aemp);
      o->T_emp = ((o->modelo.dados_part.Cemp3 * Ax + o->modelo.dados_part.Cemp2)
                  * Ax + o->modelo.dados_part.Cemp1) * Ax +
        o->modelo.dados_part.Cemp0;
    }
    break;

   case 2:
    o->T_emp = 0.0;
    break;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Iniciar(Traj_mod_foggui_T *o)
{
  real_T Tfq;
  real_T Gfi;
  real_T Rg;
  real_T Dlan;
  real_T Lr;
  real_T Rt;
  real_T Xboca;
  real_T Xfim;
  real_T Xt1;
  real_T Xt2;
  real_T Xt3;
  real_T Retemp;
  real_T Azi;
  real_T Elev;
  real_T Ralt;
  real_T Rlat;
  real_T E0;
  real_T Valt[48];
  real_T Wles[48];
  real_T Wsul[48];
  real_T L[4];
  int32_T i;
  Tfq = o->modelo.aero.Tfq;
  Gfi = o->modelo.atmosf.Gfi;
  Rg = o->modelo.cte.Rg;
  Dlan = o->modelo.dados_part.Dlan;
  Lr = o->modelo.dados_part.Lr;
  Rt = o->modelo.dados_part.Rt;
  Xboca = o->modelo.dados_part.Xboca;
  Xfim = o->modelo.dados_part.Xfim;
  Xt1 = o->modelo.dados_part.Xt1;
  Xt2 = o->modelo.dados_part.Xt2;
  Xt3 = o->modelo.dados_part.Xt3;
  Retemp = o->modelo.geometria.Retemp;
  Azi = o->modelo.lancamento.Azi;
  Elev = o->modelo.lancamento.Elev;
  Ralt = o->modelo.lancamento.Ralt;
  Rlat = o->modelo.lancamento.Rlat;
  E0 = o->modelo.propelente.E0;
  for (i = 0; i < 48; i++) {
    Valt[i] = o->modelo.ventos.altitudes[i];
    Wles[i] = o->modelo.ventos.leste[i];
    Wsul[i] = -o->modelo.ventos.norte[i];
  }

  o->Vwexp = 1.0;
  if (o->F == 1.0) {
    o->T = 0.0;
    if (E0 == 0.0) {
      o->T = Tfq;
    }

    o->Tant = -1.0;
    o->Kb = 1.0;
    o->Kc = 1.0;
    o->Apo = 1.0;
    o->Rot0 = 1.0;
    o->Pit0 = 1.0;
    o->Gir0 = 1.0;
    o->Cphia = 1.0;
    o->Maxv = 1.0;
    o->Fgrot = 1.0;
    o->Tempo = o->T;
    o->Wx = 0.0;
    o->Wy = 0.0;
    o->Wz = 0.0;
    o->Wy_p = 0.0;
    o->Wz_p = 0.0;
    o->Vx = 0.0;
    o->Vy = 0.0;
    o->Vz = 0.0;
    o->Vy_p = 0.0;
    o->Vz_p = 0.0;
    o->Dkw = 0.0;
    o->Kw = 0.0;
    o->Kh = 0.0;
    o->Ksub = 0.0;
    o->Vx = o->Vxfmr;
    o->Hkeep = 0.0;
    o->Van = 0.0;
    o->Alfap = 0.0;
    o->Alfa1 = 0.0;
    o->Alfa2 = 0.0;
    o->Alfa3 = 0.0;
    o->Alfa4 = 0.0;
    o->Alfab = 0.0;
    o->Dkh = 0.0;
    o->Fesp = 0.0;
    o->Fax = 0.0;
    o->Fay = 0.0;
    o->Faz = 0.0;
    o->Max = 0.0;
    o->May = 0.0;
    o->Maz = 0.0;
    o->Vay = 0.0;
    o->Vaz = 0.0;
    o->Alfat = 0.0;
    o->Betat = 0.0;
    o->Tetap = 0.0;
    o->Psip = 0.0;
    o->Wytp = 0.0;
    o->Wztp = 0.0;
    o->Vytp = 0.0;
    o->Vztp = 0.0;
    o->Wla = 0.0;
    o->Wno = 0.0;
    o->Cno = 0.0;
    o->Cla = 0.0;
    o->Cmno = 0.0;
    o->Cmla = 0.0;
    o->Cnow = 0.0;
    o->Cnoap = 0.0;
    o->Sphia = 0.0;
    o->Cmlas = 0.0;
    o->Cmlaw = 0.0;
    o->Cmlaap = 0.0;
    o->Pf = 0.0;
    o->Qsi = 0.0;
    o->Sm = 0.0;
    o->Root = 0.0;
    o->Cna = 0.0;
    o->Cnq = 0.0;
    o->Cnap = 0.0;
    o->Cma = 0.0;
    o->Cmq = 0.0;
    o->Cmap = 0.0;
    o->Cnae = 0.0;
    o->Lcpb = 0.0;
    o->Lcpe = 0.0;
    o->Tgrot = 1.0E+98;
    o->Tabin = 1.0E+98;
    o->Tabre = 1.0E+98;
    o->Ttubo = 1.0E+98;
    o->Vx_pmin = 1.0E+98;
    o->Wtubo = 0.0;
    o->Vmax = 0.0;
    o->Hapo = 0.0;
    o->Hejec = 0.0;
    o->Vx_pmax = 0.0;
    while (Ralt >= Valt[static_cast<int32_T>((o->Kw + 1.0)) - 1] + o->Htabv) {
      o->Kw++;
    }

    Tfq = Elev * 3.1415926535897931 / 3200.0;
    E0 = Azi * 3.1415926535897931 / 3200.0;
    o->Crgama = std::cos(Tfq);
    Azi = std::sin(Tfq);
    o->Creta = std::cos(E0);
    o->Sreta = std::sin(E0);
    Elev = o->modelo.lancamento.Phi0 * 3.1415926535897931 / 3200.0;
    Rlat *= 0.017453292519943295;
    o->Al11 = o->Crgama * o->Creta;
    o->Al21 = o->Crgama * o->Sreta;
    o->Al31 = Azi;
    o->Al12 = Azi * o->Creta;
    o->Al22 = Azi * o->Sreta;
    o->Al32 = o->Crgama;
    mod_foggui_Traj_Inercia(o);
    if (o->F < 7.0) {
      L[0] = o->Xcm - Xt1;
      L[1] = o->Xcm - Xt2;
      L[2] = o->Xcm - Xt3;
      L[3] = o->Xcm - Xfim;
      o->Rb = Rg + Ralt;
      Xfim = Rg / o->Rb;
      o->Gb = Xfim * Xfim * Gfi;
      o->Linf = 1.0;
      o->Lsup = 4.0;
      mod_foggui_Traj_R_inic(o, L);
      Xfim = o->Sgamal;
      o->Psi = E0;
      o->Teta = -(Tfq + std::asin(Xfim));
      o->Phi = Elev;
      mod_foggui_Traj_Quat(o);
      mod_foggui_Traj_Lbh(o);
      Xfim = std::cos(Elev);
      Xt1 = std::sin(Elev);
      Rt += o->Ycm * Xt1 + o->Zcm * Xfim;
      Dlan = ((L[static_cast<int32_T>(o->Linf) - 1] - L[3]) * o->Sgamal + o->Ll)
        + Dlan / 2.0;
      o->Delr = (Lr - Xboca) - o->Xcm;
      Lr = (o->Delr * std::cos(o->Teta) + Rt * std::sin(o->Teta)) + Dlan * Azi;
      Xboca = o->Ycm * Xfim - o->Zcm * Xt1;
      o->Rxr = Lr * o->Creta - Xboca * o->Sreta;
      o->Ryr = Lr * o->Sreta + Xboca * o->Creta;
      o->Rzr = (-o->Delr * std::sin(o->Teta) + Rt * std::cos(o->Teta)) - Dlan *
        o->Crgama;
      o->Delr = std::sqrt((Lr * Lr + Xboca * Xboca) + o->Rzr * o->Rzr);
    } else {
      o->Rxr = 0.0;
      o->Ryr = 0.0;
      o->Rzr = 0.0;
      o->Delr = std::sqrt((o->Rxr * o->Rxr + o->Ryr * o->Ryr) + o->Rzr * o->Rzr);
      Lr = o->Sgamal;
      o->Psi = E0;
      o->Teta = -(Tfq + std::asin(Lr));
      o->Phi = Elev;
      mod_foggui_Traj_Quat(o);
      mod_foggui_Traj_Lbh(o);
    }

    Tfq = Rg + Ralt;
    o->Rb = Tfq + o->Rzr;
    o->Dlat = std::atan(o->Rxr / o->Rb);
    o->Slat = std::sin(Rlat + o->Dlat);
    o->Clat = std::cos(Rlat + o->Dlat);
    o->Dlong = -std::atan(o->Ryr / (std::sqrt(o->Rb * o->Rb + o->Rxr * o->Rxr) *
      o->Clat));
    o->Dalt = (std::sqrt(o->Rb * o->Rb + o->Rxr * o->Rxr) - o->Rb) + o->Rzr;
    o->Rb = Tfq + o->Dalt;
    Rg /= o->Rb;
    o->Gb = Rg * Rg * Gfi;
    o->Sp = std::sqrt(o->Rxr * o->Rxr + o->Ryr * o->Ryr);
    while (o->Sp >= o->Vhor[static_cast<int32_T>((o->Kh + 1.0)) - 1]) {
      o->Kh++;
    }

    o->Hven = 6.0;
    if (o->Vwexp != 0.0) {
      o->Az1 = 0.0;
      o->Vw1 = std::sqrt(Wsul[0] * Wsul[0] + Wles[0] * Wles[0]);
      if (o->Vw1 != 0.0) {
        Rg = std::abs(Wles[0] / o->Vw1);
        if (Wles[0] < 0.0) {
          Rlat = -1.0;
        } else if (Wles[0] > 0.0) {
          Rlat = 1.0;
        } else if (Wles[0] == 0.0) {
          Rlat = 0.0;
        } else {
          Rlat = (rtNaN);
        }

        if ((1.0 < Rg) || rtIsNaN(Rg)) {
          Rg = 1.0;
        }

        o->Az1 = Rlat * Rg;
        o->Az1 = std::asin(o->Az1);
        if (Wsul[0] > 0.0) {
          o->Az1 = 3.1415926535897931 - o->Az1;
        } else {
          if (Wles[0] < 0.0) {
            o->Az1 += 6.2831853071795862;
          }
        }
      }

      Gfi = 0.0;
      o->Awz = 0.0;
      if (o->Vwexp != 2.0) {
        Gfi = std::sqrt(Wsul[1] * Wsul[1] + Wles[1] * Wles[1]);
      }

      o->Rzw = static_cast<real_T>(((o->Vwexp != 2.0) * (o->Vwexp != -1.0))) *
        (Gfi - o->Vw1) / (((Valt[1] + o->Htabv) - o->Hven) - Ralt);
      o->Alfaw = 1.0E+99;
      if ((o->Vw1 != Gfi) && (o->Nw > 1.0)) {
        Rg = std::abs(Wles[1] / Gfi);
        if (Wles[1] < 0.0) {
          Rlat = -1.0;
        } else if (Wles[1] > 0.0) {
          Rlat = 1.0;
        } else if (Wles[1] == 0.0) {
          Rlat = 0.0;
        } else {
          Rlat = (rtNaN);
        }

        if ((1.0 < Rg) || rtIsNaN(Rg)) {
          Rg = 1.0;
        }

        Rg = std::asin(Rlat * Rg);
        if (Wsul[1] > 0.0) {
          Rg = 3.1415926535897931 - Rg;
        } else {
          if (Wles[1] < 0.0) {
            Rg += 6.2831853071795862;
          }
        }

        if (std::abs(o->Az1 - Rg) > 3.1415926535897931) {
          if (Rg > o->Az1) {
            Rg -= 6.2831853071795862;
          } else {
            o->Az1 -= 6.2831853071795862;
          }
        }

        o->Alfaw = std::log((Valt[1] + o->Htabv) / (o->Hven + Ralt)) / (Gfi -
          o->Vw1);
        o->Awz = static_cast<real_T>((o->Vwexp != 2.0)) * (Rg - o->Az1) /
          (((Valt[1] + o->Htabv) - o->Hven) - Ralt);
      }
    }
  }

  if (o->F == 5.0) {
    o->Ttubo = o->T;
    o->Tabin = o->T + Retemp;
    o->Tgrot = o->T + o->Retrot;
    o->Wtubo = o->Wx / 2.0 / 3.1415926535897931;
  }

  if (o->F == 6.0) {
    o->Tabin = o->T;
    mod_foggui_Traj_Tabre_(o);
    o->Tabre = o->T_emp + o->Tabin;
  }

  o->H = 0.0;
  if (o->F == 8.0) {
    o->Ixd = 0.0;
    o->Iyd = 0.0;
    o->Izd = 0.0;
    o->Vm = 0.0;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Padrao(Traj_mod_foggui_T *o)
{
  if (o->F < 7.0) {
    if (o->modelo.aero.Tfq <= 2.0) {
      o->Hl = 0.01;
    } else if (o->modelo.aero.Tfq >= 15.0) {
      o->Hl = 0.1;
    } else {
      o->Hl = 0.05;
    }
  } else if (o->F == 7.0) {
    if (o->modelo.aero.Tfq <= 2.0) {
      o->Hl = 0.1;
    } else if (o->modelo.aero.Tfq >= 15.0) {
      o->Hl = 10.0;
    } else {
      o->Hl = 0.5;
    }
  } else if (o->modelo.aero.Tfq <= 2.0) {
    o->Hl = 2.0;
  } else {
    o->Hl = 10.0;
  }

  o->List = o->T;
  o->Rot = (o->Mod == 0.0) * (o->F < 7.0) + (o->Mod == 1.0);
  o->Pit = (o->F < 8.0) * (o->Mod == 0.0) + (o->Mod == 1.0);
  o->Gir = 0.0;
  o->Hmax = (static_cast<real_T>((o->F > 7.0)) + 1.0) * 0.25 *
    static_cast<real_T>((o->F > 4.0)) + static_cast<real_T>((o->F < 5.0)) *
    0.003;
  o->Hmax = 0.00083333333333333339;
  o->Fat = 1.0;
  o->R = 0.0;
  o->Q = 0.0;
}

void mod_fogguiModelClass::mod_foggui_Traj_Vento(Traj_mod_foggui_T *o)
{
  real_T Valt[48];
  real_T Wles[48];
  real_T Wsul[48];
  real_T Rver[48];
  real_T Kw_;
  real_T Kh_;
  real_T Vw;
  int32_T i;
  real_T Kw__tmp;
  for (i = 0; i < 48; i++) {
    Valt[i] = o->modelo.ventos.altitudes[i];
    Wles[i] = o->modelo.ventos.leste[i];
    Rver[i] = -o->modelo.ventos.norte[i] * 0.0;
    Wsul[i] = -o->modelo.ventos.norte[i];
  }

  Kw_ = o->Kw + 1.0;
  Kh_ = o->Kh + 1.0;
  if ((o->Kw + 1.0 > 1.0) || (o->Vwexp == 0.0)) {
    i = static_cast<int32_T>((o->Kw + 1.0)) - 1;
    o->Vwx = (((o->Z - o->modelo.ventos.altitudes[i]) - o->Htabv) * o->Rsul[i] +
              Wsul[i]) * o->Ws0;
    o->Vwy = (((o->Z - Valt[static_cast<int32_T>(Kw_) - 1]) - o->Htabv) *
              o->Rles[static_cast<int32_T>(Kw_) - 1] + Wles[static_cast<int32_T>
              (Kw_) - 1]) * o->Wl0;
    o->Rwx = o->Rsul[static_cast<int32_T>(Kw_) - 1] * o->Ws0;
    o->Rwy = o->Rles[static_cast<int32_T>(Kw_) - 1] * o->Wl0;
  } else {
    Kw__tmp = o->Hven + o->modelo.lancamento.Ralt;
    Vw = o->Z - Kw__tmp;
    Kw_ = Vw * o->Awz * static_cast<real_T>((o->Z > Kw__tmp)) + o->Az1;
    if ((o->Vwexp == -1.0) && (o->Z > Kw__tmp)) {
      Vw = std::log(o->Z / Kw__tmp) / o->Alfaw + o->Vw1;
      o->Rzw = 1.0 / (o->Alfaw * o->Z * Kw__tmp);
    } else {
      Vw = Vw * o->Rzw + o->Vw1;
    }

    o->Vwx = std::cos(3.1415926535897931 - Kw_) * Vw;
    o->Vwy = std::sin(3.1415926535897931 - Kw_) * Vw;
    o->Rwx = (std::cos(3.1415926535897931 - Kw_) * o->Rzw + o->Vwy * o->Awz) *
      o->Ws0;
    o->Rwy = (std::sin(3.1415926535897931 - Kw_) * o->Rzw - o->Vwx * o->Awz) *
      o->Wl0;
    o->Vwx *= o->Ws0;
    o->Vwy *= o->Wl0;
  }

  i = static_cast<int32_T>(Kh_) - 1;
  o->Vwz = ((o->Sp - Wles[i] * 0.0) * Rver[i] + Wsul[i] * 0.0) * o->Wv0;
  o->Rwz = Rver[i] * o->Wv0;
  if ((o->Apo == 0.0) && (o->Flw == 0.0)) {
    o->Vwx = 0.0;
    o->Vwy = 0.0;
    o->Rwx = 0.0;
    o->Rwy = 0.0;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Pa_vsom(Traj_mod_foggui_T *o)
{
  real_T Gfi;
  real_T Rg;
  real_T Dbal;
  real_T Tbal;
  real_T Pbal;
  Gfi = o->modelo.atmosf.Gfi;
  Rg = o->modelo.cte.Rg;
  Dbal = o->modelo.lancamento.Dbal;
  Tbal = o->modelo.lancamento.Tbal;
  Pbal = o->modelo.lancamento.Pbal;
  o->Pa = o->Ro * o->modelo.cte.Rgas * o->Ta;
  o->Ro *= Dbal;
  o->Ta *= Tbal;
  o->Pa *= Pbal;
  o->Vsom = 20.046 * std::sqrt(o->Ta);
  Rg /= o->Rb;
  o->Gb = Rg * Rg * Gfi;
}

void mod_fogguiModelClass::mod_foggui_Traj_Atmosf(Traj_mod_foggui_T *o)
{
  real_T Dtemp4;
  real_T G0;
  real_T Gfi;
  real_T Hstrat0;
  real_T Hstrat1;
  real_T Hstrat2;
  real_T Hstrat3;
  real_T Hstrat4;
  real_T Hstrat5;
  real_T Htrop;
  real_T Rfi;
  real_T Rgas;
  real_T Ro0;
  real_T Rotrop0;
  real_T T0;
  real_T Tatm;
  real_T Tstrat0;
  real_T Ttrop;
  real_T Dbat[101];
  real_T Hbat[101];
  real_T Lbat[101];
  real_T Tbat[101];
  Dtemp4 = o->modelo.atmosf.Dtemp4;
  G0 = o->modelo.cte.G0;
  Gfi = o->modelo.atmosf.Gfi;
  Hstrat0 = o->modelo.atmosf.Hstrat0;
  Hstrat1 = o->modelo.atmosf.Hstrat1;
  Hstrat2 = o->modelo.atmosf.Hstrat2;
  Hstrat3 = o->modelo.atmosf.Hstrat3;
  Hstrat4 = o->modelo.atmosf.Hstrat4;
  Hstrat5 = o->modelo.atmosf.Hstrat5;
  Htrop = o->modelo.atmosf.Htrop;
  Rfi = o->modelo.atmosf.Rfi;
  Rgas = o->modelo.cte.Rgas;
  Ro0 = o->modelo.atmosf.Ro0;
  Rotrop0 = o->modelo.atmosf.Rotrop0;
  T0 = o->modelo.atmosf.T0;
  Tatm = o->modelo.atmosf.Tatm;
  Tstrat0 = o->modelo.atmosf.Tstrat0;
  Ttrop = o->modelo.atmosf.Ttrop;
  std::memcpy(&Dbat[0], &o->modelo.Dbat[0], 101U * sizeof(real_T));
  std::memcpy(&Hbat[0], &o->modelo.Hbat[0], 101U * sizeof(real_T));
  std::memcpy(&Lbat[0], &o->modelo.Lbat[0], 101U * sizeof(real_T));
  std::memcpy(&Tbat[0], &o->modelo.Tbat[0], 101U * sizeof(real_T));
  o->Ta = 0.0;
  o->Ro = 0.0;
  o->Pa = 0.0;
  o->Vsom = 0.0;
  o->Gb = 0.0;
  Gfi = Gfi / G0 * Rfi * o->Z / (Rfi + o->Z);
  switch (static_cast<int32_T>(Tatm)) {
   case 0:
    if (Gfi < Htrop) {
      o->Ta = T0 - 0.0065 * Gfi;
      o->Ro = rt_powd_snf(o->Ta / T0, 4.2561) * Ro0;
      mod_foggui_Traj_Pa_vsom(o);
    } else if ((Gfi > Htrop) && (Gfi < Hstrat0)) {
      o->Ta = Ttrop;
      o->Ro = std::exp(G0 / (Rgas * Ttrop) * (Htrop - Gfi)) * Rotrop0;
      mod_foggui_Traj_Pa_vsom(o);
    } else if ((Gfi > Hstrat0) && (Gfi < Hstrat1)) {
      o->Ta = Tstrat0;
      Dtemp4 = (Gfi - o->modelo.atmosf.Hstrat0) * 4.6157E-6;
      o->Ro = std::exp((1.0 - (0.5 - Dtemp4 / 3.0) * Dtemp4) * Dtemp4 * -35.1656)
        * o->modelo.atmosf.Rostrat0;
      mod_foggui_Traj_Pa_vsom(o);
    } else if ((Gfi > Hstrat1) && (Gfi < Hstrat2)) {
      G0 = Gfi / 3048.0;
      o->Ta = (((((0.001395223665 - 2.374431443E-5 * G0) * G0 + -0.0325491963) *
                 G0 + 0.3768512721) * G0 + -2.134084868) * G0 + 5.434388122) *
        T0 - Dtemp4;
      Dtemp4 = (Gfi - o->modelo.atmosf.Hstrat0) * 4.6157E-6;
      o->Ro = std::exp((1.0 - (0.5 - Dtemp4 / 3.0) * Dtemp4) * Dtemp4 * -35.1656)
        * o->modelo.atmosf.Rostrat0;
      mod_foggui_Traj_Pa_vsom(o);
    } else if ((Gfi > Hstrat2) && (Gfi < Hstrat3)) {
      o->Ta = (1.6711181 - Gfi / 3048.0 * 0.0406003) * T0;
      Dtemp4 = (Gfi - o->modelo.atmosf.Hstrat0) * 4.6157E-6;
      o->Ro = std::exp((1.0 - (0.5 - Dtemp4 / 3.0) * Dtemp4) * Dtemp4 * -35.1656)
        * o->modelo.atmosf.Rostrat0;
      mod_foggui_Traj_Pa_vsom(o);
    } else if ((Gfi > Hstrat3) && (Gfi < Hstrat4)) {
      o->Ta = T0 * 0.57491;
      Dtemp4 = (Gfi - o->modelo.atmosf.Hstrat0) * 4.6157E-6;
      o->Ro = std::exp((1.0 - (0.5 - Dtemp4 / 3.0) * Dtemp4) * Dtemp4 * -35.1656)
        * o->modelo.atmosf.Rostrat0;
      mod_foggui_Traj_Pa_vsom(o);
    } else {
      if ((Gfi > Hstrat4) && (Gfi < Hstrat5)) {
        G0 = Gfi / 3048.0;
        o->Ta = (((((1.9949E-7 * G0 + -4.18035235E-5) * G0 + 0.003120835316) *
                   G0 + -0.096272433) * G0 + 1.067267) * G0 + -0.08858355483) *
          T0;
        Dtemp4 = (Gfi - o->modelo.atmosf.Hstrat0) * 4.6157E-6;
        o->Ro = std::exp((1.0 - (0.5 - Dtemp4 / 3.0) * Dtemp4) * Dtemp4 *
                         -35.1656) * o->modelo.atmosf.Rostrat0;
        mod_foggui_Traj_Pa_vsom(o);
      }
    }
    break;

   case 3:
   case 4:
   case 5:
    if (Lbat[0] == 0.0) {
      o->Ta = Tbat[0];
      o->Ro = std::exp(-G0 / Rgas * (Gfi - Hbat[0]) / o->Ta) * Dbat[0];
    } else {
      o->Ta = (Gfi - Hbat[0]) * Lbat[0] + Tbat[0];
      o->Ro = rt_powd_snf(o->Ta / Tbat[0], -1.0 - G0 / Rgas / Lbat[0]) * Dbat[0];
    }

    mod_foggui_Traj_Pa_vsom(o);
    break;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Cdist(Traj_mod_foggui_T *o)
{
  real_T Rg;
  real_T Ralt;
  real_T Crlat;
  real_T Srlat;
  Rg = o->modelo.cte.Rg;
  Ralt = o->modelo.lancamento.Ralt;
  Crlat = o->modelo.tip_off.Crlat;
  Srlat = o->modelo.tip_off.Srlat;
  o->Fdist = 0.0;
  o->Sdlong = std::sin(o->Dlong);
  o->Cdlong = std::sqrt(1.0 - o->Sdlong * o->Sdlong);
  o->R13 = o->Slat * Crlat - o->Clat * Srlat * o->Cdlong;
  o->R23 = -o->Clat * o->Sdlong;
  o->R33 = o->Clat * Crlat * o->Cdlong + o->Slat * Srlat;
  o->Rxr = o->Rb * o->R13;
  o->Ryr = o->Rb * o->R23;
  o->Rzr = o->Rb * o->R33 - (Rg + Ralt);
  o->Delr = std::sqrt((o->Rxr * o->Rxr + o->Ryr * o->Ryr) + o->Rzr * o->Rzr);
  o->Sp = 0.0;
  if (o->R33 != 0.0) {
    o->Sp = std::atan((o->R23 * o->Sreta + o->R13 * o->Creta) / o->R33);
  }

  if (o->Sp < 0.0) {
    o->Sp += 6.2831853071795862;
  }

  o->Sp *= Rg;
}

void mod_fogguiModelClass::mod_foggui_Traj_Cp_contato(Traj_mod_foggui_T *o)
{
  real_T Ldel;
  real_T Dlan;
  real_T Lr;
  real_T Ax;
  real_T Ay;
  real_T Az;
  real_T Rqyi;
  real_T Modqei;
  real_T Eqeyi;
  real_T Eqezi;
  real_T Eqexri;
  real_T Eqeyri;
  real_T Eqezri;
  real_T Calfai;
  real_T Salfai;
  Ldel = o->modelo.cte.Ldel;
  Dlan = o->modelo.dados_part.Dlan;
  Lr = o->modelo.dados_part.Lr;
  if (o->Rti == o->modelo.dados_part.Rt) {
    Ax = o->Ll11 * o->Li + o->Rxr;
    Ay = o->Ll12 * o->Li + o->Ryr;
    Az = o->Ll13 * o->Li + o->Rzr;
    o->Di = (-o->A[0] * Ax - o->A[3] * Ay) - o->A[6] * Az;
    Rqyi = (-o->A[1] * Ax - o->A[4] * Ay) - o->A[7] * Az;
    Ax = (-o->A[2] * Ax - o->A[5] * Ay) - o->A[8] * Az;
    Ay = o->Xcmp;
    Az = ((((o->Xcmp + o->Rocxip) + o->Wyl * Ax) - o->Wzl * Rqyi) - o->Di *
          o->Dicx) / o->Dipcx;
  } else {
    Ax = o->Di * o->Al11 - o->Rxr;
    Ay = o->Di * o->Al21 - o->Ryr;
    Az = o->Di * o->Al31 - o->Rzr;
    o->Li = (o->Ll11 * Ax + o->Ll12 * Ay) + o->Ll13 * Az;
    Rqyi = (o->Ll21 * Ax + o->Ll22 * Ay) + o->Ll23 * Az;
    Ax = (o->Ll31 * Ax + o->Ll32 * Ay) + o->Ll33 * Az;
    Ay = ((-o->Rocxip - o->Wyl * Ax) + o->Wzl * Rqyi) + o->Di * o->Dicx;
    Az = 0.0;
  }

  Eqeyi = o->Ycm + Rqyi;
  Eqezi = o->Zcm + Ax;
  Modqei = std::sqrt(Eqeyi * Eqeyi + Eqezi * Eqezi);
  Eqeyi = -Eqeyi / Modqei;
  Eqezi = -Eqezi / Modqei;
  Eqexri = o->Ll21 * Eqeyi + o->Ll31 * Eqezi;
  Eqeyri = o->Ll22 * Eqeyi + o->Ll32 * Eqezi;
  Eqezri = o->Ll23 * Eqeyi + o->Ll33 * Eqezi;
  Calfai = (Eqexri * o->Al11 + Eqeyri * o->Al21) + Eqezri * o->Al31;
  Salfai = std::sqrt(1.0 - Calfai * Calfai);
  o->Sgamai = (Eqexri * o->Sreta - Eqeyri * o->Creta) / Salfai;
  o->Cgamai = (-(Eqexri * o->Al12 + Eqeyri * o->Al22) + Eqezri * o->Al32) /
    Salfai;
  Eqexri = std::abs(o->Cgamai);
  if (o->Cgamai < 0.0) {
    Eqeyri = -1.0;
  } else if (o->Cgamai > 0.0) {
    Eqeyri = 1.0;
  } else if (o->Cgamai == 0.0) {
    Eqeyri = 0.0;
  } else {
    Eqeyri = (rtNaN);
  }

  if (!(Eqexri < 1.0)) {
    Eqexri = 1.0;
  }

  o->Cgamai = Eqeyri * Eqexri;
  o->Gamai = std::acos(o->Cgamai);
  if (o->Sgamai < 0.0) {
    o->Gamai = 6.2831853071795862 - o->Gamai;
  }

  o->Zci = (Modqei + o->Rti) * Salfai - Dlan / 2.0;
  o->Xi = Dlan * Calfai / (2.0 * Salfai) + o->Di;
  o->Rcxi = o->Li;
  o->Rcyi = o->Rti * Eqeyi + -o->Ycm;
  o->Rczi = o->Rti * Eqezi + -o->Zcm;
  o->Zci *= static_cast<real_T>((o->Xi <= Lr + Ldel));
  Ldel = 0.0;
  if (Modqei != 0.0) {
    Ldel = (((((Az * o->Dipcy + o->Di * o->Dicy) - o->Rocyip) - o->Wzl * o->Li)
             + o->Wxl * Ax) * Eqezi - ((((Az * o->Dipcz + o->Di * o->Dicz) -
               o->Roczip) - o->Wxl * Rqyi) + o->Wyl * o->Li) * Eqeyi) / Modqei;
  }

  Rqyi = ((o->Wyl * o->Rczi + o->Rocxip) - o->Wzl * o->Rcyi) + Ay;
  Ldel *= o->Rti;
  Dlan = (((o->Wzl * o->Rcxi + o->Rocyip) - o->Wxl * o->Rczi) - o->Ycmp) + Ldel *
    Eqezi;
  Ldel = (((o->Wxl * o->Rcyi + o->Roczip) - o->Wyl * o->Rcxi) - o->Zcmp) - Ldel *
    Eqeyi;
  Ax = (o->Ll11 * Rqyi + o->Ll21 * Dlan) + o->Ll31 * Ldel;
  Ay = (o->Ll12 * Rqyi + o->Ll22 * Dlan) + o->Ll32 * Ldel;
  o->Zcip = ((o->Al12 * Ax + o->Al22 * Ay) - ((o->Ll13 * Rqyi + o->Ll23 * Dlan)
              + o->Ll33 * Ldel) * o->Al32) * -o->Cgamai - (Ay * o->Creta - Ax *
    o->Sreta) * o->Sgamai;
}

void mod_fogguiModelClass::mod_foggui_Traj_Cr_tubo(Traj_mod_foggui_T *o)
{
  real_T Mir;
  real_T Ax;
  real_T Sgamao;
  real_T Cgamao;
  real_T Fryri;
  Mir = o->modelo.dados_part.Mir;
  if (o->Vx != 0.0) {
    Sgamao = o->Wx * o->modelo.dados_part.Rt;
    Ax = std::sqrt(o->Vx * o->Vx + Sgamao * Sgamao);
    Sgamao /= Ax;
    Cgamao = o->Vx / Ax;
  } else {
    Sgamao = 0.0;
    Cgamao = 1.0;
  }

  o->Kk = std::sqrt(o->modelo.dados_part.Ktubo * o->Massa) * o->Zcip +
    o->modelo.dados_part.Ktubo * o->Zci;
  o->Kk *= static_cast<real_T>((o->Kk > 0.0));
  Ax = (o->Cgamai * o->Al12 - o->Sgamai * o->Sreta) - ((o->Sgamai * o->Al12 +
    o->Cgamai * o->Sreta) * Sgamao + Cgamao * o->Al11) * Mir;
  Fryri = (o->Cgamai * o->Al22 + o->Sgamai * o->Creta) - ((o->Sgamai * o->Al22 -
    o->Cgamai * o->Creta) * Sgamao + Cgamao * o->Al21) * Mir;
  Mir = -o->Cgamai * o->Al32 - (Cgamao * o->Al31 - Sgamao * o->Sgamai * o->Al32)
    * Mir;
  o->Frxi = (o->Ll11 * Ax + o->Ll12 * Fryri) + o->Ll13 * Mir;
  o->Fryi = (o->Ll21 * Ax + o->Ll22 * Fryri) + o->Ll23 * Mir;
  o->Frzi = (o->Ll31 * Ax + o->Ll32 * Fryri) + o->Ll33 * Mir;
  o->Mrxi = o->Frzi * o->Rcyi - o->Fryi * o->Rczi;
  o->Mryi = o->Frxi * o->Rczi - o->Frzi * o->Rcxi;
  o->Mrzi = o->Fryi * o->Rcxi - o->Frxi * o->Rcyi;
}

void mod_fogguiModelClass::mod_foggui_Traj_Tip_off(Traj_mod_foggui_T *o)
{
  real_T Lr;
  real_T Mir;
  real_T Rt;
  real_T Xfim;
  real_T Xt1;
  real_T Xt2;
  real_T Xt3;
  real_T Dr;
  real_T Grot0;
  real_T G0;
  real_T R11;
  real_T R12;
  real_T R21;
  real_T R22;
  real_T R31;
  real_T R32;
  int32_T p1;
  int32_T p2;
  int32_T p3;
  int32_T itmp;
  real_T x_idx_1;
  real_T x_idx_4;
  real_T x_idx_7;
  real_T x_idx_5;
  real_T x_idx_8;
  real_T R12_tmp;
  Lr = o->modelo.dados_part.Lr;
  Mir = o->modelo.dados_part.Mir;
  Rt = o->modelo.dados_part.Rt;
  Xfim = o->modelo.dados_part.Xfim;
  Xt1 = o->modelo.dados_part.Xt1;
  Xt2 = o->modelo.dados_part.Xt2;
  Xt3 = o->modelo.dados_part.Xt3;
  Dr = o->modelo.geometria.Dr;
  Grot0 = o->modelo.propelente.Grot0;
  G0 = o->modelo.cte.G0;
  mod_foggui_Traj_Cdist(o);
  R11 = o->Slat * o->modelo.tip_off.Srlat * o->Cdlong + o->Clat *
    o->modelo.tip_off.Crlat;
  R12 = -o->modelo.tip_off.Srlat * o->Sdlong;
  R21 = o->Slat * o->Sdlong;
  R22 = o->Cdlong;
  R31 = -o->Slat * o->modelo.tip_off.Crlat * o->Cdlong + o->Clat *
    o->modelo.tip_off.Srlat;
  R32 = o->modelo.tip_off.Crlat * o->Sdlong;
  o->Ll11 = (o->L11 * R11 + o->L12 * R21) + o->L13 * R31;
  o->Ll12 = (o->L11 * R12 + o->L12 * R22) + o->L13 * R32;
  o->Ll13 = (o->L11 * o->R13 + o->L12 * o->R23) + o->L13 * o->R33;
  o->Ll21 = (o->L21 * R11 + o->L22 * R21) + o->L23 * R31;
  o->Ll22 = (o->L21 * R12 + o->L22 * R22) + o->L23 * R32;
  o->Ll23 = (o->L21 * o->R13 + o->L22 * o->R23) + o->L23 * o->R33;
  o->Ll31 = (o->L31 * R11 + o->L32 * R21) + o->L33 * R31;
  o->Ll32 = (o->L31 * R12 + o->L32 * R22) + o->L33 * R32;
  o->Ll33 = (o->L31 * o->R13 + o->L32 * o->R23) + o->L33 * o->R33;
  R11 = (o->Ll11 * o->Rxr + o->Ll12 * o->Ryr) + o->Ll13 * o->Rzr;
  R12 = (o->Ll21 * o->Rxr + o->Ll22 * o->Ryr) + o->Ll23 * o->Rzr;
  R21 = (o->Ll31 * o->Rxr + o->Ll32 * o->Ryr) + o->Ll33 * o->Rzr;
  o->Rocxip = (o->Wgyb * R21 + o->Vx) - o->Wgzb * R12;
  o->Rocyip = (o->Wgzb * R11 + o->Vy) - o->Wgxb * R21;
  o->Roczip = (o->Wgxb * R12 + o->Vz) - o->Wgyb * R11;
  R11 = -o->Al21 * o->Wgz;
  R12 = o->Al11 * o->Wgz - o->Al31 * o->Wgx;
  R21 = o->Al21 * o->Wgx;
  o->Dicx = (o->Ll11 * R11 + o->Ll12 * R12) + o->Ll13 * R21;
  o->Dicy = (o->Ll21 * R11 + o->Ll22 * R12) + o->Ll23 * R21;
  o->Dicz = (o->Ll31 * R11 + o->Ll32 * R12) + o->Ll33 * R21;
  o->Dipcx = (o->Ll11 * o->Al11 + o->Ll12 * o->Al21) + o->Ll13 * o->Al31;
  o->Dipcy = (o->Ll21 * o->Al11 + o->Ll22 * o->Al21) + o->Ll23 * o->Al31;
  o->Dipcz = (o->Ll31 * o->Al11 + o->Ll32 * o->Al21) + o->Ll33 * o->Al31;
  R22 = -o->Al11;
  R31 = o->Ll21;
  R32 = o->Ll31;
  x_idx_1 = -o->Al21;
  x_idx_4 = o->Ll22;
  x_idx_7 = o->Ll32;
  R12_tmp = -o->Al31;
  x_idx_5 = o->Ll23;
  x_idx_8 = o->Ll33;
  p1 = 0;
  p2 = 3;
  p3 = 6;
  R11 = std::abs(-o->Al11);
  R12 = std::abs(-o->Al21);
  R21 = std::abs(-o->Al31);
  if ((R12 > R11) && (R12 > R21)) {
    p1 = 3;
    p2 = 0;
    R22 = -o->Al21;
    x_idx_1 = -o->Al11;
    R31 = o->Ll22;
    x_idx_4 = o->Ll21;
    R32 = o->Ll32;
    x_idx_7 = o->Ll31;
  } else {
    if (R21 > R11) {
      p1 = 6;
      p3 = 0;
      R22 = -o->Al31;
      R12_tmp = -o->Al11;
      R31 = o->Ll23;
      x_idx_5 = o->Ll21;
      R32 = o->Ll33;
      x_idx_8 = o->Ll31;
    }
  }

  R21 = x_idx_1 / R22;
  x_idx_1 = R21;
  R12_tmp /= R22;
  x_idx_4 -= R21 * R31;
  x_idx_5 -= R12_tmp * R31;
  x_idx_7 -= R21 * R32;
  x_idx_8 -= R12_tmp * R32;
  if (std::abs(x_idx_5) > std::abs(x_idx_4)) {
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    x_idx_1 = R12_tmp;
    R12_tmp = R21;
    R11 = x_idx_4;
    x_idx_4 = x_idx_5;
    x_idx_5 = R11;
    R11 = x_idx_7;
    x_idx_7 = x_idx_8;
    x_idx_8 = R11;
  }

  R21 = x_idx_5 / x_idx_4;
  x_idx_8 -= R21 * x_idx_7;
  R11 = (R21 * x_idx_1 - R12_tmp) / x_idx_8;
  R12 = -(x_idx_7 * R11 + x_idx_1) / x_idx_4;
  o->A[p1] = ((1.0 - R31 * R12) - R32 * R11) / R22;
  o->A[p1 + 1] = R12;
  o->A[p1 + 2] = R11;
  R11 = -R21 / x_idx_8;
  R12 = (1.0 - x_idx_7 * R11) / x_idx_4;
  o->A[p2] = -(R31 * R12 + R32 * R11) / R22;
  o->A[p2 + 1] = R12;
  o->A[p2 + 2] = R11;
  R11 = 1.0 / x_idx_8;
  R12 = -x_idx_7 * R11 / x_idx_4;
  o->A[p3] = -(R31 * R12 + R32 * R11) / R22;
  o->A[p3 + 1] = R12;
  o->A[p3 + 2] = R11;
  o->Rti = Rt;
  o->Li = o->Xcm - Xfim;
  mod_foggui_Traj_Cp_contato(o);
  if (o->Zci > 0.0) {
    mod_foggui_Traj_Cr_tubo(o);
    o->Frx += o->Kk * o->Frxi;
    o->Fry += o->Kk * o->Fryi;
    o->Frz += o->Kk * o->Frzi;
    o->Mrx += o->Kk * o->Mrxi;
    o->Mry += o->Kk * o->Mryi;
    o->Mrz += o->Kk * o->Mrzi;
  }

  if (o->F < 4.0) {
    o->Li = o->Xcm - Xt3;
    mod_foggui_Traj_Cp_contato(o);
    if (o->Zci > 0.0) {
      mod_foggui_Traj_Cr_tubo(o);
      o->Frx += o->Kk * o->Frxi;
      o->Fry += o->Kk * o->Fryi;
      o->Frz += o->Kk * o->Frzi;
      o->Mrx += o->Kk * o->Mrxi;
      o->Mry += o->Kk * o->Mryi;
      o->Mrz += o->Kk * o->Mrzi;
    }
  }

  if (o->F < 3.0) {
    o->Li = o->Xcm - Xt2;
    mod_foggui_Traj_Cp_contato(o);
    if (o->Zci > 0.0) {
      mod_foggui_Traj_Cr_tubo(o);
      o->Frx += o->Kk * o->Frxi;
      o->Fry += o->Kk * o->Fryi;
      o->Frz += o->Kk * o->Frzi;
      o->Mrx += o->Kk * o->Mrxi;
      o->Mry += o->Kk * o->Mryi;
      o->Mrz += o->Kk * o->Mrzi;
    }
  }

  if (o->F == 1.0) {
    o->Li = o->Xcm - Xt1;
    mod_foggui_Traj_Cp_contato(o);
  } else {
    o->Rti = Dr / 2.0;
    o->Di = 0.0;
    o->Xi = 0.0;
    o->Di = (o->Di + Lr) - o->Xi;
    mod_foggui_Traj_Cp_contato(o);
    o->Di = (o->Di + Lr) - o->Xi;
    mod_foggui_Traj_Cp_contato(o);
    o->Di = (o->Di + Lr) - o->Xi;
    mod_foggui_Traj_Cp_contato(o);
  }

  if (o->Zci > 0.0) {
    mod_foggui_Traj_Cr_tubo(o);
    o->Frx += o->Kk * o->Frxi;
    o->Fry += o->Kk * o->Fryi;
    o->Frz += o->Kk * o->Frzi;
    o->Mrx += o->Kk * o->Mrxi;
    o->Mry += o->Kk * o->Mryi;
    o->Mrz += o->Kk * o->Mrzi;
  }

  if (Grot0 != 0.0) {
    o->Matr = Mir * o->Massa * G0 * o->Crgama * Dr / 2.0;
  }
}

real_T mod_fogguiModelClass::mod_foggui_Traj_Cnemp(const Traj_mod_foggui_T *o,
  real_T Alf, real_T *Dcna, real_T Cna2e, real_T Cna3e)
{
  real_T Cn;
  real_T Malfa;
  Malfa = std::abs(Alf);
  Cn = ((Malfa * Cna3e + Cna2e) * Malfa + o->Cnae) * Alf;
  *Dcna += (3.0 * Malfa * Cna3e + 2.0 * Cna2e) * Malfa;
  return Cn;
}

void mod_fogguiModelClass::mod_foggui_Traj_Empena_canard(Traj_mod_foggui_T *o,
  real_T Im, real_T Ym)
{
  real_T Alfa1_c;
  real_T Alfa2_c;
  real_T Alfa3_c;
  real_T Alfa4_c;
  real_T Cnae_c;
  real_T Cna2e_c;
  real_T Cna3e_c;
  real_T Kde_c;
  real_T Rcpe_c;
  real_T V0_c;
  real_T Lcpe2;
  real_T Vs1_c;
  real_T Vs2_c;
  real_T Va1_c;
  real_T Va2_c;
  int32_T Cx_c;
  real_T Cn1_c;
  real_T Dcna_c;
  real_T Malfa_c;
  real_T Cy1_c;
  real_T Cz2_c;
  real_T Cy3_c;
  int32_T Cna2e_c_tmp;
  int32_T Cna2e_c_tmp_0;
  int32_T Cna2e_c_tmp_tmp;
  int32_T Cna3e_c_tmp;
  Alfa1_c = 0.0;
  Alfa2_c = 0.0;
  Alfa3_c = 0.0;
  Alfa4_c = 0.0;
  Cna2e_c_tmp_tmp = (static_cast<int32_T>(Im) - 1) * 25;
  Cna2e_c_tmp = Cna2e_c_tmp_tmp + 13;
  Cna2e_c_tmp_0 = (static_cast<int32_T>((Im + 1.0)) - 1) * 25;
  Cna2e_c = ((o->modelo.C[Cna2e_c_tmp_0 + 13] - o->modelo.C[Cna2e_c_tmp]) * Ym +
             o->modelo.C[Cna2e_c_tmp]) * 0.1155;
  Cna3e_c_tmp = Cna2e_c_tmp_tmp + 14;
  Cna3e_c = ((o->modelo.C[Cna2e_c_tmp_0 + 14] - o->modelo.C[Cna3e_c_tmp]) * Ym +
             o->modelo.C[Cna3e_c_tmp]) * 0.1155;
  Cna2e_c_tmp = Cna2e_c_tmp_tmp + 2;
  Kde_c = ((o->modelo.C[Cna2e_c_tmp_0 + 2] - o->modelo.C[Cna2e_c_tmp]) * Ym +
           o->modelo.C[Cna2e_c_tmp]) * 0.1155;
  Rcpe_c = (2.0 * o->modelo.geometria.Dr + 0.11) / (4.0 * o->modelo.geometria.Dr);
  V0_c = (o->Wx - o->Whxb) * 0.5 * Rcpe_c * o->modelo.geometria.Dr;
  Vs1_c = (0.556 - o->Xcm) * o->Wbhy + o->Vaz;
  Vs2_c = o->Vay - (0.556 - o->Xcm) * o->Wbhz;
  Lcpe2 = (0.556 - o->Xcm) / o->modelo.geometria.Dr;
  Va2_c = o->Vax * o->Vax;
  Va1_c = std::sqrt(Va2_c + Vs2_c * Vs2_c);
  Va2_c = std::sqrt(Va2_c + Vs1_c * Vs1_c);
  Cna2e_c_tmp = Cna2e_c_tmp_tmp + 12;
  Cnae_c = ((o->modelo.C[Cna2e_c_tmp_0 + 12] - o->modelo.C[Cna2e_c_tmp]) * Ym +
            o->modelo.C[Cna2e_c_tmp]) * 0.1155 * o->k_canard;
  if (o->CanardON != 0) {
    if ((Va1_c != 0.0) && (Va2_c != 0.0)) {
      mod_foggui_DW.Dalfa_c = 0.0 - (Va1_c + Va2_c) * V0_c / (2.0 * Va1_c *
        Va2_c);
    }

    Cx_c = (std::abs(mod_foggui_DW.Dalfa_c) > o->modelo.cte.Ateps);
    V0_c *= static_cast<real_T>(Cx_c);
    if ((Va1_c != 0.0) && (Va2_c != 0.0)) {
      Alfa1_c = o->CanardAng1 - (Vs1_c + V0_c) / o->Vax;
      Alfa2_c = o->CanardAng2 - (Vs2_c - V0_c) / o->Vax;
      Alfa3_c = o->CanardAng3 - (Vs1_c - V0_c) / o->Vax;
      Alfa4_c = o->CanardAng4 - (Vs2_c + V0_c) / o->Vax;
    }

    Cn1_c = Cnae_c * Alfa1_c;
    Cy3_c = Cnae_c * Alfa2_c;
    Cz2_c = Cnae_c * Alfa3_c;
    Cy1_c = Cnae_c * Alfa4_c;
    Va1_c = Kde_c * Cn1_c * Cn1_c;
    Va2_c = Kde_c * Cz2_c * Cz2_c;
    Kde_c = Kde_c * Cy1_c * Cy1_c;
    Dcna_c = 4.0 * Cnae_c;
    if (std::abs(Alfa1_c) > o->modelo.aero.Atlin0) {
      Alfa1_c = o->CanardAng1 - std::atan((Vs1_c + V0_c) / o->Vax);
      Malfa_c = std::abs(Alfa1_c);
      Dcna_c += (3.0 * Malfa_c * Cna3e_c + 2.0 * Cna2e_c) * Malfa_c;
      Cn1_c = ((Malfa_c * Cna3e_c + Cna2e_c) * Malfa_c + Cnae_c) * Alfa1_c;
      Va1_c = 0.0;
    }

    if (std::abs(Alfa2_c) > o->modelo.aero.Atlin0) {
      Alfa2_c = o->CanardAng2 - std::atan((Vs2_c - V0_c) / o->Vax);
      Malfa_c = std::abs(Alfa2_c);
      Dcna_c += (3.0 * Malfa_c * Cna3e_c + 2.0 * Cna2e_c) * Malfa_c;
      Cy3_c = ((Malfa_c * Cna3e_c + Cna2e_c) * Malfa_c + Cnae_c) * Alfa2_c;
    }

    if (std::abs(Alfa3_c) > o->modelo.aero.Atlin0) {
      Alfa3_c = o->CanardAng3 - std::atan((Vs1_c - V0_c) / o->Vax);
      Malfa_c = std::abs(Alfa3_c);
      Dcna_c += (3.0 * Malfa_c * Cna3e_c + 2.0 * Cna2e_c) * Malfa_c;
      Cz2_c = ((Malfa_c * Cna3e_c + Cna2e_c) * Malfa_c + Cnae_c) * Alfa3_c;
      Va2_c = 0.0;
    }

    if (std::abs(Alfa4_c) > o->modelo.aero.Atlin0) {
      Alfa4_c = o->CanardAng4 - std::atan((Vs2_c + V0_c) / o->Vax);
      Malfa_c = std::abs(Alfa4_c);
      Dcna_c += (3.0 * Malfa_c * Cna3e_c + 2.0 * Cna2e_c) * Malfa_c;
      Cy1_c = ((Malfa_c * Cna3e_c + Cna2e_c) * Malfa_c + Cnae_c) * Alfa4_c;
      Kde_c = 0.0;
    }

    Cna3e_c_tmp = Cna2e_c_tmp_tmp + 10;
    Cna2e_c_tmp = Cna2e_c_tmp_tmp + 20;
    Cna2e_c = ((o->modelo.C[Cna2e_c_tmp_0 + 20] - o->modelo.C[Cna2e_c_tmp]) * Ym
               + o->modelo.C[Cna2e_c_tmp]) * 0.1155;
    if (Alfa1_c < 0.0) {
      Alfa1_c = -1.0;
    } else if (Alfa1_c > 0.0) {
      Alfa1_c = 1.0;
    } else if (Alfa1_c == 0.0) {
      Alfa1_c = 0.0;
    } else {
      Alfa1_c = (rtNaN);
    }

    Cna3e_c = ((o->modelo.C[Cna2e_c_tmp_0 + 10] - o->modelo.C[Cna3e_c_tmp]) * Ym
               + o->modelo.C[Cna3e_c_tmp]) * 0.1155 * 0.0 *
      o->modelo.geometria.Fnor * Cna2e_c / 4.0 / Rcpe_c;
    Alfa1_c = (Alfa1_c * 0.0 + 1.0) * Cn1_c * o->modelo.geometria.Fnor + Cna3e_c;
    if (Alfa2_c < 0.0) {
      Alfa2_c = -1.0;
    } else if (Alfa2_c > 0.0) {
      Alfa2_c = 1.0;
    } else if (Alfa2_c == 0.0) {
      Alfa2_c = 0.0;
    } else {
      Alfa2_c = (rtNaN);
    }

    Alfa2_c = (Alfa2_c * 0.0 + 1.0) * Cy3_c * o->modelo.geometria.Fnor + Cna3e_c;
    if (Alfa3_c < 0.0) {
      Alfa3_c = -1.0;
    } else if (Alfa3_c > 0.0) {
      Alfa3_c = 1.0;
    } else if (Alfa3_c == 0.0) {
      Alfa3_c = 0.0;
    } else {
      Alfa3_c = (rtNaN);
    }

    Alfa3_c = (Alfa3_c * 0.0 + 1.0) * Cz2_c * o->modelo.geometria.Fnor + Cna3e_c;
    if (Alfa4_c < 0.0) {
      Alfa4_c = -1.0;
    } else if (Alfa4_c > 0.0) {
      Alfa4_c = 1.0;
    } else if (Alfa4_c == 0.0) {
      Alfa4_c = 0.0;
    } else {
      Alfa4_c = (rtNaN);
    }

    Alfa4_c = (Alfa4_c * 0.0 + 1.0) * Cy1_c * o->modelo.geometria.Fnor + Cna3e_c;
    Cy1_c = 0.0 * Alfa1_c;
    Cz2_c = 0.0 * Alfa2_c;
    Cy3_c = 0.0 * Alfa3_c;
    Cna3e_c = 0.0 * Alfa4_c;
  } else {
    Cy1_c = 0.0;
    Cz2_c = 0.0;
    Cy3_c = 0.0;
    Cna3e_c = 0.0;
    Va1_c = 0.0;
    Va2_c = 0.0;
    Kde_c = 0.0;
    Cna2e_c = 1.0;
    Dcna_c = 0.0;
    mod_foggui_DW.Dalfa_c = 0.0;
    Cx_c = 0;
  }

  o->Cfx_c = (Va1_c + Va2_c) + Kde_c;
  o->Cfy_c = ((Cy1_c + Alfa2_c) + Cy3_c) + Alfa4_c;
  o->Cfz_c = ((Alfa1_c + Cz2_c) + Alfa3_c) + Cna3e_c;
  o->Cmx_c = ((((Alfa1_c - Alfa3_c) + Alfa4_c) - Alfa2_c) + Dcna_c *
              mod_foggui_DW.Dalfa_c * (1.0 - static_cast<real_T>(Cx_c))) *
    Rcpe_c / Cna2e_c;
  o->Cmy_c = (((Alfa1_c + Alfa3_c) + Cz2_c) + Cna3e_c) * Lcpe2;
  o->Cmz_c = -(((Cy1_c + Cy3_c) + Alfa2_c) + Alfa4_c) * Lcpe2;
}

void mod_fogguiModelClass::mod_foggui_Traj_Comb(Traj_mod_foggui_T *o)
{
  real_T Fcd;
  real_T Dr;
  Fcd = o->modelo.cte.Fcd;
  Dr = o->modelo.geometria.Dr;
  if (o->F <= 1.0) {
    o->Cfx = 2.0;
    o->Cfy = 0.0;
    o->Cfz = 0.0;
    o->Cmx = 0.0;
    o->Cmy = 0.0;
    o->Cmz = 0.0;
    o->Alfab = 0.0;
  }

  o->Fax = -o->Cfx * o->Arpd * Fcd * o->Fcdsep;
  o->Fay = o->Cfy * o->Arpd;
  o->Faz = o->Cfz * o->Arpd;
  Fcd = o->Arpd * Dr;
  o->Max = (o->Cmx * Fcd - o->Faz * o->Ycm) + o->Fay * o->Zcm;
  o->May = o->Cmy * Fcd - o->Fax * o->Zcm;
  o->Maz = o->Cmz * Fcd + o->Fax * o->Ycm;
}

real_T mod_fogguiModelClass::mod_foggui_interp1(const real_T varargin_1[40],
  const real_T varargin_2[40], real_T varargin_3)
{
  real_T Vq;
  real_T y[40];
  real_T x[40];
  real_T xtmp;
  int32_T low_i;
  int32_T low_ip1;
  int32_T high_i;
  int32_T mid_i;
  int32_T exitg1;
  std::memcpy(&y[0], &varargin_2[0], 40U * sizeof(real_T));
  std::memcpy(&x[0], &varargin_1[0], 40U * sizeof(real_T));
  Vq = (rtNaN);
  low_i = 0;
  do {
    exitg1 = 0;
    if (low_i < 40) {
      if (rtIsNaN(varargin_1[low_i])) {
        exitg1 = 1;
      } else {
        low_i++;
      }
    } else {
      if (varargin_1[1] < varargin_1[0]) {
        for (low_i = 0; low_i < 20; low_i++) {
          xtmp = x[low_i];
          x[low_i] = x[39 - low_i];
          x[39 - low_i] = xtmp;
        }

        for (low_i = 0; low_i < 20; low_i++) {
          xtmp = y[low_i];
          y[low_i] = y[39 - low_i];
          y[39 - low_i] = xtmp;
        }
      }

      if ((!rtIsNaN(varargin_3)) && (!(varargin_3 > x[39])) && (!(varargin_3 <
            x[0]))) {
        low_i = 1;
        low_ip1 = 2;
        high_i = 40;
        while (high_i > low_ip1) {
          mid_i = (low_i + high_i) >> 1;
          if (varargin_3 >= x[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }

        xtmp = x[low_i - 1];
        xtmp = (varargin_3 - xtmp) / (x[low_i] - xtmp);
        if (xtmp == 0.0) {
          Vq = y[low_i - 1];
        } else if (xtmp == 1.0) {
          Vq = y[low_i];
        } else {
          Vq = y[low_i - 1];
          if (!(Vq == y[low_i])) {
            Vq = (1.0 - xtmp) * Vq + xtmp * y[low_i];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Vq;
}

void mod_fogguiModelClass::mod_foggui_Traj_debug(const Traj_mod_foggui_T *o,
  syf7A5HdRUQxXfDjUTEKnuC_mod_foggui_T *o_)
{
  o_->Pi180 = 0.017453292519943295;
  o_->Pis2 = 1.5707963267948966;
  o_->Pi2 = 6.2831853071795862;
  o_->Href = 1.0E-5;
  o_->Hdel = 1.0E-6;
  o_->Dpit0 = 1.0;
  o_->Wdel = 0.0017453292519943296;
  o_->Wpdel = 0.0017453292519943296;
  o_->Romin = 0.01;
  o_->Atmin = 0.0017453292519943296;
  o_->Kquat = 1.0;
  o_->P0 = 94540.0;
  o_->Smax = 0.9999;
  o_->Fase_fim = o->Fase_fim;
  o_->Apo = o->Apo;
  o_->Pit0 = o->Pit0;
  o_->Maxv = o->Maxv;
  o_->H = o->H;
  o_->Htabv = o->Htabv;
  o_->Flw = o->Flw;
  o_->Refcam = o->Refcam;
  o_->Retrot = o->Retrot;
  o_->Vhor[0] = o->Vhor[0];
  o_->Vhor[1] = o->Vhor[1];
  o_->Tfim = o->Tfim;
  o_->Vwx = o->Vwx;
  o_->Vwy = o->Vwy;
  o_->Vwz = o->Vwz;
  o_->T_emp = o->T_emp;
  o_->modelo = o->modelo;
  o_->Phi = o->Phi;
  o_->Teta = o->Teta;
  o_->Psi = o->Psi;
  o_->Qt1 = o->Qt1;
  o_->Qt2 = o->Qt2;
  o_->Qt3 = o->Qt3;
  o_->Qt4 = o->Qt4;
  o_->Wx = o->Wx;
  o_->Wy = o->Wy;
  o_->Wz = o->Wz;
  o_->Wx_p = o->Wx_p;
  o_->Wy_p = o->Wy_p;
  o_->Wz_p = o->Wz_p;
  o_->Vx = o->Vx;
  o_->Vy = o->Vy;
  o_->Vz = o->Vz;
  o_->Vx_p = o->Vx_p;
  o_->Vy_p = o->Vy_p;
  o_->Vz_p = o->Vz_p;
  o_->Vax = o->Vax;
  o_->Vay = o->Vay;
  o_->Vaz = o->Vaz;
  o_->Vxh = o->Vxh;
  o_->Vyh = o->Vyh;
  o_->Vzh = o->Vzh;
  o_->Dlat = o->Dlat;
  o_->Dlong = o->Dlong;
  o_->Dalt = o->Dalt;
  o_->Fax = o->Fax;
  o_->Fay = o->Fay;
  o_->Faz = o->Faz;
  o_->Max = o->Max;
  o_->May = o->May;
  o_->Maz = o->Maz;
  o_->Z = o->Z;
  o_->Tant = o->Tant;
  o_->Kb = o->Kb;
  o_->Kc = o->Kc;
  o_->Rot0 = o->Rot0;
  o_->Gir0 = o->Gir0;
  o_->Cphia = o->Cphia;
  o_->Fgrot = o->Fgrot;
  o_->Tempo = o->Tempo;
  o_->Dkw = o->Dkw;
  o_->Kw = o->Kw;
  o_->Kh = o->Kh;
  o_->Ksub = o->Ksub;
  o_->Vxfmr = o->Vxfmr;
  o_->Hkeep = o->Hkeep;
  o_->Van = o->Van;
  o_->Alfap = o->Alfap;
  o_->Alfa1 = o->Alfa1;
  o_->Alfa2 = o->Alfa2;
  o_->Alfa3 = o->Alfa3;
  o_->Alfa4 = o->Alfa4;
  o_->Alfab = o->Alfab;
  o_->Dkh = o->Dkh;
  o_->Fesp = o->Fesp;
  o_->Alfat = o->Alfat;
  o_->Betat = o->Betat;
  o_->Tetap = o->Tetap;
  o_->Psip = o->Psip;
  o_->Wytp = o->Wytp;
  o_->Wztp = o->Wztp;
  o_->Vytp = o->Vytp;
  o_->Vztp = o->Vztp;
  o_->Wla = o->Wla;
  o_->Wno = o->Wno;
  o_->Cno = o->Cno;
  o_->Cla = o->Cla;
  o_->Cmno = o->Cmno;
  o_->Cmla = o->Cmla;
  o_->Cnow = o->Cnow;
  o_->Cnoap = o->Cnoap;
  o_->Sphia = o->Sphia;
  o_->Cmlas = o->Cmlas;
  o_->Cmlaw = o->Cmlaw;
  o_->Cmlaap = o->Cmlaap;
  o_->Root = o->Root;
  o_->Cna = o->Cna;
  o_->Cnq = o->Cnq;
  o_->Cnap = o->Cnap;
  o_->Cma = o->Cma;
  o_->Cmq = o->Cmq;
  o_->Cmap = o->Cmap;
  o_->Cnae = o->Cnae;
  o_->Lcpb = o->Lcpb;
  o_->Lcpe = o->Lcpe;
  o_->Tgrot = o->Tgrot;
  o_->Tabin = o->Tabin;
  o_->Tabre = o->Tabre;
  o_->Ttubo = o->Ttubo;
  o_->Vx_pmin = o->Vx_pmin;
  o_->Wtubo = o->Wtubo;
  o_->Vmax = o->Vmax;
  o_->Hapo = o->Hapo;
  o_->Hejec = o->Hejec;
  o_->Vx_pmax = o->Vx_pmax;
  o_->Al11 = o->Al11;
  o_->Al21 = o->Al21;
  o_->Al31 = o->Al31;
  o_->Al12 = o->Al12;
  o_->Al22 = o->Al22;
  o_->Al32 = o->Al32;
  o_->Sreta = o->Sreta;
  o_->Creta = o->Creta;
  o_->Slat = o->Slat;
  o_->Clat = o->Clat;
  o_->Rb = o->Rb;
  o_->T = o->T;
  o_->Massa = o->Massa;
  o_->Ix = o->Ix;
  o_->Iy = o->Iy;
  o_->Iz = o->Iz;
  o_->Ixy = o->Ixy;
  o_->Ixz = o->Ixz;
  o_->Iyz = o->Iyz;
  o_->Jxx = o->Jxx;
  o_->Jyy = o->Jyy;
  o_->Jzz = o->Jzz;
  o_->Jxy = o->Jxy;
  o_->Jxz = o->Jxz;
  o_->Jyz = o->Jyz;
  o_->Km0 = o->Km0;
  o_->Km1 = o->Km1;
  o_->Km2 = o->Km2;
  o_->Xcm = o->Xcm;
  o_->Ycm = o->Ycm;
  o_->Zcm = o->Zcm;
  o_->Xcmp = o->Xcmp;
  o_->Ycmp = o->Ycmp;
  o_->Zcmp = o->Zcmp;
  o_->Grot = o->Grot;
  o_->Roex = o->Roex;
  o_->Roey = o->Roey;
  o_->Roez = o->Roez;
  o_->Vm = o->Vm;
  o_->Ixd = o->Ixd;
  o_->Iyd = o->Iyd;
  o_->Izd = o->Izd;
  o_->Tx = o->Tx;
  o_->Acontr = o->Acontr;
  o_->Linf = o->Linf;
  o_->Lsup = o->Lsup;
  o_->Crgama = o->Crgama;
  o_->Gb = o->Gb;
  o_->Sgamal = o->Sgamal;
  o_->Ll = o->Ll;
  o_->L11 = o->L11;
  o_->L12 = o->L12;
  o_->L13 = o->L13;
  o_->L21 = o->L21;
  o_->L22 = o->L22;
  o_->L23 = o->L23;
  o_->L31 = o->L31;
  o_->L32 = o->L32;
  o_->L33 = o->L33;
  o_->Eps = o->Eps;
  o_->F = o->F;
  o_->R = o->R;
  o_->Q = o->Q;
  o_->M = o->M;
  o_->Rxr = o->Rxr;
  o_->Ryr = o->Ryr;
  o_->Rzr = o->Rzr;
  o_->Delr = o->Delr;
  o_->Sp = o->Sp;
  o_->Sdlong = o->Sdlong;
  o_->Cdlong = o->Cdlong;
  o_->R13 = o->R13;
  o_->R23 = o->R23;
  o_->R33 = o->R33;
  o_->Hl = o->Hl;
  o_->Hmax = o->Hmax;
  o_->Fat = o->Fat;
  o_->Rot = o->Rot;
  o_->Pit = o->Pit;
  o_->Gir = o->Gir;
  o_->Mod = o->Mod;
  o_->U = o->U;
  o_->List = o->List;
  o_->Parada = o->Parada;
  o_->Fdist = o->Fdist;
  o_->Fang = o->Fang;
  o_->Fder = o->Fder;
  o_->Fcoef = o->Fcoef;
  o_->Fataq = o->Fataq;
  o_->Fpf = o->Fpf;
  o_->Rwx = o->Rwx;
  o_->Rwy = o->Rwy;
  o_->Rwz = o->Rwz;
  o_->Az1 = o->Az1;
  o_->Awz = o->Awz;
  o_->Nw = o->Nw;
  std::memcpy(&o_->Rsul[0], &o->Rsul[0], 48U * sizeof(real_T));
  std::memcpy(&o_->Rles[0], &o->Rles[0], 48U * sizeof(real_T));
  o_->Ws0 = o->Ws0;
  o_->Wl0 = o->Wl0;
  o_->Wv0 = o->Wv0;
  o_->Hven = o->Hven;
  o_->Rzw = o->Rzw;
  o_->Vwexp = o->Vwexp;
  o_->Vw1 = o->Vw1;
  o_->Alfaw = o->Alfaw;
  o_->Ta = o->Ta;
  o_->Ro = o->Ro;
  o_->Pa = o->Pa;
  o_->Vsom = o->Vsom;
  o_->Wxl = o->Wxl;
  o_->Wyl = o->Wyl;
  o_->Wzl = o->Wzl;
  o_->Kquat0 = o->Kquat0;
  o_->Qt1_p = o->Qt1_p;
  o_->Qt2_p = o->Qt2_p;
  o_->Qt3_p = o->Qt3_p;
  o_->Qt4_p = o->Qt4_p;
  o_->Wbhx = o->Wbhx;
  o_->Wbhy = o->Wbhy;
  o_->Wbhz = o->Wbhz;
  o_->Wgxb = o->Wgxb;
  o_->Wgyb = o->Wgyb;
  o_->Wgzb = o->Wgzb;
  o_->Wgx = o->Wgx;
  o_->Wgz = o->Wgz;
  o_->Vwxb = o->Vwxb;
  o_->Vwyb = o->Vwyb;
  o_->Vwzb = o->Vwzb;
  o_->Dlat_p = o->Dlat_p;
  o_->Dlong_p = o->Dlong_p;
  o_->Dalt_p = o->Dalt_p;
  o_->Frx = o->Frx;
  o_->Fry = o->Fry;
  o_->Frz = o->Frz;
  o_->Mrx = o->Mrx;
  o_->Mry = o->Mry;
  o_->Mrz = o->Mrz;
  o_->Matr = o->Matr;
  o_->Ll11 = o->Ll11;
  o_->Ll12 = o->Ll12;
  o_->Ll13 = o->Ll13;
  o_->Ll21 = o->Ll21;
  o_->Ll22 = o->Ll22;
  o_->Ll23 = o->Ll23;
  o_->Ll31 = o->Ll31;
  o_->Ll32 = o->Ll32;
  o_->Ll33 = o->Ll33;
  std::memcpy(&o_->A[0], &o->A[0], 9U * sizeof(real_T));
  o_->Rti = o->Rti;
  o_->Li = o->Li;
  o_->Di = o->Di;
  o_->Xi = o->Xi;
  o_->Zci = o->Zci;
  o_->Zcip = o->Zcip;
  o_->Cgamai = o->Cgamai;
  o_->Sgamai = o->Sgamai;
  o_->Gamai = o->Gamai;
  o_->Rcxi = o->Rcxi;
  o_->Rcyi = o->Rcyi;
  o_->Rczi = o->Rczi;
  o_->Rocxip = o->Rocxip;
  o_->Rocyip = o->Rocyip;
  o_->Roczip = o->Roczip;
  o_->Dicx = o->Dicx;
  o_->Dicy = o->Dicy;
  o_->Dicz = o->Dicz;
  o_->Dipcx = o->Dipcx;
  o_->Dipcy = o->Dipcy;
  o_->Dipcz = o->Dipcz;
  o_->Frxi = o->Frxi;
  o_->Fryi = o->Fryi;
  o_->Frzi = o->Frzi;
  o_->Mrxi = o->Mrxi;
  o_->Mryi = o->Mryi;
  o_->Mrzi = o->Mrzi;
  o_->Kk = o->Kk;
  o_->Pf = o->Pf;
  o_->Qsi = o->Qsi;
  o_->Sm = o->Sm;
  o_->Claw = o->Claw;
  o_->Lcp0 = o->Lcp0;
  o_->Rot1 = o->Rot1;
  o_->Pit1 = o->Pit1;
  o_->Gir1 = o->Gir1;
  o_->Asm = o->Asm;
  o_->Acel = o->Acel;
  o_->Frot = o->Frot;
  o_->Cnab = o->Cnab;
  o_->Xcp0 = o->Xcp0;
  o_->Va = o->Va;
  o_->Arpd = o->Arpd;
  o_->Pd = o->Pd;
  o_->Fcdsep = o->Fcdsep;
  o_->Whxb = o->Whxb;
  o_->Cfx = o->Cfx;
  o_->Cfy = o->Cfy;
  o_->Cfz = o->Cfz;
  o_->Cmx = o->Cmx;
  o_->Cmy = o->Cmy;
  o_->Cmz = o->Cmz;
  o_->F_trans = o->F_trans;
  o_->Rcpe = o->Rcpe;
  o_->Contador = o->Contador;
  o_->Contador_aux = o->Contador_aux;
  o_->CanardON = o->CanardON;
  o_->CanardAng1 = o->CanardAng1;
  o_->CanardAng2 = o->CanardAng2;
  o_->CanardAng3 = o->CanardAng3;
  o_->CanardAng4 = o->CanardAng4;
  o_->Cfx_c = o->Cfx_c;
  o_->Cfy_c = o->Cfy_c;
  o_->Cfz_c = o->Cfz_c;
  o_->Cmx_c = o->Cmx_c;
  o_->Cmz_c = o->Cmz_c;
  o_->Cmy_c = o->Cmy_c;
  o_->controle_z_roll_on = o->controle_z_roll_on;
  o_->controle_z_rollrate_on = o->controle_z_rollrate_on;
  o_->controle_z_rollrate_ref = o->controle_z_rollrate_ref;
}

void mod_fogguiModelClass::mod_foggui_Traj_Forca_canard(Traj_mod_foggui_T *o)
{
  real_T arpd;
  real_T xcpc;
  real_T Lcpc;
  real_T Vs1;
  real_T Vs2;
  real_T V0;
  real_T Alfa1;
  real_T Alfa2;
  real_T cna;
  real_T ca;
  real_T M_idx_1;
  arpd = o->Pd * 0.02461;
  xcpc = mod_foggui_interp1(o->Coef_canard.Mo, o->Coef_canard.xCP, o->Mach) /
    1000.0;
  Lcpc = o->Xcm - xcpc;
  Vs1 = o->Vaz - o->Wbhy * Lcpc;
  Vs2 = o->Wbhz * Lcpc + o->Vay;
  V0 = (o->Wx - o->Whxb) * 0.5 * 0.136;
  Alfa1 = (o->CanardAng1 - std::atan((Vs1 - V0) / o->Vax)) * 57.295779513082323;
  Alfa2 = (o->CanardAng2 - std::atan((Vs2 - V0) / o->Vax)) * 57.295779513082323;
  Vs1 = (-o->CanardAng3 - std::atan((Vs1 + V0) / o->Vax)) * 57.295779513082323;
  Vs2 = (-o->CanardAng4 - std::atan((Vs2 + V0) / o->Vax)) * 57.295779513082323;
  V0 = mod_foggui_interp1(o->Coef_canard.Mo, o->Coef_canard.CMa, o->Mach);
  cna = mod_foggui_interp1(o->Coef_canard.Mo, o->Coef_canard.CNa, o->Mach);
  ca = mod_foggui_interp1(o->Coef_canard.Mo, o->Coef_canard.CA, o->Mach);
  M_idx_1 = -Alfa1 * V0 * arpd * o->modelo.geometria.Dr * Lcpc / xcpc + Vs1 * V0
    * arpd * o->modelo.geometria.Dr * Lcpc / xcpc;
  xcpc = Alfa2 * V0 * arpd * o->modelo.geometria.Dr * Lcpc / xcpc + -Vs2 * V0 *
    arpd * o->modelo.geometria.Dr * Lcpc / xcpc;
  mod_foggui_DW.cont_kimmltz2iq++;
  mod_foggui_Traj_debug(o, &mod_foggui_B.unusedExpr_mbvzarwird);
  o->Fax += ((-std::abs(Alfa1) * ca * arpd + -std::abs(Alfa2) * ca * arpd) +
             -std::abs(Vs1) * ca * arpd) + -std::abs(Vs2) * ca * arpd;
  o->Fay += (((Alfa2 * cna * arpd + 0.0 * arpd) + 0.0 * arpd) + -Vs2 * cna *
             arpd) * 0.0;
  o->Faz += (((Alfa1 * cna * arpd + 0.0 * arpd) + -Vs1 * cna * arpd) + 0.0 *
             arpd) * 0.0;
  o->May += M_idx_1 * 0.0;
  o->Maz += xcpc * 0.0;
}

void mod_fogguiModelClass::mod_foggui_Traj_Empena(Traj_mod_foggui_T *o, real_T
  Im, real_T Ym, real_T Clind)
{
  real_T A11;
  real_T Atlin0;
  real_T Ateps;
  real_T De0;
  real_T Dr;
  real_T Fe;
  real_T Fnor;
  real_T Cna2e;
  real_T Cna3e;
  real_T Kde;
  real_T De_tot;
  real_T V0;
  real_T Vs1;
  real_T Vs2;
  real_T Va2;
  boolean_T Cx;
  real_T Cn1;
  real_T Cn2;
  real_T Cn3;
  real_T Cn4;
  int32_T tmp;
  int32_T tmp_0;
  int32_T Cna2e_tmp;
  A11 = o->modelo.aero.A11;
  Atlin0 = o->modelo.aero.Atlin0;
  std::memcpy(&mod_foggui_B.C_cl54gopm0x[0], &o->modelo.C[0], 1025U * sizeof
              (real_T));
  Ateps = o->modelo.cte.Ateps;
  De0 = o->modelo.geometria.De0;
  Dr = o->modelo.geometria.Dr;
  Fe = o->modelo.geometria.Fe;
  Fnor = o->modelo.geometria.Fnor;
  if (o->F < 7.0) {
    mod_foggui_Traj_Comb(o);
  } else {
    tmp_0 = (static_cast<int32_T>(Im) - 1) * 25;
    Cna2e_tmp = tmp_0 + 12;
    tmp = (static_cast<int32_T>((Im + 1.0)) - 1) * 25;
    o->Cnae = (o->modelo.C[tmp + 12] - o->modelo.C[Cna2e_tmp]) * Ym +
      o->modelo.C[Cna2e_tmp];
    Cna2e_tmp = tmp_0 + 13;
    Cna2e = (mod_foggui_B.C_cl54gopm0x[tmp + 13] -
             mod_foggui_B.C_cl54gopm0x[Cna2e_tmp]) * Ym +
      mod_foggui_B.C_cl54gopm0x[Cna2e_tmp];
    Cna2e_tmp = tmp_0 + 14;
    Cna3e = (mod_foggui_B.C_cl54gopm0x[tmp + 14] -
             mod_foggui_B.C_cl54gopm0x[Cna2e_tmp]) * Ym +
      mod_foggui_B.C_cl54gopm0x[Cna2e_tmp];
    Cna2e_tmp = tmp_0 + 2;
    Kde = (mod_foggui_B.C_cl54gopm0x[tmp + 2] -
           mod_foggui_B.C_cl54gopm0x[Cna2e_tmp]) * Ym +
      mod_foggui_B.C_cl54gopm0x[Cna2e_tmp];
    V0 = (o->Wx - o->Whxb) * 0.5 * o->Rcpe * Dr;
    Cna2e_tmp = tmp_0 + 15;
    o->Lcpe = ((mod_foggui_B.C_cl54gopm0x[tmp + 15] -
                mod_foggui_B.C_cl54gopm0x[Cna2e_tmp]) * Ym +
               mod_foggui_B.C_cl54gopm0x[Cna2e_tmp]) - o->Xcm;
    Vs1 = o->Wbhy * o->Lcpe + o->Vaz;
    Vs2 = o->Vay - o->Wbhz * o->Lcpe;
    o->Lcpe /= Dr;
    Cn3 = o->Vax * o->Vax;
    Dr = std::sqrt(Cn3 + Vs2 * Vs2);
    Va2 = std::sqrt(Cn3 + Vs1 * Vs1);
    if ((Dr != 0.0) && (Va2 != 0.0)) {
      mod_foggui_DW.Dalfa = De0 - (Dr + Va2) * V0 / (2.0 * Dr * Va2);
    }

    Cx = (std::abs(mod_foggui_DW.Dalfa) > Ateps);
    De_tot = De0 * static_cast<real_T>(Cx);
    V0 *= static_cast<real_T>(Cx);
    if ((Dr != 0.0) && (Va2 != 0.0)) {
      o->Alfa1 = De_tot - (Vs1 + V0) / o->Vax;
      o->Alfa2 = -De_tot - (Vs2 - V0) / o->Vax;
      o->Alfa3 = -De_tot - (Vs1 - V0) / o->Vax;
      o->Alfa4 = De_tot - (Vs2 + V0) / o->Vax;
    }

    Cn1 = o->Cnae * o->Alfa1;
    Cn2 = o->Cnae * o->Alfa2;
    Cn3 = o->Cnae * o->Alfa3;
    Cn4 = o->Cnae * o->Alfa4;
    Ateps = Kde * Cn1 * Cn1;
    De0 = Kde * Cn2 * Cn2;
    Dr = Kde * Cn3 * Cn3;
    Va2 = Kde * Cn4 * Cn4;
    Kde = 4.0 * o->Cnae;
    if (std::abs(o->Alfa1) > Atlin0) {
      Ateps = (Vs1 + V0) / o->Vax;
      o->Alfa1 = De_tot - std::atan(Ateps);
      Cn1 = mod_foggui_Traj_Cnemp(o, De_tot - std::atan(Ateps), &Kde, Cna2e,
        Cna3e);
      Ateps = 0.0;
    }

    if (std::abs(o->Alfa2) > Atlin0) {
      De0 = (Vs2 - V0) / o->Vax;
      o->Alfa2 = -De_tot - std::atan(De0);
      Cn2 = mod_foggui_Traj_Cnemp(o, -De_tot - std::atan(De0), &Kde, Cna2e,
        Cna3e);
      De0 = 0.0;
    }

    if (std::abs(o->Alfa3) > Atlin0) {
      Cn3 = (Vs1 - V0) / o->Vax;
      o->Alfa3 = -De_tot - std::atan(Cn3);
      Cn3 = mod_foggui_Traj_Cnemp(o, -De_tot - std::atan(Cn3), &Kde, Cna2e,
        Cna3e);
      Dr = 0.0;
    }

    if (std::abs(o->Alfa4) > Atlin0) {
      Va2 = (Vs2 + V0) / o->Vax;
      o->Alfa4 = De_tot - std::atan(Va2);
      Cn4 = mod_foggui_Traj_Cnemp(o, De_tot - std::atan(Va2), &Kde, Cna2e, Cna3e);
      Va2 = 0.0;
    }

    if (Fe < 0.0) {
      Cna3e = -1.0;
    } else if (Fe > 0.0) {
      Cna3e = 1.0;
    } else if (Fe == 0.0) {
      Cna3e = 0.0;
    } else {
      Cna3e = (rtNaN);
    }

    Cna2e_tmp = tmp_0 + 20;
    Cna2e = (mod_foggui_B.C_cl54gopm0x[tmp + 20] -
             mod_foggui_B.C_cl54gopm0x[Cna2e_tmp]) * Ym +
      mod_foggui_B.C_cl54gopm0x[Cna2e_tmp];
    if (o->Alfa1 < 0.0) {
      De_tot = -1.0;
    } else if (o->Alfa1 > 0.0) {
      De_tot = 1.0;
    } else if (o->Alfa1 == 0.0) {
      De_tot = 0.0;
    } else {
      De_tot = (rtNaN);
    }

    Atlin0 = Clind * Cna3e * Fnor * Cna2e / 4.0 / o->Rcpe;
    Cna3e = (De_tot * Fe + 1.0) * Cn1 * Fnor + Atlin0;
    if (o->Alfa2 < 0.0) {
      De_tot = -1.0;
    } else if (o->Alfa2 > 0.0) {
      De_tot = 1.0;
    } else if (o->Alfa2 == 0.0) {
      De_tot = 0.0;
    } else {
      De_tot = (rtNaN);
    }

    V0 = (1.0 - De_tot * Fe) * Cn2 * Fnor - Atlin0;
    if (o->Alfa3 < 0.0) {
      De_tot = -1.0;
    } else if (o->Alfa3 > 0.0) {
      De_tot = 1.0;
    } else if (o->Alfa3 == 0.0) {
      De_tot = 0.0;
    } else {
      De_tot = (rtNaN);
    }

    Vs2 = (1.0 - De_tot * Fe) * Cn3 * Fnor - Atlin0;
    if (o->Alfa4 < 0.0) {
      De_tot = -1.0;
    } else if (o->Alfa4 > 0.0) {
      De_tot = 1.0;
    } else if (o->Alfa4 == 0.0) {
      De_tot = 0.0;
    } else {
      De_tot = (rtNaN);
    }

    Fe = (De_tot * Fe + 1.0) * Cn4 * Fnor + Atlin0;
    Fnor = A11 * Cna3e;
    Atlin0 = -A11 * V0;
    Vs1 = A11 * Vs2;
    A11 = -A11 * Fe;
    o->Cfx = (((o->Cfx + Ateps) + De0) + Dr) + Va2;
    o->Cfy = (((o->Cfy + V0) + Fe) + Fnor) + Vs1;
    o->Cfz = (((o->Cfz + Cna3e) + Vs2) + Atlin0) + A11;
    o->Cmx = ((((Cna3e - Vs2) + Fe) - V0) + Kde * mod_foggui_DW.Dalfa * (1.0 -
               static_cast<real_T>(Cx))) * o->Rcpe / Cna2e;
    o->Cmy += (((Cna3e + Vs2) + Atlin0) + A11) * o->Lcpe;
    o->Cmz -= (((Fnor + Vs1) + V0) + Fe) * o->Lcpe;
    o->cfx_e = o->Cfx - o->cfx_b;
    o->cfy_e = o->Cfy - o->cfy_b;
    o->cfz_e = o->Cfz - o->cfz_b;
    o->cmx_e = o->Cmx - o->cmx_b;
    o->cmz_e = o->Cmy - o->cmz_b;
    o->cmy_e = o->Cmz - o->cmy_b;
    mod_foggui_Traj_Empena_canard(o, Im, Ym);
    o->Cfx += o->Cfx_c * 0.0;
    o->Cfy += o->Cfy_c;
    o->Cfz += o->Cfz_c;
    o->Cmx += o->Cmx_c;
    o->Cmy += o->Cmy_c;
    o->Cmz += o->Cmz_c;
    mod_foggui_Traj_Comb(o);
    mod_foggui_Traj_Forca_canard(o);
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Aero(Traj_mod_foggui_T *o)
{
  real_T A1;
  real_T A3;
  real_T A6;
  real_T A8;
  real_T Ar;
  real_T Atlin0;
  real_T Ltab;
  real_T Msep;
  real_T Nova_trans;
  real_T Tfq;
  real_T Tsep;
  real_T Dmach;
  real_T Fcd;
  real_T Dsub;
  real_T Fcdsub;
  real_T Msub;
  real_T Dalfog0;
  real_T Dr;
  real_T Mf;
  real_T T_trans;
  real_T Tb0;
  real_T Bz;
  int32_T J;
  int32_T Fcd_tmp;
  int32_T Fcd_tmp_0;
  int32_T Mf_tmp;
  A1 = o->modelo.aero.A1;
  A3 = o->modelo.aero.A3;
  A6 = o->modelo.aero.A6;
  A8 = o->modelo.aero.A8;
  Ar = o->modelo.aero.Ar;
  Atlin0 = o->modelo.aero.Atlin0;
  Ltab = o->modelo.aero.Ltab;
  Msep = o->modelo.aero.Msep;
  Nova_trans = o->modelo.aero.Nova_trans;
  Tfq = o->modelo.aero.Tfq;
  Tsep = o->modelo.aero.Tsep;
  std::memcpy(&mod_foggui_B.C[0], &o->modelo.C[0], 1025U * sizeof(real_T));
  Dmach = o->modelo.cte.Dmach;
  Fcd = o->modelo.cte.Fcd;
  Dsub = o->modelo.dados_part.Dsub;
  Fcdsub = o->modelo.dados_part.Fcdsub;
  Msub = o->modelo.dados_part.Msub;
  Dalfog0 = o->modelo.geometria.Dalfog0;
  Dr = o->modelo.geometria.Dr;
  Mf = o->modelo.inercia.Mf;
  T_trans = o->modelo.propelente.T_trans;
  Tb0 = o->modelo.propelente.Tb0;
  Bz = 0.0;
  o->Alfab = 0.0;
  o->Cmx = 0.0;
  o->Cmy = 0.0;
  o->Cmz = 0.0;
  o->Cfy = 0.0;
  o->Cfz = 0.0;
  Dalfog0 = o->Vax * Dalfog0 + o->Vaz;
  o->Van = Dalfog0 * Dalfog0 + o->Vay * o->Vay;
  o->Pd = (o->Vax * o->Vax + o->Vay * o->Vay) + o->Vaz * o->Vaz;
  o->Va = std::sqrt(o->Pd);
  o->Van = std::sqrt(o->Van);
  o->Pd = o->Ro * o->Pd / 2.0;
  o->Mach = o->Va / o->Vsom;
  o->Arpd = Ar * o->Pd;
  Ar = o->Mach / Dmach + 1.0;
  if (Ar < 0.0) {
    Dmach = std::ceil(Ar);
  } else {
    Dmach = std::floor(Ar);
  }

  if ((Ltab - 1.0 < Dmach) || rtIsNaN(Dmach)) {
    Ltab--;
  } else {
    Ltab = Dmach;
  }

  Ar -= Ltab;
  if (o->Tempo > Tfq) {
    o->Massa = Mf;
  }

  if (o->Tempo > Tfq + Tsep) {
    o->Fcdsep = 1.0;
    o->Massa = Msep;
  }

  if (o->Fesp != 0.0) {
    J = 1;
    if (Fcdsub == 0.0) {
      J = 16;
    }

    Mf_tmp = (static_cast<int32_T>(Ltab) - 1) * 25 + J;
    o->Cfx = (mod_foggui_B.C[(static_cast<int32_T>((Ltab + 1.0)) - 1) * 25 + J]
              - mod_foggui_B.C[Mf_tmp]) * Ar + mod_foggui_B.C[Mf_tmp];
    Bz = Dsub / Dr;
    o->Cfx = Bz * Bz * o->Cfx * (o->Massa / Msub);
    if (Fcdsub != 0.0) {
      o->Cfx *= Fcdsub;
    }

    o->Fax = -o->Cfx * o->Arpd * Fcd;
    o->Fay = 0.0;
    o->Faz = 0.0;
    o->Max = 0.0;
    o->May = 0.0;
    o->Maz = 0.0;
  } else {
    o->F_trans = 0.0;
    if (Nova_trans != 0.0) {
      if (o->Tempo <= Tfq + T_trans) {
        if (o->Tempo <= Tfq) {
          Tsep = o->Tempo / Tb0;
          Msep = (12.3325 - 24.0525 * Tsep) + 11.9592 * Tsep * Tsep;
          if ((1.0 < Msep) || rtIsNaN(Msep)) {
            o->F_trans = 1.0;
            mod_foggui_DW.F_aux = 1.0;
          } else {
            o->F_trans = Msep;
            mod_foggui_DW.F_aux = Msep;
          }
        } else {
          o->F_trans = (1.0 - (o->Tempo - Tfq) / T_trans) * mod_foggui_DW.F_aux;
        }
      }
    } else {
      Dalfog0 = Tfq - o->Tempo;
      if (std::abs(Dalfog0) < T_trans) {
        o->F_trans = (Dalfog0 / T_trans + 1.0) / 2.0;
      } else {
        if (o->Tempo < Tfq) {
          o->F_trans = 1.0;
        }
      }
    }

    Mf_tmp = (static_cast<int32_T>(Ltab) - 1) * 25;
    J = (static_cast<int32_T>((Ltab + 1.0)) - 1) * 25;
    o->Cfx = (mod_foggui_B.C[J] - mod_foggui_B.C[Mf_tmp]) * Ar +
      mod_foggui_B.C[Mf_tmp];
    Fcd_tmp = Mf_tmp + 1;
    o->Cfx = ((mod_foggui_B.C[J + 1] - mod_foggui_B.C[Fcd_tmp]) * Ar +
              mod_foggui_B.C[Fcd_tmp]) * (1.0 - o->F_trans) + o->Cfx *
      o->F_trans;
    Msub = o->Cfx;
    Fcd_tmp = Mf_tmp + 19;
    Fcd_tmp_0 = Mf_tmp + 10;
    Fcd = ((mod_foggui_B.C[J + 19] - mod_foggui_B.C[Fcd_tmp]) * Ar +
           mod_foggui_B.C[Fcd_tmp]) * o->F_trans + ((mod_foggui_B.C[J + 10] -
      mod_foggui_B.C[Fcd_tmp_0]) * Ar + mod_foggui_B.C[Fcd_tmp_0]) * (1.0 -
      o->F_trans);
    Fcd_tmp = Mf_tmp + 11;
    Fcdsub = (mod_foggui_B.C[J + 11] - mod_foggui_B.C[Fcd_tmp]) * Ar +
      mod_foggui_B.C[Fcd_tmp];
    o->Rcpe = A8;
    Fcd_tmp = Mf_tmp + 3;
    Nova_trans = (mod_foggui_B.C[J + 3] - mod_foggui_B.C[Fcd_tmp]) * Ar +
      mod_foggui_B.C[Fcd_tmp];
    o->Cnab = Nova_trans;
    Fcd_tmp = Mf_tmp + 6;
    Tfq = (mod_foggui_B.C[J + 6] - mod_foggui_B.C[Fcd_tmp]) * Ar +
      mod_foggui_B.C[Fcd_tmp];
    o->Xcp0 = Tfq;
    if (!(o->Pit0 != 0.0)) {
      mod_foggui_Traj_Empena(o, Ltab, Ar, Fcd);
    }

    Fcd_tmp = Mf_tmp + 7;
    Tsep = (mod_foggui_B.C[J + 7] - mod_foggui_B.C[Fcd_tmp]) * Ar +
      mod_foggui_B.C[Fcd_tmp];
    Dsub = Tsep;
    o->Cphia = 1.0;
    o->Sphia = 0.0;
    if (o->Van != 0.0) {
      o->Cphia = o->Vaz / o->Van;
      o->Sphia = -o->Vay / o->Van;
    }

    if (o->Va != 0.0) {
      o->Alfab = o->Van / o->Va;
      mod_foggui_DW.Salfab = o->Van / o->Va;
    }

    A8 = o->Alfab * o->Alfab * 2.0;
    Msep = o->Alfab * o->Cnab;
    if (o->Alfab > Atlin0) {
      o->Alfab = std::asin(o->Alfab);
      Fcd_tmp = Mf_tmp + 4;
      Nova_trans = (mod_foggui_B.C[J + 4] - mod_foggui_B.C[Fcd_tmp]) * Ar +
        mod_foggui_B.C[Fcd_tmp];
      Fcd_tmp = Mf_tmp + 5;
      Tfq = (mod_foggui_B.C[J + 5] - mod_foggui_B.C[Fcd_tmp]) * Ar +
        mod_foggui_B.C[Fcd_tmp];
      Fcd_tmp = Mf_tmp + 8;
      Dsub = (mod_foggui_B.C[J + 8] - mod_foggui_B.C[Fcd_tmp]) * Ar +
        mod_foggui_B.C[Fcd_tmp];
      Mf_tmp += 9;
      Mf = (mod_foggui_B.C[J + 9] - mod_foggui_B.C[Mf_tmp]) * Ar +
        mod_foggui_B.C[Mf_tmp];
      Msep = ((o->Alfab * Tfq + Nova_trans) * o->Alfab + o->Cnab) * o->Alfab;
      T_trans = 3.0 * o->Alfab;
      Nova_trans = (T_trans * Tfq + 2.0 * Nova_trans) * o->Alfab + o->Cnab;
      Tfq = ((o->Alfab * Mf + Dsub) * o->Alfab + Tsep) * o->Alfab + o->Xcp0;
      Dsub = (T_trans * Mf + 2.0 * Dsub) * o->Alfab + Tsep;
      Tsep = Fcdsub - Msub;
      Mf = std::sqrt(1.0 - mod_foggui_DW.Salfab * mod_foggui_DW.Salfab);
      if (std::abs(o->Alfab - 1.5707963267948966) <= Atlin0) {
        Mf = std::cos(Atlin0 - 1.5707963267948966);
      }

      A8 = ((A8 - Tsep) - Msep * mod_foggui_DW.Salfab) / Mf + Tsep;
      o->Rcpe = A6;
    }

    o->Cfx = Msub + A8;
    o->Wla = -o->Wbhy * o->Cphia - o->Wbhz * o->Sphia;
    o->Wno = o->Wbhy * o->Sphia - o->Wbhz * o->Cphia;
    o->Cnow = -o->Km0 * A1 * Nova_trans;
    o->Cnoap = A3 * Nova_trans;
    if (o->Va != 0.0) {
      Bz = Dr / (2.0 * o->Va);
    }

    o->Cno = (o->Cnow * o->Wla + o->Cnoap * o->Alfap) * Bz + Msep;
    o->Claw = A1 * o->Km0 * o->Cnab;
    o->Cla = Bz * o->Claw * o->Wno;
    o->Cfy = -o->Cla * o->Cphia + o->Cno * o->Sphia;
    o->Cfz = -o->Cla * o->Sphia - o->Cno * o->Cphia;
    o->Lcp0 = (o->Xcp0 - o->Xcm) / Dr;
    o->Lcpb = (Tfq - o->Xcm) / Dr;
    o->Cmno = -Bz * o->Wno * o->Km1 * o->Cnab * o->Lcp0;
    o->Cmlas = Msep * o->Lcpb;
    A1 = -Nova_trans * o->Lcpb - Msep * Dsub / Dr;
    A3 = o->Km1 * A1;
    o->Cmlaap = -o->Km2 * A1;
    o->Cmla = (A3 * o->Wla + o->Cmlaap * o->Alfap) * Bz + o->Cmlas;
    o->Cmy = -o->Cmla * o->Cphia + o->Cmno * o->Sphia;
    o->Cmz = -o->Cmla * o->Sphia - o->Cmno * o->Cphia;
    o->cfx_e = o->Cfx - o->cfx_b;
    o->cfy_e = o->Cfy - o->cfy_b;
    o->cfz_e = o->Cfz - o->cfz_b;
    o->cmx_e = o->Cmx - o->cmx_b;
    o->cmz_e = o->Cmy - o->cmz_b;
    o->cmy_e = o->Cmz - o->cmy_b;
    mod_foggui_Traj_Empena(o, Ltab, Ar, Fcd);
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Cpf(Traj_mod_foggui_T *o)
{
  real_T Fnor;
  real_T A3;
  real_T Ar;
  real_T Dr;
  real_T A1;
  real_T b_A3;
  real_T b_Dr;
  real_T b_Bz;
  Fnor = o->modelo.geometria.Fnor;
  A3 = o->modelo.aero.A3;
  Ar = o->modelo.aero.Ar;
  Dr = o->modelo.geometria.Dr;
  o->Fpf = false;
  if (o->Fcoef != 0.0) {
    A1 = o->modelo.aero.A1;
    b_A3 = o->modelo.aero.A3;
    b_Dr = o->modelo.geometria.Dr;
    b_Bz = 0.0;
    o->Fcoef = 0.0;
    o->Cphia = 1.0;
    o->Sphia = 0.0;
    o->Wla = std::sqrt(o->Wbhy * o->Wbhy + o->Wbhz * o->Wbhz);
    if (o->Wla != 0.0) {
      o->Cphia = -o->Wbhy / o->Wla;
      o->Sphia = -o->Wbhz / o->Wla;
    }

    o->Cnow = -o->Km0 * A1 * o->Cnab;
    o->Cnoap = b_A3 * o->Cnab;
    o->Lcp0 = (o->Xcp0 - o->Xcm) / b_Dr;
    o->Lcpb = (o->Xcp0 - o->Xcm) / b_Dr;
    A1 = -o->Cnab * o->Lcp0;
    o->Cmlaw = o->Km1 * A1;
    o->Cmlaap = -o->Km2 * A1;
    o->Claw = -o->Cnow;
    if (o->Va != 0.0) {
      b_Bz = b_Dr / (2.0 * o->Va);
    }

    o->Cno = b_Bz * o->Cnow * o->Wla;
    o->Cmla = b_Bz * o->Cmlaw * o->Wla;
  }

  o->Cna = 2.0 * o->Cnae * Fnor + o->Cnab;
  o->Cnq = 4.0 * o->Cnae * o->Lcpe * Fnor + o->Claw;
  o->Cnap = A3 * o->Cnab;
  A3 = -o->Cnab * o->Lcp0 * o->Km1;
  o->Cma = A3 / o->Km1 - 2.0 * o->Cnae * o->Lcpe * Fnor;
  o->Cmq = A3 - 4.0 * o->Cnae * o->Lcpe * o->Lcpe * Fnor;
  o->Cmap = -o->Km2 * o->Lcp0 * o->Cnab;
  b_Dr = o->Ro * Ar * Dr / 4.0;
  Ar = -o->Massa * o->Gb * o->L13 * Dr;
  A3 = (b_Dr * o->Cnap + o->Massa) * o->Va;
  b_Bz = (o->Massa - b_Dr * o->Cnq) * o->Va;
  A1 = (o->Vm * o->Roex * o->Roex + o->Iyd) - b_Dr * o->Va * Dr * o->Cmq;
  Fnor = A3 * o->Iy;
  A3 = (o->Arpd * o->Cna * o->Iy + A3 * A1) - b_Bz * b_Dr * o->Va * Dr * o->Cmap;
  Dr = (o->Cna * A1 - b_Bz * Dr * o->Cma) * o->Arpd - Ar * b_Dr * o->Va *
    o->Cmap;
  Ar = -Ar * o->Arpd * o->Cma;
  if (o->Va != 0.0) {
    o->Pf = Dr / Fnor;
    if (o->Pf < 0.0) {
      A1 = -1.0;
    } else if (o->Pf > 0.0) {
      A1 = 1.0;
    } else if (o->Pf == 0.0) {
      A1 = 0.0;
    } else {
      A1 = (rtNaN);
    }

    o->Pf = A1 * std::sqrt(std::abs(o->Pf));
    o->Root = -Ar / Dr;
    o->Qsi = (A3 / Fnor + o->Root) / (2.0 * o->Pf);
  }

  o->Sm = -o->Cma / o->Cna;
  mod_foggui_Traj_Atmosf(o);
}

void mod_fogguiModelClass::mod_foggui_Traj_Deriv(Traj_mod_foggui_T *o)
{
  real_T Rg;
  real_T Wg;
  real_T Ralt;
  real_T Rlat;
  real_T Tfq;
  real_T G0;
  real_T Dr;
  real_T Lb;
  real_T Fog;
  real_T Alfaj;
  real_T Kcan;
  real_T By;
  real_T Bz;
  Rg = o->modelo.cte.Rg;
  Wg = o->modelo.cte.Wg;
  Ralt = o->modelo.lancamento.Ralt;
  Rlat = o->modelo.lancamento.Rlat;
  mod_foggui_Traj_Lbh(o);
  o->Z = Ralt + o->Dalt;
  mod_foggui_Traj_Vento(o);
  o->Vwxb = (o->L11 * o->Vwx + o->L12 * o->Vwy) + o->L13 * o->Vwz;
  o->Vwyb = (o->L21 * o->Vwx + o->L22 * o->Vwy) + o->L23 * o->Vwz;
  o->Vwzb = (o->L31 * o->Vwx + o->L32 * o->Vwy) + o->L33 * o->Vwz;
  if (!(o->Pit0 != 0.0)) {
    o->Vy = o->Vwyb;
    o->Vz = o->Vwzb;
  }

  o->Vxh = (o->L11 * o->Vx + o->L21 * o->Vy) + o->L31 * o->Vz;
  o->Vyh = (o->L12 * o->Vx + o->L22 * o->Vy) + o->L32 * o->Vz;
  o->Vzh = (o->L13 * o->Vx + o->L23 * o->Vy) + o->L33 * o->Vz;
  o->Slat = std::sin(Rlat * 0.017453292519943295 + o->Dlat);
  o->Clat = std::sqrt(1.0 - o->Slat * o->Slat);
  o->Rb = Rg + o->Z;
  mod_foggui_Traj_Atmosf(o);
  Rg = -o->Vyh / o->Rb;
  Ralt = o->Vxh / o->Rb;
  o->Dlat_p = Ralt;
  o->Dlong_p = Rg / o->Clat;
  Rlat = o->Dlong_p * o->Slat;
  o->Dalt_p = o->Vzh;
  o->Wgx = Wg * o->Clat;
  o->Wgz = Wg * o->Slat;
  o->Wgxb = o->L11 * o->Wgx + o->L13 * o->Wgz;
  o->Wgyb = o->L21 * o->Wgx + o->L23 * o->Wgz;
  o->Wgzb = o->L31 * o->Wgx + o->L33 * o->Wgz;
  o->Whxb = (o->L11 * Rg + o->L12 * Ralt) + o->L13 * Rlat;
  Wg = (o->L21 * Rg + o->L22 * Ralt) + o->L23 * Rlat;
  Rg = (o->L31 * Rg + o->L32 * Ralt) + o->L33 * Rlat;
  o->Wbhx = (o->Wx - o->Whxb) * o->Rot0;
  if (o->Pit0 != 0.0) {
    o->Wbhy = o->Wy - Wg;
    o->Wbhz = o->Wz - Rg;
  } else {
    Rlat = o->Vx - o->Vwxb;
    if ((Rlat < 0.01) || rtIsNaN(Rlat)) {
      o->Vax = 0.01;
    } else {
      o->Vax = Rlat;
    }

    Ralt = 2.0 * o->Wgxb + o->Whxb;
    Rlat = std::sqrt(o->Vxh * o->Vxh + o->Vyh * o->Vyh) * o->Rwz;
    o->Wbhy = ((((o->L31 * o->Rwx + o->L32 * o->Rwy) * o->Vzh + Ralt * o->Vy) +
                (Rlat + o->Gb) * o->L33) - (2.0 * o->Wgyb + Wg) * o->Vx) /
      o->Vax;
    o->Wbhz = (((Ralt * o->Vz - (o->L21 * o->Rwx + o->L22 * o->Rwy) * o->Vzh) -
                (Rlat + o->Gb) * o->L23) - (2.0 * o->Wgzb + Rg) * o->Vx) /
      o->Vax;
    o->Wy = o->Wbhy + Wg;
    o->Wz = o->Wbhz + Rg;
  }

  o->Wxl = (o->Wbhx + o->Whxb) + o->Wgxb;
  o->Wyl = o->Wy + o->Wgyb;
  o->Wzl = o->Wz + o->Wgzb;
  Ralt = o->Kquat0 * o->Eps;
  o->Qt1_p = ((-o->Wbhx * o->Qt4 - o->Wbhy * o->Qt3) - o->Wbhz * o->Qt2) / 2.0 +
    o->Qt1 * Ralt;
  o->Qt2_p = ((-o->Wbhx * o->Qt3 + o->Wbhy * o->Qt4) + o->Wbhz * o->Qt1) / 2.0 +
    o->Qt2 * Ralt;
  o->Qt3_p = ((o->Wbhx * o->Qt2 + o->Wbhy * o->Qt1) - o->Wbhz * o->Qt4) / 2.0 +
    o->Qt3 * Ralt;
  o->Qt4_p = ((o->Wbhx * o->Qt1 - o->Wbhy * o->Qt2) + o->Wbhz * o->Qt3) / 2.0 +
    o->Qt4 * Ralt;
  o->Frx = 0.0;
  o->Fry = 0.0;
  o->Frz = 0.0;
  o->Mrx = 0.0;
  o->Mry = 0.0;
  o->Mrz = 0.0;
  o->Matr = 0.0;
  if (o->F <= 4.0) {
    mod_foggui_Traj_Tip_off(o);
  }

  Tfq = o->modelo.aero.Tfq;
  G0 = o->modelo.cte.G0;
  Dr = o->modelo.geometria.Dr;
  Lb = o->modelo.geometria.Lb;
  Fog = o->modelo.inercia.Fog;
  Wg = o->modelo.propelente.Ae;
  Alfaj = o->modelo.propelente.Alfaj;
  Rlat = o->modelo.propelente.Betaj;
  Kcan = o->modelo.propelente.Kcan;
  o->Vax = o->Vx - o->Vwxb;
  o->Vay = o->Vy - o->Vwyb;
  o->Vaz = o->Vz - o->Vwzb;
  mod_foggui_Traj_Aero(o);
  Ralt = o->Fax + o->Frx;
  By = o->Fay + o->Fry;
  Bz = o->Faz + o->Frz;
  if (o->F < 8.0) {
    Rg = (94540.0 - o->Pa) * Wg * o->F_trans + o->Tx;
  } else {
    Rg = (94540.0 - o->Pa) * Wg * o->F_trans;
  }

  Wg = Rg * o->Grot;
  Rg *= static_cast<real_T>((o->F < 5.0)) * Kcan + 1.0;
  Rlat = std::sin(Rlat * 0.017453292519943295) * Rg;
  o->Acontr = 0.0;
  if ((Rg != 0.0) && (o->Vx > 0.0) && (o->Tempo < Tfq) && (Fog == 2.0)) {
    if (o->Fpf) {
      mod_foggui_Traj_Cpf(o);
    }

    o->Acontr = -o->Arpd * Dr * o->Cma / Rg / (Lb - o->Xcm);
    o->Acontr = 0.0;
    if ((o->Arpd * o->Alfab * o->Cna + std::sin(o->Acontr) * Rg) / o->Massa / G0
        > 0.0) {
      o->Acontr = (0.0 * o->Massa * G0 - o->Arpd * o->Cna * o->Alfab) / Rg;
    }

    if (!(o->Acontr > 0.0)) {
      o->Acontr = 0.0;
    }
  }

  Tfq = std::sin(Alfaj * 0.017453292519943295 + o->Acontr) * Rg;
  if ((Rlat != 0.0) || (Tfq != 0.0)) {
    Rg = std::sqrt((Rg * Rg - Rlat * Rlat) - Tfq * Tfq);
  }

  Ralt += Rg;
  By += Rlat * o->Rot0;
  Bz += Tfq * o->Rot0;
  o->Vx_p = ((-o->L13 * o->Gb + Ralt / o->Massa) - (o->Wyl + o->Wgyb) * o->Vz) +
    (o->Wzl + o->Wgzb) * o->Vy;
  if (o->Vx_p > o->Vx_pmax) {
    o->Vx_pmax = o->Vx_p;
  }

  if (o->Vx_p < o->Vx_pmin) {
    o->Vx_pmin = o->Vx_p;
  }

  if (o->Pit0 != 0.0) {
    o->Vy_p = ((-o->L23 * o->Gb + By / o->Massa) - (o->Wzl + o->Wgzb) * o->Vx) +
      (o->Wxl + o->Wgxb) * o->Vz;
    o->Vz_p = ((-o->L33 * o->Gb + Bz / o->Massa) - (o->Wxl + o->Wgxb) * o->Vy) +
      (o->Wyl + o->Wgyb) * o->Vx;
  } else {
    o->Vy_p = (o->Wbhx + o->Wgxb) * o->Vz - o->Vwxb * o->Wbhz;
    o->Vz_p = o->Vwxb * o->Wbhy - (o->Wbhx + o->Wgxb) * o->Vy;
  }

  o->Acel = std::sqrt((o->Vx_p * o->Vx_p + o->Vy_p * o->Vy_p) + o->Vz_p *
                      o->Vz_p);
  By = (o->Max + o->Mrx) + o->Matr;
  Bz = o->May + o->Mry;
  G0 = o->Maz + o->Mrz;
  if (o->Tempo >= o->controle_z_t0) {
    if (o->controle_z_roll_on != 0.0) {
      mod_foggui_DW.erroint += ((0.0 - o->Phi) + mod_foggui_DW.err_) *
        0.00083333333333333339 / 2.0;
      mod_foggui_DW.err_ = 0.0 - o->Phi;
      By += ((0.0 - o->Phi) * 150.0 + mod_foggui_DW.erroint * 20.0) - o->Wx *
        30.0;
    }

    if (o->controle_z_rollrate_on != 0.0) {
      By += (o->controle_z_rollrate_ref - o->Wx) * 60.0;
    }
  }

  if (o->Rot0 != 0.0) {
    Dr = (o->Ix * o->Wxl - o->Ixy * o->Wyl) - o->Ixz * o->Wzl;
    Ralt = (-o->Ixy * o->Wxl + o->Iy * o->Wyl) - o->Iyz * o->Wzl;
    Lb = (-o->Ixz * o->Wxl - o->Iyz * o->Wyl) + o->Iz * o->Wzl;
    By = (By - o->Wyl * Lb) + o->Wzl * Ralt;
    Bz = (Bz - o->Wzl * Dr) + o->Wxl * Lb;
    G0 = (G0 - o->Wxl * Ralt) + o->Wyl * Dr;
    if (o->F < 8.0) {
      Rg += (o->Wzl * o->Roey - o->Wyl * o->Roez) * o->Vm;
      Ralt = (o->Wxl * o->Roez - o->Wzl * o->Roex) * o->Vm + Rlat;
      Rlat = (o->Wyl * o->Roex - o->Wxl * o->Roey) * o->Vm + Tfq;
      By = (((o->Roey * Rlat + By) - o->Roez * Ralt) - o->Ixd * o->Wxl) + Wg;
      Bz = ((o->Roez * Rg + Bz) - o->Roex * Rlat) - o->Iyd * o->Wyl;
      G0 = ((o->Roex * Ralt + G0) - o->Roey * Rg) - o->Izd * o->Wzl;
    }

    o->Wx_p = ((o->Jxx * By + o->Jxy * Bz) + o->Jxz * G0) * o->Frot;
    o->Wy_p = (o->Jxy * By + o->Jyy * Bz) + o->Jyz * G0;
    o->Wz_p = (o->Jxz * By + o->Jyz * Bz) + o->Jzz * G0;
  } else {
    Bz -= o->Wzl * o->Wxl * o->Ix;
    G0 += o->Wyl * o->Wxl * o->Ix;
    if (o->F < 8.0) {
      Dr = (o->Roey * o->Roey + o->Roez * o->Roez) * o->Vm;
      Ralt = (o->Roex * o->Roex * o->Vm + Dr / 2.0) + o->Iyd;
      By = (((o->Roey * Tfq + By) - o->Roez * Rlat) - (Dr + o->Ixd) * o->Wxl) +
        Wg;
      Bz -= o->Wyl * Ralt;
      G0 -= o->Wzl * Ralt;
    }

    o->Wx_p = o->Frot * o->Jxx * By;
    o->Wy_p = o->Jyy * Bz * o->Pit0;
    o->Wz_p = o->Jzz * G0 * o->Pit0;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Degree(Traj_mod_foggui_T *o)
{
  real_T Fog;
  real_T Tfq;
  real_T Atlin0;
  real_T Tpit0;
  real_T Ax;
  boolean_T c;
  Fog = o->modelo.inercia.Fog;
  Tfq = o->modelo.aero.Tfq;
  Atlin0 = o->modelo.aero.Atlin0;
  Tpit0 = 0.0;
  o->Rot1 = (o->Rot + 1.0) / 2.0;
  Ax = o->Alfab;
  if (o->Pf > 0.0) {
    Ax = std::sqrt(o->Alfap * o->Alfap / (o->Pf * o->Pf) + o->Alfab * o->Alfab);
  }

  if (o->Rot == 0.0) {
    o->Rot1 = ((Ax > Atlin0) || (o->Asm != 0.0) || ((Fog == 2.0) && (o->T < Tfq)));
  }

  o->Pit1 = (o->Pit + 1.0) / 2.0;
  if ((Ax >= 0.0017453292519943296) || (o->Pit == 1.0)) {
    Tpit0 = o->T + 1.0;
  }

  if (o->Pit == 0.0) {
    o->Pit1 = ((Tpit0 > o->T) && (o->Ro > 0.01));
  }

  if (o->Fesp != 0.0) {
    o->Pit1 = 0.0;
    o->Rot1 = 0.0;
  }

  o->Gir1 = (o->Gir + 1.0) / 2.0;
  if (o->Gir == 0.0) {
    if ((std::abs(o->Wx) > 0.0017453292519943296) || (std::abs(o->Wx_p) >
         0.0017453292519943296)) {
      c = true;
    } else {
      c = false;
    }

    o->Gir1 = c;
  }

  if (o->Rot1 != 0.0) {
    o->Pit1 = 1.0;
    o->Gir1 = 1.0;
  }

  o->Q = ((o->Q != 0.0) || ((2.0 * o->Pit1 + o->Rot1) + 4.0 * o->Gir1 != (2.0 *
            o->Pit0 + o->Rot0) + 4.0 * o->Gir0));
}

void mod_fogguiModelClass::mod_foggui_Traj_Newstate(Traj_mod_foggui_T *o, const
  real_T estadoAnterior[13], real_T Hfat)
{
  o->Dlat = o->Dlat_p * Hfat + estadoAnterior[0];
  o->Dlong = o->Dlong_p * Hfat + estadoAnterior[1];
  o->Dalt = o->Dalt_p * Hfat + estadoAnterior[2];
  o->Vx = o->Vx_p * Hfat + estadoAnterior[3];
  o->Vy = o->Vy_p * Hfat + estadoAnterior[4];
  o->Vz = o->Vz_p * Hfat + estadoAnterior[5];
  o->Wx = o->Wx_p * Hfat * o->Gir0 + estadoAnterior[6];
  o->Wy = o->Wy_p * Hfat + estadoAnterior[7];
  o->Wz = o->Wz_p * Hfat + estadoAnterior[8];
  o->Qt1 = o->Qt1_p * Hfat + estadoAnterior[9];
  o->Qt2 = o->Qt2_p * Hfat + estadoAnterior[10];
  o->Qt3 = o->Qt3_p * Hfat + estadoAnterior[11];
  o->Qt4 = o->Qt4_p * Hfat + estadoAnterior[12];
}

void mod_fogguiModelClass::mod_foggui_Traj_Runge(Traj_mod_foggui_T *o, const
  real_T P_[13])
{
  real_T Hfat;
  real_T Hres;
  real_T H__idx_0;
  real_T H__idx_1;
  real_T H__idx_2;
  real_T H__idx_3;
  real_T H__idx_4;
  real_T H__idx_5;
  real_T H__idx_6;
  real_T H__idx_7;
  real_T H__idx_8;
  real_T H__idx_9;
  real_T H__idx_10;
  real_T H__idx_11;
  real_T H__idx_12;
  H__idx_0 = o->Dlat_p;
  H__idx_1 = o->Dlong_p;
  H__idx_2 = o->Dalt_p;
  H__idx_3 = o->Vx_p;
  H__idx_4 = o->Vy_p;
  H__idx_5 = o->Vz_p;
  H__idx_6 = o->Wx_p;
  H__idx_7 = o->Wy_p;
  H__idx_8 = o->Wz_p;
  H__idx_9 = o->Qt1_p;
  H__idx_10 = o->Qt2_p;
  H__idx_11 = o->Qt3_p;
  H__idx_12 = o->Qt4_p;
  Hfat = o->H / 2.0;
  Hres = o->H / 6.0;
  mod_foggui_Traj_Newstate(o, P_, Hfat);
  o->Tempo = o->T + Hfat;
  if (o->F < 8.0) {
    mod_foggui_Traj_Inercia(o);
  }

  mod_foggui_Traj_Deriv(o);
  H__idx_0 += 2.0 * o->Dlat_p;
  H__idx_1 += 2.0 * o->Dlong_p;
  H__idx_2 += 2.0 * o->Dalt_p;
  H__idx_3 += 2.0 * o->Vx_p;
  H__idx_4 += 2.0 * o->Vy_p;
  H__idx_5 += 2.0 * o->Vz_p;
  H__idx_6 += 2.0 * o->Wx_p;
  H__idx_7 += 2.0 * o->Wy_p;
  H__idx_8 += 2.0 * o->Wz_p;
  H__idx_9 += 2.0 * o->Qt1_p;
  H__idx_10 += 2.0 * o->Qt2_p;
  H__idx_11 += 2.0 * o->Qt3_p;
  H__idx_12 += 2.0 * o->Qt4_p;
  mod_foggui_Traj_Newstate(o, P_, Hfat);
  mod_foggui_Traj_Deriv(o);
  H__idx_0 += 2.0 * o->Dlat_p;
  H__idx_1 += 2.0 * o->Dlong_p;
  H__idx_2 += 2.0 * o->Dalt_p;
  H__idx_3 += 2.0 * o->Vx_p;
  H__idx_4 += 2.0 * o->Vy_p;
  H__idx_5 += 2.0 * o->Vz_p;
  H__idx_6 += 2.0 * o->Wx_p;
  H__idx_7 += 2.0 * o->Wy_p;
  H__idx_8 += 2.0 * o->Wz_p;
  H__idx_9 += 2.0 * o->Qt1_p;
  H__idx_10 += 2.0 * o->Qt2_p;
  H__idx_11 += 2.0 * o->Qt3_p;
  H__idx_12 += 2.0 * o->Qt4_p;
  Hfat = o->H;
  mod_foggui_Traj_Newstate(o, P_, o->H);
  o->Tempo = o->T + Hfat;
  if (o->F < 8.0) {
    mod_foggui_Traj_Inercia(o);
  }

  mod_foggui_Traj_Deriv(o);
  o->Dlat = (H__idx_0 + o->Dlat_p) * Hres + P_[0];
  o->Dlong = (H__idx_1 + o->Dlong_p) * Hres + P_[1];
  o->Dalt = (H__idx_2 + o->Dalt_p) * Hres + P_[2];
  o->Vx = (H__idx_3 + o->Vx_p) * Hres + P_[3];
  o->Wx = (H__idx_6 + o->Wx_p) * Hres * o->Gir0 + P_[6];
  o->Vy = (H__idx_4 + o->Vy_p) * Hres + P_[4];
  o->Vz = (H__idx_5 + o->Vz_p) * Hres + P_[5];
  o->Wy = (H__idx_7 + o->Wy_p) * Hres + P_[7];
  o->Wz = (H__idx_8 + o->Wz_p) * Hres + P_[8];
  o->Qt1 = (H__idx_9 + o->Qt1_p) * Hres + P_[9];
  o->Qt2 = (H__idx_10 + o->Qt2_p) * Hres + P_[10];
  o->Qt3 = (H__idx_11 + o->Qt3_p) * Hres + P_[11];
  o->Qt4 = (H__idx_12 + o->Qt4_p) * Hres + P_[12];
}

void mod_fogguiModelClass::mod_foggui_Traj_Apogeu(Traj_mod_foggui_T *o)
{
  real_T Hsub;
  real_T Ralt;
  real_T Talt;
  real_T Tesp;
  real_T Valt[48];
  boolean_T Cv;
  Hsub = o->modelo.lancamento.Hsub;
  Ralt = o->modelo.lancamento.Ralt;
  Talt = o->modelo.lancamento.Talt;
  Tesp = o->modelo.lancamento.Tesp;
  std::memcpy(&Valt[0], &o->modelo.ventos.altitudes[0], 48U * sizeof(real_T));
  if (o->F == 8.0) {
    o->Dkw = 0.0;
    o->Dkh = 0.0;
    if (o->Vzh > 0.0) {
      o->Apo = 0.0;
    }

    Ralt = static_cast<real_T>((o->Z > Valt[static_cast<int32_T>(((o->Kw + 1.0)
      + 1.0)) - 1] + o->Htabv)) * std::abs(o->Apo) - static_cast<real_T>(((o->Z <
      Valt[static_cast<int32_T>((o->Kw + 1.0)) - 1] + o->Htabv) * (o->Flw ==
      -1.0))) * static_cast<real_T>(!(o->Apo != 0.0));
    mod_foggui_Traj_debug(o, &mod_foggui_B.unusedExpr);
    if ((o->Ws0 == 0.0) && (o->Wl0 == 0.0)) {
      Ralt = 0.0;
    }

    if (Ralt != 0.0) {
      o->Dkw = Ralt;
    }

    if ((o->Sp > o->Vhor[static_cast<int32_T>((o->Kh + 1.0)) - 1]) && (o->Wv0 !=
         0.0)) {
      o->Dkh = 1.0;
    }
  } else {
    if (o->Apo != 0.0) {
      mod_foggui_Traj_Lbh(o);
      if (!(o->Pit0 != 0.0)) {
        o->Vy = (o->L21 * o->Vwx + o->L22 * o->Vwy) + o->L23 * o->Vwz;
        o->Vz = (o->L31 * o->Vwx + o->L32 * o->Vwy) + o->L33 * o->Vwz;
      }

      o->Vzh = (o->L13 * o->Vx + o->L23 * o->Vy) + o->L33 * o->Vz;
      if (o->Vzh <= 0.0) {
        o->R = -1.0;
        o->Apo = -1.0;
      }
    }

    if ((o->Maxv != 0.0) && (o->Vx_p <= 0.0)) {
      o->R = -1.0;
      o->Maxv = -1.0;
    }

    if ((std::abs((o->T + o->H) - Tesp) <= 1.0E-6) && (!(o->Fesp != 0.0))) {
      o->Q = 1.0;
    }

    o->Z = Ralt + o->Dalt;
    Hsub += Talt;
    if ((o->Ksub != 0.0) && (o->Z <= Hsub)) {
      o->Ksub = -1.0;
      if (o->F < 8.0) {
        o->Ksub = 0.0;
      }

      if (o->Ksub != 0.0) {
        o->R = 1.0;
      }
    }

    o->Dkw = 0.0;
    o->Dkh = 0.0;
    Ralt = static_cast<real_T>((o->Z > Valt[static_cast<int32_T>(((o->Kw + 1.0)
      + 1.0)) - 1] + o->Htabv)) * std::abs(o->Apo) - static_cast<real_T>(((o->Z <
      Valt[static_cast<int32_T>((o->Kw + 1.0)) - 1] + o->Htabv) * (o->Flw ==
      -1.0))) * static_cast<real_T>(!(o->Apo != 0.0));
    if ((o->Ws0 == 0.0) && (o->Wl0 == 0.0)) {
      Ralt = 0.0;
    }

    if (Ralt != 0.0) {
      o->Dkw = Ralt;
    }

    if ((o->Sp > o->Vhor[static_cast<int32_T>((o->Kh + 1.0)) - 1]) && (o->Wv0 !=
         0.0)) {
      Cv = true;
      o->Dkh = 1.0;
    } else {
      Cv = false;
    }

    if (o->Refcam != 0.0) {
      o->R = ((o->R != 0.0) || (Ralt != 0.0) || Cv);
    }

    o->Q = ((o->Q != 0.0) || (o->R != 0.0));
    if ((o->Apo == -1.0) && (o->Q != 0.0) && (o->Vzh > 0.0)) {
      o->Apo = 1.0;
    }

    if ((o->Maxv == -1.0) && (o->Q != 0.0) && (o->Vx_p > 0.0)) {
      o->Maxv = 1.0;
    }

    if ((o->Ksub == -1.0) && (o->Q != 0.0) && (o->Z > Hsub)) {
      o->Ksub = 1.0;
    }
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Fase(Traj_mod_foggui_T *o)
{
  real_T Ldel;
  real_T Lr;
  real_T Xt1;
  real_T Xt2;
  real_T Xt3;
  real_T Xfim;
  real_T Wabre;
  real_T Tfq;
  real_T Tdalt;
  boolean_T Aux;
  Ldel = o->modelo.cte.Ldel;
  Lr = o->modelo.dados_part.Lr;
  Xt1 = o->modelo.dados_part.Xt1;
  Xt2 = o->modelo.dados_part.Xt2;
  Xt3 = o->modelo.dados_part.Xt3;
  Xfim = o->modelo.dados_part.Xfim;
  Wabre = o->modelo.geometria.Wabre;
  Tfq = o->modelo.aero.Tfq;
  Tdalt = o->modelo.lancamento.Talt - o->modelo.lancamento.Ralt;
  o->R = 0.0;
  o->Q = 0.0;
  o->M = 0.0;
  mod_foggui_Traj_Cdist(o);
  switch (static_cast<int32_T>(o->F)) {
   case 1:
    o->M = (o->Delr >= (Lr + Xt1) - o->Xcm);
    o->R = (o->Delr >= (Lr + Xt1) - o->Xcm);
    o->Q = (o->Delr >= (Lr + Xt1) - o->Xcm);
    break;

   case 2:
    o->M = (o->Delr >= (Lr + Xt2) - o->Xcm);
    o->R = (o->Delr >= (Lr + Xt2) - o->Xcm);
    o->Q = (o->Delr >= (Lr + Xt2) - o->Xcm);
    mod_foggui_Traj_Apogeu(o);
    break;

   case 3:
    o->M = (o->Delr >= (Lr + Xt3) - o->Xcm);
    o->R = (o->Delr >= (Lr + Xt3) - o->Xcm);
    o->Q = (o->Delr >= (Lr + Xt3) - o->Xcm);
    mod_foggui_Traj_Apogeu(o);
    break;

   case 4:
    o->M = (o->Delr + Ldel >= (Lr + Xfim) - o->Xcm);
    o->R = (o->Delr + Ldel >= (Lr + Xfim) - o->Xcm);
    o->Q = (o->Delr + Ldel >= (Lr + Xfim) - o->Xcm);
    mod_foggui_Traj_Apogeu(o);
    break;

   case 5:
    o->M = ((o->T + o->H) + 1.0E-6 > o->Tabin);
    o->Q = ((o->T + o->H) + 1.0E-6 > o->Tabin);
    Aux = (std::abs(o->Wx) >= std::abs(Wabre) * 2.0 * 3.1415926535897931);
    if (!(o->M != 0.0)) {
      o->M = Aux;
      o->R = Aux;
      o->Q = Aux;
    }

    mod_foggui_Traj_Apogeu(o);
    break;

   case 6:
    o->M = ((o->T + o->H) + 1.0E-6 > o->Tabre);
    o->Q = ((o->T + o->H) + 1.0E-6 > o->Tabre);
    mod_foggui_Traj_Apogeu(o);
    break;

   case 7:
    o->M = ((o->T + o->H) + 1.0E-6 > Tfq);
    o->Q = ((o->T + o->H) + 1.0E-6 > Tfq);
    if (o->M != 0.0) {
      mod_foggui_Traj_Apogeu(o);
    } else {
      o->M = ((o->Dalt <= Tdalt) && (o->Apo == 0.0));
      o->R = ((o->Dalt <= Tdalt) && (o->Apo == 0.0));
      o->Q = ((o->Dalt <= Tdalt) && (o->Apo == 0.0));
      mod_foggui_Traj_Apogeu(o);
    }
    break;

   case 8:
    o->M = ((o->Dalt <= Tdalt) && (o->Apo == 0.0));
    o->R = ((o->Dalt <= Tdalt) && (o->Apo == 0.0));
    o->Q = ((o->Dalt <= Tdalt) && (o->Apo == 0.0));
    mod_foggui_Traj_Apogeu(o);
    break;
  }
}

void mod_fogguiModelClass::mod_foggui_Traj_Flag(Traj_mod_foggui_T *o)
{
  real_T Ralt;
  real_T Hsub;
  real_T Talt;
  real_T Tesp;
  real_T Ldel;
  real_T Yf;
  real_T Zf;
  real_T Ixyf;
  real_T Ixzf;
  real_T Iyf;
  real_T Iyzf;
  real_T Izf;
  boolean_T Bx;
  real_T Bz;
  real_T Hsub_tmp;
  real_T tmp;
  Ralt = o->modelo.lancamento.Ralt;
  Hsub = o->modelo.lancamento.Hsub;
  Talt = o->modelo.lancamento.Talt;
  Tesp = o->modelo.lancamento.Tesp;
  Ldel = o->modelo.cte.Ldel;
  Yf = o->modelo.inercia.Yf;
  Zf = o->modelo.inercia.Zf;
  Ixyf = o->modelo.inercia.Ixyf;
  Ixzf = o->modelo.inercia.Ixzf;
  Iyf = o->modelo.inercia.Iyf;
  Iyzf = o->modelo.inercia.Iyzf;
  Izf = o->modelo.inercia.Izf;
  o->Z = o->modelo.lancamento.Ralt + o->Dalt;
  if ((o->Dkw != 0.0) || (o->Dkh != 0.0)) {
    o->Pit1 = 1.0;
  }

  if (o->Apo == -1.0) {
    o->Apo = 0.0;
    o->Pit1 = 1.0;
    if ((o->Z > Hsub + Talt) && (!(o->Fesp != 0.0))) {
      o->Ksub = 1.0;
    }
  }

  if (((o->Ksub == -1.0) && (Hsub > 0.0)) || (std::abs(o->T - Tesp) <= 1.0E-6))
  {
    o->Ksub = 0.0;
    o->Fesp = 1.0;
  }

  if (o->Maxv == -1.0) {
    o->Maxv = 0.0;
    o->Vmax = o->Vx;
  }

  o->F = static_cast<real_T>(((o->Dalt <= (Talt - Ralt) + Ldel) * ((o->F == 7.0)
    * (o->Apo == 0.0)))) + (o->F + o->M);
  o->R = 0.0;
  o->Q = 0.0;
  o->Dkw = 0.0;
  o->Dkh = 0.0;
  o->Rot0 = o->Rot1;
  Bx = ((o->Pit0 == 1.0) && (o->Pit1 == 0.0));
  o->Pit0 = o->Pit1;
  o->Gir0 = o->Gir1;
  if (Bx) {
    mod_foggui_Traj_Vento(o);
    Ralt = o->Vxh - o->Vwx;
    Hsub = o->Vyh - o->Vwy;
    Talt = o->Vzh - o->Vwz;
    o->Phi = 0.0;
    if (Hsub < 0.0) {
      Tesp = -1.0;
    } else if (Hsub > 0.0) {
      Tesp = 1.0;
    } else if (Hsub == 0.0) {
      Tesp = 0.0;
    } else {
      Tesp = (rtNaN);
    }

    o->Psi = 1.5707963267948966 * Tesp;
    if (Ralt != 0.0) {
      o->Psi = (3.1415926535897931 - static_cast<real_T>((Hsub < 0.0)) *
                6.2831853071795862) * static_cast<real_T>((Ralt < 0.0)) + std::
        atan(Hsub / Ralt);
    }

    if (Talt < 0.0) {
      Tesp = -1.0;
    } else if (Talt > 0.0) {
      Tesp = 1.0;
    } else if (Talt == 0.0) {
      Tesp = 0.0;
    } else {
      Tesp = (rtNaN);
    }

    o->Teta = -1.5707963267948966 * Tesp;
    if ((Ralt != 0.0) || (Hsub != 0.0)) {
      o->Teta = -std::atan(Talt / std::sqrt(Ralt * Ralt + Hsub * Hsub));
    }

    o->Alfap = 0.0;
    Tesp = o->Psi / 2.0;
    Ralt = std::cos(Tesp);
    Hsub_tmp = o->Teta / 2.0;
    Hsub = std::cos(Hsub_tmp);
    Bz = o->Phi / 2.0;
    Talt = std::cos(Bz);
    Tesp = std::sin(Tesp);
    Ldel = std::sin(Hsub_tmp);
    Bz = std::sin(Bz);
    Hsub_tmp = Ralt * Hsub;
    tmp = Tesp * Ldel;
    o->Qt1 = Hsub_tmp * Talt + tmp * Bz;
    Ralt *= Ldel;
    Hsub *= Tesp;
    o->Qt2 = Hsub * Talt - Ralt * Bz;
    o->Qt3 = Ralt * Talt + Hsub * Bz;
    o->Qt4 = Hsub_tmp * Bz - tmp * Talt;
  }

  if (o->F > 7.0) {
    o->Asm = ((Yf != 0.0) || (Zf != 0.0) || (Iyf != Izf) || (Ixyf != 0.0) ||
              (Ixzf != 0.0) || (Iyzf != 0.0));
  }
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if (std::abs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = std::floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = std::ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    if (u0 > 0.0F) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0F) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = std::atan2(static_cast<real32_T>(u0_0), static_cast<real32_T>(u1_0));
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

void mod_fogguiModelClass::mod_foggui_circshift(real32_T a[1000])
{
  real32_T buffer;
  int32_T pageroot;
  int32_T i;
  int32_T b_k;
  int32_T tmp;
  for (i = 0; i < 2; i++) {
    pageroot = i * 500;
    buffer = a[pageroot];
    for (b_k = 0; b_k < 499; b_k++) {
      tmp = pageroot + b_k;
      a[tmp] = a[tmp + 1];
    }

    a[pageroot + 499] = buffer;
  }
}

real32_T rt_hypotf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T a;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0F);
  } else if (a > y) {
    y /= a;
    y = std::sqrt(y * y + 1.0F) * a;
  } else {
    if (!rtIsNaNF(y)) {
      y = a * 1.41421354F;
    }
  }

  return y;
}

void mod_fogguiModelClass::mod_foggui_mldivide(const real32_T A[9], const
  real32_T B[1500], real32_T Y[1500])
{
  real32_T b_A[9];
  int32_T r2;
  int32_T r3;
  int32_T k;
  real32_T z_tmp;
  real32_T b_z_tmp;
  int32_T Y_tmp;
  int32_T Y_tmp_0;
  for (r2 = 0; r2 < 9; r2++) {
    b_A[r2] = A[r2];
  }

  r2 = 1;
  r3 = 2;
  z_tmp = A[1] / A[0];
  b_A[1] = z_tmp;
  b_z_tmp = A[2] / A[0];
  b_A[2] = b_z_tmp;
  b_A[4] = A[4] - z_tmp * A[3];
  b_A[5] = A[5] - b_z_tmp * A[3];
  b_A[7] = A[7] - z_tmp * A[6];
  b_A[8] = A[8] - b_z_tmp * A[6];
  if (std::abs(b_A[5]) > std::abs(b_A[4])) {
    r2 = 2;
    r3 = 1;
  }

  b_A[r3 + 3] /= b_A[r2 + 3];
  b_A[r3 + 6] -= b_A[r3 + 3] * b_A[r2 + 6];
  for (k = 0; k < 500; k++) {
    Y[3 * k] = B[3 * k];
    Y_tmp = 3 * k + 1;
    Y[Y_tmp] = B[3 * k + r2] - Y[3 * k] * b_A[r2];
    Y_tmp_0 = 3 * k + 2;
    Y[Y_tmp_0] = (B[3 * k + r3] - Y[3 * k] * b_A[r3]) - Y[Y_tmp] * b_A[r3 + 3];
    Y[Y_tmp_0] /= b_A[r3 + 6];
    Y[3 * k] -= Y[Y_tmp_0] * b_A[6];
    Y[Y_tmp] -= Y[Y_tmp_0] * b_A[r2 + 6];
    Y[Y_tmp] /= b_A[r2 + 3];
    Y[3 * k] -= Y[Y_tmp] * b_A[3];
    Y[3 * k] /= b_A[0];
  }
}

real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T tmp;
  real32_T tmp_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (rtIsInfF(u1)) {
      if (tmp == 1.0F) {
        y = 1.0F;
      } else if (tmp > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (tmp_0 == 0.0F) {
      y = 1.0F;
    } else if (tmp_0 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > std::floor(u1))) {
      y = (rtNaNF);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

real32_T mod_fogguiModelClass::mod_foggui_calculoRaioCurvatura(const real32_T d
  [1000])
{
  real32_T a[3];
  real32_T b[3];
  real32_T x_[500];
  real32_T y_[500];
  int32_T i;
  int32_T i_0;
  real32_T a_tmp;
  static const real32_T c[9] = { 6.28129E+12F, 1.56875653E+10F, 4.1791684E+7F,
    1.56875653E+10F, 4.1791684E+7F, 125250.0F, 4.1791684E+7F, 125250.0F, 500.0F
  };

  static const real32_T e[1500] = { 1.0F, 1.0F, 1.0F, 4.0F, 2.0F, 1.0F, 9.0F,
    3.0F, 1.0F, 16.0F, 4.0F, 1.0F, 25.0F, 5.0F, 1.0F, 36.0F, 6.0F, 1.0F, 49.0F,
    7.0F, 1.0F, 64.0F, 8.0F, 1.0F, 81.0F, 9.0F, 1.0F, 100.0F, 10.0F, 1.0F,
    121.0F, 11.0F, 1.0F, 144.0F, 12.0F, 1.0F, 169.0F, 13.0F, 1.0F, 196.0F, 14.0F,
    1.0F, 225.0F, 15.0F, 1.0F, 256.0F, 16.0F, 1.0F, 289.0F, 17.0F, 1.0F, 324.0F,
    18.0F, 1.0F, 361.0F, 19.0F, 1.0F, 400.0F, 20.0F, 1.0F, 441.0F, 21.0F, 1.0F,
    484.0F, 22.0F, 1.0F, 529.0F, 23.0F, 1.0F, 576.0F, 24.0F, 1.0F, 625.0F, 25.0F,
    1.0F, 676.0F, 26.0F, 1.0F, 729.0F, 27.0F, 1.0F, 784.0F, 28.0F, 1.0F, 841.0F,
    29.0F, 1.0F, 900.0F, 30.0F, 1.0F, 961.0F, 31.0F, 1.0F, 1024.0F, 32.0F, 1.0F,
    1089.0F, 33.0F, 1.0F, 1156.0F, 34.0F, 1.0F, 1225.0F, 35.0F, 1.0F, 1296.0F,
    36.0F, 1.0F, 1369.0F, 37.0F, 1.0F, 1444.0F, 38.0F, 1.0F, 1521.0F, 39.0F,
    1.0F, 1600.0F, 40.0F, 1.0F, 1681.0F, 41.0F, 1.0F, 1764.0F, 42.0F, 1.0F,
    1849.0F, 43.0F, 1.0F, 1936.0F, 44.0F, 1.0F, 2025.0F, 45.0F, 1.0F, 2116.0F,
    46.0F, 1.0F, 2209.0F, 47.0F, 1.0F, 2304.0F, 48.0F, 1.0F, 2401.0F, 49.0F,
    1.0F, 2500.0F, 50.0F, 1.0F, 2601.0F, 51.0F, 1.0F, 2704.0F, 52.0F, 1.0F,
    2809.0F, 53.0F, 1.0F, 2916.0F, 54.0F, 1.0F, 3025.0F, 55.0F, 1.0F, 3136.0F,
    56.0F, 1.0F, 3249.0F, 57.0F, 1.0F, 3364.0F, 58.0F, 1.0F, 3481.0F, 59.0F,
    1.0F, 3600.0F, 60.0F, 1.0F, 3721.0F, 61.0F, 1.0F, 3844.0F, 62.0F, 1.0F,
    3969.0F, 63.0F, 1.0F, 4096.0F, 64.0F, 1.0F, 4225.0F, 65.0F, 1.0F, 4356.0F,
    66.0F, 1.0F, 4489.0F, 67.0F, 1.0F, 4624.0F, 68.0F, 1.0F, 4761.0F, 69.0F,
    1.0F, 4900.0F, 70.0F, 1.0F, 5041.0F, 71.0F, 1.0F, 5184.0F, 72.0F, 1.0F,
    5329.0F, 73.0F, 1.0F, 5476.0F, 74.0F, 1.0F, 5625.0F, 75.0F, 1.0F, 5776.0F,
    76.0F, 1.0F, 5929.0F, 77.0F, 1.0F, 6084.0F, 78.0F, 1.0F, 6241.0F, 79.0F,
    1.0F, 6400.0F, 80.0F, 1.0F, 6561.0F, 81.0F, 1.0F, 6724.0F, 82.0F, 1.0F,
    6889.0F, 83.0F, 1.0F, 7056.0F, 84.0F, 1.0F, 7225.0F, 85.0F, 1.0F, 7396.0F,
    86.0F, 1.0F, 7569.0F, 87.0F, 1.0F, 7744.0F, 88.0F, 1.0F, 7921.0F, 89.0F,
    1.0F, 8100.0F, 90.0F, 1.0F, 8281.0F, 91.0F, 1.0F, 8464.0F, 92.0F, 1.0F,
    8649.0F, 93.0F, 1.0F, 8836.0F, 94.0F, 1.0F, 9025.0F, 95.0F, 1.0F, 9216.0F,
    96.0F, 1.0F, 9409.0F, 97.0F, 1.0F, 9604.0F, 98.0F, 1.0F, 9801.0F, 99.0F,
    1.0F, 10000.0F, 100.0F, 1.0F, 10201.0F, 101.0F, 1.0F, 10404.0F, 102.0F, 1.0F,
    10609.0F, 103.0F, 1.0F, 10816.0F, 104.0F, 1.0F, 11025.0F, 105.0F, 1.0F,
    11236.0F, 106.0F, 1.0F, 11449.0F, 107.0F, 1.0F, 11664.0F, 108.0F, 1.0F,
    11881.0F, 109.0F, 1.0F, 12100.0F, 110.0F, 1.0F, 12321.0F, 111.0F, 1.0F,
    12544.0F, 112.0F, 1.0F, 12769.0F, 113.0F, 1.0F, 12996.0F, 114.0F, 1.0F,
    13225.0F, 115.0F, 1.0F, 13456.0F, 116.0F, 1.0F, 13689.0F, 117.0F, 1.0F,
    13924.0F, 118.0F, 1.0F, 14161.0F, 119.0F, 1.0F, 14400.0F, 120.0F, 1.0F,
    14641.0F, 121.0F, 1.0F, 14884.0F, 122.0F, 1.0F, 15129.0F, 123.0F, 1.0F,
    15376.0F, 124.0F, 1.0F, 15625.0F, 125.0F, 1.0F, 15876.0F, 126.0F, 1.0F,
    16129.0F, 127.0F, 1.0F, 16384.0F, 128.0F, 1.0F, 16641.0F, 129.0F, 1.0F,
    16900.0F, 130.0F, 1.0F, 17161.0F, 131.0F, 1.0F, 17424.0F, 132.0F, 1.0F,
    17689.0F, 133.0F, 1.0F, 17956.0F, 134.0F, 1.0F, 18225.0F, 135.0F, 1.0F,
    18496.0F, 136.0F, 1.0F, 18769.0F, 137.0F, 1.0F, 19044.0F, 138.0F, 1.0F,
    19321.0F, 139.0F, 1.0F, 19600.0F, 140.0F, 1.0F, 19881.0F, 141.0F, 1.0F,
    20164.0F, 142.0F, 1.0F, 20449.0F, 143.0F, 1.0F, 20736.0F, 144.0F, 1.0F,
    21025.0F, 145.0F, 1.0F, 21316.0F, 146.0F, 1.0F, 21609.0F, 147.0F, 1.0F,
    21904.0F, 148.0F, 1.0F, 22201.0F, 149.0F, 1.0F, 22500.0F, 150.0F, 1.0F,
    22801.0F, 151.0F, 1.0F, 23104.0F, 152.0F, 1.0F, 23409.0F, 153.0F, 1.0F,
    23716.0F, 154.0F, 1.0F, 24025.0F, 155.0F, 1.0F, 24336.0F, 156.0F, 1.0F,
    24649.0F, 157.0F, 1.0F, 24964.0F, 158.0F, 1.0F, 25281.0F, 159.0F, 1.0F,
    25600.0F, 160.0F, 1.0F, 25921.0F, 161.0F, 1.0F, 26244.0F, 162.0F, 1.0F,
    26569.0F, 163.0F, 1.0F, 26896.0F, 164.0F, 1.0F, 27225.0F, 165.0F, 1.0F,
    27556.0F, 166.0F, 1.0F, 27889.0F, 167.0F, 1.0F, 28224.0F, 168.0F, 1.0F,
    28561.0F, 169.0F, 1.0F, 28900.0F, 170.0F, 1.0F, 29241.0F, 171.0F, 1.0F,
    29584.0F, 172.0F, 1.0F, 29929.0F, 173.0F, 1.0F, 30276.0F, 174.0F, 1.0F,
    30625.0F, 175.0F, 1.0F, 30976.0F, 176.0F, 1.0F, 31329.0F, 177.0F, 1.0F,
    31684.0F, 178.0F, 1.0F, 32041.0F, 179.0F, 1.0F, 32400.0F, 180.0F, 1.0F,
    32761.0F, 181.0F, 1.0F, 33124.0F, 182.0F, 1.0F, 33489.0F, 183.0F, 1.0F,
    33856.0F, 184.0F, 1.0F, 34225.0F, 185.0F, 1.0F, 34596.0F, 186.0F, 1.0F,
    34969.0F, 187.0F, 1.0F, 35344.0F, 188.0F, 1.0F, 35721.0F, 189.0F, 1.0F,
    36100.0F, 190.0F, 1.0F, 36481.0F, 191.0F, 1.0F, 36864.0F, 192.0F, 1.0F,
    37249.0F, 193.0F, 1.0F, 37636.0F, 194.0F, 1.0F, 38025.0F, 195.0F, 1.0F,
    38416.0F, 196.0F, 1.0F, 38809.0F, 197.0F, 1.0F, 39204.0F, 198.0F, 1.0F,
    39601.0F, 199.0F, 1.0F, 40000.0F, 200.0F, 1.0F, 40401.0F, 201.0F, 1.0F,
    40804.0F, 202.0F, 1.0F, 41209.0F, 203.0F, 1.0F, 41616.0F, 204.0F, 1.0F,
    42025.0F, 205.0F, 1.0F, 42436.0F, 206.0F, 1.0F, 42849.0F, 207.0F, 1.0F,
    43264.0F, 208.0F, 1.0F, 43681.0F, 209.0F, 1.0F, 44100.0F, 210.0F, 1.0F,
    44521.0F, 211.0F, 1.0F, 44944.0F, 212.0F, 1.0F, 45369.0F, 213.0F, 1.0F,
    45796.0F, 214.0F, 1.0F, 46225.0F, 215.0F, 1.0F, 46656.0F, 216.0F, 1.0F,
    47089.0F, 217.0F, 1.0F, 47524.0F, 218.0F, 1.0F, 47961.0F, 219.0F, 1.0F,
    48400.0F, 220.0F, 1.0F, 48841.0F, 221.0F, 1.0F, 49284.0F, 222.0F, 1.0F,
    49729.0F, 223.0F, 1.0F, 50176.0F, 224.0F, 1.0F, 50625.0F, 225.0F, 1.0F,
    51076.0F, 226.0F, 1.0F, 51529.0F, 227.0F, 1.0F, 51984.0F, 228.0F, 1.0F,
    52441.0F, 229.0F, 1.0F, 52900.0F, 230.0F, 1.0F, 53361.0F, 231.0F, 1.0F,
    53824.0F, 232.0F, 1.0F, 54289.0F, 233.0F, 1.0F, 54756.0F, 234.0F, 1.0F,
    55225.0F, 235.0F, 1.0F, 55696.0F, 236.0F, 1.0F, 56169.0F, 237.0F, 1.0F,
    56644.0F, 238.0F, 1.0F, 57121.0F, 239.0F, 1.0F, 57600.0F, 240.0F, 1.0F,
    58081.0F, 241.0F, 1.0F, 58564.0F, 242.0F, 1.0F, 59049.0F, 243.0F, 1.0F,
    59536.0F, 244.0F, 1.0F, 60025.0F, 245.0F, 1.0F, 60516.0F, 246.0F, 1.0F,
    61009.0F, 247.0F, 1.0F, 61504.0F, 248.0F, 1.0F, 62001.0F, 249.0F, 1.0F,
    62500.0F, 250.0F, 1.0F, 63001.0F, 251.0F, 1.0F, 63504.0F, 252.0F, 1.0F,
    64009.0F, 253.0F, 1.0F, 64516.0F, 254.0F, 1.0F, 65025.0F, 255.0F, 1.0F,
    65536.0F, 256.0F, 1.0F, 66049.0F, 257.0F, 1.0F, 66564.0F, 258.0F, 1.0F,
    67081.0F, 259.0F, 1.0F, 67600.0F, 260.0F, 1.0F, 68121.0F, 261.0F, 1.0F,
    68644.0F, 262.0F, 1.0F, 69169.0F, 263.0F, 1.0F, 69696.0F, 264.0F, 1.0F,
    70225.0F, 265.0F, 1.0F, 70756.0F, 266.0F, 1.0F, 71289.0F, 267.0F, 1.0F,
    71824.0F, 268.0F, 1.0F, 72361.0F, 269.0F, 1.0F, 72900.0F, 270.0F, 1.0F,
    73441.0F, 271.0F, 1.0F, 73984.0F, 272.0F, 1.0F, 74529.0F, 273.0F, 1.0F,
    75076.0F, 274.0F, 1.0F, 75625.0F, 275.0F, 1.0F, 76176.0F, 276.0F, 1.0F,
    76729.0F, 277.0F, 1.0F, 77284.0F, 278.0F, 1.0F, 77841.0F, 279.0F, 1.0F,
    78400.0F, 280.0F, 1.0F, 78961.0F, 281.0F, 1.0F, 79524.0F, 282.0F, 1.0F,
    80089.0F, 283.0F, 1.0F, 80656.0F, 284.0F, 1.0F, 81225.0F, 285.0F, 1.0F,
    81796.0F, 286.0F, 1.0F, 82369.0F, 287.0F, 1.0F, 82944.0F, 288.0F, 1.0F,
    83521.0F, 289.0F, 1.0F, 84100.0F, 290.0F, 1.0F, 84681.0F, 291.0F, 1.0F,
    85264.0F, 292.0F, 1.0F, 85849.0F, 293.0F, 1.0F, 86436.0F, 294.0F, 1.0F,
    87025.0F, 295.0F, 1.0F, 87616.0F, 296.0F, 1.0F, 88209.0F, 297.0F, 1.0F,
    88804.0F, 298.0F, 1.0F, 89401.0F, 299.0F, 1.0F, 90000.0F, 300.0F, 1.0F,
    90601.0F, 301.0F, 1.0F, 91204.0F, 302.0F, 1.0F, 91809.0F, 303.0F, 1.0F,
    92416.0F, 304.0F, 1.0F, 93025.0F, 305.0F, 1.0F, 93636.0F, 306.0F, 1.0F,
    94249.0F, 307.0F, 1.0F, 94864.0F, 308.0F, 1.0F, 95481.0F, 309.0F, 1.0F,
    96100.0F, 310.0F, 1.0F, 96721.0F, 311.0F, 1.0F, 97344.0F, 312.0F, 1.0F,
    97969.0F, 313.0F, 1.0F, 98596.0F, 314.0F, 1.0F, 99225.0F, 315.0F, 1.0F,
    99856.0F, 316.0F, 1.0F, 100489.0F, 317.0F, 1.0F, 101124.0F, 318.0F, 1.0F,
    101761.0F, 319.0F, 1.0F, 102400.0F, 320.0F, 1.0F, 103041.0F, 321.0F, 1.0F,
    103684.0F, 322.0F, 1.0F, 104329.0F, 323.0F, 1.0F, 104976.0F, 324.0F, 1.0F,
    105625.0F, 325.0F, 1.0F, 106276.0F, 326.0F, 1.0F, 106929.0F, 327.0F, 1.0F,
    107584.0F, 328.0F, 1.0F, 108241.0F, 329.0F, 1.0F, 108900.0F, 330.0F, 1.0F,
    109561.0F, 331.0F, 1.0F, 110224.0F, 332.0F, 1.0F, 110889.0F, 333.0F, 1.0F,
    111556.0F, 334.0F, 1.0F, 112225.0F, 335.0F, 1.0F, 112896.0F, 336.0F, 1.0F,
    113569.0F, 337.0F, 1.0F, 114244.0F, 338.0F, 1.0F, 114921.0F, 339.0F, 1.0F,
    115600.0F, 340.0F, 1.0F, 116281.0F, 341.0F, 1.0F, 116964.0F, 342.0F, 1.0F,
    117649.0F, 343.0F, 1.0F, 118336.0F, 344.0F, 1.0F, 119025.0F, 345.0F, 1.0F,
    119716.0F, 346.0F, 1.0F, 120409.0F, 347.0F, 1.0F, 121104.0F, 348.0F, 1.0F,
    121801.0F, 349.0F, 1.0F, 122500.0F, 350.0F, 1.0F, 123201.0F, 351.0F, 1.0F,
    123904.0F, 352.0F, 1.0F, 124609.0F, 353.0F, 1.0F, 125316.0F, 354.0F, 1.0F,
    126025.0F, 355.0F, 1.0F, 126736.0F, 356.0F, 1.0F, 127449.0F, 357.0F, 1.0F,
    128164.0F, 358.0F, 1.0F, 128881.0F, 359.0F, 1.0F, 129600.0F, 360.0F, 1.0F,
    130321.0F, 361.0F, 1.0F, 131044.0F, 362.0F, 1.0F, 131769.0F, 363.0F, 1.0F,
    132496.0F, 364.0F, 1.0F, 133225.0F, 365.0F, 1.0F, 133956.0F, 366.0F, 1.0F,
    134689.0F, 367.0F, 1.0F, 135424.0F, 368.0F, 1.0F, 136161.0F, 369.0F, 1.0F,
    136900.0F, 370.0F, 1.0F, 137641.0F, 371.0F, 1.0F, 138384.0F, 372.0F, 1.0F,
    139129.0F, 373.0F, 1.0F, 139876.0F, 374.0F, 1.0F, 140625.0F, 375.0F, 1.0F,
    141376.0F, 376.0F, 1.0F, 142129.0F, 377.0F, 1.0F, 142884.0F, 378.0F, 1.0F,
    143641.0F, 379.0F, 1.0F, 144400.0F, 380.0F, 1.0F, 145161.0F, 381.0F, 1.0F,
    145924.0F, 382.0F, 1.0F, 146689.0F, 383.0F, 1.0F, 147456.0F, 384.0F, 1.0F,
    148225.0F, 385.0F, 1.0F, 148996.0F, 386.0F, 1.0F, 149769.0F, 387.0F, 1.0F,
    150544.0F, 388.0F, 1.0F, 151321.0F, 389.0F, 1.0F, 152100.0F, 390.0F, 1.0F,
    152881.0F, 391.0F, 1.0F, 153664.0F, 392.0F, 1.0F, 154449.0F, 393.0F, 1.0F,
    155236.0F, 394.0F, 1.0F, 156025.0F, 395.0F, 1.0F, 156816.0F, 396.0F, 1.0F,
    157609.0F, 397.0F, 1.0F, 158404.0F, 398.0F, 1.0F, 159201.0F, 399.0F, 1.0F,
    160000.0F, 400.0F, 1.0F, 160801.0F, 401.0F, 1.0F, 161604.0F, 402.0F, 1.0F,
    162409.0F, 403.0F, 1.0F, 163216.0F, 404.0F, 1.0F, 164025.0F, 405.0F, 1.0F,
    164836.0F, 406.0F, 1.0F, 165649.0F, 407.0F, 1.0F, 166464.0F, 408.0F, 1.0F,
    167281.0F, 409.0F, 1.0F, 168100.0F, 410.0F, 1.0F, 168921.0F, 411.0F, 1.0F,
    169744.0F, 412.0F, 1.0F, 170569.0F, 413.0F, 1.0F, 171396.0F, 414.0F, 1.0F,
    172225.0F, 415.0F, 1.0F, 173056.0F, 416.0F, 1.0F, 173889.0F, 417.0F, 1.0F,
    174724.0F, 418.0F, 1.0F, 175561.0F, 419.0F, 1.0F, 176400.0F, 420.0F, 1.0F,
    177241.0F, 421.0F, 1.0F, 178084.0F, 422.0F, 1.0F, 178929.0F, 423.0F, 1.0F,
    179776.0F, 424.0F, 1.0F, 180625.0F, 425.0F, 1.0F, 181476.0F, 426.0F, 1.0F,
    182329.0F, 427.0F, 1.0F, 183184.0F, 428.0F, 1.0F, 184041.0F, 429.0F, 1.0F,
    184900.0F, 430.0F, 1.0F, 185761.0F, 431.0F, 1.0F, 186624.0F, 432.0F, 1.0F,
    187489.0F, 433.0F, 1.0F, 188356.0F, 434.0F, 1.0F, 189225.0F, 435.0F, 1.0F,
    190096.0F, 436.0F, 1.0F, 190969.0F, 437.0F, 1.0F, 191844.0F, 438.0F, 1.0F,
    192721.0F, 439.0F, 1.0F, 193600.0F, 440.0F, 1.0F, 194481.0F, 441.0F, 1.0F,
    195364.0F, 442.0F, 1.0F, 196249.0F, 443.0F, 1.0F, 197136.0F, 444.0F, 1.0F,
    198025.0F, 445.0F, 1.0F, 198916.0F, 446.0F, 1.0F, 199809.0F, 447.0F, 1.0F,
    200704.0F, 448.0F, 1.0F, 201601.0F, 449.0F, 1.0F, 202500.0F, 450.0F, 1.0F,
    203401.0F, 451.0F, 1.0F, 204304.0F, 452.0F, 1.0F, 205209.0F, 453.0F, 1.0F,
    206116.0F, 454.0F, 1.0F, 207025.0F, 455.0F, 1.0F, 207936.0F, 456.0F, 1.0F,
    208849.0F, 457.0F, 1.0F, 209764.0F, 458.0F, 1.0F, 210681.0F, 459.0F, 1.0F,
    211600.0F, 460.0F, 1.0F, 212521.0F, 461.0F, 1.0F, 213444.0F, 462.0F, 1.0F,
    214369.0F, 463.0F, 1.0F, 215296.0F, 464.0F, 1.0F, 216225.0F, 465.0F, 1.0F,
    217156.0F, 466.0F, 1.0F, 218089.0F, 467.0F, 1.0F, 219024.0F, 468.0F, 1.0F,
    219961.0F, 469.0F, 1.0F, 220900.0F, 470.0F, 1.0F, 221841.0F, 471.0F, 1.0F,
    222784.0F, 472.0F, 1.0F, 223729.0F, 473.0F, 1.0F, 224676.0F, 474.0F, 1.0F,
    225625.0F, 475.0F, 1.0F, 226576.0F, 476.0F, 1.0F, 227529.0F, 477.0F, 1.0F,
    228484.0F, 478.0F, 1.0F, 229441.0F, 479.0F, 1.0F, 230400.0F, 480.0F, 1.0F,
    231361.0F, 481.0F, 1.0F, 232324.0F, 482.0F, 1.0F, 233289.0F, 483.0F, 1.0F,
    234256.0F, 484.0F, 1.0F, 235225.0F, 485.0F, 1.0F, 236196.0F, 486.0F, 1.0F,
    237169.0F, 487.0F, 1.0F, 238144.0F, 488.0F, 1.0F, 239121.0F, 489.0F, 1.0F,
    240100.0F, 490.0F, 1.0F, 241081.0F, 491.0F, 1.0F, 242064.0F, 492.0F, 1.0F,
    243049.0F, 493.0F, 1.0F, 244036.0F, 494.0F, 1.0F, 245025.0F, 495.0F, 1.0F,
    246016.0F, 496.0F, 1.0F, 247009.0F, 497.0F, 1.0F, 248004.0F, 498.0F, 1.0F,
    249001.0F, 499.0F, 1.0F, 250000.0F, 500.0F, 1.0F };

  mod_foggui_mldivide(c, e, mod_foggui_B.a_tmp);
  for (i = 0; i < 3; i++) {
    a[i] = 0.0F;
    b[i] = 0.0F;
    for (i_0 = 0; i_0 < 500; i_0++) {
      a_tmp = mod_foggui_B.a_tmp[3 * i_0 + i];
      a[i] += a_tmp * d[i_0];
      b[i] += d[i_0 + 500] * a_tmp;
    }
  }

  a_tmp = 2.0F * a[0];
  for (i = 0; i < 500; i++) {
    x_[i] = (static_cast<real32_T>(i) + 1.0F) * a_tmp + a[1];
  }

  a_tmp = 2.0F * b[0];
  for (i = 0; i < 500; i++) {
    y_[i] = (static_cast<real32_T>(i) + 1.0F) * a_tmp + b[1];
  }

  return 1.0F / ((2.0F * a[0] * x_[499] - 2.0F * a[0] * y_[499]) / rt_powf_snf
                 (x_[499] * x_[499] + y_[499] * y_[499], 1.5F));
}

real32_T mod_fogguiModelClass::mod_foggui_norm(const real32_T x[2])
{
  real32_T y;
  real32_T scale;
  real32_T absxk;
  real32_T t;
  scale = 1.29246971E-26F;
  absxk = std::abs(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * std::sqrt(y);
}

void mod_fogguiModelClass::mod_foggui_guiamentoLongitudinal(const real32_T vh[3],
  const real32_T pos[3], const real32_T pos_a[3], const real32_T pos_buffer[1000],
  real32_T Dgui, real32_T fator_curvatura, real32_T *vc, real32_T *lambda_dot,
  real32_T pontos_out[10], int8_T *modo)
{
  real32_T vx;
  real32_T raio_curvatura;
  real32_T vu[2];
  real32_T alpha;
  real32_T m1;
  real32_T m2;
  real32_T a2;
  real32_T b2;
  real32_T k1;
  real32_T k2;
  int32_T i;
  real32_T x1;
  real32_T b_y1;
  real32_T y_tmp[2];
  real32_T b_px[2];
  real32_T p1;
  real32_T p4;
  real32_T tmp[4];
  int32_T i_0;
  real32_T p1_idx_1;
  real32_T p4_idx_1;
  real32_T b_px_idx_0;
  real32_T b_px_idx_1;
  real32_T p3_idx_0;
  int32_T tmp_0;
  static const int8_T d[16] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0,
    0 };

  boolean_T exitg1;
  vx = rt_hypotf_snf(vh[0], vh[1]);
  if (!mod_foggui_DW.pontos_not_empty) {
    raio_curvatura = mod_foggui_calculoRaioCurvatura(pos_buffer) *
      fator_curvatura;
    alpha = rt_hypotf_snf(vx, -vh[2]);
    vu[0] = vx / alpha;
    vu[1] = -vh[2] / alpha;
    p1 = rt_hypotf_snf(pos[0], pos[1]);
    p1_idx_1 = pos[2];
    p4 = rt_hypotf_snf(pos_a[0], pos_a[1]);
    p4_idx_1 = pos_a[2];
    alpha = ((3.14159274F - rt_atan2f_snf(pos[2] - pos_a[2], p1 - p4)) +
             1.57079637F) / 2.0F;
    m1 = rt_atan2f_snf(vu[1], vu[0]);
    m2 = std::tan(3.14159274F - alpha);
    m2 = (((pos_a[2] - pos[2]) + p1 * m1) - p4 * m2) / (m1 - m2);
    b_px_idx_0 = m2;
    b_px_idx_1 = (m2 - p1) * m1 + pos[2];
    m1 = 0.5F;
    m2 = 0.9F;
    a2 = 0.1F;
    b2 = 0.9F;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 15)) {
      k1 = (m1 + m2) / 2.0F;
      k2 = (a2 + b2) / 2.0F;
      b_px[0] = b_px_idx_0 - p1;
      b_px[1] = b_px_idx_1 - p1_idx_1;
      x1 = mod_foggui_norm(b_px);
      b_px[0] = b_px_idx_0 - p4;
      b_px[1] = b_px_idx_1 - p4_idx_1;
      b_y1 = mod_foggui_norm(b_px);
      p3_idx_0 = -std::cos(alpha) * b_y1 * k2 + p4;
      b_y1 = std::sin(alpha) * b_y1 * k2 + p4_idx_1;
      y_tmp[0] = p4 - p3_idx_0;
      mod_foggui_DW.pontos[0] = p1;
      mod_foggui_DW.pontos[1] = vu[0] * x1 * k1 + p1;
      mod_foggui_DW.pontos[2] = p3_idx_0;
      mod_foggui_DW.pontos[3] = p4;
      y_tmp[1] = p4_idx_1 - b_y1;
      mod_foggui_DW.pontos[5] = p1_idx_1;
      mod_foggui_DW.pontos[6] = vu[1] * x1 * k1 + p1_idx_1;
      mod_foggui_DW.pontos[7] = b_y1;
      mod_foggui_DW.pontos[8] = p4_idx_1;
      b_y1 = mod_foggui_norm(y_tmp);
      mod_foggui_DW.pontos[4] = y_tmp[0] / b_y1 * 10000.0F + p4;
      mod_foggui_DW.pontos[9] = y_tmp[1] / b_y1 * 10000.0F + p4_idx_1;
      x1 = mod_foggui_DW.pontos[1] - mod_foggui_DW.pontos[0];
      b_y1 = mod_foggui_DW.pontos[6] - mod_foggui_DW.pontos[5];
      b_px[0] = x1;
      b_px[1] = b_y1;
      p3_idx_0 = mod_foggui_norm(b_px);
      x1 = 1.0F / (((mod_foggui_DW.pontos[7] - mod_foggui_DW.pontos[5]) * x1 -
                    (mod_foggui_DW.pontos[2] - mod_foggui_DW.pontos[0]) * b_y1) *
                   0.666666687F / p3_idx_0 / p3_idx_0 / p3_idx_0);
      x1 = std::abs(x1) - raio_curvatura;
      if (x1 > 0.0F) {
        m2 = k1;
        a2 = k2;
      } else {
        m1 = k1;
        b2 = k2;
      }

      if (std::abs(x1) < 1.0F) {
        exitg1 = true;
      } else {
        i++;
      }
    }

    mod_foggui_DW.pontos_not_empty = true;
  }

  raio_curvatura = rt_hypotf_snf(pos[0], pos[1]);
  alpha = raio_curvatura + Dgui;
  *modo = 1;
  m1 = 0.0F;
  m2 = 1.0F;
  a2 = 0.0F;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 20)) {
    b2 = (m1 + m2) / 2.0F;
    if (!(alpha >= mod_foggui_DW.pontos[3])) {
      p1 = rt_powf_snf(b2, 3.0F);
      p1_idx_1 = b2 * b2;
      for (i_0 = 0; i_0 < 4; i_0++) {
        tmp_0 = i_0 << 2;
        x1 = static_cast<real32_T>(d[tmp_0 + 3]) + (static_cast<real32_T>
          (d[tmp_0 + 2]) * b2 + (static_cast<real32_T>(d[tmp_0 + 1]) * p1_idx_1
          + static_cast<real32_T>(d[tmp_0]) * p1));
        tmp[i_0] = x1;
      }

      for (i_0 = 0; i_0 < 2; i_0++) {
        p1 = mod_foggui_DW.pontos[5 * i_0 + 3] * tmp[3] + (mod_foggui_DW.pontos
          [5 * i_0 + 2] * tmp[2] + (mod_foggui_DW.pontos[5 * i_0 + 1] * tmp[1] +
          mod_foggui_DW.pontos[5 * i_0] * tmp[0]));
        vu[i_0] = p1;
      }
    } else {
      vu[0] = (-b2 + 1.0F) * mod_foggui_DW.pontos[3] + b2 *
        mod_foggui_DW.pontos[4];
      vu[1] = b2 * mod_foggui_DW.pontos[9] + (-b2 + 1.0F) *
        mod_foggui_DW.pontos[8];
      *modo = 2;
    }

    if (vu[0] >= alpha) {
      m2 = b2;
    } else {
      m1 = b2;
    }

    if (std::abs(vu[0] - alpha) <= 1.0F) {
      a2 = vu[1];
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (mod_foggui_DW.y_ == -999.0F) {
    mod_foggui_DW.y_ = a2;
  }

  mod_foggui_DW.y_ = mod_foggui_DW.y_ * 0.7304F + a2 * 0.2696F;
  raio_curvatura -= alpha;
  alpha = pos[2] - mod_foggui_DW.y_;
  m1 = rt_hypotf_snf(raio_curvatura, alpha);
  *vc = (vx * raio_curvatura + -vh[2] * alpha) / m1;
  *lambda_dot = (alpha * vx - raio_curvatura * -vh[2]) / m1 / m1;
  pontos_out[0] = mod_foggui_DW.pontos[0];
  pontos_out[1] = mod_foggui_DW.pontos[1];
  pontos_out[2] = mod_foggui_DW.pontos[2];
  pontos_out[3] = mod_foggui_DW.pontos[3];
  pontos_out[4] = mod_foggui_DW.pontos[4];
  pontos_out[5] = mod_foggui_DW.pontos[5];
  pontos_out[6] = mod_foggui_DW.pontos[6];
  pontos_out[7] = mod_foggui_DW.pontos[7];
  pontos_out[8] = mod_foggui_DW.pontos[8];
  pontos_out[9] = mod_foggui_DW.pontos[9];
}

real32_T rt_remf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T u1_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1) || rtIsInfF(u0)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0F) {
      u1_0 = std::ceil(u1);
    } else {
      u1_0 = std::floor(u1);
    }

    if ((u1 != 0.0F) && (u1 != u1_0)) {
      u1_0 = std::abs(u0 / u1);
      if (std::abs(u1_0 - std::floor(u1_0 + 0.5F)) <= FLT_EPSILON * u1_0) {
        y = 0.0F * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

void mod_fogguiModelClass::mod_foggui_cosd(real32_T *x)
{
  int8_T n;
  real32_T b_x;
  real32_T absx;
  if (rtIsInfF(*x) || rtIsNaNF(*x)) {
    *x = (rtNaNF);
  } else {
    b_x = rt_remf_snf(*x, 360.0F);
    absx = std::abs(b_x);
    if (absx > 180.0F) {
      if (b_x > 0.0F) {
        b_x -= 360.0F;
      } else {
        b_x += 360.0F;
      }

      absx = std::abs(b_x);
    }

    if (absx <= 45.0F) {
      b_x *= 0.0174532924F;
      *x = std::cos(b_x);
    } else {
      if (absx <= 135.0F) {
        if (b_x > 0.0F) {
          b_x = (b_x - 90.0F) * 0.0174532924F;
          n = 1;
        } else {
          b_x = (b_x + 90.0F) * 0.0174532924F;
          n = -1;
        }
      } else if (b_x > 0.0F) {
        b_x = (b_x - 180.0F) * 0.0174532924F;
        n = 2;
      } else {
        b_x = (b_x + 180.0F) * 0.0174532924F;
        n = -2;
      }

      if (n == 1) {
        *x = -std::sin(b_x);
      } else if (n == -1) {
        *x = std::sin(b_x);
      } else {
        *x = -std::cos(b_x);
      }
    }
  }
}

void mod_fogguiModelClass::mod_foggui_sind(real32_T *x)
{
  int8_T n;
  real32_T c_x;
  real32_T absx;
  if (rtIsInfF(*x) || rtIsNaNF(*x)) {
    *x = (rtNaNF);
  } else {
    c_x = rt_remf_snf(*x, 360.0F);
    absx = std::abs(c_x);
    if (absx > 180.0F) {
      if (c_x > 0.0F) {
        c_x -= 360.0F;
      } else {
        c_x += 360.0F;
      }

      absx = std::abs(c_x);
    }

    if (absx <= 45.0F) {
      c_x *= 0.0174532924F;
      *x = std::sin(c_x);
    } else {
      if (absx <= 135.0F) {
        if (c_x > 0.0F) {
          c_x = (c_x - 90.0F) * 0.0174532924F;
          n = 1;
        } else {
          c_x = (c_x + 90.0F) * 0.0174532924F;
          n = -1;
        }
      } else if (c_x > 0.0F) {
        c_x = (c_x - 180.0F) * 0.0174532924F;
        n = 2;
      } else {
        c_x = (c_x + 180.0F) * 0.0174532924F;
        n = -2;
      }

      if (n == 1) {
        *x = std::cos(c_x);
      } else if (n == -1) {
        *x = -std::cos(c_x);
      } else {
        *x = -std::sin(c_x);
      }
    }
  }
}

int32_T mod_fogguiModelClass::mod_foggui_thirdOfFive(const real32_T v[10],
  int32_T ia, int32_T ib)
{
  int32_T im;
  int32_T j4;
  int32_T j5;
  real32_T v4;
  real32_T v5;
  int32_T b_j1;
  int32_T j2;
  real32_T v5_tmp;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    v4 = v[ia - 1];
    if (v4 < v[ia]) {
      v5_tmp = v[ia + 1];
      if (v[ia] < v5_tmp) {
        im = ia + 1;
      } else if (v4 < v5_tmp) {
        im = ia + 2;
      } else {
        im = ia;
      }
    } else {
      v5_tmp = v[ia + 1];
      if (v4 < v5_tmp) {
        im = ia;
      } else if (v[ia] < v5_tmp) {
        im = ia + 2;
      } else {
        im = ia + 1;
      }
    }
  } else {
    v4 = v[ia - 1];
    if (v4 < v[ia]) {
      v5_tmp = v[ia + 1];
      if (v[ia] < v5_tmp) {
        b_j1 = ia;
        j2 = ia;
        im = ia + 2;
      } else if (v4 < v5_tmp) {
        b_j1 = ia;
        j2 = ia + 1;
        im = ia + 1;
      } else {
        b_j1 = ia + 2;
        j2 = ia - 1;
        im = ia + 1;
      }
    } else {
      v5_tmp = v[ia + 1];
      if (v4 < v5_tmp) {
        b_j1 = ia + 1;
        j2 = ia - 1;
        im = ia + 2;
      } else if (v[ia] < v5_tmp) {
        b_j1 = ia + 1;
        j2 = ia + 1;
        im = ia;
      } else {
        b_j1 = ia + 2;
        j2 = ia;
        im = ia;
      }
    }

    j4 = ia;
    j5 = ia + 1;
    v4 = v[ia + 2];
    v5_tmp = v[ia + 3];
    v5 = v5_tmp;
    if (v5_tmp < v4) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v4;
      v4 = v5_tmp;
    }

    if (v5 < v[b_j1 - 1]) {
      im = b_j1;
    } else if (v5 < v[j2]) {
      im = j5 + 3;
    } else if (v4 < v[j2]) {
      im = j2 + 1;
    } else {
      if (v4 < v[im - 1]) {
        im = j4 + 3;
      }
    }
  }

  return im;
}

void mod_fogguiModelClass::mod_foggui_quickselect(real32_T v[10], int32_T n,
  int32_T idx0, int32_T vlen, real32_T *vn, int32_T *nfirst, int32_T *nlast)
{
  int32_T itarget;
  int32_T ipiv;
  int32_T ia;
  int32_T ib;
  int32_T ifirst;
  int32_T ilast;
  int32_T oldnv;
  boolean_T checkspeed;
  boolean_T isslow;
  real32_T b_v[10];
  real32_T vref;
  real32_T vk;
  int32_T b_nlast;
  int32_T i1;
  int32_T destidx;
  boolean_T exitg1;
  boolean_T guard1 = false;
  if ((n < 1) || (n > vlen)) {
    *vn = (rtNaNF);
    *nfirst = 0;
    *nlast = 0;
  } else {
    itarget = (idx0 + n) - 1;
    ipiv = itarget - 1;
    ia = idx0 - 1;
    ib = (idx0 + vlen) - 2;
    ifirst = idx0;
    ilast = ib;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia + 1 < ib + 1)) {
      for (ilast = 0; ilast < 10; ilast++) {
        b_v[ilast] = v[ilast];
      }

      vref = v[ipiv];
      b_v[ipiv] = v[ib];
      b_v[ib] = v[ipiv];
      b_nlast = ia;
      ifirst = -1;
      for (ilast = ia; ilast < ib; ilast++) {
        vk = b_v[ilast];
        if (b_v[ilast] == vref) {
          b_v[ilast] = b_v[b_nlast];
          b_v[b_nlast] = vk;
          ifirst++;
          b_nlast++;
        } else {
          if (b_v[ilast] < vref) {
            b_v[ilast] = b_v[b_nlast];
            b_v[b_nlast] = vk;
            b_nlast++;
          }
        }
      }

      b_v[ib] = b_v[b_nlast];
      b_v[b_nlast] = v[ipiv];
      for (ilast = 0; ilast < 10; ilast++) {
        v[ilast] = b_v[ilast];
      }

      ilast = b_nlast;
      guard1 = false;
      if (itarget <= b_nlast + 1) {
        ifirst = b_nlast - ifirst;
        if (itarget >= ifirst) {
          exitg1 = true;
        } else {
          ib = b_nlast - 1;
          guard1 = true;
        }
      } else {
        ia = b_nlast + 1;
        guard1 = true;
      }

      if (guard1) {
        ipiv = (ib - ia) + 1;
        if (checkspeed) {
          isslow = (ipiv > oldnv / 2);
          oldnv = ipiv;
        }

        checkspeed = !checkspeed;
        if (isslow) {
          while (ipiv > 1) {
            ilast = ipiv / 5;
            b_nlast = ipiv - ilast * 5;
            ipiv = ilast;
            for (ifirst = 0; ifirst < ilast; ifirst++) {
              i1 = (ifirst * 5 + ia) + 1;
              i1 = mod_foggui_thirdOfFive(v, i1, i1 + 4) - 1;
              destidx = ia + ifirst;
              vref = v[destidx];
              v[destidx] = v[i1];
              v[i1] = vref;
            }

            if (b_nlast > 0) {
              i1 = (ilast * 5 + ia) + 1;
              i1 = mod_foggui_thirdOfFive(v, i1, (i1 + b_nlast) - 1) - 1;
              destidx = ia + ilast;
              vref = v[destidx];
              v[destidx] = v[i1];
              v[i1] = vref;
              ipiv = ilast + 1;
            }
          }
        } else {
          if (ipiv >= 3) {
            ipiv = (ipiv - 1) / 2 + ia;
            if (b_v[ia] < b_v[ipiv]) {
              if (b_v[ipiv] < b_v[ib]) {
                ipiv++;
              } else if (b_v[ia] < b_v[ib]) {
                ipiv = ib + 1;
              } else {
                ipiv = ia + 1;
              }
            } else if (b_v[ia] < b_v[ib]) {
              ipiv = ia + 1;
            } else if (b_v[ipiv] < b_v[ib]) {
              ipiv = ib + 1;
            } else {
              ipiv++;
            }

            ipiv--;
            if (ipiv + 1 > ia + 1) {
              v[ia] = b_v[ipiv];
              v[ipiv] = b_v[ia];
            }
          }
        }

        ipiv = ia;
        ifirst = ia + 1;
        ilast = ib;
      }
    }

    *vn = v[ilast];
    *nfirst = (ifirst - idx0) + 1;
    *nlast = (ilast - idx0) + 2;
  }
}

real_T mod_fogguiModelClass::mod_foggui_norm_hmux2c0tmp(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = std::abs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * std::sqrt(y);
}

void mod_fogguiModelClass::mod_foggui_dynamicEquations3DoF(const real_T entrada
  [6], real_T g, real_T Fa, real_T Xp[6])
{
  real_T VEL[3];
  real_T clat;
  real_T slat;
  real_T la_p;
  real_T lo_p;
  real_T tmp;
  real_T Xp_tmp;
  VEL[0] = entrada[3];
  VEL[1] = entrada[4];
  VEL[2] = entrada[5];
  clat = std::cos(entrada[0]);
  slat = std::sqrt(1.0 - clat * clat);
  tmp = mod_foggui_norm_hmux2c0tmp(VEL);
  la_p = entrada[3] / (entrada[2] + 6.378138E+6);
  lo_p = entrada[4] / (entrada[2] + 6.378138E+6) / clat;
  Xp[0] = la_p;
  Xp[1] = lo_p;
  Xp[2] = -entrada[5];
  Xp_tmp = (lo_p + 0.0001458423) * entrada[4];
  Xp[3] = (-entrada[3] / tmp * Fa - Xp_tmp * slat) + entrada[5] * la_p;
  Xp[4] = ((lo_p + 0.0001458423) * entrada[3] * slat + -entrada[4] / tmp * Fa) +
    (lo_p + 0.0001458423) * entrada[5] * clat;
  Xp[5] = ((-entrada[5] / tmp * Fa - Xp_tmp * clat) - entrada[3] * la_p) + g;
}

void mod_fogguiModelClass::mod_foggui_calculaTrajetoria(const real32_T LLA[3],
  const real32_T VEL[3], const real32_T ALVO[3], real32_T config_step_ini,
  real32_T config_step_mid, real32_T config_step_fim, real32_T
  config_tempo_step_ini, real32_T config_tempo_step_mid, real32_T
  config_epsilon_step, real32_T config_epsilon_altura, real32_T
  config_max_iteracoes, const s8zZSU4DcwnDyW5HgyKzKEG_mod_foggui_T *fog,
  real32_T Tref, real32_T P0, real32_T lla[3], int32_T *nro_iteracoes, int32_T
  *flag_caiu)
{
  real32_T fatorEngenhariaCd;
  real_T VEL_double[3];
  int32_T flag_step_ini;
  int32_T flag_step_mid;
  real32_T tempo;
  real32_T step_aux;
  real32_T rho0;
  real32_T Fa;
  int32_T i;
  real32_T Mach;
  int32_T indice;
  real32_T b_fator;
  real_T entrada[6];
  real_T k1[6];
  real_T k2[6];
  real32_T z;
  real_T a_tmp;
  real_T tmp[6];
  real_T entrada_0[6];
  real_T LLA_double_idx_0;
  real_T LLA_double_idx_1;
  real_T LLA_double_idx_2;
  real_T LLAaux_idx_0;
  real_T VELaux_idx_0;
  real_T LLAaux_idx_1;
  real_T VELaux_idx_1;
  real_T LLAaux_idx_2;
  real_T VELaux_idx_2;
  int32_T Mach_tmp;
  boolean_T exitg1;
  *nro_iteracoes = 0;
  *flag_caiu = 0;
  fatorEngenhariaCd = fog->Cd_fac_eng;
  LLA_double_idx_0 = LLA[0];
  VEL_double[0] = VEL[0];
  LLA_double_idx_1 = LLA[1];
  VEL_double[1] = VEL[1];
  LLA_double_idx_2 = LLA[2];
  VEL_double[2] = VEL[2];
  flag_step_ini = 0;
  flag_step_mid = 0;
  tempo = 0.0F;
  step_aux = 0.0F;
  rho0 = P0 / (287.058F * Tref);
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i <= static_cast<int32_T>(config_max_iteracoes) - 1)) {
    if (static_cast<real32_T>(i) + 1.0F < 2.14748365E+9F) {
      *nro_iteracoes = static_cast<int32_T>((static_cast<real32_T>(i) + 1.0F));
    } else {
      *nro_iteracoes = MAX_int32_T;
    }

    z = 6.371E+6F / (static_cast<real32_T>(LLA_double_idx_2) + 6.371E+6F);
    z = z * z * 9.80665F;
    Mach = std::sqrt((-0.0065F * LLA[2] + Tref) * 401.881226F);
    if (fog->Cd_fac_eng <= -1.0F) {
      fatorEngenhariaCd = 1.0F;
    }

    if (static_cast<real32_T>(i) + 1.0F <= fog->Delta_ejec / config_step_fim) {
      Mach = static_cast<real32_T>(mod_foggui_norm_hmux2c0tmp(VEL_double)) /
        Mach;
      Fa = rt_roundf_snf(Mach * 10.0F);
      if (Fa < 2.14748365E+9F) {
        if (Fa >= -2.14748365E+9F) {
          indice = static_cast<int32_T>(Fa);
        } else {
          indice = MIN_int32_T;
        }
      } else {
        indice = MAX_int32_T;
      }

      if (indice > 39) {
        indice = 39;
      }

      indice++;
      Mach_tmp = static_cast<int32_T>(static_cast<real32_T>(indice)) - 1;
      Mach = ((Mach * 10.0F - static_cast<real32_T>(indice)) * (fog->Cwss[
               static_cast<int32_T>(static_cast<real32_T>(indice))] - fog->
               Cwss[Mach_tmp]) + fog->Cwss[Mach_tmp]) * fatorEngenhariaCd;
    } else {
      Mach = static_cast<real32_T>(mod_foggui_norm_hmux2c0tmp(VEL_double)) /
        Mach;
      Fa = rt_roundf_snf(Mach * 10.0F);
      if (Fa < 2.14748365E+9F) {
        if (Fa >= -2.14748365E+9F) {
          indice = static_cast<int32_T>(Fa);
        } else {
          indice = MIN_int32_T;
        }
      } else {
        indice = MAX_int32_T;
      }

      if (indice > 39) {
        indice = 39;
      }

      indice++;
      Mach_tmp = static_cast<int32_T>(static_cast<real32_T>(indice)) - 1;
      Mach = ((Mach * 10.0F - static_cast<real32_T>(indice)) * (fog->Cwss[
               static_cast<int32_T>(static_cast<real32_T>(indice))] - fog->
               Cwss[Mach_tmp]) + fog->Cwss[Mach_tmp]) * fog->Cdadjsm *
        fatorEngenhariaCd;
    }

    a_tmp = mod_foggui_norm_hmux2c0tmp(VEL_double);
    Mach *= rt_powf_snf(-0.0065F * LLA[2] / Tref + 1.0F, -z / -1.86587715F -
                        1.0F) * rho0 * static_cast<real32_T>((a_tmp * a_tmp)) /
      2.0F * fog->S;
    Fa = Mach / fog->Massa;
    if (a_tmp != 0.0) {
      LLAaux_idx_0 = LLA_double_idx_0;
      VELaux_idx_0 = VEL_double[0];
      LLAaux_idx_1 = LLA_double_idx_1;
      VELaux_idx_1 = VEL_double[1];
      LLAaux_idx_2 = LLA_double_idx_2;
      VELaux_idx_2 = VEL_double[2];
      tempo += step_aux;
      if (tempo >= config_tempo_step_ini) {
        flag_step_ini = 1;
      }

      if (tempo >= config_tempo_step_mid) {
        flag_step_mid = 1;
      }

      if (flag_step_ini != 0) {
        step_aux = 1.0F / (std::exp(-mod_foggui_DW.x[0]) + 1.0F);
        mod_foggui_DW.x[0] += 0.709F;
      } else {
        mod_foggui_DW.x[0] = -7.09F;
        step_aux = 0.0F;
      }

      if (flag_step_mid != 0) {
        b_fator = 1.0F / (std::exp(-mod_foggui_DW.x[1]) + 1.0F);
        mod_foggui_DW.x[1] += 0.709F;
      } else {
        mod_foggui_DW.x[1] = -7.09F;
        b_fator = 0.0F;
      }

      step_aux = ((1.0F - step_aux) * config_step_ini + config_step_mid *
                  step_aux) * (1.0F - b_fator) + config_step_fim * b_fator;
      entrada[0] = LLA_double_idx_0;
      entrada[3] = VEL_double[0];
      entrada[1] = LLA_double_idx_1;
      entrada[4] = VEL_double[1];
      entrada[2] = LLA_double_idx_2;
      entrada[5] = VEL_double[2];
      mod_foggui_dynamicEquations3DoF(entrada, static_cast<real_T>(z),
        static_cast<real_T>(Fa), k1);
      for (indice = 0; indice < 6; indice++) {
        entrada_0[indice] = 0.5 * k1[indice] * step_aux + entrada[indice];
      }

      mod_foggui_dynamicEquations3DoF(entrada_0, static_cast<real_T>(z),
        static_cast<real_T>(Fa), k2);
      a_tmp = 2.0 * step_aux;
      for (indice = 0; indice < 6; indice++) {
        entrada_0[indice] = (a_tmp * k2[indice] + entrada[indice]) - step_aux *
          k1[indice];
      }

      mod_foggui_dynamicEquations3DoF(entrada_0, static_cast<real_T>(z),
        static_cast<real_T>((Mach / fog->Massa)), tmp);
      for (indice = 0; indice < 6; indice++) {
        entrada[indice] += ((4.0 * k2[indice] + k1[indice]) + tmp[indice]) *
          step_aux / 6.0;
      }

      LLA_double_idx_0 = entrada[0];
      VEL_double[0] = entrada[3];
      LLA_double_idx_1 = entrada[1];
      VEL_double[1] = entrada[4];
      LLA_double_idx_2 = entrada[2];
      VEL_double[2] = entrada[5];
      if ((entrada[2] < ALVO[2]) && (config_step_fim > config_epsilon_step) &&
          (std::abs(static_cast<real32_T>(entrada[2]) - ALVO[2]) >
           config_epsilon_altura)) {
        config_step_fim /= 2.0F;
        LLA_double_idx_0 = LLAaux_idx_0;
        VEL_double[0] = VELaux_idx_0;
        LLA_double_idx_1 = LLAaux_idx_1;
        VEL_double[1] = VELaux_idx_1;
        LLA_double_idx_2 = LLAaux_idx_2;
        VEL_double[2] = VELaux_idx_2;
        i++;
      } else {
        tempo += step_aux;
        if (entrada[2] <= ALVO[2]) {
          *flag_caiu = 1;
          exitg1 = true;
        } else {
          i++;
        }
      }
    } else {
      exitg1 = true;
    }
  }

  lla[0] = static_cast<real32_T>((LLA_double_idx_0 * 180.0 / 3.1415926535897931));
  lla[1] = static_cast<real32_T>((LLA_double_idx_1 * 180.0 / 3.1415926535897931));
  lla[2] = static_cast<real32_T>(LLA_double_idx_2);
}

void mod_fogguiModelClass::mod_foggui_calculaErro(const real32_T lla[3], const
  real32_T lla_targ[3], int32_T flag_caiu, int32_T *flag_ejecao, real32_T
  *modulo_erro)
{
  boolean_T crescente_[5];
  real32_T Rn;
  real32_T b_y1[5];
  int32_T iyLead;
  int32_T m;
  real32_T a[6];
  real32_T absxk;
  int32_T i;
  real32_T p[3];
  real32_T rll0_idx_0;
  static const int8_T b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, -1 };

  *flag_ejecao = 0;
  *modulo_erro = 0.0F;
  if (flag_caiu != 0) {
    rll0_idx_0 = lla_targ[0] * 3.14159274F / 180.0F;
    Rn = std::sin(rll0_idx_0);
    Rn = 6.378137E+6F / std::sqrt(1.0F - 0.00669437973F * Rn * Rn);
    absxk = (lla[0] - lla_targ[0]) * 3.14159274F / 180.0F / rt_atan2f_snf(1.0F,
      0.993305624F / (1.0F - 0.00669437973F * std::sin(rll0_idx_0) * std::sin
                      (rll0_idx_0)) * Rn);
    Rn = (lla[1] - lla_targ[1]) * 3.14159274F / 180.0F / rt_atan2f_snf(1.0F, Rn *
      std::cos(rll0_idx_0));
    for (i = 0; i < 3; i++) {
      p[i] = static_cast<real32_T>(b[3 * i + 2]) * lla[2] +
        (static_cast<real32_T>(b[3 * i + 1]) * Rn + static_cast<real32_T>(b[3 *
          i]) * absxk);
    }

    Rn = 1.29246971E-26F;
    absxk = std::abs(p[0]);
    if (absxk > 1.29246971E-26F) {
      *modulo_erro = 1.0F;
      Rn = absxk;
    } else {
      rll0_idx_0 = absxk / 1.29246971E-26F;
      *modulo_erro = rll0_idx_0 * rll0_idx_0;
    }

    absxk = std::abs(p[1]);
    if (absxk > Rn) {
      rll0_idx_0 = Rn / absxk;
      *modulo_erro = *modulo_erro * rll0_idx_0 * rll0_idx_0 + 1.0F;
      Rn = absxk;
    } else {
      rll0_idx_0 = absxk / Rn;
      *modulo_erro += rll0_idx_0 * rll0_idx_0;
    }

    *modulo_erro = Rn * std::sqrt(*modulo_erro);
    mod_foggui_DW.lista_circular[0] = *modulo_erro;
    for (i = 0; i < 6; i++) {
      a[i] = mod_foggui_DW.lista_circular[i];
    }

    for (i = 0; i < 5; i++) {
      a[i] = a[i + 1];
    }

    a[5] = mod_foggui_DW.lista_circular[0];
    for (i = 0; i < 6; i++) {
      mod_foggui_DW.lista_circular[i] = a[i];
    }

    i = 1;
    iyLead = 0;
    Rn = mod_foggui_DW.lista_circular[0];
    for (m = 0; m < 5; m++) {
      absxk = Rn;
      Rn = mod_foggui_DW.lista_circular[i];
      b_y1[iyLead] = mod_foggui_DW.lista_circular[i] - absxk;
      i++;
      iyLead++;
    }

    for (i = 0; i < 5; i++) {
      crescente_[i] = (b_y1[i] > 0.0F);
    }

    if ((((crescente_[0] + crescente_[1]) + crescente_[2]) + crescente_[3]) +
        crescente_[4] >= 4) {
      *flag_ejecao = 1;
      mod_foggui_DW.mantem_ejecao = true;
    }
  } else {
    *flag_ejecao = -1;
  }

  if (mod_foggui_DW.mantem_ejecao) {
    *flag_ejecao = 1;
  }
}

void mod_fogguiModelClass::step()
{
  real32_T rtb_DataTypeConversion[3];
  real32_T rtb_DataTypeConversion17[3];
  real32_T rtb_DataTypeConversion18[3];
  real32_T rtb_RateTransition14;
  real_T ACEL[3];
  real_T Keep;
  real_T P_[13];
  boolean_T x[48];
  real_T Az;
  real_T b_Az;
  int32_T stride;
  int32_T pageroot;
  real32_T buffer;
  real32_T phi;
  real32_T theta[3];
  real32_T flat[3];
  real32_T flat_targ[3];
  real32_T Ry;
  real32_T R;
  real32_T duracao;
  real32_T sigma_lat_;
  real32_T sigma1_;
  real32_T ganhos[16];
  real32_T G[8];
  char_T op_b_data[16];
  real32_T rll0[2];
  real32_T Rn;
  int32_T nd2;
  char_T tmp;
  boolean_T p;
  static const real32_T c[16] = { 0.977F, 0.386F, 2.422F, 2.95F, 3.0F, 2.5F,
    -60.0F, 1500.0F, 5.3F, 0.5F, 1.5F, 20.0F, 7.0F, 0.75F, 2.0F, 500.0F };

  real32_T LLA0[2];
  real32_T P[3];
  real32_T v[10];
  static const real32_T d[41] = { 0.561795F, 0.561795F, 0.561795F, 0.561795F,
    0.561795F, 0.561795F, 0.561795F, 0.561795F, 0.57058394F, 0.69071424F,
    0.77385F, 0.81405F, 0.806962311F, 0.795001209F, 0.776544F, 0.756333828F,
    0.735814393F, 0.717975795F, 0.695909619F, 0.674771488F, 0.655076861F,
    0.635794759F, 0.620121598F, 0.605067074F, 0.589187682F, 0.574030042F,
    0.556046426F, 0.54165256F, 0.527835429F, 0.515049458F, 0.502985239F,
    0.491642773F, 0.479475439F, 0.467617452F, 0.455965698F, 0.442148536F,
    0.430599898F, 0.418948114F, 0.407502562F, 0.395953923F, 0.384611487F };

  real_T rtb_canardON;
  real_T rtb_flagEjecao;
  real_T rtb_DataTypeConversion7;
  real_T rtb_DataTypeConversion8;
  real_T rtb_DataTypeConversion9;
  real_T rtb_DataTypeConversion10;
  real_T rtb_DataTypeConversion13[2];
  real_T rtb_DiscreteTransferFcn1;
  real_T rtb_UnitDelay;
  s8zZSU4DcwnDyW5HgyKzKEG_mod_foggui_T expl_temp;
  int32_T i;
  real32_T flat_targ_0[3];
  real_T tmp_0[9];
  real_T tmp_1[3];
  char_T op_b_data_0[16];
  real_T rtb_Saturation_idx_0;
  int8_T ii_data_idx_0;
  uint16_T tmp_2;
  int16_T tmp_3;
  real32_T rll0_tmp;
  static const int8_T f[9] = { 1, 0, 0, 0, 1, 0, 0, 0, -1 };

  boolean_T guard1 = false;
  boolean_T exitg1;
  int32_T exitg2;
  rtb_DiscreteTransferFcn1 = mod_foggui_P.DiscreteTransferFcn1_NumCoef *
    mod_foggui_DW.DiscreteTransferFcn1_states;
  Keep = mod_foggui_P.DiscreteTransferFcn3_NumCoef *
    mod_foggui_DW.DiscreteTransferFcn3_states;
  if (rtb_DiscreteTransferFcn1 > mod_foggui_P.Saturation_UpperSat) {
    rtb_Saturation_idx_0 = mod_foggui_P.Saturation_UpperSat;
  } else if (rtb_DiscreteTransferFcn1 < mod_foggui_P.Saturation_LowerSat) {
    rtb_Saturation_idx_0 = mod_foggui_P.Saturation_LowerSat;
  } else {
    rtb_Saturation_idx_0 = rtb_DiscreteTransferFcn1;
  }

  if (Keep > mod_foggui_P.Saturation_UpperSat) {
    Keep = mod_foggui_P.Saturation_UpperSat;
  } else {
    if (Keep < mod_foggui_P.Saturation_LowerSat) {
      Keep = mod_foggui_P.Saturation_LowerSat;
    }
  }

  Az = rtb_Saturation_idx_0 - mod_foggui_DW.PrevY[0];
  if (Az > mod_foggui_P.RateLimiter_RisingLim) {
    mod_foggui_Y.canard_y[0] = mod_foggui_DW.PrevY[0] +
      mod_foggui_P.RateLimiter_RisingLim;
  } else if (Az < mod_foggui_P.RateLimiter_FallingLim) {
    mod_foggui_Y.canard_y[0] = mod_foggui_DW.PrevY[0] +
      mod_foggui_P.RateLimiter_FallingLim;
  } else {
    mod_foggui_Y.canard_y[0] = rtb_Saturation_idx_0;
  }

  mod_foggui_DW.PrevY[0] = mod_foggui_Y.canard_y[0];
  Az = Keep - mod_foggui_DW.PrevY[1];
  if (Az > mod_foggui_P.RateLimiter_RisingLim) {
    mod_foggui_Y.canard_y[1] = mod_foggui_DW.PrevY[1] +
      mod_foggui_P.RateLimiter_RisingLim;
  } else if (Az < mod_foggui_P.RateLimiter_FallingLim) {
    mod_foggui_Y.canard_y[1] = mod_foggui_DW.PrevY[1] +
      mod_foggui_P.RateLimiter_FallingLim;
  } else {
    mod_foggui_Y.canard_y[1] = Keep;
  }

  mod_foggui_DW.PrevY[1] = mod_foggui_Y.canard_y[1];
  mod_foggui_Y.fim = false;
  if (!mod_foggui_DW.o_not_empty) {
    mod_foggui_Traj_Inicializa_traj(&mod_foggui_DW.o,
      mod_foggui_P.state.config.lancamento.Elev,
      mod_foggui_P.state.config.lancamento.Rlat,
      mod_foggui_P.state.config.lancamento.Rlong,
      mod_foggui_P.state.config.lancamento.Ralt,
      -mod_foggui_P.state.config.lancamento.Azi,
      mod_foggui_P.state.config.lancamento.Talt,
      mod_foggui_P.state.config.lancamento.Tesp,
      mod_foggui_P.state.config.lancamento.Hsub,
      mod_foggui_P.state.config.lancamento.Hmet,
      mod_foggui_P.state.config.lancamento.Rtemp,
      mod_foggui_P.state.config.lancamento.Rde,
      mod_foggui_P.state.config.lancamento.Dbal,
      mod_foggui_P.state.config.lancamento.Tbal,
      mod_foggui_P.state.config.lancamento.Pbal,
      mod_foggui_P.state.config.lancamento.Phi0,
      &mod_foggui_P.state.config.inercia, &mod_foggui_P.state.config.propelente,
      &mod_foggui_P.state.config.geometria,
      &mod_foggui_P.state.config.dados_part,
      &mod_foggui_P.state.config.dados_empuxo,
      &mod_foggui_P.state.config.dados_vento, mod_foggui_P.state.config.tabaer,
      &mod_foggui_P.state.config.coef_canard,
      mod_foggui_P.state.config.controle_z);
    mod_foggui_DW.o_not_empty = true;
    mod_foggui_Traj_Iniciar(&mod_foggui_DW.o);
    mod_foggui_Traj_Lbh(&mod_foggui_DW.o);
    mod_foggui_DW.o.Z = mod_foggui_DW.o.modelo.lancamento.Ralt +
      mod_foggui_DW.o.Dalt;
  }

  mod_foggui_Y.log_anmk3tusmu[0] = mod_foggui_DW.o.Pd;
  mod_foggui_Y.log_anmk3tusmu[1] = mod_foggui_DW.o.Arpd;
  mod_foggui_Y.log_anmk3tusmu[2] = mod_foggui_DW.o.Xcm;
  mod_foggui_Y.log_anmk3tusmu[3] = mod_foggui_DW.o.Sm;
  mod_foggui_Y.log_anmk3tusmu[4] = mod_foggui_DW.o.Mach;
  mod_foggui_Y.log_anmk3tusmu[5] = mod_foggui_DW.o.Alfab * 180.0 /
    3.1415926535897931;
  mod_foggui_Y.log_anmk3tusmu[6] = mod_foggui_DW.o.CanardAng1;
  mod_foggui_Y.log_anmk3tusmu[7] = mod_foggui_DW.o.CanardAng2;
  mod_foggui_Y.log_anmk3tusmu[8] = mod_foggui_DW.o.CanardAng3;
  mod_foggui_Y.log_anmk3tusmu[9] = mod_foggui_DW.o.CanardAng4;
  mod_foggui_Y.log_anmk3tusmu[10] = mod_foggui_DW.o.Cfx_c;
  mod_foggui_Y.log_anmk3tusmu[11] = mod_foggui_DW.o.Cfy_c;
  mod_foggui_Y.log_anmk3tusmu[12] = mod_foggui_DW.o.Cfz_c;
  mod_foggui_Y.log_anmk3tusmu[13] = mod_foggui_DW.o.Cmx_c;
  mod_foggui_Y.log_anmk3tusmu[14] = mod_foggui_DW.o.Cmz_c;
  mod_foggui_Y.log_anmk3tusmu[15] = mod_foggui_DW.o.Cmy_c;
  mod_foggui_Y.log_anmk3tusmu[16] = mod_foggui_DW.o.k_canard;
  mod_foggui_Y.log_anmk3tusmu[17] = mod_foggui_DW.o.cfx_b;
  mod_foggui_Y.log_anmk3tusmu[18] = mod_foggui_DW.o.cfy_b;
  mod_foggui_Y.log_anmk3tusmu[19] = mod_foggui_DW.o.cfz_b;
  mod_foggui_Y.log_anmk3tusmu[20] = mod_foggui_DW.o.cmx_b;
  mod_foggui_Y.log_anmk3tusmu[21] = mod_foggui_DW.o.cmz_b;
  mod_foggui_Y.log_anmk3tusmu[22] = mod_foggui_DW.o.cmy_b;
  mod_foggui_Y.log_anmk3tusmu[23] = mod_foggui_DW.o.cfx_e;
  mod_foggui_Y.log_anmk3tusmu[24] = mod_foggui_DW.o.cfy_e;
  mod_foggui_Y.log_anmk3tusmu[25] = mod_foggui_DW.o.cfz_e;
  mod_foggui_Y.log_anmk3tusmu[26] = mod_foggui_DW.o.cmx_e;
  mod_foggui_Y.log_anmk3tusmu[27] = mod_foggui_DW.o.cmz_e;
  mod_foggui_Y.log_anmk3tusmu[28] = mod_foggui_DW.o.cmy_e;
  mod_foggui_Y.fm[0] = mod_foggui_DW.o.Fax;
  mod_foggui_Y.fm[1] = mod_foggui_DW.o.Fay;
  mod_foggui_Y.fm[2] = mod_foggui_DW.o.Faz;
  mod_foggui_Y.fm[3] = mod_foggui_DW.o.Max;
  mod_foggui_Y.fm[4] = mod_foggui_DW.o.May;
  mod_foggui_Y.fm[5] = mod_foggui_DW.o.Maz;
  mod_foggui_Y.fm[6] = mod_foggui_DW.o.Cfx;
  if (mod_foggui_U.tiro == 0) {
    mod_foggui_Traj_Inicializa_traj(&mod_foggui_DW.o,
      mod_foggui_P.state.config.lancamento.Elev,
      mod_foggui_P.state.config.lancamento.Rlat,
      mod_foggui_P.state.config.lancamento.Rlong,
      mod_foggui_P.state.config.lancamento.Ralt,
      -mod_foggui_P.state.config.lancamento.Azi,
      mod_foggui_P.state.config.lancamento.Talt,
      mod_foggui_P.state.config.lancamento.Tesp,
      mod_foggui_P.state.config.lancamento.Hsub,
      mod_foggui_P.state.config.lancamento.Hmet,
      mod_foggui_P.state.config.lancamento.Rtemp,
      mod_foggui_P.state.config.lancamento.Rde,
      mod_foggui_P.state.config.lancamento.Dbal,
      mod_foggui_P.state.config.lancamento.Tbal,
      mod_foggui_P.state.config.lancamento.Pbal,
      mod_foggui_P.state.config.lancamento.Phi0,
      &mod_foggui_P.state.config.inercia, &mod_foggui_P.state.config.propelente,
      &mod_foggui_P.state.config.geometria,
      &mod_foggui_P.state.config.dados_part,
      &mod_foggui_P.state.config.dados_empuxo,
      &mod_foggui_P.state.config.dados_vento, mod_foggui_P.state.config.tabaer,
      &mod_foggui_P.state.config.coef_canard,
      mod_foggui_P.state.config.controle_z);
    mod_foggui_Traj_Iniciar(&mod_foggui_DW.o);
    mod_foggui_Traj_Lbh(&mod_foggui_DW.o);
    mod_foggui_DW.o.Z = mod_foggui_DW.o.modelo.lancamento.Ralt +
      mod_foggui_DW.o.Dalt;
    mod_foggui_Y.tempo = 0.0;
    mod_foggui_Y.vel[0] = mod_foggui_DW.o.Vxh;
    mod_foggui_Y.vel[1] = -mod_foggui_DW.o.Vyh;
    mod_foggui_Y.vel[2] = -mod_foggui_DW.o.Vzh;
    mod_foggui_Y.uvw[0] = mod_foggui_DW.o.Vx;
    mod_foggui_Y.uvw[1] = -mod_foggui_DW.o.Vy;
    mod_foggui_Y.uvw[2] = -mod_foggui_DW.o.Vz;
    mod_foggui_Y.ang[0] = mod_foggui_DW.o.Phi;
    mod_foggui_Y.ang[1] = -mod_foggui_DW.o.Teta;
    mod_foggui_Y.ang[2] = -mod_foggui_DW.o.Psi;
    mod_foggui_Y.pqr[0] = mod_foggui_DW.o.Wx;
    mod_foggui_Y.pqr[1] = -mod_foggui_DW.o.Wy;
    mod_foggui_Y.pqr[2] = -mod_foggui_DW.o.Wz;
    mod_foggui_Y.pos[0] = mod_foggui_DW.o.Rxr;
    mod_foggui_Y.pos[1] = -mod_foggui_DW.o.Ryr;
    mod_foggui_Y.pos[2] = -mod_foggui_DW.o.Z;
    mod_foggui_Y.latlong[0] = mod_foggui_DW.o.Dlat +
      mod_foggui_DW.o.modelo.lancamento.Rlat;
    mod_foggui_Y.latlong[1] = mod_foggui_DW.o.Dlong
      + mod_foggui_DW.o.modelo.lancamento.Rlong;
    tmp_0[0] = mod_foggui_DW.o.L11;
    tmp_0[3] = -mod_foggui_DW.o.L12;
    tmp_0[6] = -mod_foggui_DW.o.L13;
    tmp_0[1] = -mod_foggui_DW.o.L21;
    tmp_0[4] = mod_foggui_DW.o.L22;
    tmp_0[7] = mod_foggui_DW.o.L23;
    tmp_0[2] = -mod_foggui_DW.o.L31;
    tmp_0[5] = mod_foggui_DW.o.L32;
    tmp_0[8] = mod_foggui_DW.o.L33;
    tmp_1[0] = mod_foggui_DW.o.Vx_p;
    tmp_1[1] = -mod_foggui_DW.o.Vy_p;
    tmp_1[2] = -mod_foggui_DW.o.Vz_p;
    for (stride = 0; stride < 3; stride++) {
      ACEL[stride] = tmp_1[stride] + (tmp_0[stride + 6] * -mod_foggui_DW.o.Gb +
        (tmp_0[stride + 3] * 0.0 + tmp_0[stride] * 0.0));
    }
  } else {
    if (mod_foggui_DW.UnitDelay_DSTATE_gupgjp1fb1 != 0) {
      mod_foggui_DW.o.CanardON = mod_foggui_DW.UnitDelay_DSTATE_gupgjp1fb1;
      mod_foggui_DW.o.CanardAng1 = mod_foggui_Y.canard_y[0];
      mod_foggui_DW.o.CanardAng2 = -mod_foggui_Y.canard_y[1];
      mod_foggui_DW.o.CanardAng3 = mod_foggui_Y.canard_y[0];
      mod_foggui_DW.o.CanardAng4 = -mod_foggui_Y.canard_y[1];
      mod_foggui_DW.o.k_canard = mod_foggui_P.state.config.k_canard;
    }

    if ((mod_foggui_DW.UnitDelay2_DSTATE == 1) ||
        (mod_foggui_DW.UnitDelay2_DSTATE == 2)) {
      mod_foggui_DW.o.Fesp = 1.0;
    }

    if (mod_foggui_DW.flagLoopFases1) {
      mod_foggui_DW.flagLoopFases1 = false;
      Keep = mod_foggui_DW.o.M;
      while ((mod_foggui_DW.o.M != 0.0) && (mod_foggui_DW.o.F <=
              mod_foggui_DW.o.Fase_fim) && (mod_foggui_DW.o.T + 1.0E-6 <
              mod_foggui_DW.o.Tfim)) {
        mod_foggui_Traj_Iniciar(&mod_foggui_DW.o);
        mod_foggui_Traj_Fase(&mod_foggui_DW.o);
        mod_foggui_DW.o.F += mod_foggui_DW.o.M;
      }

      if (Keep != 0.0) {
        mod_foggui_Traj_Padrao(&mod_foggui_DW.o);
      }

      if (mod_foggui_DW.o.T + 1.0E-6 >= mod_foggui_DW.o.U) {
        mod_foggui_DW.o.U = mod_foggui_DW.o.Tfim;
      }

      mod_foggui_Y.fim = ((mod_foggui_DW.o.F > mod_foggui_DW.o.Fase_fim) ||
                          (mod_foggui_DW.o.T + 1.0E-6 >= mod_foggui_DW.o.Tfim));
    }

    mod_foggui_DW.o.Pf = 0.0;
    mod_foggui_DW.o.Fpf = !(mod_foggui_DW.o.Fesp != 0.0);
    mod_foggui_DW.o.Fdist = 1.0;
    mod_foggui_DW.o.Fang = 1.0;
    mod_foggui_DW.o.Fder = 1.0;
    mod_foggui_DW.o.Fcoef = ((!(mod_foggui_DW.o.Pit0 != 0.0)) &&
      mod_foggui_DW.o.Fpf);
    mod_foggui_DW.o.Fataq = ((mod_foggui_DW.o.Pit0 != 0.0) &&
      mod_foggui_DW.o.Fpf);
    for (i = 0; i < 48; i++) {
      x[i] = (mod_foggui_DW.o.Z - (mod_foggui_DW.o.modelo.ventos.altitudes[i] +
               mod_foggui_DW.o.Htabv) < 0.0);
    }

    i = 0;
    nd2 = 0;
    exitg1 = false;
    while ((!exitg1) && (nd2 < 48)) {
      if (x[nd2]) {
        i = 1;
        ii_data_idx_0 = static_cast<int8_T>((nd2 + 1));
        exitg1 = true;
      } else {
        nd2++;
      }
    }

    if (i == 0) {
      ii_data_idx_0 = 48;
    }

    mod_foggui_DW.o.Kw = (static_cast<real_T>(ii_data_idx_0) - 1.0) - 1.0;
    if ((mod_foggui_DW.o.Kw < 0.0) || rtIsNaN(mod_foggui_DW.o.Kw)) {
      mod_foggui_DW.o.Kw = 0.0;
    }

    mod_foggui_DW.o.Kh += mod_foggui_DW.o.Dkh;
    mod_foggui_Traj_Deriv(&mod_foggui_DW.o);
    if ((mod_foggui_DW.o.Pit0 != 0.0) && mod_foggui_DW.o.Fpf) {
      mod_foggui_Traj_Cpf(&mod_foggui_DW.o);
    }

    mod_foggui_Traj_Degree(&mod_foggui_DW.o);
    mod_foggui_DW.o.F = std::abs(mod_foggui_DW.o.F);
    mod_foggui_Y.vel[0] = mod_foggui_DW.o.Vxh;
    mod_foggui_Y.vel[1] = -mod_foggui_DW.o.Vyh;
    mod_foggui_Y.vel[2] = -mod_foggui_DW.o.Vzh;
    mod_foggui_Y.uvw[0] = mod_foggui_DW.o.Vx;
    mod_foggui_Y.uvw[1] = -mod_foggui_DW.o.Vy;
    mod_foggui_Y.uvw[2] = -mod_foggui_DW.o.Vz;
    mod_foggui_Y.ang[0] = mod_foggui_DW.o.Phi;
    mod_foggui_Y.ang[1] = -mod_foggui_DW.o.Teta;
    mod_foggui_Y.ang[2] = -mod_foggui_DW.o.Psi;
    mod_foggui_Y.pqr[0] = mod_foggui_DW.o.Wx;
    mod_foggui_Y.pqr[1] = -mod_foggui_DW.o.Wy;
    mod_foggui_Y.pqr[2] = -mod_foggui_DW.o.Wz;
    mod_foggui_Y.pos[0] = mod_foggui_DW.o.Rxr;
    mod_foggui_Y.pos[1] = -mod_foggui_DW.o.Ryr;
    mod_foggui_Y.pos[2] = -mod_foggui_DW.o.Z;
    mod_foggui_Y.latlong[0] = mod_foggui_DW.o.Dlat +
      mod_foggui_DW.o.modelo.lancamento.Rlat;
    mod_foggui_Y.latlong[1] = mod_foggui_DW.o.Dlong
      + mod_foggui_DW.o.modelo.lancamento.Rlong;
    tmp_0[0] = mod_foggui_DW.o.L11;
    tmp_0[3] = -mod_foggui_DW.o.L12;
    tmp_0[6] = -mod_foggui_DW.o.L13;
    tmp_0[1] = -mod_foggui_DW.o.L21;
    tmp_0[4] = mod_foggui_DW.o.L22;
    tmp_0[7] = mod_foggui_DW.o.L23;
    tmp_0[2] = -mod_foggui_DW.o.L31;
    tmp_0[5] = mod_foggui_DW.o.L32;
    tmp_0[8] = mod_foggui_DW.o.L33;
    tmp_1[0] = mod_foggui_DW.o.Vx_p;
    tmp_1[1] = -mod_foggui_DW.o.Vy_p;
    tmp_1[2] = -mod_foggui_DW.o.Vz_p;
    for (stride = 0; stride < 3; stride++) {
      ACEL[stride] = tmp_1[stride] + (tmp_0[stride + 6] * -mod_foggui_DW.o.Gb +
        (tmp_0[stride + 3] * 0.0 + tmp_0[stride] * 0.0));
    }

    mod_foggui_Y.tempo = mod_foggui_DW.o.Tempo;
    guard1 = false;
    if ((mod_foggui_DW.o.Q != 0.0) || (mod_foggui_DW.o.Parada != 0.0)) {
      mod_foggui_DW.flagLoopFases2 = true;
      guard1 = true;
    } else {
      mod_foggui_DW.o.Alfap = 0.0;
      if ((mod_foggui_DW.o.Vax != 0.0) && (mod_foggui_DW.o.Pit0 != 0.0)) {
        Keep = std::sqrt(mod_foggui_DW.o.Vxh * mod_foggui_DW.o.Vxh +
                         mod_foggui_DW.o.Vyh * mod_foggui_DW.o.Vyh) *
          mod_foggui_DW.o.Rwz;
        rtb_Saturation_idx_0 = (((mod_foggui_DW.o.Vy_p - (mod_foggui_DW.o.L21 *
          mod_foggui_DW.o.Rwx + mod_foggui_DW.o.L22 * mod_foggui_DW.o.Rwy) *
          mod_foggui_DW.o.Vzh) - mod_foggui_DW.o.L23 * Keep) -
          mod_foggui_DW.o.Wbhx * mod_foggui_DW.o.Vwzb) + mod_foggui_DW.o.Wbhz *
          mod_foggui_DW.o.Vwxb;
        Az = (((mod_foggui_DW.o.Vz_p - (mod_foggui_DW.o.L31 *
                 mod_foggui_DW.o.Rwx + mod_foggui_DW.o.L32 * mod_foggui_DW.o.Rwy)
                * mod_foggui_DW.o.Vzh) - mod_foggui_DW.o.L33 * Keep) -
              mod_foggui_DW.o.Wbhy * mod_foggui_DW.o.Vwxb) +
          mod_foggui_DW.o.Wbhx * mod_foggui_DW.o.Vwyb;
        if (mod_foggui_DW.o.Van != 0.0) {
          mod_foggui_DW.o.Alfap = ((mod_foggui_DW.o.Vay * rtb_Saturation_idx_0 +
            mod_foggui_DW.o.Vaz * Az) * mod_foggui_DW.o.Vax -
            ((((mod_foggui_DW.o.Vx_p - (mod_foggui_DW.o.L11 *
            mod_foggui_DW.o.Rwx + mod_foggui_DW.o.L12 * mod_foggui_DW.o.Rwy) *
                mod_foggui_DW.o.Vzh) - mod_foggui_DW.o.L13 * Keep) -
              mod_foggui_DW.o.Wbhz * mod_foggui_DW.o.Vwyb) +
             mod_foggui_DW.o.Wbhy * mod_foggui_DW.o.Vwzb) * mod_foggui_DW.o.Van *
            mod_foggui_DW.o.Van) / (mod_foggui_DW.o.Van * mod_foggui_DW.o.Va *
            mod_foggui_DW.o.Va);
        } else {
          mod_foggui_DW.o.Alfap = std::sqrt(rtb_Saturation_idx_0 *
            rtb_Saturation_idx_0 + Az * Az) / mod_foggui_DW.o.Vax;
        }
      }

      mod_foggui_DW.o.H = 0.00083333333333333339;
      mod_foggui_DW.o.Hkeep = mod_foggui_DW.o.H;
      if (mod_foggui_DW.o.T + 1.0E-6 > mod_foggui_DW.o.Tgrot) {
        mod_foggui_DW.o.Fgrot = 0.0;
      }

      if (mod_foggui_DW.o.T + 1.0E-6 > mod_foggui_DW.o.modelo.Tb
          [static_cast<int32_T>((mod_foggui_DW.o.Kb + 1.0)) - 1] *
          mod_foggui_DW.o.modelo.propelente.Tb0) {
        mod_foggui_DW.o.Kb++;
      }

      if (mod_foggui_DW.o.T + 1.0E-6 > mod_foggui_DW.o.modelo.Tc
          [static_cast<int32_T>((mod_foggui_DW.o.Kc + 1.0)) - 1]) {
        mod_foggui_DW.o.Kc++;
      }

      P_[0] = mod_foggui_DW.o.Dlat;
      P_[1] = mod_foggui_DW.o.Dlong;
      P_[2] = mod_foggui_DW.o.Dalt;
      P_[3] = mod_foggui_DW.o.Vx;
      P_[4] = mod_foggui_DW.o.Vy;
      P_[5] = mod_foggui_DW.o.Vz;
      P_[6] = mod_foggui_DW.o.Wx;
      P_[7] = mod_foggui_DW.o.Wy;
      P_[8] = mod_foggui_DW.o.Wz;
      P_[9] = mod_foggui_DW.o.Qt1;
      P_[10] = mod_foggui_DW.o.Qt2;
      P_[11] = mod_foggui_DW.o.Qt3;
      P_[12] = mod_foggui_DW.o.Qt4;
      mod_foggui_DW.o.Contador++;
      mod_foggui_DW.o.Fang = 0.0;
      if (std::abs(mod_foggui_DW.o.L13) < 0.9999) {
        mod_foggui_DW.o.Teta = -std::atan(mod_foggui_DW.o.L13 / std::sqrt(1.0 -
          mod_foggui_DW.o.L13 * mod_foggui_DW.o.L13));
        if (mod_foggui_DW.o.L12 < 0.0) {
          Keep = -1.0;
        } else if (mod_foggui_DW.o.L12 > 0.0) {
          Keep = 1.0;
        } else if (mod_foggui_DW.o.L12 == 0.0) {
          Keep = 0.0;
        } else {
          Keep = (rtNaN);
        }

        mod_foggui_DW.o.Psi = 1.5707963267948966 * Keep;
        if (mod_foggui_DW.o.L11 != 0.0) {
          mod_foggui_DW.o.Psi = (3.1415926535897931 - static_cast<real_T>
            ((mod_foggui_DW.o.L12 < 0.0)) * 6.2831853071795862) *
            static_cast<real_T>((mod_foggui_DW.o.L11 < 0.0)) + std::atan
            (mod_foggui_DW.o.L12 / mod_foggui_DW.o.L11);
        }

        if (mod_foggui_DW.o.L23 < 0.0) {
          Keep = -1.0;
        } else if (mod_foggui_DW.o.L23 > 0.0) {
          Keep = 1.0;
        } else if (mod_foggui_DW.o.L23 == 0.0) {
          Keep = 0.0;
        } else {
          Keep = (rtNaN);
        }

        mod_foggui_DW.o.Phi = 1.5707963267948966 * Keep;
        if (mod_foggui_DW.o.L33 != 0.0) {
          mod_foggui_DW.o.Phi = (3.1415926535897931 - static_cast<real_T>
            ((mod_foggui_DW.o.L23 < 0.0)) * 6.2831853071795862) *
            static_cast<real_T>((mod_foggui_DW.o.L33 < 0.0)) + std::atan
            (mod_foggui_DW.o.L23 / mod_foggui_DW.o.L33);
        }
      } else {
        if (mod_foggui_DW.o.L13 < 0.0) {
          Keep = -1.0;
        } else if (mod_foggui_DW.o.L13 > 0.0) {
          Keep = 1.0;
        } else if (mod_foggui_DW.o.L13 == 0.0) {
          Keep = 0.0;
        } else {
          Keep = (rtNaN);
        }

        mod_foggui_DW.o.Teta = -1.5707963267948966 * Keep;
        mod_foggui_DW.o.Phi = 0.0;
        if (mod_foggui_DW.o.L21 < 0.0) {
          Keep = -1.0;
        } else if (mod_foggui_DW.o.L21 > 0.0) {
          Keep = 1.0;
        } else if (mod_foggui_DW.o.L21 == 0.0) {
          Keep = 0.0;
        } else {
          Keep = (rtNaN);
        }

        mod_foggui_DW.o.Psi = -1.5707963267948966 * Keep;
        if (mod_foggui_DW.o.L22 != 0.0) {
          mod_foggui_DW.o.Psi = (3.1415926535897931 - static_cast<real_T>
            ((mod_foggui_DW.o.L21 > 0.0)) * 6.2831853071795862) *
            static_cast<real_T>((mod_foggui_DW.o.L22 < 0.0)) + -std::atan
            (mod_foggui_DW.o.L21 / mod_foggui_DW.o.L22);
        }
      }

      if ((mod_foggui_DW.o.Z < mod_foggui_DW.o.modelo.lancamento.Talt) &&
          (mod_foggui_DW.o.Vzh < -10.0)) {
        mod_foggui_Y.fim = true;
      } else {
        mod_foggui_Traj_Runge(&mod_foggui_DW.o, P_);
        mod_foggui_Traj_Fase(&mod_foggui_DW.o);
        mod_foggui_DW.cont++;
        if (mod_foggui_DW.o.R != 0.0) {
          Keep = mod_foggui_DW.o.M;
          do {
            exitg2 = 0;
            mod_foggui_DW.o.H /= 2.0;
            if (mod_foggui_DW.o.R != 0.0) {
              mod_foggui_DW.o.Dlat = P_[0];
              mod_foggui_DW.o.Dlong = P_[1];
              mod_foggui_DW.o.Dalt = P_[2];
              mod_foggui_DW.o.Vx = P_[3];
              mod_foggui_DW.o.Vy = P_[4];
              mod_foggui_DW.o.Vz = P_[5];
              mod_foggui_DW.o.Wx = P_[6];
              mod_foggui_DW.o.Wy = P_[7];
              mod_foggui_DW.o.Wz = P_[8];
              mod_foggui_DW.o.Qt1 = P_[9];
              mod_foggui_DW.o.Qt2 = P_[10];
              mod_foggui_DW.o.Qt3 = P_[11];
              mod_foggui_DW.o.Qt4 = P_[12];
              mod_foggui_Traj_Deriv(&mod_foggui_DW.o);
            }

            mod_foggui_Traj_Runge(&mod_foggui_DW.o, P_);
            if (mod_foggui_DW.o.H < 1.0E-5) {
              exitg2 = 1;
            } else {
              mod_foggui_Traj_Fase(&mod_foggui_DW.o);
              if ((mod_foggui_DW.o.R != 0.0) && (!(mod_foggui_DW.o.M != 0.0))) {
                Keep = 0.0;
              }

              if (mod_foggui_DW.o.R == 0.0) {
                mod_foggui_Traj_Deriv(&mod_foggui_DW.o);
                mod_foggui_DW.o.Alfap = 0.0;
                if ((mod_foggui_DW.o.Vax != 0.0) && (mod_foggui_DW.o.Pit0 != 0.0))
                {
                  rtb_Saturation_idx_0 = std::sqrt(mod_foggui_DW.o.Vxh *
                    mod_foggui_DW.o.Vxh + mod_foggui_DW.o.Vyh *
                    mod_foggui_DW.o.Vyh) * mod_foggui_DW.o.Rwz;
                  Az = (((mod_foggui_DW.o.Vy_p - (mod_foggui_DW.o.L21 *
                           mod_foggui_DW.o.Rwx + mod_foggui_DW.o.L22 *
                           mod_foggui_DW.o.Rwy) * mod_foggui_DW.o.Vzh) -
                         mod_foggui_DW.o.L23 * rtb_Saturation_idx_0) -
                        mod_foggui_DW.o.Wbhx * mod_foggui_DW.o.Vwzb) +
                    mod_foggui_DW.o.Wbhz * mod_foggui_DW.o.Vwxb;
                  b_Az = (((mod_foggui_DW.o.Vz_p - (mod_foggui_DW.o.L31 *
                             mod_foggui_DW.o.Rwx + mod_foggui_DW.o.L32 *
                             mod_foggui_DW.o.Rwy) * mod_foggui_DW.o.Vzh) -
                           mod_foggui_DW.o.L33 * rtb_Saturation_idx_0) -
                          mod_foggui_DW.o.Wbhy * mod_foggui_DW.o.Vwxb) +
                    mod_foggui_DW.o.Wbhx * mod_foggui_DW.o.Vwyb;
                  if (mod_foggui_DW.o.Van != 0.0) {
                    mod_foggui_DW.o.Alfap = ((mod_foggui_DW.o.Vay * Az +
                      mod_foggui_DW.o.Vaz * b_Az) * mod_foggui_DW.o.Vax -
                      ((((mod_foggui_DW.o.Vx_p - (mod_foggui_DW.o.L11 *
                      mod_foggui_DW.o.Rwx + mod_foggui_DW.o.L12 *
                      mod_foggui_DW.o.Rwy) * mod_foggui_DW.o.Vzh) -
                         mod_foggui_DW.o.L13 * rtb_Saturation_idx_0) -
                        mod_foggui_DW.o.Wbhz * mod_foggui_DW.o.Vwyb) +
                       mod_foggui_DW.o.Wbhy * mod_foggui_DW.o.Vwzb) *
                      mod_foggui_DW.o.Van * mod_foggui_DW.o.Van) /
                      (mod_foggui_DW.o.Van * mod_foggui_DW.o.Va *
                       mod_foggui_DW.o.Va);
                  } else {
                    mod_foggui_DW.o.Alfap = std::sqrt(Az * Az + b_Az * b_Az) /
                      mod_foggui_DW.o.Vax;
                  }
                }

                mod_foggui_DW.o.T += mod_foggui_DW.o.H;
              }
            }
          } while (exitg2 == 0);

          mod_foggui_DW.o.R = 1.0;
          mod_foggui_DW.o.Q = 1.0;
          mod_foggui_DW.o.M = Keep;
        }

        mod_foggui_DW.o.T += mod_foggui_DW.o.H;
        if ((mod_foggui_DW.o.U > mod_foggui_DW.o.Tfim) || (rtIsNaN
             (mod_foggui_DW.o.U) && (!rtIsNaN(mod_foggui_DW.o.Tfim)))) {
          mod_foggui_DW.o.U = mod_foggui_DW.o.Tfim;
        }

        mod_foggui_DW.o.Parada = static_cast<real_T>((mod_foggui_DW.o.T + 1.0E-6
          >= mod_foggui_DW.o.U)) * 2.0;
        guard1 = true;
      }
    }

    if (guard1) {
      if (mod_foggui_DW.flagLoopFases2) {
        mod_foggui_DW.flagLoopFases1 = true;
        mod_foggui_DW.flagLoopFases2 = false;
        mod_foggui_Traj_Flag(&mod_foggui_DW.o);
        mod_foggui_DW.o.List = mod_foggui_DW.o.T;
      }
    }
  }

  if ((&mod_foggui_M)->Timing.TaskCounters.TID[1] == 0) {
    mod_foggui_DW.RateTransition29_Buffer = static_cast<real32_T>
      (mod_foggui_Y.tempo);
    mod_foggui_B.RateTransition29 = mod_foggui_DW.RateTransition29_Buffer;
  }

  mod_foggui_B.RateTransition[0] = mod_foggui_Y.ang[0];
  mod_foggui_B.RateTransition[1] = mod_foggui_Y.ang[1];
  mod_foggui_B.RateTransition[2] = mod_foggui_Y.ang[2];
  mod_foggui_B.RateTransition1 = mod_foggui_Y.pqr[0];
  mod_foggui_B.RateTransition2 = mod_foggui_Y.pqr[1];
  mod_foggui_B.RateTransition3 = mod_foggui_Y.pqr[2];
  mod_foggui_B.RateTransition4 = ACEL[0];
  mod_foggui_B.RateTransition16 = ACEL[1];
  mod_foggui_B.RateTransition17 = ACEL[2];
  if (mod_foggui_DW.i3 == 10.0) {
    mod_foggui_DW.m3[0] = mod_foggui_B.RateTransition[0];
    mod_foggui_DW.m3[3] = mod_foggui_B.RateTransition[1];
    mod_foggui_DW.m3[6] = mod_foggui_B.RateTransition[2];
    for (i = 0; i < 3; i++) {
      pageroot = i * 3;
      Keep = mod_foggui_DW.m3[pageroot];
      for (stride = 0; stride < 2; stride++) {
        nd2 = pageroot + stride;
        mod_foggui_DW.m3[nd2] = mod_foggui_DW.m3[nd2 + 1];
      }

      mod_foggui_DW.m3[pageroot + 2] = Keep;
    }

    mod_foggui_DW.i3 = 0.0;
  }

  mod_foggui_DW.i3++;
  if (mod_foggui_DW.i6 == 4.0) {
    mod_foggui_DW.m6[0] = mod_foggui_B.RateTransition1;
    mod_foggui_DW.m6[6] = mod_foggui_B.RateTransition2;
    mod_foggui_DW.m6[12] = mod_foggui_B.RateTransition3;
    mod_foggui_DW.m6[18] = mod_foggui_B.RateTransition4;
    mod_foggui_DW.m6[24] = mod_foggui_B.RateTransition16;
    mod_foggui_DW.m6[30] = mod_foggui_B.RateTransition17;
    for (i = 0; i < 6; i++) {
      stride = i * 6;
      Keep = mod_foggui_DW.m6[stride];
      for (pageroot = 0; pageroot < 5; pageroot++) {
        nd2 = stride + pageroot;
        mod_foggui_DW.m6[nd2] = mod_foggui_DW.m6[nd2 + 1];
      }

      mod_foggui_DW.m6[stride + 5] = Keep;
    }

    mod_foggui_DW.i6 = 0.0;
  }

  mod_foggui_DW.i6++;
  mod_foggui_B.DataTypeConversion8 = static_cast<real32_T>
    (mod_foggui_P.state.controle.t_canard);
  if ((&mod_foggui_M)->Timing.TaskCounters.TID[1] == 0) {
    mod_foggui_DW.RateTransition5_Buffer[0] = mod_foggui_DW.m3[0];
    mod_foggui_DW.RateTransition5_Buffer[1] = mod_foggui_DW.m3[1];
    mod_foggui_DW.RateTransition5_Buffer[2] = mod_foggui_DW.m3[2];
    rtb_DataTypeConversion[0] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition5_Buffer[0]);
    rtb_DataTypeConversion[1] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition5_Buffer[1]);
    rtb_DataTypeConversion[2] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition5_Buffer[2]);
    for (i = 0; i < 6; i++) {
      mod_foggui_DW.RateTransition18_Buffer[i] = mod_foggui_DW.m6[i];
      mod_foggui_B.DataTypeConversion1[i] = static_cast<real32_T>
        (mod_foggui_DW.RateTransition18_Buffer[i]);
      mod_foggui_DW.RateTransition20_Buffer[i] = mod_foggui_DW.m6[i + 24];
    }

    for (i = 0; i < 6; i++) {
      mod_foggui_B.DataTypeConversion13[i] = static_cast<real32_T>
        (mod_foggui_DW.RateTransition20_Buffer[i]);
    }

    for (stride = 0; stride < 6; stride++) {
      mod_foggui_DW.RateTransition21_Buffer[stride] = mod_foggui_DW.m6[stride +
        30];
    }

    for (i = 0; i < 6; i++) {
      mod_foggui_B.DataTypeConversion14[i] = static_cast<real32_T>
        (mod_foggui_DW.RateTransition21_Buffer[i]);
    }

    for (i = 0; i < 6; i++) {
      mod_foggui_DW.RateTransition6_Buffer[i] = mod_foggui_DW.m6[i + 6];
      mod_foggui_B.DataTypeConversion15[i] = static_cast<real32_T>
        (mod_foggui_DW.RateTransition6_Buffer[i]);
      mod_foggui_DW.RateTransition7_Buffer[i] = mod_foggui_DW.m6[i + 12];
      mod_foggui_B.DataTypeConversion16[i] = static_cast<real32_T>
        (mod_foggui_DW.RateTransition7_Buffer[i]);
    }

    mod_foggui_DW.RateTransition22_Buffer[0] = mod_foggui_DW.m3[3];
    mod_foggui_DW.RateTransition22_Buffer[1] = mod_foggui_DW.m3[4];
    mod_foggui_DW.RateTransition22_Buffer[2] = mod_foggui_DW.m3[5];
    rtb_DataTypeConversion17[0] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition22_Buffer[0]);
    rtb_DataTypeConversion17[1] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition22_Buffer[1]);
    rtb_DataTypeConversion17[2] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition22_Buffer[2]);
    mod_foggui_DW.RateTransition23_Buffer[0] = mod_foggui_DW.m3[6];
    mod_foggui_DW.RateTransition23_Buffer[1] = mod_foggui_DW.m3[7];
    mod_foggui_DW.RateTransition23_Buffer[2] = mod_foggui_DW.m3[8];
    rtb_DataTypeConversion18[0] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition23_Buffer[0]);
    rtb_DataTypeConversion18[1] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition23_Buffer[1]);
    rtb_DataTypeConversion18[2] = static_cast<real32_T>
      (mod_foggui_DW.RateTransition23_Buffer[2]);
    for (stride = 0; stride < 6; stride++) {
      mod_foggui_DW.RateTransition19_Buffer[stride] = mod_foggui_DW.m6[stride +
        18];
    }

    for (i = 0; i < 6; i++) {
      mod_foggui_B.DataTypeConversion2[i] = static_cast<real32_T>
        (mod_foggui_DW.RateTransition19_Buffer[i]);
    }
  }

  rtb_UnitDelay = mod_foggui_DW.UnitDelay_DSTATE;
  if ((&mod_foggui_M)->Timing.TaskCounters.TID[1] == 0) {
    mod_foggui_DW.RateTransition10_Buffer[0] = static_cast<real32_T>
      (mod_foggui_P.state.controle.alvo[0]);
    mod_foggui_DW.RateTransition10_Buffer[1] = static_cast<real32_T>
      (mod_foggui_P.state.controle.alvo[1]);
    mod_foggui_DW.RateTransition10_Buffer[2] = static_cast<real32_T>
      (mod_foggui_P.state.controle.alvo[2]);
    mod_foggui_DW.RateTransition12_Buffer = static_cast<real32_T>
      (mod_foggui_P.state.controle.dh_alvo);
    mod_foggui_B.RateTransition12 = mod_foggui_DW.RateTransition12_Buffer;
    mod_foggui_DW.RateTransition13_Buffer = static_cast<real32_T>
      (mod_foggui_P.state.controle.cd_subm);
    mod_foggui_B.RateTransition13_fhpnmvyjeu =
      mod_foggui_DW.RateTransition13_Buffer;
    rtb_RateTransition14 = mod_foggui_B.DataTypeConversion8;
    for (i = 0; i < 10; i++) {
      mod_foggui_DW.RateTransition15_Buffer[i] = static_cast<real32_T>
        (mod_foggui_P.state.controle.ganhos[i]);
    }

    for (i = 0; i < 10; i++) {
      mod_foggui_B.RateTransition15[i] = mod_foggui_DW.RateTransition15_Buffer[i];
    }

    mod_foggui_DW.RateTransition24_Buffer[0] = static_cast<real32_T>
      (mod_foggui_Y.ang[0]);
    mod_foggui_DW.RateTransition30_Buffer[0] = static_cast<real32_T>
      (mod_foggui_Y.vel[0]);
    mod_foggui_DW.RateTransition24_Buffer[1] = static_cast<real32_T>
      (mod_foggui_Y.ang[1]);
    mod_foggui_DW.RateTransition30_Buffer[1] = static_cast<real32_T>
      (mod_foggui_Y.vel[1]);
    mod_foggui_DW.RateTransition24_Buffer[2] = static_cast<real32_T>
      (mod_foggui_Y.ang[2]);
    mod_foggui_DW.RateTransition30_Buffer[2] = static_cast<real32_T>
      (mod_foggui_Y.vel[2]);
    mod_foggui_DW.RateTransition8_Buffer[0] = static_cast<real32_T>
      (mod_foggui_Y.latlong[0]);
    mod_foggui_DW.RateTransition8_Buffer[1] = static_cast<real32_T>
      (mod_foggui_Y.latlong[1]);
    mod_foggui_DW.RateTransition9_Buffer[0] = static_cast<real32_T>
      (mod_foggui_Y.pos[0]);
    mod_foggui_DW.RateTransition9_Buffer[1] = static_cast<real32_T>
      (mod_foggui_Y.pos[1]);
    mod_foggui_DW.RateTransition9_Buffer[2] = static_cast<real32_T>
      (mod_foggui_Y.pos[2]);
    for (i = 0; i < 9; i++) {
      pageroot = i * 3;
      buffer = mod_foggui_DW.buffer[pageroot];
      for (stride = 0; stride < 2; stride++) {
        nd2 = pageroot + stride;
        mod_foggui_DW.buffer[nd2] = mod_foggui_DW.buffer[nd2 + 1];
      }

      mod_foggui_DW.buffer[pageroot + 2] = buffer;
    }

    mod_foggui_DW.buffer[2] = mod_foggui_DW.RateTransition24_Buffer[0];
    mod_foggui_DW.buffer[5] = mod_foggui_DW.RateTransition24_Buffer[1];
    mod_foggui_DW.buffer[8] = mod_foggui_DW.RateTransition24_Buffer[2];
    mod_foggui_DW.buffer[11] = mod_foggui_DW.RateTransition30_Buffer[1];
    mod_foggui_DW.buffer[14] = mod_foggui_DW.RateTransition30_Buffer[0];
    mod_foggui_DW.buffer[17] = mod_foggui_DW.RateTransition30_Buffer[2];
    mod_foggui_DW.buffer[20] = mod_foggui_DW.RateTransition8_Buffer[0];
    mod_foggui_DW.buffer[23] = mod_foggui_DW.RateTransition8_Buffer[1];
    mod_foggui_DW.buffer[26] = -mod_foggui_DW.RateTransition9_Buffer[2];
    mod_foggui_B.Bank[0] = mod_foggui_DW.buffer[0];
    mod_foggui_B.Elevation[0] = mod_foggui_DW.buffer[3];
    mod_foggui_B.Bank[1] = mod_foggui_DW.buffer[1];
    mod_foggui_B.Elevation[1] = mod_foggui_DW.buffer[4];
    mod_foggui_B.Bank[2] = mod_foggui_DW.buffer[2];
    mod_foggui_B.Elevation[2] = mod_foggui_DW.buffer[5];
    mod_foggui_B.Ve[0] = mod_foggui_DW.buffer[9];
    mod_foggui_B.Ve[1] = mod_foggui_DW.buffer[10];
    mod_foggui_B.Ve[2] = mod_foggui_DW.buffer[11];
    mod_foggui_B.Vn[0] = mod_foggui_DW.buffer[12];
    mod_foggui_B.Vn[1] = mod_foggui_DW.buffer[13];
    mod_foggui_B.Vn[2] = mod_foggui_DW.buffer[14];
    mod_foggui_B.Vd[0] = mod_foggui_DW.buffer[15];
    mod_foggui_B.Vd[1] = mod_foggui_DW.buffer[16];
    mod_foggui_B.Vd[2] = mod_foggui_DW.buffer[17];
    mod_foggui_B.Lat[0] = mod_foggui_DW.buffer[18];
    mod_foggui_B.Lon[0] = mod_foggui_DW.buffer[21];
    mod_foggui_B.Lat[1] = mod_foggui_DW.buffer[19];
    mod_foggui_B.Lon[1] = mod_foggui_DW.buffer[22];
    mod_foggui_B.Lat[2] = mod_foggui_DW.buffer[20];
    mod_foggui_B.Lon[2] = mod_foggui_DW.buffer[23];
    mod_foggui_B.Alt[0] = mod_foggui_DW.buffer[24];
    mod_foggui_B.Alt[1] = mod_foggui_DW.buffer[25];
    mod_foggui_B.Alt[2] = mod_foggui_DW.buffer[26];
    mod_foggui_B.lat_targ = mod_foggui_DW.RateTransition10_Buffer[0];
    mod_foggui_B.lon_targ = mod_foggui_DW.RateTransition10_Buffer[1];
    mod_foggui_B.alt_targ = mod_foggui_DW.RateTransition10_Buffer[2];
    mod_foggui_DW.RateTransition25_Buffer = static_cast<real32_T>
      (mod_foggui_P.state.config.lancamento.Rlong);
    mod_foggui_B.RateTransition25 = mod_foggui_DW.RateTransition25_Buffer;
    mod_foggui_DW.RateTransition26_Buffer = static_cast<real32_T>
      (mod_foggui_P.state.config.lancamento.Rlat);
    mod_foggui_B.RateTransition26 = mod_foggui_DW.RateTransition26_Buffer;
    mod_foggui_DW.RateTransition27_Buffer = static_cast<real32_T>
      ((mod_foggui_P.R_Gain * mod_foggui_P.state.config.lancamento.Rde *
        (mod_foggui_P.state.config.lancamento.Rtemp + mod_foggui_P.kelvin_Value)
        * mod_foggui_P.Gain_Gain));
    mod_foggui_B.RateTransition27 = mod_foggui_DW.RateTransition27_Buffer;
    mod_foggui_DW.RateTransition28_Buffer = static_cast<real32_T>
      (mod_foggui_P.state.config.lancamento.Rtemp);
    mod_foggui_B.RateTransition28 = mod_foggui_DW.RateTransition28_Buffer;
    mod_foggui_DW.RateTransition11_Buffer[0] = mod_foggui_P.Constant_Value;
    mod_foggui_DW.RateTransition11_Buffer[1] = mod_foggui_DW.UnitDelay_DSTATE;
    mod_foggui_DW.RateTransition11_Buffer[2] =
      mod_foggui_DW.UnitDelay1_DSTATE_mtu4iijmx1;
    mod_foggui_B.fom[0] = static_cast<int32_T>(std::floor
      (mod_foggui_DW.RateTransition11_Buffer[0]));
    mod_foggui_B.fom[1] = static_cast<int32_T>(std::floor
      (mod_foggui_DW.RateTransition11_Buffer[1]));
    mod_foggui_B.fom[2] = static_cast<int32_T>(std::floor
      (mod_foggui_DW.RateTransition11_Buffer[2]));
    mod_foggui_B.RateTransition12_mwuhtr5lwn =
      mod_foggui_DW.RateTransition12_Buffer0;
    mod_foggui_B.RateTransition13[0] = mod_foggui_DW.RateTransition13_Buffer0[0];
    mod_foggui_B.RateTransition13[1] = mod_foggui_DW.RateTransition13_Buffer0[1];
    mod_foggui_B.RateTransition3_jscxuhpmkl =
      mod_foggui_DW.RateTransition3_Buffer0;
    mod_foggui_B.UnitDelay1_fvkxsdqnex =
      mod_foggui_DW.UnitDelay1_DSTATE_jwmvbzzmma;

    {
      SimStruct *rts = (&mod_foggui_M)->childSfunctions[0];
      sfcnOutputs(rts,1);
    }

    sigma1_ = 0.0F;
    duracao = 0.0F;
    buffer = 0.0F;
    Ry = 0.0F;
    sigma_lat_ = 0.0F;
    R = 0.0F;
    for (i = 0; i < 10; i++) {
      mod_foggui_Y.pontos_traj[i] = -999.0F;
    }

    std::memcpy(&ganhos[0], &c[0], sizeof(real32_T) << 4U);
    G[0] = mod_foggui_B.RateTransition15[3];
    G[1] = mod_foggui_B.RateTransition15[4];
    G[2] = mod_foggui_B.RateTransition15[5];
    G[3] = mod_foggui_B.RateTransition15[6];
    G[4] = mod_foggui_B.RateTransition15[7];
    G[5] = mod_foggui_B.RateTransition15[8];
    G[6] = mod_foggui_B.RateTransition15[9];
    G[7] = mod_foggui_B.RateTransition12;
    Rn = rt_roundf_snf(mod_foggui_B.RateTransition15[2]);
    if (Rn < 65536.0F) {
      if (Rn >= 0.0F) {
        tmp_2 = static_cast<uint16_T>(Rn);
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint16_T;
    }

    pageroot = 16;
    for (stride = 0; stride < 16; stride++) {
      op_b_data[stride] = '0';
    }

    for (i = 0; i < 16; i++) {
      if ((1 << i & tmp_2) != 0) {
        op_b_data[15 - i] = '1';
      }
    }

    i = 16;
    nd2 = 0;
    exitg1 = false;
    while ((!exitg1) && (nd2 < 15)) {
      if (op_b_data[nd2] != '0') {
        i = nd2 + 1;
        exitg1 = true;
      } else {
        nd2++;
      }
    }

    if (i > 1) {
      for (nd2 = i; nd2 < 17; nd2++) {
        op_b_data[nd2 - i] = op_b_data[nd2 - 1];
      }

      i = 16 - i;
      pageroot = i + 1;
      if (0 <= i) {
        std::memcpy(&op_b_data_0[0], &op_b_data[0], (i + 1) * sizeof(char_T));
      }

      if (0 <= pageroot - 1) {
        std::memcpy(&op_b_data[0], &op_b_data_0[0], pageroot * sizeof(char_T));
      }
    }

    if (pageroot > 1) {
      nd2 = pageroot >> 1;
      for (stride = 0; stride < nd2; stride++) {
        tmp = op_b_data[stride];
        i = (pageroot - stride) - 1;
        op_b_data[stride] = op_b_data[i];
        op_b_data[i] = tmp;
      }
    }

    Keep = 0.0;
    for (i = 0; i < pageroot; i++) {
      p = false;
      if (!(op_b_data[i] != '1')) {
        p = true;
      }

      if (p) {
        Keep++;
        ganhos[i] = G[static_cast<int32_T>(Keep) - 1];
      }
    }

    phi = mod_foggui_B.Bank[2] * 57.2957802F + mod_foggui_B.DataTypeConversion1
      [5] * ganhos[4];
    if ((mod_foggui_DW.theta0[0] > 400.0F) && (mod_foggui_B.fom[2] <= 8)) {
      mod_foggui_DW.theta0[0] = mod_foggui_B.Elevation[0] * 57.2957802F;
      mod_foggui_DW.theta0[1] = mod_foggui_B.Elevation[1] * 57.2957802F;
      mod_foggui_DW.theta0[2] = mod_foggui_B.Elevation[2] * 57.2957802F;
    }

    LLA0[0] = mod_foggui_B.RateTransition26 * 57.2957802F;
    LLA0[1] = mod_foggui_B.RateTransition25 * 57.2957802F;
    rll0_tmp = LLA0[0] * 3.14159274F / 180.0F;
    Rn = std::sin(rll0_tmp);
    Rn = 6.378137E+6F / std::sqrt(1.0F - 0.00669437973F * Rn * Rn);
    flat[0] = (mod_foggui_B.Lat[2] * 57.2957802F - LLA0[0]) * 3.14159274F /
      180.0F / rt_atan2f_snf(1.0F, 0.993305624F / (1.0F - 0.00669437973F * std::
      sin(rll0_tmp) * std::sin(rll0_tmp)) * Rn);
    flat[1] = (mod_foggui_B.Lon[2] * 57.2957802F - LLA0[1]) * 3.14159274F /
      180.0F / rt_atan2f_snf(1.0F, Rn * std::cos(rll0_tmp));
    Rn = std::sin(rll0_tmp);
    Rn = 6.378137E+6F / std::sqrt(1.0F - 0.00669437973F * Rn * Rn);
    flat_targ[0] = (mod_foggui_B.lat_targ - LLA0[0]) * 3.14159274F / 180.0F /
      rt_atan2f_snf(1.0F, 0.993305624F / (1.0F - 0.00669437973F * std::sin
      (rll0_tmp) * std::sin(rll0_tmp)) * Rn);
    flat_targ[1] = (mod_foggui_B.lon_targ - LLA0[1]) * 3.14159274F / 180.0F /
      rt_atan2f_snf(1.0F, Rn * std::cos(rll0_tmp));
    theta[0] = flat[0];
    theta[1] = flat[1];
    theta[2] = mod_foggui_B.Alt[2];
    mod_foggui_circshift(mod_foggui_DW.pos_buffer);
    mod_foggui_DW.pos_buffer[499] = rt_hypotf_snf(flat[0], flat[1]);
    mod_foggui_DW.pos_buffer[999] = mod_foggui_B.Alt[2];
    if ((mod_foggui_B.sfunSSV_o1 != 0) && (mod_foggui_B.sfunSSV_o1 != 2)) {
      stride = mod_foggui_DW.cont_fpqdtmbzoo + 1;
      if (stride > 32767) {
        stride = 32767;
      }

      mod_foggui_DW.cont_fpqdtmbzoo = static_cast<int16_T>(stride);
      Rn = rt_roundf_snf(ganhos[9] * 50.0F);
      if (Rn < 32768.0F) {
        if (Rn >= -32768.0F) {
          tmp_3 = static_cast<int16_T>(Rn);
        } else {
          tmp_3 = MIN_int16_T;
        }
      } else {
        tmp_3 = MAX_int16_T;
      }

      if ((mod_foggui_DW.cont_fpqdtmbzoo > tmp_3) &&
          ((!(mod_foggui_B.DataTypeConversion1[5] / 2.0F / 3.14159274F > ganhos
              [5])) || (mod_foggui_DW.flag_wx != 0))) {
        mod_foggui_DW.flag_wx = 1;
        if ((mod_foggui_DW.flag_gui_lat == 0) && (mod_foggui_B.Vd[2] > ganhos[6])
            && (mod_foggui_B.sfunSSV_o1 == 1)) {
          mod_foggui_DW.flag_gui_lat = 1;
        }

        if (mod_foggui_DW.flag_gui_lat == 1) {
          buffer = flat_targ[1] - flat[1];
          Ry = flat_targ[0] - flat[0];
          R = std::sqrt(buffer * buffer + Ry * Ry);
          buffer = (buffer * mod_foggui_B.Ve[2] + Ry * mod_foggui_B.Vn[2]) / R *
            ganhos[0] * ((Ry * mod_foggui_B.Ve[2] - buffer * mod_foggui_B.Vn[2])
                         / R / R);
        }

        if ((mod_foggui_DW.flag_gui_lon == 0) && (std::abs(buffer) < ganhos[10])
            && (mod_foggui_DW.flag_gui_lat == 1)) {
          mod_foggui_DW.flag_gui_lon = 1;
        }

        Ry = 0.0F;
        if (mod_foggui_DW.flag_gui_lon == 1) {
          P[0] = mod_foggui_B.Vn[2];
          P[1] = mod_foggui_B.Ve[2];
          P[2] = mod_foggui_B.Vd[2];
          flat_targ_0[0] = flat_targ[0];
          flat_targ_0[1] = flat_targ[1];
          flat_targ_0[2] = mod_foggui_B.alt_targ + ganhos[15];
          mod_foggui_guiamentoLongitudinal(P, theta, flat_targ_0,
            mod_foggui_DW.pos_buffer, ganhos[7], ganhos[14], &Ry, &R,
            mod_foggui_Y.pontos_traj, &ii_data_idx_0);
          Ry = ganhos[1] * Ry * R;
          if (ii_data_idx_0 == 2) {
            Ry = 0.0F;
          }

          R = 1.0F / (std::exp(-mod_foggui_DW.x_bio4k4d4zb[2]) + 1.0F);
          mod_foggui_DW.x_bio4k4d4zb[2] += 14.18F / (ganhos[13] * 50.0F);
          Ry = (1.0F - R) * 0.0F + Ry * R;
        }

        if ((!(buffer > -ganhos[11])) && (!rtIsNaNF(-ganhos[11]))) {
          buffer = -ganhos[11];
        }

        if ((!(buffer < ganhos[11])) && (!rtIsNaNF(ganhos[11]))) {
          buffer = ganhos[11];
        }

        if ((!(Ry > -ganhos[12])) && (!rtIsNaNF(-ganhos[12]))) {
          Ry = -ganhos[12];
        }

        if ((!(Ry < ganhos[12])) && (!rtIsNaNF(ganhos[12]))) {
          Ry = ganhos[12];
        }

        R = phi;
        mod_foggui_cosd(&R);
        sigma_lat_ = phi;
        mod_foggui_sind(&sigma_lat_);
        R = Ry * ganhos[2] - (mod_foggui_B.DataTypeConversion15[5] * R -
                              mod_foggui_B.DataTypeConversion16[5] * sigma_lat_)
          * ganhos[3];
        sigma_lat_ = phi;
        mod_foggui_sind(&sigma_lat_);
        sigma1_ = phi;
        mod_foggui_cosd(&sigma1_);
        sigma_lat_ = (mod_foggui_B.DataTypeConversion15[5] * sigma_lat_ +
                      mod_foggui_B.DataTypeConversion16[5] * sigma1_) * ganhos[3]
          + buffer * ganhos[2];
        rll0[0] = sigma_lat_;
        rll0[1] = R;
        sigma1_ = mod_foggui_norm(rll0);
        if (sigma1_ > ganhos[8]) {
          sigma_lat_ = sigma_lat_ / sigma1_ * ganhos[8];
          R = R / sigma1_ * ganhos[8];
        }

        sigma1_ = phi;
        mod_foggui_cosd(&sigma1_);
        duracao = phi;
        mod_foggui_sind(&duracao);
        sigma1_ = R * sigma1_ - sigma_lat_ * duracao;
        duracao = phi;
        mod_foggui_sind(&duracao);
        mod_foggui_cosd(&phi);
        phi = -R * duracao - sigma_lat_ * phi;
        if (rtIsNaNF(sigma1_)) {
          sigma1_ = mod_foggui_DW.ang13_;
        }

        if (rtIsNaNF(phi)) {
          phi = mod_foggui_DW.ang24_;
        }

        mod_foggui_DW.ang13_ = sigma1_;
        mod_foggui_DW.ang24_ = phi;
        sigma1_ /= 57.2957802F;
        phi /= 57.2957802F;
        duracao = ganhos[13] * 50.0F;
        if (mod_foggui_DW.flag_gui_lat != 0) {
          Rn = 1.0F / (std::exp(-mod_foggui_DW.x_bio4k4d4zb[0]) + 1.0F);
          mod_foggui_DW.x_bio4k4d4zb[0] += 14.18F / duracao;
        } else {
          Rn = 0.0F;
        }

        sigma1_ = (1.0F - Rn) * 0.0F + sigma1_ * Rn;
        if (mod_foggui_DW.flag_gui_lat != 0) {
          Rn = 1.0F / (std::exp(-mod_foggui_DW.x_bio4k4d4zb[1]) + 1.0F);
          mod_foggui_DW.x_bio4k4d4zb[1] += 14.18F / duracao;
        } else {
          Rn = 0.0F;
        }

        duracao = (1.0F - Rn) * 0.0F + phi * Rn;
      }
    }

    rtb_DataTypeConversion10 = R;
    rtb_DataTypeConversion13[0] = sigma1_;
    rtb_DataTypeConversion13[1] = duracao;
    rtb_DataTypeConversion7 = buffer;
    rtb_DataTypeConversion8 = Ry;
    rtb_DataTypeConversion9 = sigma_lat_;
    flat[0] = mod_foggui_B.Vn[2];
    flat[1] = mod_foggui_B.Ve[2];
    flat[2] = mod_foggui_B.Vd[2];
    flat_targ[0] = mod_foggui_B.lat_targ;
    flat_targ[1] = mod_foggui_B.lon_targ;
    flat_targ[2] = mod_foggui_B.alt_targ;
    mod_foggui_B.flag_ejecao = -1;
    mod_foggui_Y.modulo_erro = mod_foggui_DW.moduloERRO_;
    mod_foggui_Y.nro_iteracoes = 0;
    if (mod_foggui_B.flag_sb == 0) {
      for (i = 0; i < 2; i++) {
        pageroot = i * 10;
        buffer = mod_foggui_DW.vetorPOS[pageroot];
        for (stride = 0; stride < 9; stride++) {
          nd2 = pageroot + stride;
          mod_foggui_DW.vetorPOS[nd2] = mod_foggui_DW.vetorPOS[nd2 + 1];
        }

        mod_foggui_DW.vetorPOS[pageroot + 9] = buffer;
      }

      mod_foggui_DW.vetorPOS[0] = mod_foggui_B.Lat[2];
      mod_foggui_DW.vetorPOS[10] = mod_foggui_B.Lon[2];
    } else if (mod_foggui_B.Alt[2] <= mod_foggui_B.RateTransition15[1] +
               mod_foggui_B.alt_targ) {
      mod_foggui_B.flag_ejecao = 2;
    } else {
      for (i = 0; i < 2; i++) {
        for (stride = 0; stride < 10; stride++) {
          v[stride] = mod_foggui_DW.vetorPOS[10 * i + stride];
        }

        stride = 0;
        do {
          exitg2 = 0;
          if (stride < 10) {
            if (rtIsNaNF(mod_foggui_DW.vetorPOS[10 * i + stride])) {
              LLA0[i] = (rtNaNF);
              exitg2 = 1;
            } else {
              stride++;
            }
          } else {
            mod_foggui_quickselect(v, 6, 1, 10, &buffer, &stride, &nd2);
            LLA0[i] = buffer;
            if (5 < stride) {
              mod_foggui_quickselect(v, 5, 1, nd2 - 1, &phi, &stride, &pageroot);
              if (rtIsInfF(buffer) || rtIsInfF(phi)) {
                LLA0[i] = (buffer + phi) / 2.0F;
              } else {
                LLA0[i] = (phi - buffer) / 2.0F + buffer;
              }
            }

            exitg2 = 1;
          }
        } while (exitg2 == 0);
      }

      buffer = LLA0[0] * 57.2957802F;
      rll0[0] = buffer * 3.14159274F / 180.0F;
      LLA0[0] = buffer;
      buffer = LLA0[1] * 57.2957802F;
      Rn = std::sin(rll0[0]);
      Rn = 6.378137E+6F / std::sqrt(1.0F - 0.00669437973F * Rn * Rn);
      sigma1_ = (mod_foggui_B.Lat[2] * 57.2957802F - LLA0[0]) * 3.14159274F /
        180.0F / rt_atan2f_snf(1.0F, 0.993305624F / (1.0F - 0.00669437973F * std::
        sin(rll0[0]) * std::sin(rll0[0])) * Rn);
      Rn = (mod_foggui_B.Lon[2] * 57.2957802F - buffer) * 3.14159274F / 180.0F /
        rt_atan2f_snf(1.0F, Rn * std::cos(rll0[0]));
      for (stride = 0; stride < 3; stride++) {
        P[stride] = static_cast<real32_T>(f[3 * stride + 2]) * mod_foggui_B.Alt
          [2] + (static_cast<real32_T>(f[3 * stride + 1]) * Rn +
                 static_cast<real32_T>(f[3 * stride]) * sigma1_);
      }

      P[0] += 0.099999994F * mod_foggui_B.Vn[2];
      P[1] += 0.099999994F * mod_foggui_B.Ve[2];
      P[2] += 0.099999994F * mod_foggui_B.Vd[2];
      rll0[0] = LLA0[0] * 3.14159274F / 180.0F;
      Rn = std::sin(rll0[0]);
      Rn = 6.378137E+6F / std::sqrt(1.0F - 0.00669437973F * Rn * Rn);
      theta[0] = (rt_atan2f_snf(1.0F, 0.993305624F / (1.0F - 0.00669437973F *
        std::sin(rll0[0]) * std::sin(rll0[0])) * Rn) * P[0] * 180.0F /
                  3.14159274F + LLA0[0]) / 57.2957802F;
      theta[1] = (rt_atan2f_snf(1.0F, Rn * std::cos(rll0[0])) * P[1] * 180.0F /
                  3.14159274F + buffer) / 57.2957802F;
      theta[2] = -P[2];
      expl_temp.Delta_ejec = 0.1F;
      expl_temp.Cd_fac_eng = mod_foggui_B.RateTransition13_fhpnmvyjeu;
      expl_temp.Cdadjsm = 52.2339859F;
      expl_temp.Massa = 130.0F;
      std::memcpy(&expl_temp.Cwss[0], &d[0], 41U * sizeof(real32_T));
      expl_temp.S = 0.0246057417F;
      mod_foggui_calculaTrajetoria(theta, flat, flat_targ, 0.008F, 0.1F, 1.0F,
        0.02F, 2.0F, 0.02F, 0.3F, 1200.0F, &expl_temp,
        mod_foggui_B.RateTransition28 + 273.15F, mod_foggui_B.RateTransition27 *
        100.0F, P, &mod_foggui_Y.nro_iteracoes, &i);
      mod_foggui_calculaErro(P, flat_targ, i, &mod_foggui_B.flag_ejecao, &buffer);
      mod_foggui_Y.modulo_erro = buffer;
      mod_foggui_DW.moduloERRO_ = buffer;
    }

    mod_foggui_DW.UnitDelay1_DSTATE_jwmvbzzmma = mod_foggui_B.flag_ejecao;
    mod_foggui_DW.RateTransition12_Buffer0 = mod_foggui_B.sfunSSV_o1;
    mod_foggui_DW.RateTransition13_Buffer0[0] = rtb_DataTypeConversion13[0];
    mod_foggui_DW.RateTransition13_Buffer0[1] = rtb_DataTypeConversion13[1];
    mod_foggui_DW.RateTransition3_Buffer0 = mod_foggui_B.flag_ejecao;
  }

  mod_foggui_DW.UnitDelay_DSTATE = mod_foggui_P.Constant_Value;
  mod_foggui_DW.UnitDelay1_DSTATE_mtu4iijmx1 = rtb_UnitDelay;
  rtb_canardON = mod_foggui_P.state.config.flags.controle_on *
    static_cast<real_T>(mod_foggui_B.RateTransition12_mwuhtr5lwn);
  mod_foggui_Y.canard_on = rtb_canardON;
  Keep = mod_foggui_P.state.config.flags.controle_on *
    mod_foggui_B.RateTransition13[0];
  mod_foggui_Y.canard_u[0] = Keep;
  Az = Keep;
  Keep = mod_foggui_P.state.config.flags.controle_on *
    mod_foggui_B.RateTransition13[1];
  mod_foggui_Y.canard_u[1] = Keep;
  if ((&mod_foggui_M)->Timing.TaskCounters.TID[1] == 0) {
    mod_foggui_Y.erro_lat = rtb_DataTypeConversion7;
    mod_foggui_Y.erro_lon = rtb_DataTypeConversion8;
    mod_foggui_Y.sigma_lat = rtb_DataTypeConversion9;
    mod_foggui_Y.sigma_lon = rtb_DataTypeConversion10;
    mod_foggui_Y.tempo_ejecao = mod_foggui_B.sfunSSV_o2;
    mod_foggui_Y.nro_timeout = mod_foggui_B.sfunSSV_o4;
    mod_foggui_Y.pulso_flag_voo = mod_foggui_B.sfunSSV_o5;
    mod_foggui_Y.ssv_fimdequeima = mod_foggui_B.sfunSSV_o6;
  }

  rtb_flagEjecao = static_cast<real_T>((static_cast<int64_T>
    (mod_foggui_P.Gain_Gain_o4w1mvc04r) *
    mod_foggui_B.RateTransition3_jscxuhpmkl)) * 9.3132257461547852E-10 *
    mod_foggui_P.state.config.flags.controle_on;
  mod_foggui_Y.flag_ejecao = rtb_flagEjecao;
  if (mod_foggui_Y.fim) {
    rtmSetStopRequested((&mod_foggui_M), 1);
  }

  mod_foggui_DW.UnitDelay_DSTATE_gupgjp1fb1 = static_cast<int32_T>(std::floor
    (rtb_canardON));
  mod_foggui_DW.UnitDelay2_DSTATE = static_cast<int32_T>(std::floor
    (rtb_flagEjecao));
  rtb_Saturation_idx_0 = mod_foggui_DW.UnitDelay1_DSTATE[0];
  mod_foggui_DW.UnitDelay1_DSTATE[0] = Az;
  Az = mod_foggui_DW.UnitDelay1_DSTATE[1];
  mod_foggui_DW.UnitDelay1_DSTATE[1] = Keep;
  mod_foggui_DW.DiscreteTransferFcn1_states = (rtb_Saturation_idx_0 -
    mod_foggui_P.DiscreteTransferFcn1_DenCoef[1] *
    mod_foggui_DW.DiscreteTransferFcn1_states) /
    mod_foggui_P.DiscreteTransferFcn1_DenCoef[0];
  mod_foggui_DW.DiscreteTransferFcn3_states = (Az -
    mod_foggui_P.DiscreteTransferFcn3_DenCoef[1] *
    mod_foggui_DW.DiscreteTransferFcn3_states) /
    mod_foggui_P.DiscreteTransferFcn3_DenCoef[0];
  if ((&mod_foggui_M)->Timing.TaskCounters.TID[1] == 0) {
    if (!(++(&mod_foggui_M)->Timing.clockTick1)) {
      ++(&mod_foggui_M)->Timing.clockTickH1;
    }

    (&mod_foggui_M)->Timing.t[1] = (&mod_foggui_M)->Timing.clockTick1 *
      (&mod_foggui_M)->Timing.stepSize1 + (&mod_foggui_M)->Timing.clockTickH1 *
      (&mod_foggui_M)->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler((&mod_foggui_M));
}

void mod_fogguiModelClass::initialize()
{
  rt_InitInfAndNaN(sizeof(real_T));
  rtsiSetSolverName(&(&mod_foggui_M)->solverInfo,"FixedStepDiscrete");
  (&mod_foggui_M)->solverInfoPtr = (&(&mod_foggui_M)->solverInfo);

  {
    int_T *mdlTsMap = (&mod_foggui_M)->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    (&mod_foggui_M)->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    (&mod_foggui_M)->Timing.sampleTimes = (&(&mod_foggui_M)
      ->Timing.sampleTimesArray[0]);
    (&mod_foggui_M)->Timing.offsetTimes = (&(&mod_foggui_M)
      ->Timing.offsetTimesArray[0]);
    (&mod_foggui_M)->Timing.sampleTimes[0] = (0.00083333333333333339);
    (&mod_foggui_M)->Timing.sampleTimes[1] = (0.02);
    (&mod_foggui_M)->Timing.offsetTimes[0] = (0.0);
    (&mod_foggui_M)->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr((&mod_foggui_M), &(&mod_foggui_M)->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = (&mod_foggui_M)->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    (&mod_foggui_M)->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal((&mod_foggui_M), -1);
  (&mod_foggui_M)->Timing.stepSize1 = 0.02;
  (&mod_foggui_M)->solverInfoPtr = (&(&mod_foggui_M)->solverInfo);
  (&mod_foggui_M)->Timing.stepSize = (0.00083333333333333339);
  rtsiSetFixedStepSize(&(&mod_foggui_M)->solverInfo, 0.00083333333333333339);
  rtsiSetSolverMode(&(&mod_foggui_M)->solverInfo, SOLVER_MODE_SINGLETASKING);
  (void) std::memset((static_cast<void *>(&mod_foggui_B)), 0,
                     sizeof(B_mod_foggui_T));
  (void) std::memset(static_cast<void *>(&mod_foggui_DW), 0,
                     sizeof(DW_mod_foggui_T));
  mod_foggui_U.tiro = 0;
  (void) std::memset(static_cast<void *>(&mod_foggui_Y), 0,
                     sizeof(ExtY_mod_foggui_T));
  mod_foggui_InitializeDataMapInfo((&mod_foggui_M), &mod_foggui_B, &mod_foggui_P,
    &mod_foggui_DW);

  {
    RTWSfcnInfo *sfcnInfo = &(&mod_foggui_M)->NonInlinedSFcns.sfcnInfo;
    (&mod_foggui_M)->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus((&mod_foggui_M))));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &(&mod_foggui_M)->Sizes.numSampTimes);
    (&mod_foggui_M)->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      ((&mod_foggui_M))[0]);
    (&mod_foggui_M)->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr
      ((&mod_foggui_M))[1]);
    rtssSetTPtrPtr(sfcnInfo,(&mod_foggui_M)->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart((&mod_foggui_M)));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal((&mod_foggui_M)));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput((&mod_foggui_M)));
    rtssSetStepSizePtr(sfcnInfo, &(&mod_foggui_M)->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested((&mod_foggui_M)));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo, &(&mod_foggui_M)
      ->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &(&mod_foggui_M)->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &(&mod_foggui_M)->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &(&mod_foggui_M)->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &(&mod_foggui_M)
      ->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &(&mod_foggui_M)->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &(&mod_foggui_M)->solverInfoPtr);
  }

  (&mod_foggui_M)->Sizes.numSFcns = (1);

  {
    (void) std::memset(static_cast<void *>(&(&mod_foggui_M)
      ->NonInlinedSFcns.childSFunctions[0]), 0,
                       1*sizeof(SimStruct));
    (&mod_foggui_M)->childSfunctions = (&(&mod_foggui_M)
      ->NonInlinedSFcns.childSFunctionPtrs[0]);
    (&mod_foggui_M)->childSfunctions[0] = (&(&mod_foggui_M)
      ->NonInlinedSFcns.childSFunctions[0]);

    {
      SimStruct *rts = (&mod_foggui_M)->childSfunctions[0];
      time_T *sfcnPeriod = (&mod_foggui_M)->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = (&mod_foggui_M)->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = (&mod_foggui_M)->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &(&mod_foggui_M)->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts, &(&mod_foggui_M)
        ->NonInlinedSFcns.inputOutputPortInfo2[0]);
      ssSetRTWSfcnInfo(rts, (&mod_foggui_M)->sfcnInfo);

      {
        ssSetModelMethods2(rts, &(&mod_foggui_M)->NonInlinedSFcns.methods2[0]);
      }

      {
        ssSetModelMethods3(rts, &(&mod_foggui_M)->NonInlinedSFcns.methods3[0]);
      }

      {
        ssSetModelMethods4(rts, &(&mod_foggui_M)->NonInlinedSFcns.methods4[0]);
      }

      {
        ssSetStatesInfo2(rts, &(&mod_foggui_M)->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      {
        _ssSetNumInputPorts(rts, 12);
        ssSetPortInfoForInputs(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.Sfcn0.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        ssSetInputPortUnit(rts, 2, 0);
        ssSetInputPortUnit(rts, 3, 0);
        ssSetInputPortUnit(rts, 4, 0);
        ssSetInputPortUnit(rts, 5, 0);
        ssSetInputPortUnit(rts, 6, 0);
        ssSetInputPortUnit(rts, 7, 0);
        ssSetInputPortUnit(rts, 8, 0);
        ssSetInputPortUnit(rts, 9, 0);
        ssSetInputPortUnit(rts, 10, 0);
        ssSetInputPortUnit(rts, 11, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.Sfcn0.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);
        ssSetInputPortIsContinuousQuantity(rts, 2, 0);
        ssSetInputPortIsContinuousQuantity(rts, 3, 0);
        ssSetInputPortIsContinuousQuantity(rts, 4, 0);
        ssSetInputPortIsContinuousQuantity(rts, 5, 0);
        ssSetInputPortIsContinuousQuantity(rts, 6, 0);
        ssSetInputPortIsContinuousQuantity(rts, 7, 0);
        ssSetInputPortIsContinuousQuantity(rts, 8, 0);
        ssSetInputPortIsContinuousQuantity(rts, 9, 0);
        ssSetInputPortIsContinuousQuantity(rts, 10, 0);
        ssSetInputPortIsContinuousQuantity(rts, 11, 0);

        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0, &mod_foggui_B.UnitDelay1_fvkxsdqnex);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1, mod_foggui_B.DataTypeConversion2);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 6);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 2, 1);
          ssSetInputPortSignal(rts, 2, mod_foggui_B.DataTypeConversion13);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 6);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 3, 1);
          ssSetInputPortSignal(rts, 3, mod_foggui_B.DataTypeConversion14);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 6);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 4, 1);
          ssSetInputPortSignal(rts, 4, mod_foggui_B.Vn);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidth(rts, 4, 3);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 5, 1);
          ssSetInputPortSignal(rts, 5, mod_foggui_B.Ve);
          _ssSetInputPortNumDimensions(rts, 5, 1);
          ssSetInputPortWidth(rts, 5, 3);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 6, 1);
          ssSetInputPortSignal(rts, 6, mod_foggui_B.Vd);
          _ssSetInputPortNumDimensions(rts, 6, 1);
          ssSetInputPortWidth(rts, 6, 3);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 7, 1);
          ssSetInputPortSignal(rts, 7, mod_foggui_B.Alt);
          _ssSetInputPortNumDimensions(rts, 7, 1);
          ssSetInputPortWidth(rts, 7, 3);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 8, 1);
          ssSetInputPortSignal(rts, 8, &mod_foggui_B.alt_targ);
          _ssSetInputPortNumDimensions(rts, 8, 1);
          ssSetInputPortWidth(rts, 8, 1);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 9, 1);
          ssSetInputPortSignal(rts, 9, &mod_foggui_B.RateTransition15[0]);
          _ssSetInputPortNumDimensions(rts, 9, 1);
          ssSetInputPortWidth(rts, 9, 1);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 10, 1);
          ssSetInputPortSignal(rts, 10, &mod_foggui_B.RateTransition29);
          _ssSetInputPortNumDimensions(rts, 10, 1);
          ssSetInputPortWidth(rts, 10, 1);
        }

        {
          ssSetInputPortRequiredContiguous(rts, 11, 1);
          ssSetInputPortSignal(rts, 11, mod_foggui_B.fom);
          _ssSetInputPortNumDimensions(rts, 11, 1);
          ssSetInputPortWidth(rts, 11, 3);
        }
      }

      {
        ssSetPortInfoForOutputs(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 6);
        _ssSetPortInfo2ForOutputUnits(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);
        ssSetOutputPortUnit(rts, 2, 0);
        ssSetOutputPortUnit(rts, 3, 0);
        ssSetOutputPortUnit(rts, 4, 0);
        ssSetOutputPortUnit(rts, 5, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts, &(&mod_foggui_M)
          ->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 1, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 2, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 3, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 4, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 5, 0);

        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((int32_T *) &mod_foggui_B.sfunSSV_o1));
        }

        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((uint16_T *) &mod_foggui_B.sfunSSV_o2));
        }

        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((int32_T *) &mod_foggui_B.flag_sb));
        }

        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((uint16_T *) &mod_foggui_B.sfunSSV_o4));
        }

        {
          _ssSetOutputPortNumDimensions(rts, 4, 1);
          ssSetOutputPortWidth(rts, 4, 1);
          ssSetOutputPortSignal(rts, 4, ((uint16_T *) &mod_foggui_B.sfunSSV_o5));
        }

        {
          _ssSetOutputPortNumDimensions(rts, 5, 1);
          ssSetOutputPortWidth(rts, 5, 1);
          ssSetOutputPortSignal(rts, 5, ((uint16_T *) &mod_foggui_B.sfunSSV_o6));
        }
      }

      ssSetModelName(rts, "sfunSSV");
      ssSetPath(rts, "mod_foggui/Controle/controleJATOSeCANARDS/sfunSSV");
      ssSetRTModel(rts,(&mod_foggui_M));
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);
      ssSetPWork(rts, (void **) &mod_foggui_DW.sfunSSV_PWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &(&mod_foggui_M)->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &(&mod_foggui_M)->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);
        ssSetDWorkWidth(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &mod_foggui_DW.sfunSSV_PWORK[0]);
      }

      sfunSSV(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);
      ssSetSampleTime(rts, 0, 0.02);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;
      ssSetNumNonsampledZCs(rts, 0);
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);
      _ssSetInputPortConnected(rts, 5, 1);
      _ssSetInputPortConnected(rts, 6, 1);
      _ssSetInputPortConnected(rts, 7, 1);
      _ssSetInputPortConnected(rts, 8, 1);
      _ssSetInputPortConnected(rts, 9, 1);
      _ssSetInputPortConnected(rts, 10, 1);
      _ssSetInputPortConnected(rts, 11, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 4, 1);
      _ssSetOutputPortConnected(rts, 5, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 4, 0);
      _ssSetOutputPortBeingMerged(rts, 5, 0);
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
      ssSetInputPortBufferDstPort(rts, 5, -1);
      ssSetInputPortBufferDstPort(rts, 6, -1);
      ssSetInputPortBufferDstPort(rts, 7, -1);
      ssSetInputPortBufferDstPort(rts, 8, -1);
      ssSetInputPortBufferDstPort(rts, 9, -1);
      ssSetInputPortBufferDstPort(rts, 10, -1);
      ssSetInputPortBufferDstPort(rts, 11, -1);
    }
  }

  mod_foggui_B.RateTransition12_mwuhtr5lwn =
    mod_foggui_P.RateTransition12_InitialCondition;
  mod_foggui_B.RateTransition13[0] =
    mod_foggui_P.RateTransition13_InitialCondition;
  mod_foggui_B.RateTransition13[1] =
    mod_foggui_P.RateTransition13_InitialCondition;
  mod_foggui_B.RateTransition3_jscxuhpmkl =
    mod_foggui_P.RateTransition3_InitialCondition;

  {
    SimStruct *rts = (&mod_foggui_M)->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  {
    int32_T i;
    mod_foggui_DW.UnitDelay_DSTATE_gupgjp1fb1 =
      mod_foggui_P.UnitDelay_InitialCondition_ixzxscpueh;
    mod_foggui_DW.UnitDelay2_DSTATE = mod_foggui_P.UnitDelay2_InitialCondition;
    mod_foggui_DW.DiscreteTransferFcn1_states =
      mod_foggui_P.DiscreteTransferFcn1_InitialStates;
    mod_foggui_DW.DiscreteTransferFcn3_states =
      mod_foggui_P.DiscreteTransferFcn3_InitialStates;
    mod_foggui_DW.o_not_empty = false;
    mod_foggui_DW.cont = 0.0;
    mod_foggui_DW.flagLoopFases1 = true;
    mod_foggui_DW.flagLoopFases2 = true;
    mod_foggui_DW.F_aux = 1.0;
    mod_foggui_DW.Salfab = 0.0;
    mod_foggui_DW.Dalfa = 0.0;
    mod_foggui_DW.Dalfa_c = 0.0;
    mod_foggui_DW.cont_kimmltz2iq = 0.0;
    mod_foggui_DW.erroint = 0.0;
    mod_foggui_DW.err_ = 0.0;
    mod_foggui_DW.UnitDelay_DSTATE = mod_foggui_P.UnitDelay_InitialCondition;
    mod_foggui_DW.UnitDelay1_DSTATE_mtu4iijmx1 =
      mod_foggui_P.UnitDelay1_InitialCondition;
    mod_foggui_DW.RateTransition12_Buffer0 =
      mod_foggui_P.RateTransition12_InitialCondition;
    mod_foggui_DW.UnitDelay1_DSTATE[0] =
      mod_foggui_P.UnitDelay1_InitialCondition_ev2gupt1pg;
    mod_foggui_DW.PrevY[0] = mod_foggui_P.RateLimiter_IC;
    mod_foggui_DW.RateTransition13_Buffer0[0] =
      mod_foggui_P.RateTransition13_InitialCondition;
    mod_foggui_DW.UnitDelay1_DSTATE[1] =
      mod_foggui_P.UnitDelay1_InitialCondition_ev2gupt1pg;
    mod_foggui_DW.PrevY[1] = mod_foggui_P.RateLimiter_IC;
    mod_foggui_DW.RateTransition13_Buffer0[1] =
      mod_foggui_P.RateTransition13_InitialCondition;
    mod_foggui_DW.RateTransition3_Buffer0 =
      mod_foggui_P.RateTransition3_InitialCondition;
    std::memset(&mod_foggui_DW.m3[0], 0, 9U * sizeof(real_T));
    std::memset(&mod_foggui_DW.m6[0], 0, 36U * sizeof(real_T));
    mod_foggui_DW.i3 = 1.0;
    mod_foggui_DW.i6 = 1.0;
    std::memset(&mod_foggui_DW.buffer[0], 0, 27U * sizeof(real32_T));
    mod_foggui_DW.UnitDelay1_DSTATE_jwmvbzzmma =
      mod_foggui_P.UnitDelay1_InitialCondition_fywu2qaory;
    mod_foggui_DW.pontos_not_empty = false;
    mod_foggui_DW.cont_fpqdtmbzoo = 0;
    std::memset(&mod_foggui_DW.pos_buffer[0], 0, 1000U * sizeof(real32_T));
    mod_foggui_DW.theta0[0] = 500.0F;
    mod_foggui_DW.theta0[1] = 500.0F;
    mod_foggui_DW.theta0[2] = 500.0F;
    mod_foggui_DW.ang13_ = 0.0F;
    mod_foggui_DW.ang24_ = 0.0F;
    mod_foggui_DW.flag_wx = 0;
    mod_foggui_DW.flag_gui_lat = 0;
    mod_foggui_DW.flag_gui_lon = 0;
    mod_foggui_DW.y_ = -999.0F;
    for (i = 0; i < 10; i++) {
      mod_foggui_DW.x_bio4k4d4zb[i] = -7.09F;
    }

    mod_foggui_DW.moduloERRO_ = -999.0F;
    std::memset(&mod_foggui_DW.vetorPOS[0], 0, 20U * sizeof(real32_T));
    for (i = 0; i < 10; i++) {
      mod_foggui_DW.x[i] = -7.09F;
    }

    for (i = 0; i < 6; i++) {
      mod_foggui_DW.lista_circular[i] = 0.0F;
    }

    mod_foggui_DW.mantem_ejecao = false;
  }
}

void mod_fogguiModelClass::terminate()
{
  {
    SimStruct *rts = (&mod_foggui_M)->childSfunctions[0];
    sfcnTerminate(rts);
  }
}

mod_fogguiModelClass::mod_fogguiModelClass() : mod_foggui_M()
{
}

mod_fogguiModelClass::~mod_fogguiModelClass()
{
}

RT_MODEL_mod_foggui_T * mod_fogguiModelClass::getRTM()
{
  return (&mod_foggui_M);
}
