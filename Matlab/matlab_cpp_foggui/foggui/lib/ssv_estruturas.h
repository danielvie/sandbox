/*
 * ssv_estruturas.h
 *
 *  Created on: 9 de ago de 2017
 *      Author: dvieira
 */

#ifndef SRC_SSV_ESTRUTURAS_H_
#define SRC_SSV_ESTRUTURAS_H_

typedef struct {
	int flag_ejecao;
	float ax[6];
	float ay[6];
	float az[6];
	float vx[3];
	float vy[3];
	float vz[3];
	float altitude[3];
	float altitude_alvo;
	float perc_gps;
	float tempo;
	unsigned int fom[3];
} ssv_step_in_fg;

typedef struct {
	int flag_ejecao;
	float ax;
	float ay;
	float az;
	float vx;
	float vy;
	float vz;
	float altitude;
	float altitude_alvo;
	float perc_gps;
	float tempo;
	unsigned int fom;
} ssv_step_fg;

#endif /* SRC_SSV_ESTRUTURAS_H_ */
