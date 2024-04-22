import React from 'react'

import {Row, Col} from 'react-bootstrap'

import { StyleInput } from '../styles/Styles';

import { Input1x } from './Input1x'

export const  Input3x = (props: any) => {

    const middleware_setter_3x = (value:any, n:number) => {
        
        if ((props.values[n] === '') && (value === ''))
        {
            props.setters[0](value);
            props.setters[1](value);
            props.setters[2](value);
            return;
        }
        
        props.setters[n](value);
        
    }

    let values = ['', '', ''];
    values = (props.values)?props.values:values;
	
	let labels = ['', '', ''];
    labels = (props.labels)?props.labels:labels;
	
    return (
        <StyleInput>
            <Row className="input-multi">
                <Col xs className="pr-1">
                    <Input1x className={props.className} label={labels[0]} type={props.type} value={values[0]} setter={(v:any) => middleware_setter_3x(v, 0)}/>
                </Col>
                <Col xs className="px-1">
                    <Input1x className={props.className} label={labels[1]} type={props.type} value={values[1]} setter={(v:any) => middleware_setter_3x(v, 1)}/>
                </Col>
                <Col xs className="px-1">
                    <Input1x className={props.className} label={labels[2]} type={props.type} value={values[2]} setter={(v:any) => middleware_setter_3x(v, 2)}/>
                </Col>

                <Col xs='auto' className="coluna-cpy-del pl-1">
                    <div>
                
                    </div>                
                </Col>
            </Row>
        </StyleInput>
    )
}
