
export const limpaFormulario = (props:any) => {
    
    // console.log(props.value);
    if (props.value.constructor === Array) {
        let value = props.value.map(() => "");
        props.setter(value);

    } else {
        props.setter("")
    }
}

export const getHora = () => {
    const data = new Date();

    const zeroEsquerda = (nro:number) => {
        const str = (nro > 10)?`${nro}`:`0${nro}`;
        return str;
    }

    const dia = zeroEsquerda(data.getDate())
    const mes = zeroEsquerda(data.getMonth())
    const ano = `${data.getFullYear()}`
    
    const hor = zeroEsquerda(data.getHours())
    const min = zeroEsquerda(data.getMinutes())
    const sec = zeroEsquerda(data.getSeconds())

    const str_data = `${dia}/${mes}/${ano}, ${hor}:${min}:${sec}`
    
    return str_data;
}