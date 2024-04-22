import React  from 'react'
import { Form } from 'react-bootstrap'

import { UtilsMET } from './UtilsMET';
import { UtilsUTM2DEG } from "./UtilsUTM2DEG";
import { UtilsDEG2UTM } from "./UtilsDEG2UTM";
import { UtilsAtmosISA } from "./UtilsAtmosISA";
import { UtilsCalculoAlvo } from "./UtilsCalculoAlvo";
import { UtilsCalculoDesvios } from "./UtilsCalculoDesvios";

import { Style } from './styles/Styles'

export default function Utils(props:any) {
	
	return (
		<Style>
			
			<p className="titulo">UTILS</p>
			<hr className='titulo'/>

			<Form>
				<UtilsMET/>

				<UtilsUTM2DEG memory={props.memory} setMemory={props.setMemory}/>
				
				<UtilsDEG2UTM memory={props.memory} setMemory={props.setMemory}/>

				<UtilsAtmosISA/>
				
				<UtilsCalculoAlvo memory={props.memory} setMemory={props.setMemory}/>

				<UtilsCalculoDesvios memory={props.memory} setMemory={props.setMemory}/>

			</Form>

		</Style>
	)
}
