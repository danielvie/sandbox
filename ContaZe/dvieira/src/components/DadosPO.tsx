import React, { useState } from 'react'

import { GrFormUpload } from 'react-icons/gr'

import { Row, Col, Button, Form } from 'react-bootstrap';

import { Resposta } from './Resposta'

import { StyleDados } from './styles/Styles'

import { Alerta } from './Alerta'

export const DadosPO = (props:any) => {
    
    const [ show, setShow ] = useState(false);

    const { dados } = props;
    
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

    const updateChecked = (id:number, e:any) => {
        props.updateChecked(id, e.target.checked);        
    }

    return (
        <StyleDados>
            {dados.map((d:any) => {
                
                const titulo = d.config?d.config.titulo:""
                const dalc   = d.config?d.res.desvios.alcance:""
                const dlat   = d.config?d.res.desvios.lateral:""
                const dtot   = d.config?d.res.desvios.total:""
                const hora   = d.config?d.hora:""
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
                                <div className="dados-titulo">{(titulo==="")?"sem titulo":titulo}</div>
                                <div>A: {dalc} L: {dlat}</div>
                                <div>T: {dtot}</div>
                                <div className="dados-footer">{hora}</div>
                            </Col>
                            <Col xs='3' className="dados-btn text-right">
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