import React, { useState } from 'react'

import * as calc from '../utils/calc'
import { Input2x } from "./inputs/Input2x";
import { Input1x } from "./inputs/Input1x";
import { Resposta } from './Resposta'
import { ButtonOk } from './ButtonOk'
import { Form, Col, Row } from 'react-bootstrap'

export const UtilsUTM2DEG = (props:any) => {

	const [coord1, setCoord1] = useState('');
	const [coord2, setCoord2] = useState('');
	const [zona, setZona] = useState('23');
    const [hemis, setHemis] = useState('S');
    const [resposta, setResposta] = useState(<Resposta></Resposta>);

	const submit = () => {
		// lendo valores
		const coord = [coord1, coord2].map((v) => parseFloat(v) || 0.)
		let zona_ = parseInt(zona)
		let hemis_ = hemis;

		let res = ['', '']
		let unit = ['m', 'deg']

		if (coord[0] > 1000. || coord[1] > 1000) {
			// calculando UTM -> DEG
			let aux = calc.utm2deg(coord[0], coord[1], zona_, hemis)
			res = aux.map((v) => v.toFixed(7))
		} else {
			// calculando DEG -> UTM
			let aux = calc.deg2utm(coord[0], coord[1])
			res = aux.en.map((v:number) => v.toFixed(0))

			// ajustes nos campos de zona e unidade
			// setZona(aux.zona.toFixed(0))
			// setHemis(aux.hemis)
			zona_  = aux.zona;
			hemis_ = aux.hemis
			unit   = ['deg', 'm']
		}

		const resposta = <Resposta clickClear={setResposta}>
			<p><span>Conversao:</span></p>
			<p>COORD ORIG: {coord[0]}, {coord[1]} {unit[0]}</p>
			<p>COORD CALC: {res[0]}, {res[1]} {unit[1]}</p>
			<p>ZONA: <span>{zona_} {hemis_}</span></p>
		</Resposta>
			
		setResposta(resposta);
	}

	const exemplo = () => {
		setCoord1('259747');
		setCoord2('8273489');
		setZona('23');
		setHemis('S');
	}

	const limpaCampos = () => {
		setCoord1('');
		setCoord2('');
		setZona('');
		setHemis('');
	}


	const teste = (e:string) => {
		setHemis(e)
	}

    return (
        <div>
            <p className="titulo-2">UTM -> DEG</p>
            <Input2x memory={props.memory} setMemory={props.setMemory} name="UTM" labels={['COORD 1', 'COORD 2']} type="number" values={[coord1, coord2]} setters={[setCoord1, setCoord2]}/>
            
			<Row className="input-multi mt-1">
                <Col xs="4" className="pr-1">
                    <Input1x className={props.className} label="Zona" type="number" value={zona} setter={setZona}/>
                </Col>

                <Form.Group as={Row} className="">
					<Form.Label as="legend" column sm={2}>
					</Form.Label>
					<Col sm={10} className="ft-monospace ft-16">
						<Form.Check
							type="radio"
							label="Hemisf. S."
							name="formHorizontalRadios"
							id="formHorizontalRadios1"
							checked={(hemis === "S")}
							onChange={() => teste("S")}
							/>
						<Form.Check
							className="mt-1"
							type="radio"
							label="Hemisf. N."
							name="formHorizontalRadios"
							id="formHorizontalRadios2"
							checked={(hemis === "N")}
							onChange={() => teste("N")}
						/>
					</Col>
				</Form.Group>

				<Col xs="1">
				</Col>

            </Row>

            <ButtonOk clickClear={limpaCampos} clickList={exemplo} clickSubmit={submit}>CONVERTER</ButtonOk>
            {resposta}
        </div>
    )
}
