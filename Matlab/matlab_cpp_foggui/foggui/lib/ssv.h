/*
 *  ssv.h
 *
 *  Created on: 18 de out de 2016
 *      Author: dvieira
 *      Version: 1
 */

#ifndef SRC_MDV_H_
#define SRC_MDV_H_

#include <algorithm>
#include <vector>
#include <iostream>
#include <math.h>
#include "ssv_estruturas.h"

const float const_G  = 9.80665F;
const float const_dt = 0.0033F;
const float TIMEOUT_TEMPO = 5.0F;
const float TIMEOUT_OFF   = -10.0F;

class ssv{
	float dt;
	float nivel_dc;
	float referencia_G;
	std::vector<float> acel; // acelerometros
	std::vector<float> acel_mediana; // mediana acelerometros

private:
	float num_ciclos_ejecao;
	float num_ciclos_gps_ok;
	float fg_tempo_timeout;
	ssv_step_fg getStep(ssv_step_in_fg step_in);

public:
	float tempo;
	unsigned int flag_voo;
	unsigned int flag_fim_de_queima;
	unsigned int fg_canard_on;
	unsigned int fg_tempo_ejecao;
	unsigned int fg_flag_sb; // flag de submunicao
	unsigned int fg_timeout; // flag de submunicao

	ssv(const unsigned int tam_janela, const float referencia_G);
	~ssv();
	void step(ssv_step_in_fg step_in);
	void reset(void);
	float getAreaRef(void);
	float trapz(void);
	float moduloMedidas(float x, float y, float z);
	float medfilt(std::vector<float> *vetor);
	float getMediana(void);
	float minimo(std::vector<float> *vetor);
	float maximo(std::vector<float> *vetor);
	void printVetorMedidas(void);
};

#endif /* SRC_MDV_H_ */
