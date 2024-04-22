import React, { useState } from 'react'

import * as calc from "../utils/calc";
import { Input1x } from "./inputs/Input1x";
import { Input2x } from "./inputs/Input2x";
import { Resposta } from './Resposta'
import { ButtonOk } from './ButtonOk'

export const UtilsCalculoDesvios = (props:any) => {

	const [titulo, setTitulo]       = useState("");
	const [LMU_e, setLMU_e]         = useState('');
	const [LMU_n, setLMU_n]         = useState('');
	const [alvo_e, setAlvo_e]       = useState('');
	const [alvo_n, setAlvo_n]       = useState('');
	const [impacto_e, setImpacto_e] = useState('');
	const [impacto_n, setImpacto_n] = useState('');
	const [resposta, setResposta] = useState(<Resposta></Resposta>)

    const submit = () => {
		const lmu     = [parseFloat(LMU_e), parseFloat(LMU_n)]
		const alvo    = [parseFloat(alvo_e), parseFloat(alvo_n)]
		const impacto = [parseFloat(impacto_e), parseFloat(impacto_n)]

		// calculando dgt
		const dgt  = calc.calcula_azi_mils(lmu, alvo)
		const dist_a = calc.calcula_distancia(lmu, alvo)
		const dist_i = calc.calcula_distancia(lmu, impacto)
		const desvio = calc.calcula_desvios(lmu, alvo, impacto)
		const dalc   = parseFloat(desvio.alcance)
		const dlat   = parseFloat(desvio.lateral)
		const dtot   = parseFloat(desvio.total)
		
		// gerando resposta
		const res  = <Resposta clickClear={setResposta}>
						<p><label className="font-weight-bold">dgt ......[mils]:</label> {dgt.toFixed(2)}</p>
						<p><label className="font-weight-bold">dist impacto.[m]:</label> {dist_i.toFixed(2)}</p>
						<p><label className="font-weight-bold">dist alvo ...[m]:</label> {dist_a.toFixed(2)}</p>
						<p><label className="font-weight-bold">desvio alc ..[m]:</label> {dalc.toFixed(2)}</p>
						<p><label className="font-weight-bold">desvio lat ..[m]:</label> {dlat.toFixed(2)}</p>
						<p><label className="font-weight-bold">desvio tot ..[m]:</label> {dtot.toFixed(2)}</p>
					</Resposta>

		// gravando resposta na div de resposta
		setResposta(res);
    }

    const populateAlvo = () => {
		setTitulo('Alvo teste');
		setLMU_e('352740');
		setLMU_n('9138738');
		setAlvo_e('359592');
		setAlvo_n('9069052');
		setImpacto_e('363603');
		setImpacto_n('9070070');
	}

	const clearAlvo = () => {
		setTitulo('');
		setLMU_e('');
		setLMU_n('');
		setAlvo_e('');
		setAlvo_n('');
		setImpacto_e('');
		setImpacto_n('');
	}

    return (
        <div>
            <p className="titulo-2">CALCULO DESVIOS</p>
				
				<Input1x name='alvo-titulo' label='titulo' value={titulo} setter={setTitulo}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} name='origem' labels={['LMU E', 'LMU N']} type="number" values={[LMU_e, LMU_n]} setters={[setLMU_e,setLMU_n]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} name='alvo' labels={['ALVO E', 'ALVO N']} type="number" values={[alvo_e, alvo_n]} setters={[setAlvo_e, setAlvo_n]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} name='fim' labels={['IMPACTO E', 'IMPACTO N']} type="number" values={[impacto_e, impacto_n]} setters={[setImpacto_e, setImpacto_n]}/>

				<ButtonOk label='CALCULAR DESVIO' clickSubmit={submit} clickList={populateAlvo} clickClear={clearAlvo}/>
				{resposta}
        </div>
    )
}
