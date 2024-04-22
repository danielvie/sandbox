import React, { SFC } from 'react'

import { IoIosCopy as Copy } from "react-icons/io";
import { Button, Row, Col } from "react-bootstrap";

import { StyleInput } from '../styles/Styles';

import { Input1x } from "./Input1x";

export interface InputProps {
	values?:any;
	setters?:any;
	memory?:any;
	setMemory?:null;
    labels?:any;
    type?:string;
    className?:string;
    name?:string;
    select1?:any;
    select2?:any;
}

export const Input2x:SFC<InputProps> = (props: any) => {

    const handleCopy = (values:Array<string>, setters:any) => {
        
        const colar = values.map((v:string)=>v==="").some((e)=>e)
        
        if (colar) {
            setters[0](props.memory[0])
            setters[1](props.memory[1])
        } else {
            props.setMemory(values)        
        }

    }

    let values = ["", ""];
    if (props.values) {
        values = props.values    
    }
    
    let labels = ['', ''];
    if (props.labels) {
        labels = props.labels    
    }
    
    let setters = [null, null];
    if (props.setters) {
        setters = props.setters    
    }

    const type = (props.type)?props.type:"text"

    const middleware_setter_2x = (value:any, n:number) => {
        
        if ((props.values[n] === '') && (value === ''))
        {
            props.setters[0](value);
            props.setters[1](value);
            return;
        }
        
        props.setters[n](value);
        
    }

    return (
        <StyleInput>
            <Row className="input-multi">
                <Col xs className="pr-1">
                    <Input1x className={props.className} label={labels[0]} type={type} value={values[0]} setter={(v:any) => middleware_setter_2x(v, 0)}/>
                </Col>

                <Col xs className="px-1">
                    <Input1x className={props.className} label={labels[1]} type={type} value={values[1]} setter={(v:any) => middleware_setter_2x(v, 1)}/>          
                </Col>

                <Col xs='auto' className="coluna-cpy-del pl-1" onClick={() => handleCopy(values, setters)}>
                    <Button variant="primary" className="btn-icon"> <Copy/> </Button>{' '}
                </Col>

            </Row>
        </StyleInput>
    )
}