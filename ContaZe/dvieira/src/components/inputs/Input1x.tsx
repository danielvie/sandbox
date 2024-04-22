import React from 'react'

import { IoMdTrash as Trash } from "react-icons/io";
import { Form, Button, Row, Col } from "react-bootstrap";

import { StyleInput } from '../styles/Styles'

import { limpaFormulario } from '../../utils/utils'

export const Input1x = (props: any) => {

    const type = (props.type)?props.type:"text";
    // console.log(type)
    const className = `input-row ${props.className}`
    return (
        <StyleInput>
            <Row className={className}>
                <Col>
                    <Row>
                        <span className="input-label">{props.label}</span>
                    </Row>
                    <Row>
                        <Form.Control size="lg" type={type}
                            className="input-placeholder"
                            placeholder={props.label} 
                            onChange={e => props.setter(e.target.value)} 
                            value = {props.value}                            
                        />
                    </Row>
                    
                </Col>

                <Col xs='auto' className='pl-0'>
                    <Button variant="danger" className="btn-icon btn-del" onClick={() => limpaFormulario(props)}>
                        <Trash/>
                    </Button>
                </Col>
            </Row>            
        </StyleInput>
    )
}
