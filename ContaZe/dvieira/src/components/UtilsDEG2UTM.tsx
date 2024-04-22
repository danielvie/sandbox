import React, { useState } from 'react'

import * as calc from '../utils/calc'
import { Input2x } from "./inputs/Input2x";
import { Resposta } from './Resposta'
import { ButtonOk } from './ButtonOk'

export const UtilsDEG2UTM = (props:any) => {

	const [coord1, setCoord1] = useState('');
	const [coord2, setCoord2] = useState('');
    const [resposta, setResposta] = useState(<Resposta></Resposta>);

	const submit = () => {
		// lendo valores
		console.log([coord1, coord2])
		
		const coord = [coord1, coord2].map((c) => 
		{
			let cc = -1.;
			const cs = c.split(',')
			if (cs.length === 1) {
				cc = parseFloat(c)
			}
			else if (cs.length === 3) {
				cc = Math.abs(parseFloat(cs[0])) + parseFloat(cs[1])/60 + parseFloat(cs[2].replace(/[^\d.]/g, ''))/60/60
				
				if (cs[2].match(/[SW]/g) || (parseFloat(cs[0]) < 0.)) {
					cc = -cc
				}
			}
			else {
				console.log('ERRO, coordenada nao valida!!!')
			}
			
			return cc
		})

		let res = ['', '']
		let unit = ['m', 'deg']

		// calculando DEG -> UTM
		let aux = calc.deg2utm(coord[0], coord[1])
		res = aux.en.map((v:number) => v.toFixed(1))

		// ajustes nos campos de zona e unidade
		// setZona(aux.zona.toFixed(0))
		// setHemis(aux.hemis)
		const zona_  = aux.zona;
		const hemis_ = aux.hemis
		unit   = ['deg', 'm']

		const resposta = <Resposta clickClear={setResposta}>
			<p><span>Conversao:</span></p>
			<p>COORD ORIG: {coord[0].toFixed(7)}, {coord[1].toFixed(7)} {unit[0]}</p>
			<p>COORD CALC: {res[0]}, {res[1]} {unit[1]}</p>
			<p>ZONA: <span>{zona_} {hemis_}</span></p>
		</Resposta>
			
		setResposta(resposta);
	}

	const exemplo = () => {
		setCoord1('-15, 34, 31.12346');
		setCoord2('47, 18, 02.17671 W');
	}

	const limpaCampos = () => {
		setCoord1('');
		setCoord2('');
	}


    return (
        <div>
            <p className="titulo-2">DEG -> UTM</p>
            <Input2x memory={props.memory} setMemory={props.setMemory} name="UTM" labels={['COORD 1', 'COORD 2']} type="text" values={[coord1, coord2]} setters={[setCoord1, setCoord2]}/>

            <ButtonOk clickClear={limpaCampos} clickList={exemplo} clickSubmit={submit}>CONVERTER</ButtonOk>
            {resposta}
        </div>
    )
}
