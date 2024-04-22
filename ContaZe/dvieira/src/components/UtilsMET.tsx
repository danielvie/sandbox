import React, { useState } from 'react'

import { Input1x } from "./inputs/Input1x";
import { Resposta } from './Resposta'
import { ButtonOk } from './ButtonOk'

export const UtilsMET = () => {

    const [altitude, setAltitude] = useState('3800')
    const [resposta, setResposta] = useState(<Resposta></Resposta>)

    const submitMet = () => {
        let camadas = [
            0     , 200   , 500   , 1000  , 1500  , 2000  , 2500  , 3000  , 3500  ,
            4000  , 4500  , 5000  , 6000  , 7000  , 8000  , 9000  , 10000 , 11000 ,
            12000 , 13000 ,14000  , 15000 , 16000 , 17000 , 18000 , 19000 , 20000 ,
            21000 , 22000 , 23000 , 24000 , 25000 , 26000 , 27000 , 28000 , 29000 ,
            30000 , 31000 , 32000 , 33000 , 34000
        ]
        
		const h = parseFloat(altitude) || 0.
		const cam_nro = camadas.filter((v)=> {return v <= h}).length
        let cam_txt = []

        let ii
        for (let i = 0; i < cam_nro; i++) {
            ii = i + 1
            if (ii < 10)
                ii = '0' + ii
            
            cam_txt.push(<p key={i}>{ii}: {camadas[i]} - {camadas[i+1]}</p>)
        }
        
        let resposta = (
            <Resposta clickClear={setResposta}>
                <p className='font-weight-bold'>Nro de camadas: {cam_nro}</p>
                {cam_txt}
            </Resposta>
        );
		
		setResposta(resposta)
	}

    return (
        <div>
            <p className="titulo-2 mt-0">MET</p>
            <Input1x name="altitude" label="Altitude" type="number" value={altitude} setter={setAltitude}/>
        
            <ButtonOk label='NRO CAMADAS' clickSubmit={submitMet}/>
            {resposta}
            
        </div>
    )
}
