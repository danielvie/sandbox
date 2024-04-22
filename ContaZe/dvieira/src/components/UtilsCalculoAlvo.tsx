import React, { useState } from 'react'

import * as calc from "../utils/calc";
import { Input1x } from "./inputs/Input1x";
import { Input2x } from "./inputs/Input2x";
import { Resposta } from './Resposta'
import { ButtonOk } from './ButtonOk'

export const UtilsCalculoAlvo = (props:any) => {

	const [alvoTitulo, setAlvoTitulo]     = useState("");
	const [alvoLMUe, setAlvoLMUe]         = useState('');
	const [alvoLMUn, setAlvoLMUn]         = useState('');
	const [alvoDist, setAlvoDist]         = useState('');
	const [alvoAzi,  setAlvoAzi]          = useState('');
    const [resposta, setResposta] = useState(<Resposta></Resposta>)

    const submit = () => {
		// calculando alvo
		const alvo = calc.calcula_alvo([parseFloat(alvoLMUe), parseFloat(alvoLMUn)], parseFloat(alvoDist), parseFloat(alvoAzi));
		
		// gerando resposta
		const res  = <Resposta clickClear={setResposta}>
						<p>POSICAO ALVO:</p>
						<p className="font-weight-bold">{alvo[0].toFixed(1)}, {alvo[1].toFixed(1)}</p>
					</Resposta>

		// gravando resposta na div de resposta
		setResposta(res);
    }

    const populateAlvo = () => {
		setAlvoTitulo('Alvo teste');
		setAlvoLMUe('352731');
		setAlvoLMUn('9138715');
		setAlvoDist('70000');
		setAlvoAzi('3100');
	}

	const clearAlvo = () => {
		setAlvoTitulo('');
		setAlvoLMUe('');
		setAlvoLMUn('');
		setAlvoDist('');
		setAlvoAzi('');
	}

    return (
        <div>
            <p className="titulo-2">CALCULO ALVO</p>
				
				<Input1x name='alvo-titulo' label='Titulo' value={alvoTitulo} setter={setAlvoTitulo}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} name='alvo-lmu' labels={['LMU E', 'LMU N']} type="number" values={[alvoLMUe,alvoLMUn]} setters={[setAlvoLMUe,setAlvoLMUn]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} name='alvo-dist' labels={['DIST', 'AZI']} type="number" values={[alvoDist, alvoAzi]} setters={[setAlvoDist,setAlvoAzi]}/>

				<ButtonOk label='GERAR ALVO' clickSubmit={submit} clickList={populateAlvo} clickClear={clearAlvo}/>
				{resposta}
        </div>
    )
}
