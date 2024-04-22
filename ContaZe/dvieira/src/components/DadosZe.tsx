import React, { useState } from 'react'

import { GrFormUpload } from 'react-icons/gr'

import { Row, Col, Button, Form } from 'react-bootstrap';

import { Resposta } from './Resposta'

import { StyleDados } from './styles/Styles'
import { Alerta } from './Alerta'

export const DadosZe = (props:any) => {
    const [ show, setShow ] = useState(false);
    
    const {dados} = props;
    
    const updateChecked = (id:number, e:any) => {
        props.updateChecked(id, e.target.checked);        
    }

    const deleteItems = () => {

        const items = dados.filter((d:any)=>d.checked===true).map((d:any) => d.id)
        
        props.bulkDelete(items)
    }

    const copyItems = () => {
        
        const items:any = dados.filter( (d:any) => d.checked === true)
        
        const texto = JSON.stringify(items)
        navigator.clipboard.writeText(texto);

        setShow(true)
    }
    
    return (
        <StyleDados>
            {dados.map((d:any) => {
                
                const titulo = d.config?d.config.titulo:""
                const hora   = d.hora?d.hora:""

                let DGT      = ""
                let dheading = ""
                
                if (d.hasOwnProperty('res')) {
                    DGT = (d.res.DGT)?d.res.DGT.toFixed(2):"NaN"
                    dheading = (d.res.dheading)?d.res.dheading.toFixed(2):"NaN"
                }
                    
                const check  = d.checked?d.checked:false

                return (
                    <Resposta key={d.id}>
                        <Row>
                            <Col xs='1' className="pl-2">
                                <Form.Check
                                    className="dados-switch"
                                    type="switch"
                                    id={`custom-switch-${d.id}`}
                                    label=" "
                                    checked={check}
                                    onChange={(e:any) => updateChecked(d.id, e)}
                                />
                            </Col>
                            <Col xs>
                                <p className="dados-titulo">{(titulo === "")?"sem titulo":titulo}</p>                                        
                                <p>diff: {dheading}, DGT: {DGT}</p>
                                <p className="dados-footer">{hora}</p>
                            </Col>
                            <Col xs="3" className="dados-btn text-right">
                                <Button onClick={() => props.load(d.id)} className='dados-btn-item'>
                                    <GrFormUpload/>
                                </Button>
                            </Col>
                        </Row>
                    </Resposta>
                )}
            )}

            {(dados.length > 0)?
                <div className="btn-linha mb-2">
                    <Button variant="info" onClick={() => props.switchAll(false)}>OFF</Button>
                    <Button variant="success" className="ml-2" onClick={() => props.switchAll(true)}>ON</Button>
                    <Button variant="primary" className="ml-2" onClick={copyItems}>copy</Button>
                    <Button variant="danger" className="ml-5" onClick={deleteItems}>delete</Button>
                </div>:""
            }
            
            <div className="my-3 mx-2">
                <Alerta show={show} setShow={setShow}>Dados Copiados!</Alerta>
            </div>
        </StyleDados>
    )
}
