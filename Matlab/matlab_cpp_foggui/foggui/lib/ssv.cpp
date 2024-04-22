/* 
 *  ssv.cpp
 * 
 *  Software de Supervisao de Voo
 * 
 *   Created on: 18 de out de 2016
 *       Author: dvieira
 *       Version: 1
 * 
 *   Verified on: 10 de nov de 2016
 *       Rev.: ujsouza
 *       Static A. JSF (rev 1.0-2016)
 */

#include "ssv.h"

#ifndef isNotaNumber
#define isNotaNumber(x) ((x)!=(x))
#endif

/*  CONSTRUCTOR
 *  Construtor do SSV (Software de Supervisao de Voo)
 * 
 *  SINTAXE:
 * 
 *  ssv o(const unsigned int tam_janela, const float referencia_G);
 * 
 *  em que,
 *  -> tam_janela define o numero de elementos da lista circular usada para fazer
 *  a janela movel de dados
 * 
 *  -> referencia_G define o valor de referencia que, quando ultrapassado aciona a
 *  flag de indicacao de Voo
 *  ex.: se o referencia_G for "3" o voo sera considerado como iniciado quando o
 *  valor da integral da janela de aceleracoes for superior a 3 vezes seu valor
 *  nominal
 *
 */
ssv::ssv(const unsigned int tam_janela, const float referencia_G):
							dt(const_dt),
							nivel_dc(const_G * const_dt * (float)tam_janela),
							referencia_G(referencia_G),
							num_ciclos_ejecao(0.0F),
							num_ciclos_gps_ok(0.0F),
							fg_tempo_timeout(0.0F),
							tempo(0.0F),
							flag_voo(0U),
							flag_fim_de_queima(0U),
							fg_canard_on(0U),
							fg_tempo_ejecao(0U),
							fg_flag_sb(0U),
							fg_timeout(0U){

	// inicializando tamanho do vetor de mediana
    unsigned int tam_medfilt = 5U;

	// inicializando vetor janela
	this->acel.assign(tam_janela,const_G);

	// inicializando vetor de filtro de mediana
	this->acel_mediana.assign(tam_medfilt,const_G);

}

// DESTRUCTOR
ssv::~ssv() {

}

/* METODO:step
*  Metodo chamado a cada passo com os parametros de entrada
*  no formato da estrutura 'mgv_step_in' para fazer os calculos
*  do gerenciador de voo e atualizar as propriedades do objeto.
*
*  SINTAXE:
*  void ssv::step(mgv_step_in step_in)
*
*     em que step_in eh uma estrutura do tipo mgv_step com as medidas
*     atuais.
*
*/

void ssv::step(ssv_step_in_fg step_in) {
	// declarando variaveis auxiliares
	float area     = 0.0F;
	float area_ref = 0.0F;
    unsigned int c1 = 0U;
    unsigned int c2 = 0U;
    unsigned int c3 = 0U;
    unsigned int c4 = 0U;

    // declarando variaveis
    float percentual_gps = 1.0F;
	ssv_step_fg step_fg;

    // constantes
    const float Delta_T = 0.02F;

	step_fg = this->getStep(step_in);

	// testando valores nan ou infinite
	// usar valor de gravidade no lugar de um numero invalido
	if((int)isNotaNumber(step_fg.ax) || (int)isNotaNumber(step_fg.ay) || (int)isNotaNumber(step_fg.az)) {
		step_fg.ax = const_G;
		step_fg.ay = 0.0F;
		step_fg.az = 0.0F;
	}

	// filtro de mediana
	this->acel_mediana[0] = step_fg.ax;
	std::rotate(this->acel_mediana.begin(),this->acel_mediana.begin()+1,this->acel_mediana.end());

	// inserindo valores na janela
	this->acel[0] = this->medfilt(&this->acel_mediana);
	std::rotate(this->acel.begin(),this->acel.begin()+1,this->acel.end());

	// atualizando flag_voo
	area     = this->trapz();
	area_ref = this->referencia_G*this->nivel_dc;

	if ((area > area_ref) && (this->flag_voo == 0U)) {
		this->flag_voo = 1U;
	}

	// atualizando flag_fim_de_voo
	// a ideia aqui eh de passar a flag para positivo quando, apos a flag_voo ter sido levantada
	// a integral das medidas cruza o valor de 95% da referencia de voo
	if ((this->flag_voo == 1U) && (area < area_ref*0.99)){
		this->flag_fim_de_queima = 1U;
	}

	// INICIO DO CANARD, REAVALIAR CRITERIOS
    c1 = (this->flag_fim_de_queima == 1U); // booster terminou de queimar
    c2 = (step_fg.tempo > 10.0); // tempo do CDB maior que 10 segundos
    c3 = (this->fg_canard_on == 0U); // canard nao foi iniciado ainda

    if (c1 && c2 && c3) {
        this->fg_canard_on = 1U;
    }
	
    // ESSA FLAG ACOMPANHA O ACIONAMENTO DE ABERTURA DO CANARD.
    c1 = (this->fg_canard_on == 1U); // comandado a abertura do canard
    c2 = ((step_in.altitude[2] - step_in.altitude_alvo)<=3000.0F); // foguete estah a menos de 3000m acima do alvo
    c3 = (step_in.vz[2U] > 0.0F); // velocidade vz estah indicando voo na descendente
    c4 = (percentual_gps > step_in.perc_gps); // percentual de GPS, por seguranca, deve ser maior que ganho 5 (0.9 == 90%)

    if (c1 && c2 && c3 && c4){
        this->fg_flag_sb = 1;
    }

    // guardando tempo de ejecao
    c1 = (step_in.flag_ejecao > 0);
    c2 = (this->fg_canard_on != 2U);

    if (c1 && c2) {
        // ejetou, para de mexer canard e guarda o tempo.
        this->fg_canard_on = 2U;
        this->fg_tempo_ejecao = (unsigned int)(floor(this->tempo*100.0F));
    }

    // LOGICA DE TIMEOUT
    c1 = (step_fg.fom <= 8U); // se o inercial entrou em modo de voo
    c2 = (this->fg_tempo_timeout >= 0.0F); // tempo de timeout deve ser positivo

    if (c1 && c2) {
    	if (this->flag_voo == 0U) {
    		// se o voo nao foi detectado, incrementar tempo
    		this->fg_tempo_timeout += Delta_T;

    		// se o tempo chegar a 5 segundos, indicar o timeout
    		if (this->fg_tempo_timeout > TIMEOUT_TEMPO) {
    			this->fg_timeout = 1U;
    			this->fg_tempo_timeout = TIMEOUT_OFF;
    		}
    	}
    }

    // reset do tempo caso o sistema volte a estacionario
    c1 = (step_fg.fom == 9U);
    c2 = (this->fg_tempo_timeout >= 0.0F); // tempo de timeout deve ser positivo

    if (c1 && c2) {
    	this->fg_tempo_timeout = 0.0F;
    }
    
    // INCREMENTANDO TEMPO
    this->tempo = this->tempo + Delta_T;
}

ssv_step_fg ssv::getStep(ssv_step_in_fg step_in) {
	ssv_step_fg step_fg;

	step_fg.flag_ejecao   = step_in.flag_ejecao;
	step_fg.ax            = step_in.ax[5];
	step_fg.ay            = step_in.ay[5];
	step_fg.az            = step_in.az[5];
	step_fg.vx            = step_in.vx[2];
	step_fg.vy            = step_in.vy[2];
	step_fg.vz            = step_in.vz[2];
	step_fg.altitude      = step_in.altitude[2];
	step_fg.altitude_alvo = step_in.altitude_alvo;
	step_fg.perc_gps      = step_in.perc_gps;
	step_fg.tempo         = step_in.tempo;
	step_fg.fom           = step_in.fom[2];

	return step_fg;
}

/* METODO:reset
*  Metodo que zera restaura o objeto para a condicao inicial.
*
*  SINTAXE:
*  void ssv::reset()
*
*/

void ssv::reset(void) {
	std::vector<float>::iterator v;

	// zerando flag_voo
	this->flag_voo = 0U;

	// zerando vetores janela
	for (v = this->acel.begin(); v != this->acel.end(); v++) {
		*v = 0.0F;
	}

	// zerando vetores mediana
	for (v = this->acel_mediana.begin(); v != this->acel_mediana.end(); v++) {
		*v = 0.0F;
	}

}

/* METODO:getAreaRef
*  Metodo que calcula a area de referencia para comparacao com a integral das medidas
*
*  SINTAXE:
*  float ssv::get_area_ref()
*
*     o retorno da funcao eh o valor de referencia da integral
*
*/

float ssv::getAreaRef(void){
	float area_ref = this->referencia_G*this->nivel_dc;
	return area_ref;
}

/* METODO:trapz
*  Metodo que calcula a integral do vetor ssv->vetor_janela
*
*  SINTAXE:
*  float ssv::trapz()
*
*     o retorno da funcao eh o valor da integral
*
*/

float ssv::trapz(void){
	std::vector<float>::iterator v;
	float soma  = 0.0F;

	// caso com apenas um ponto
	if (this->acel.size() < 2.0F) {
		return 0.0F;
	}

	// calculando area trapezio
	for (v = this->acel.begin() + 1.0F; v != this->acel.end(); v++) {
		soma += (*(v-1) + *v);
	}
	soma *= this->dt/2.0F;

	return soma;
}

/* METODO:moduloMedidas
*  Metodo auxiliar que calcula o modulo de tres numeros
*
*  SINTAXE:
*  float ssv::modulo_medidas(float x, float y, float z)
*
*     em que x, y e z sao os paramatros de entrada e o retorno
*     eh o resultado de sqrt(x*x + y*y + z*z)
*
*/

float ssv::moduloMedidas(const float x,const float y,const float z) {
	float res = sqrt(x*x + y*y + z*z);
	return res;
}

/* METODO:medfilt
*  Metodo auxiliar que calcula a mediana dos elementos do vetor
*  ssv->vetor_mediana
*
*  SINTAXE:
*  float ssv::medfilt()
*
*/

float ssv::medfilt(std::vector<float> *vetor) {
	std::vector<float> v = *vetor;
	float mediana = 0.0F;
	float aux = 0.0F;
	unsigned int indice  = 0U;
	unsigned int indice2 = 0U;
	unsigned int tam = v.size();

	// ordenando vetor
	std::sort(v.begin(),v.end());

	// calculando mediana
	if(((int)tam % 2) == 1) { // impar
		aux     = floor(((float)tam + 1.0F) / 2.0F - 1.0F);
		indice  = (unsigned int) aux;
		mediana = v[indice];
	}
	else { // par
		aux     = floor((float)tam / 2.0F - 1.0F);
		indice  = (unsigned int) aux;
		indice2 = (unsigned int) ((int)indice + 1);
		mediana = (v[indice] + v[indice2])/2;
	}
	return mediana;
}

/* METODO:getMediana
*  Metodo auxiliar que calcula a mediana dos elementos do vetor
*  ssv->vetor_mediana
*
*  SINTAXE:
*  float ssv::medfilt()
*
*/

float ssv::getMediana(void) {
	float mediana = this->medfilt(&this->acel_mediana);
	return mediana;
}

/* METODO:minimo
*  Metodo auxiliar que calcula o valor minimo de um vetor
*  ssv->minimo(vetor)
*
*
*/

float ssv::minimo(std::vector<float> *vetor) {
	std::vector<float>::iterator v;

	float min = (*vetor)[0];
	for(v = (*vetor).begin() + 1.0; v != (*vetor).end(); v++) {
		if (min > *v ) {
			min = *v;
		}

	}
	return min;
}

/* METODO:maximo
*  Metodo auxiliar que calcula o valor maximo de um vetor
*  ssv->maximo(vetor)
*
*  SINTAXE:
*  float ssv::medfilt()
*
*/

float ssv::maximo(std::vector<float> *vetor) {
	std::vector<float>::iterator v;

	float max = (*vetor)[0];
	for(v = (*vetor).begin() + 1.0; v != (*vetor).end(); v++) {
		if (max < *v ) {
			max = *v;
		}

	}
	return max;
}

/* METODO:printVetorMedidas
*  Metodo auxiliar que imprime vetor de medidas
*
*  SINTAXE:
*  float ssv::printVetorMedidas(void)
*
*/

void ssv::printVetorMedidas(void) {
	std::vector<float>::iterator v;

	for(v = this->acel.begin(); v != this->acel.end(); v++) {
		std::cout << *v << " ";
	}
	std::cout << "\n";
}
