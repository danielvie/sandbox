import React from 'react'

import { Alert } from 'react-bootstrap'

export const Alerta = (props:any) => {

    const { show, setShow } = props;
    
    if (show)
        return (
        <Alert variant="success" onClose={() => setShow(false)} dismissible>
            <Alert.Heading>{props.children}</Alert.Heading>            
        </Alert>
    )

    return <div></div>
}
