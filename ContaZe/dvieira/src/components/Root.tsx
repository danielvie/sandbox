import React, { useEffect, useState } from 'react'

import { Tab, Tabs } from 'react-bootstrap'
import Utils from './Utils';
import ContaDoZe from './ContaDoZe';
import { Config } from './Config';
import PO from './PO';
import UCF from './UCF';

import db from '../utils/db'

import {StylesRoot} from './styles/Styles'

export default function Root() {

	const [key, setKey] = useState<number>(3)
	const [memory, setMemory] = useState<any>(['', '', ''])
	// const [countBlank, setCountBlank] = useState<number>(0)

	const inicializaTab = (pos:number) => {
		const item = { id: 1, pos }

		db.table('root')
		  .add(item)
		  .then(() => console.log(`inicializando tab: ${pos}`))
	}

	const atualizaTab = (pos:number) => {
		const id = 1;
		db.table('root')
		  .update(id, { pos })
		  .then(() => setKey(pos))
	}

	useEffect(() => {
		db.table('root')
		  .toArray()
		  .then((res) => {
			  if (res.length === 0) inicializaTab(key)
			  else setKey(res[0].pos)
		  })
	});
	
    return (
        <StylesRoot>
			<Tabs variant="pills" transition={false} id="tab-navigation" activeKey={key} onSelect={(k:any) => atualizaTab(k)} >

                <Tab eventKey="1" title="Utils">
                  <Utils memory={memory} setMemory={setMemory}/>
                </Tab>
                
                <Tab eventKey="2" title="UCF">
                  <UCF memory={memory} setMemory={setMemory}/>
                </Tab>
                
                <Tab eventKey="3" title="ContaDoZe" memory={memory}>
                  <ContaDoZe memory={memory} setMemory={setMemory}/>
                </Tab>
                
                <Tab eventKey="4" title="PO">
                  <PO memory={memory} setMemory={setMemory}/>
                </Tab>
                
				<Tab eventKey="5" title="⚙">
                  <Config memory={memory} setMemory={setMemory}/>
                </Tab>
                
            </Tabs>
        </StylesRoot>
    )
}
