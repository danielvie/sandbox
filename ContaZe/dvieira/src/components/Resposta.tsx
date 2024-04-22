import React from 'react'
import styled from 'styled-components'

import { Button } from 'react-bootstrap'
import { GrClearOption } from 'react-icons/gr'

const Styled = styled.div`
    .resposta {
        position: relative;
    }

    .limpa-resposta {
        position: absolute;
        top: 5px;
        right: 5px;
    }

    .resposta span {
        font-weight: bold;
    }
`

export const Resposta = (props: any) => {
    let flagLimpa = false;
    if (props.children && props.clickClear) {
        flagLimpa = true;
    }
    
    return (
        <Styled>
            <div className="resposta ft-13">
                { props.children }

                { flagLimpa ? <Button variant="outline-secondary" 
                                      className='ml-1 limpa-resposta' 
                                      onClick={() => props.clickClear(<div className='resposta'/>)}
                                      > 
                                <GrClearOption className='icons'/> 
                              </Button>: ''}
            </div>


        </Styled>
    )
}
