import React, { useState } from 'react'

import * as calc from "../utils/calc";
import { Input1x } from "./inputs/Input1x";
import { Resposta } from './Resposta'
import { ButtonOk } from './ButtonOk'

export const UtilsAtmosISA = () => {

    const [altitude, setAltitude] = useState('0')
    const [resposta, setResposta] = useState(<Resposta></Resposta>)
    
    const submitAtmosISA = () => {
		const h = parseFloat(altitude) || 0.
		const atmos = calc.atmos_isa(h);

		const temp = (atmos.temp - 273.15).toFixed(2)
		const pres = (atmos.pressao/100.).toFixed(2)
		
		const res = <Resposta clickClear={setResposta}>
			<p>Altitude ..: <span>{h.toFixed(2)} m</span></p>
			<p>Temperatura: <span>{temp} C</span></p>
			<p>Pressao ...: <span>{pres} mBar</span></p>
			<p>Rho .......: <span>{atmos.rho.toFixed(2)} kg/m3</span></p>
			<p>Vel. Som ..: <span>{atmos.vsom.toFixed(2)} m/s</span></p>
		</Resposta>

		setResposta(res);
    }
    
    return (
        <div>
          <p className="titulo-2">ATMOS ISA</p>
				<Input1x name="atmosISA" label="AtmosISA" type="number" value={altitude} setter={setAltitude}/>
				<ButtonOk label='ATMOS ISA' clickSubmit={submitAtmosISA}/>
				{resposta}  
        </div>
    )
}
