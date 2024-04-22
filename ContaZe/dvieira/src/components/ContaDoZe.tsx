import React, { useEffect, useState } from 'react'
import { Style } from './styles/Styles'
import { Form, Button } from 'react-bootstrap'
import { Input1x } from './inputs/Input1x';
import { Input2x } from './inputs/Input2x';

import { FaRecycle } from 'react-icons/fa'

import {ButtonOk} from './ButtonOk'
import {Resposta} from './Resposta'

import { DadosZe } from "./DadosZe";

import { WHURL } from "./WHURL";

import db from "../utils/db";

import * as calc from "../utils/calc";
import { getHora } from "../utils/utils";

import axios from 'axios';

const TABLE:string = 'dados_contaze';

export default function ContaDoZe(props:any) {
	const [titulo, setTitulo] = useState('');
	const [tituloLMU, setTituloLMU] = useState('');
	const [LMU1, setLMU1] = useState('');
	const [LMU2, setLMU2] = useState('');
	const [REF1, setREF1] = useState('');
	const [REF2, setREF2] = useState('');
	const [ALVO1, setALVO1] = useState('');
	const [ALVO2, setALVO2] = useState('');
	const [AO, setAO] = useState('');
	const [heading, setHeading] = useState('');
	const [resposta, setResposta] = useState(<Resposta></Resposta>);
		
	const [dados, setDados] = useState<any>([])

	const setDataFromDB = () => {
		db.table(TABLE)
			.toArray()
			.then((dados) => {
				setDados(dados)
			})
	}

	useEffect(() => {
		setDataFromDB();
	}, [])

	const getConfig = () => {
		const config = {
			titulo: titulo,
			titulo_lmu: tituloLMU,
			lmu: [LMU1, LMU2],
			ref: [REF1, REF2],
			alvo: [ALVO1, ALVO2],
			AO: AO,
			heading: heading
		}
		return config;
	}

	const saveZe = () => {

        const hora   = getHora();
		const config = getConfig();
		const res    = calc.calcRespostaZe(config);

        const item = {
            hora: hora,
			config: config,
			res: res
        }

        db.table(TABLE)
          .add(item)
          .then((id) => {
			  setDados([{...item, id}, ...dados])
			  send2discord()
          })
    }

	const deleteZe = (id:any) => {
        db.table(TABLE)
          .delete(id)
          .then(() => {
              const da = dados.filter((d:any)=> d.id !== id) 
              setDados(da)
          })
	}
	
	const bulkDeleteZe = (ids:number[]) => {
        // console.log(ids)
        db.table(TABLE)
          .bulkDelete(ids)
          .then(() => {
            const items = dados.filter((d:any) => !ids.includes(d.id))
            setDados(items);
          })
    }

	const loadZe = (id:any) => {
        // lendo dados state do id certo
        const d = dados.filter((d:any)=> d.id === id)[0]
		let titulo_lmu = '';
		if ('titulo_lmu' in d.config) {
			titulo_lmu = d.config.titulo_lmu
		} 		
		
		// escrevendo nos campos do formulario
		setTitulo(d.config.titulo)
		setTituloLMU(titulo_lmu)
        setLMU1(d.config.lmu[0])
        setLMU2(d.config.lmu[1])
        setALVO1(d.config.alvo[0])
        setALVO2(d.config.alvo[1])
        setREF1(d.config.ref[0])
        setREF2(d.config.ref[1])
        setAO(d.config.AO)
        setHeading(d.config.heading)
    }

	const preecherContaZe = () => {
		setTitulo('Titulo Teste');
		setTituloLMU('LMU#638');
		setLMU1('259747');
		setLMU2('8273489');
		setREF1('261122');
		setREF2('8274390');
		setALVO1('262142');
		setALVO2('8263825');
		setAO('4430');
		setHeading('2982.6');
	}

	const clearContaZe = () => {
		setTitulo('');
		setTituloLMU('');
		setLMU1('');
		setLMU2('');
		setREF1('');
		setREF2('');
		setALVO1('');
		setALVO2('');
		setAO('');
		setHeading('');
	}

	const submitContaZe = () => {
		// calculando DR
		const config = getConfig();
		const res    = calc.calcRespostaZe(config);

		const resposta = <Resposta clickClear={setResposta}>
			<p><span>{titulo}</span></p>
			<p>Direcao de Ref. (DR): <span>{res.DR.toFixed(2)}</span></p>
			<p>Heading (DR - AO): <span>{res.heading.toFixed(2)}</span></p>
			<p>diff Heading: <span>{res.dheading.toFixed(2)}</span></p>
			<p>Direcao Geral de Tiro (DGT): <span>{res.DGT.toFixed(2)}</span></p>
		</Resposta>

		setResposta(resposta)
	}

	const send2discord = () => {
		// lendo resposta conta
		const config = getConfig();
		const res    = calc.calcRespostaZe(config);
		
		const data = {
"content": `
\`\`\`md
${titulo}
(${tituloLMU})

< PARAMETROS >
LMU......: [${LMU1}, ${LMU2}] 
REF......: [${REF1}, ${REF2}]
ALVO.....: [${ALVO1}, ${ALVO2}]
AO.......: ${AO}
Heading..: ${heading}

< RESPOSTA >
Direcao de Ref. (DR).: ${res.DR.toFixed(2)}
Heading (DR - AO)....: ${res.heading.toFixed(2)}
diff Heading.........: ${res.dheading.toFixed(2)}
DGT..................: ${res.DGT.toFixed(2)}
\`\`\`
`
		};		

		const headers = {"content-type":"application/json"}
		
		// discord
		axios.post(WHURL.DISCORD_AVTM+"?wait=true", data, {headers})
		.then(res => {
		  console.log(res);
		  console.log(res.data);
		})
		.catch(() => console.log('ERROR!!!!'))

		// slack
		axios.post(WHURL.SLACK_DADOS, {'text': data.content.replace("```md", "```")}, {'headers': {'Content-Type': 'application/x-www-form-urlencoded'}})
		.then(res => {
		  console.log(res);
		  console.log(res.data);
		})
        .catch(() => console.log('ERROR!!!!'))
	}


	const updateChecked = (id:number, flag:boolean) => {
        db.table(TABLE)
            .update(id, {checked: flag})
            .then((id_) => {
                let atual = [...dados].map((d:any) => {
                    if (d.id === id) {
						d.checked = flag;
						// console.log(d);
					}
                    
                    return d;
                })                
                setDados(atual);
            })        
	}
	
	const switchAll = (flag:boolean) => {
        const allOn = dados.map((d:any) => {
            return {...d, checked:flag}
        });

        db.table(TABLE)
            .bulkPut(allOn)
            .then( () => setDados(allOn) )
    }

	return (
		<Style>
			
			<p className='titulo'>CONTA DO ZE</p>
			
			<Form>
				<hr className='titulo'/>
				
				<Input1x className="input-linha" name='titulo' label='TITULO' value={titulo} setter={setTitulo}/>
				<Input1x className="input-linha" name='titulo_lmu' label='#LMU' value={tituloLMU} setter={setTituloLMU}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='LMU' type="number" labels={['LMU E', 'LMU N']} values={[LMU1, LMU2]} setters={[setLMU1, setLMU2]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='REF' type="number" labels={['REF E', 'REF N']} values={[REF1, REF2]} setters={[setREF1, setREF2]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='ALVO' type="number" labels={['ALVO E', 'ALVO N']} values={[ALVO1, ALVO2]} setters={[setALVO1, setALVO2]}/>
				<Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='AO' type="number" labels={['AO', 'HEADING']} values={[AO, heading]} setters={[setAO, setHeading]}/>

				<ButtonOk label='CONTA ZE' clickList={preecherContaZe} clickSubmit={submitContaZe} clickClear={clearContaZe} clickSave={saveZe}/>

				<hr className='fim'/>
			</Form>
			{resposta}
			<hr/>
			<div className="btn-linha">
                <Button onClick={setDataFromDB} className="px-3"><FaRecycle className="co-white"/></Button>
            </div>

			<DadosZe 
				dados={dados} 
				delete={deleteZe}
                bulkDelete={bulkDeleteZe} 
				load={loadZe}
                updateChecked={updateChecked}
                switchAll={switchAll}
				/>
		</Style>
		)
	}
