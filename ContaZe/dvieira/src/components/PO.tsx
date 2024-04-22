import React, { useEffect, useState } from 'react'
import { Style } from './styles/Styles'
import { Form, Button } from 'react-bootstrap'
import { Input1x } from './inputs/Input1x';
import { Input2x } from './inputs/Input2x';
import { Input3x } from './inputs/Input3x';

import {ButtonGroup, ToggleButton} from 'react-bootstrap'

import axios from 'axios';

import { FaRecycle } from 'react-icons/fa'

import { ButtonOk } from './ButtonOk'
import { Resposta } from './Resposta'

import { DadosPO } from './DadosPO'

import * as calc from '../utils/calc'
import * as math from 'mathjs'

import { getHora } from '../utils/utils'

import { WHURL } from "./WHURL";
import db from "../utils/db";

import { POSICOES } from "../components/Posicoes";

export default function PO(props:any) {

    // STATES
    const [titulo, setTitulo] = useState('');
    const [LMU1, setLMU1] = useState('');
    const [LMU2, setLMU2] = useState('');
    const [ALVO1, setALVO1] = useState('');
    const [ALVO2, setALVO2] = useState('');
    const [PODEC1, setPODEC1] = useState('');
    
    const [PODMS_po1_1, setPODMS_po1_1] = useState('');
    const [PODMS_po1_2, setPODMS_po1_2] = useState('');
    const [PODMS_po1_3, setPODMS_po1_3] = useState('');

    const [PODEC2, setPODEC2] = useState('');
    
    const [PODMS_po2_1, setPODMS_po2_1] = useState('');
    const [PODMS_po2_2, setPODMS_po2_2] = useState('');
    const [PODMS_po2_3, setPODMS_po2_3] = useState('');
    
    const [resposta, setResposta] = useState(<Resposta></Resposta>);

    const [dados, setDados] = useState<any>([])
    
    const [radioValue, setRadioValue] = useState('1');
    
    const [angulosALVO, setAngulosALVO] = useState('0.0, 0.0');

    const radios = [
        { name: 'PO1 e PO4', value: '1' },
        { name: 'PO2 e PO4', value: '2' },
    ];

    const setDataFromDB = () => {
        db.table('dados_calculo_po')
          .toArray()
          .then((D) => {
            setDados(D)
          })
    }

    useEffect(() => {
        setDataFromDB();
    }, [])
    
    useEffect(() => {
        const angs = calculaAngulosAlvo(radioValue)
        setAngulosALVO(angs)
    }, [radioValue])

    const clearPO = () => {
        setTitulo('')
        setLMU1('')
        setLMU2('')
        setALVO1('')
        setALVO2('')
        setPODEC1('')
        setPODMS_po1_1('')
        setPODMS_po1_2('')
        setPODMS_po1_3('')
        setPODEC2('')
        setPODMS_po2_1('')
        setPODMS_po2_2('')
        setPODMS_po2_3('')
    }

    const preenchePO = () => {
        setTitulo('Titulo Dummy')
        setLMU1('259747')
        setLMU2('8273489')
        setALVO1('263769')
        setALVO2('8246145')
        setPODEC1('55.34')
        setPODMS_po1_1('57')
        setPODMS_po1_2('19')
        setPODMS_po1_3('30')
        setPODEC2('298.74')
        setPODMS_po2_1('301')
        setPODMS_po2_2('33')
        setPODMS_po2_3('20')
    }

    const savePO = () => {

        const hora   = getHora();
        const config = getConfig();
        const res    = calc.calcRespostaPO(config);

        const item = {
            hora: hora,
            config: config,
            res: res 
        }

        db.table('dados_calculo_po')
          .add(item)
          .then((id) => {
            setDados([{...item, id}, ...dados])
            send2discord();
          })
    }

    const deletePO = (id:number) => {
        db.table('dados_calculo_po')
          .delete(id)
          .then(() => {
              const da = dados.filter((d:any)=> d.id !== id) 
              setDados(da)
          })
    }
    
    const bulkDeletePO = (ids:number[]) => {
        db.table('dados_calculo_po')
          .bulkDelete(ids)
          .then(() => {
            const items = dados.filter((d:any) => !ids.includes(d.id))
            setDados(items);
          })
    }


    const updateChecked = (id:number, flag:boolean) => {
        db.table('dados_calculo_po')
            .update(id, {checked: flag})
            .then((id_) => {
                let atual = [...dados].map((d:any) => {
                    
                    if (d.id === id) {
                        d.checked = flag;
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

        db.table('dados_calculo_po')
            .bulkPut(allOn)
            .then( () => setDados(allOn) )
        
    }

    const getRespostaFromConfig = (config:any) =>
    {
        const res = calc.calcRespostaPO(config);
        
        return <Resposta clickClear={setResposta}>
            <p><span>{titulo}</span></p>
            <p><span>PO{radioValue} e PO4</span></p>
            <p>lmu............: <span>[{config.lmu[0]}, {config.lmu[1]}]</span></p>
            <p>alvo...........: <span>[{config.alvo[0]}, {config.alvo[1]}]</span></p>
            <p>impacto........: <span>[{res.impacto[0]}, {res.impacto[1]}]</span></p>
            <p>distancia......: <span>{res.dist}</span></p>
            <p>desvio alcance.: <span>{res.desvios.alcance}</span></p>
            <p>desvio lateral.: <span>{res.desvios.lateral}</span></p>
            <p>desvio total...: <span>{res.desvios.total}</span></p>
        </Resposta>
    }

    const loadPO = (id:any) => {
        // lendo dados state do id certo
        const d = dados.filter((d:any)=> d.id === id)[0]
        
        // escrevendo nos campos do formulario
        setTitulo(d.config.titulo)
        setLMU1(d.config.lmu[0])
        setLMU2(d.config.lmu[1])
        setALVO1(d.config.alvo[0])
        setALVO2(d.config.alvo[1])
        setPODEC1(d.config.ang1)
        setPODMS_po1_1(d.config.ang1_[0])
        setPODMS_po1_2(d.config.ang1_[1])
        setPODMS_po1_3(d.config.ang1_[2])
        setPODEC2(d.config.ang2)
        setPODMS_po2_1(d.config.ang2_[0])
        setPODMS_po2_2(d.config.ang2_[1])
        setPODMS_po2_3(d.config.ang2_[2])


        // const config = getConfig();
        // console.log(config);
        const resposta = getRespostaFromConfig(d.config);

        setResposta(resposta)
    }    
    
    const getConfig = () => {
        
        const posPO_A = (radioValue === '1')?POSICOES.PO1:POSICOES.PO2;
        const posPO_B = POSICOES.PO4;
        
        const config = {
            titulo: titulo,
            lmu: [LMU1, LMU2],
            alvo: [ALVO1, ALVO2],
            ang1: PODEC1,
            ang1_: [ PODMS_po1_1, PODMS_po1_2, PODMS_po1_3 ], 
            ang2: PODEC2,
            ang2_: [ PODMS_po2_1, PODMS_po2_2, PODMS_po2_3 ],
            posicao_po1: posPO_A,
            observacao_po1: posPO_B,
            posicao_po2: posPO_B,
            observacao_po2: posPO_A
        };
        return config;
    }

    const send2discord = () => {
		// lendo resposta conta
		const config = getConfig();
        const res    = calc.calcRespostaPO(config);

		const data = {
"content": `
\`\`\`md
${titulo}
----------------------------------

< PARAMETROS >
POS. PO A.: [${config.posicao_po1[0]}, ${config.posicao_po1[1]}] (PO${radioValue})
POS. PO B.: [${config.posicao_po2[0]}, ${config.posicao_po2[1]}] (PO4)
LMU.......: [${LMU1}, ${LMU2}]
ALVO......: [${ALVO1}, ${ALVO2}]
ANG. PO1..: [${PODEC1}], [${PODMS_po1_1}, ${PODMS_po1_2}, ${PODMS_po1_3}]
ANG. PO2..: [${PODEC2}], [${PODMS_po2_1}, ${PODMS_po2_2}, ${PODMS_po2_3}]

< RESPOSTA >
impacto........: ${res.impacto[0]}, ${res.impacto[1]}
desvio alcance.: ${res.desvios.alcance}
desvio lateral.: ${res.desvios.lateral}
desvio total...: ${res.desvios.total}

\`\`\`
`
		};		

        const headers = {"content-type":"application/json"}
        // DISCORD
		axios.post(WHURL.DISCORD_KOKALUKIA_LOG+"?wait=true", data, {headers})
		.then(res => {
            console.log(res);
            console.log(res.data);
		})
        .catch(() => console.log('ERROR!!!!'))
        
        // SLACK
		axios.post(WHURL.SLACK_DADOS, {'text': data.content.replace("```md", "```")}, {'headers': {'Content-Type': 'application/x-www-form-urlencoded'}})
		.then(res => {
		  console.log(res);
		  console.log(res.data);
		})
        .catch(() => console.log('ERROR!!!!'))
        
	}
    
   
    const submitPO = () => {

        const config = getConfig();
        const resposta = getRespostaFromConfig(config);

        setResposta(resposta)

    }

    const calculaAngulosAlvo = (poA:string) => {
        const po1  = (poA === '1')?POSICOES.PO1:POSICOES.PO2
        const po2  = POSICOES.PO4
        const alvo = POSICOES.alvo
        
        const v1po1:any = math.subtract(po2, po1)
        const v2po1:any = math.subtract(alvo, po1)
        let ang1 = calc.calcula_ang(v1po1, v2po1)*180./math.pi
        
        const v1po2:any = math.subtract(po1, po2)
        const v2po2:any = math.subtract(alvo, po2)
        let ang2 = calc.calcula_ang(v1po2, v2po2)*180./math.pi
        
        // ajuste de quadrante
        if (ang1 < 0.) {
            ang1 += 360.
        }
        
        if (ang2 < 0.) {
            ang2 += 360.
        }

        return `${ang1.toFixed(2)}, ${ang2.toFixed(2)}`
    }

    const middleware_setPO = (value:any, n:number) => {
           
        // ajuste PO1        
        if (n === 1)
        {
            if ((PODEC1 === '') && (value === ''))
            {
                setPODEC1('');
                setPODMS_po1_1('');
                setPODMS_po1_2('');
                setPODMS_po1_3('');
                return;
            }
            
            setPODEC1(value);        
        }
        
        // ajuste PO2
        if (n === 2)
        {
            if ((PODEC2 === '') && (value === ''))
            {
                setPODEC2('');
                setPODMS_po2_1('');
                setPODMS_po2_2('');
                setPODMS_po2_3('');
                return;
            }
            
            setPODEC2(value);        
        }

    }


    return (
        <Style>
            
            <p className='titulo'>CALCULO PO ({radioValue})</p>
            <Form>
                <div className='div-btn-sel-po'>
                    <ButtonGroup className="mt-1" toggle>
                        {radios.map((radio, idx) => (
                            <ToggleButton
                            size="sm"
                            key={idx}
                            type="radio"
                            variant="secondary"
                            name="radio"
                            value={radio.value}
                            checked={radioValue === radio.value}
                            onChange={(e:any) => setRadioValue(e.currentTarget.value)}>
                            {radio.name}
                        </ToggleButton>
                        ))}
                    </ButtonGroup>
                    <p className='style-angulos-alvo'>
                        <span className='bg-gray'>{angulosALVO}</span></p>
                </div>

                <hr className='titulo'/>
                
                <Input1x className="input-linha" name='titulo' label='TITULO' value={titulo} setter={setTitulo}/>
                <Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='LMU' type="number" labels={['LMU E', 'LMU N']} values={[LMU1, LMU2]} setters={[setLMU1, setLMU2]}/>
                <Input2x memory={props.memory} setMemory={props.setMemory} className="input-linha" name='ALVO' type="number" labels={['ALVO E', 'ALVO N']} values={[ALVO1, ALVO2]} setters={[setALVO1, setALVO2]}/>
                
                <Input1x className="input-linha" name='po1_dec' type="number" label='PO1 dec' value={PODEC1} setter={(v:any) => middleware_setPO(v, 1)}/>
                <Input3x className="input-linha" name='po1_dms' type="number" labels={['Deg', 'Min', 'Sec']} values={[PODMS_po1_1, PODMS_po1_2, PODMS_po1_3]} setters={[setPODMS_po1_1, setPODMS_po1_2, setPODMS_po1_3]}/>
                
                <Input1x className="input-linha" name='po2_dec' type="number" label='PO2 dec' value={PODEC2} setter={(v:any) => middleware_setPO(v, 2)}/>
                <Input3x className="input-linha" name='po2_dms' type="number" labels= {['Deg', 'Min', 'Sec']} values={[PODMS_po2_1, PODMS_po2_2, PODMS_po2_3]} setters={[setPODMS_po2_1, setPODMS_po2_2, setPODMS_po2_3]}/>
                                    
                
                <ButtonOk label='IMPACTO' clickSubmit={submitPO} clickClear={clearPO} clickList={preenchePO} clickSave={savePO}/>

            </Form>
            {resposta}
            <hr/>
            
            <div className="btn-linha">
                <Button onClick={setDataFromDB} className="px-3"><FaRecycle className="co-white"/></Button>
            </div>

            <DadosPO 
                dados={dados}
                delete={deletePO} 
                bulkDelete={bulkDeletePO} 
                load={loadPO}
                updateChecked={updateChecked}
                switchAll={switchAll}
                />
        </Style>
        )
    }
