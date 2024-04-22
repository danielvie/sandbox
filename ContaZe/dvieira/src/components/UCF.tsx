import React, {useState} from 'react'
import {Style} from './styles/Styles'
import { Form } from 'react-bootstrap'
import { Input1x } from './inputs/Input1x';
import { Input2x } from './inputs/Input2x';

import * as calc from "../utils/calc";
import { ButtonOk } from "./ButtonOk";
import { Resposta } from "./Resposta";

export default function UCF(props:any){
	
	const [titulo, setTitulo] = useState('');
	const [ALVO1, setALVO1] = useState('');
	const [ALVO2, setALVO2] = useState('');
	const [LMU1, setLMU1] = useState('');
	const [LMU2, setLMU2] = useState('');
	const [UCF1, setUCF1] = useState('');
	const [UCF2, setUCF2] = useState('');
	const [DIST, setDIST] = useState('');
	const [ANG, setANG] = useState('');
	const [resposta, setResposta] = useState(<Resposta></Resposta>);
	
	const preencherUCF = () => {
		setTitulo('Titulo UCF')
		setALVO1('263769')
		setALVO2('8246145')
		setLMU1('273820')
		setLMU2('8284209')
		setUCF1('')
		setUCF2('')
		setDIST('217')
		setANG('5.5')
	}
	
	const clearUCF = () => {
		setTitulo('')
		setALVO1('')
		setALVO2('')
		setLMU1('')
		setLMU2('')
		setUCF1('')
		setUCF2('')
		setDIST('')
		setANG('')
	}

	const submit = () => {

		const lmu:number[]  = [LMU1, LMU2].map(parseFloat)
		const alvo:number[] = [ALVO1, ALVO2].map(parseFloat)
		const dist = parseFloat(DIST)
		const ang  = parseFloat(ANG)
		const angmils = ang/0.05625

		const alc  = calc.calcula_distancia(lmu, alvo).toFixed(2);
		const dgt  = calc.calcula_azi_mils(lmu, alvo);
		const ucf_ = calc.calcula_alvo(lmu, dist, angmils + dgt + 3200.).map((v) => v.toFixed(0))

		const dgtdeg = dgt*0.05625;
		const resposta = <Resposta clickClear={setResposta}>
			<p><span>{titulo}</span></p>
			<p>Alcance (m) : <span>{alc} m</span></p>
			<p>DGT ........: <span>{dgt.toFixed(1)} mils ({dgtdeg.toFixed(1)} deg)</span></p>
			<p>UCF ........: <span>{ucf_[0]}, {ucf_[1]} m</span></p>
		</Resposta>

		setUCF1(ucf_[0])
		setUCF2(ucf_[1])
		setResposta(resposta)
	}

	const submit2 = () => {

		const lmu  = [LMU1, LMU2].map((v) => parseFloat(v) || 0.)
		const alvo = [ALVO1, ALVO2].map((v) => parseFloat(v) || 0.)
		const ucf  = [UCF1, UCF2].map((v) => parseFloat(v) || 0.)
		
		const alc  = calc.calcula_distancia(lmu, alvo).toFixed(2);
		const dgt  = calc.calcula_azi_mils(lmu, alvo);
		
		const ang_ucf  = calc.calcula_azi_deg(lmu, ucf)
		const ang_alvo = dgt*0.05625

		const dist = calc.calcula_distancia(lmu, ucf).toFixed(1)
		const ang  = (ang_ucf + 180. - ang_alvo).toFixed(1)

		const dgtdeg = dgt*0.05625;
		const resposta = <Resposta clickClear={setResposta}>
			<p>{titulo}</p>
			<p>Alcance (m) .: <span>{alc} m</span></p>
			<p>Distancia (m): <span>{dist} m</span></p>
			<p>Angulo (deg) : <span>{ang} deg</span></p>
			<p>DGT .........: <span>{dgt.toFixed(2)} mils ({dgtdeg.toFixed(1)} deg)</span></p>
		</Resposta>

		setDIST(dist)
		setANG(ang)
		setResposta(resposta)
	}

	return (
		<Style>
			<p className='titulo'>UCF</p>
			<Form>
				<hr className='titulo'/>
				
				<Input1x className="input-linha" name='titulo' label='TITULO' value={titulo} setter={setTitulo}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='ALVO'     type="number" labels={['ALVO E', 'ALVO N']} values={[ALVO1, ALVO2]}    setters={[setALVO1, setALVO2]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='LMU'      type="number" labels={['LMU E', 'LMU N']} values={[LMU1, LMU2]}     setters={[setLMU1, setLMU2]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='UCF'      type="number" labels={['UCF E', 'UCF N']} values={[UCF1, UCF2]}     setters={[setUCF1, setUCF2]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='DIST_ANG' type="number" labels={['DIST. (m)', 'ANG. (deg)']} values={[DIST, ANG]} setters={[setDIST, setANG]}/>
				
				<ButtonOk label='UCF' clickList={preencherUCF} clickClear={clearUCF} clickSubmit={submit} 
										   label2='ANG' clickSubmit2={submit2}/>

			</Form>
			<hr className='fim'/>
			{resposta}
		
		</Style>
		)
	}