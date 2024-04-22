import React, { SFC } from 'react'

import { IoMdList, IoMdTrash, IoMdSave } from 'react-icons/io'
import { Button } from 'react-bootstrap'

import styled from 'styled-components'

const Styled = styled.div`
	.icons {
		font-size: 23px;
		/* margin-left: 5px; */
	}
`
export interface ButtonProps {
	label?:string;
	label2?:string;
	clickClear?:any;
	clickList?:any;
	clickSave?:any;
	clickSubmit?:any;
	clickSubmit2?:any;	
}

export const ButtonOk:SFC<ButtonProps> = (props: any) => {

	let label = props.label
	if (props.children) {
		label = props.children;
	}
	
	let clear = <span></span>;
	if (props.clickClear) {
		clear = <span>
			<Button variant="outline-secondary" className='ml-1' onClick={props.clickClear}> <IoMdTrash className='icons'/> </Button>
		</span>;
	}

	let list = <span></span>
	if (props.clickList) {
		list = <span>
			<Button variant="outline-secondary" className='ml-1' onClick={props.clickList}> <IoMdList className='icons'/> </Button>
		</span>
	}

	let submit2 = <span></span>;
	if (props.clickSubmit2) {
		submit2 = <span>
			<Button variant="primary" className="btn-ok ml-1" onClick={props.clickSubmit2}> {props.label2} </Button>
		</span>
	}

	let save = <span></span>
	if (props.clickSave) {
		save = <span><Button variant="secondary" className="btn-ok ml-1" onClick={props.clickSave}> <IoMdSave/> </Button></span>
	}
	
	return (
		<Styled className='btn-linha'>
			{clear}
			{list}
			<Button variant="primary" className="btn-ok ml-1" onClick={props.clickSubmit}> {label} </Button>
			{submit2}
			{save}
		</Styled>
	)
}
