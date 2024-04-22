import React, { useState } from 'react'

import { Form } from 'react-bootstrap'

import { Style } from './styles/Styles'
import * as calc from '../utils/calc'
import { getHora } from '../utils/utils'

import db from "../utils/db";
import { ButtonOk } from './ButtonOk'
import { Alerta } from './Alerta'


export const Config = (props:any) => {

    const [dados, setDados] = useState<string>('');
    const [showAlert, setShowAlert] = useState(false);

    const clearDados = () => {
        setDados('');
    }

    // const escreverDadosPO = () => {
    //     const json = [{"titulo":"Leituras Dummy","lmu":[259747,8273489],"alvo":[263769,8246145],"leitura_po1":55.34,"leitura_po1_":[57,19,30],"leitura_po2":298.74,"leitura_po2_":[301,33,20],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"-434.30","lateral":"173.04","total":"467.51"},"data_hora":"2020-06-22T00:57:12.507Z","id":51},{"titulo":"C7.ss40.4.09h54","lmu":["262545","8277036"],"alvo":[263769,8246145],"leitura_po1":"46.48","leitura_po1_":["46","17","40"],"leitura_po2":"289.03","leitura_po2_":["287","36","50"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"-180.76","lateral":"-570.40","total":"598.36"},"data":"2020-03-16T05:47:35.990Z","id":46},{"titulo":"C7.ss40.4.09h54","lmu":["262545","8277036"],"alvo":[263769,8246145],"leitura_po1":"46.48","leitura_po1_":["46","17","40"],"leitura_po2":"289.03","leitura_po2_":["287","36","50"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"-180.76","lateral":"-570.40","total":"598.36"},"id":43},{"titulo":"C7.ss40.3","lmu":["262545","8277036"],"alvo":[263769,8246145],"leitura_po1":"75.16","leitura_po1_":["73","19","00"],"leitura_po2":"316.19","leitura_po2_":["314","48","20"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"-1014.17","lateral":"1317.78","total":"1662.85"},"id":42},{"titulo":"C7.ss40.2","lmu":["262545","8277036"],"alvo":[263769,8246145],"leitura_po1":"55.63","leitura_po1_":["54","41","20"],"leitura_po2":"293.58","leitura_po2_":["291","54","20"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"66.52","lateral":"36.26","total":"75.76"},"id":39},{"titulo":"C7.ss40.1","lmu":["262545","8277036"],"alvo":[263769,8246145],"leitura_po1":"","leitura_po1_":["","",""],"leitura_po2":"","leitura_po2_":["","",""],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"NaN","lateral":"NaN","total":"NaN"},"id":38},{"titulo":"Último tiro","lmu":["262547","8277042"],"alvo":[263769,8246145],"leitura_po1":"55.82","leitura_po1_":["54","19","30"],"leitura_po2":"294.16","leitura_po2_":["290","45","30"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"83.03","lateral":"26.10","total":"87.04"},"id":37},{"titulo":"Ruínas. 31 out Tiro 3","lmu":["262546","8277039"],"alvo":[263769,8246145],"leitura_po1":"55.84","leitura_po1_":["54","19","30"],"leitura_po2":"294.16","leitura_po2_":["290","45","30"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"83.71","lateral":"26.73","total":"87.87"},"id":34},{"titulo":"Ruínas. 31 out Tiro 2","lmu":["262546","8277039"],"alvo":[263769,8246145],"leitura_po1":"56.15","leitura_po1_":["55","05","20"],"leitura_po2":"294.54","leitura_po2_":["293","01","20"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"14.56","lateral":"82.14","total":"83.42"},"id":33},{"titulo":"Ruínas. 31 out Tiro 1","lmu":["262546","8277039"],"alvo":[263769,8246145],"leitura_po1":"56.06","leitura_po1_":["55","02","40"],"leitura_po2":"294.00","leitura_po2_":["290","38","00"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"124.65","lateral":"54.37","total":"135.99"},"id":32},{"titulo":"Cascalheiras. 30 out Tiro 2","lmu":["255137","8278290"],"alvo":[263769,8246145],"leitura_po1":"89.41","leitura_po1_":["87","42","90"],"leitura_po2":"290.72","leitura_po2_":["289","45","00"],"posicao_po1":[264796,8249229],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[264796,8249229],"desvio":{"alcance":"916.26","lateral":"48.17","total":"917.52"},"id":31},{"titulo":"Cascalheiras. 30 out Tiro 1","lmu":["255137","8278290"],"alvo":[263769,8246145],"leitura_po1":"96.60","leitura_po1_":["93","59","40"],"leitura_po2":"301.13","leitura_po2_":["297","58","10"],"posicao_po1":[264796,8249229],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[264796,8249229],"desvio":{"alcance":"111.24","lateral":"85.47","total":"140.28"},"id":30},{"titulo":"Posição DB. 29 out Tiro 1","lmu":["264278","8268569"],"alvo":[263769,8246145],"leitura_po1":"56.12","leitura_po1_":["55","35","40"],"leitura_po2":"293.94","leitura_po2_":["290","48","50"],"posicao_po1":[262672,8250238],"posicao_po2":[266354,8248861],"observacao_po1":[266354,8248861],"observacao_po2":[262672,8250238],"desvio":{"alcance":"143.84","lateral":"66.15","total":"158.32"},"id":29}];
    //     const txt  = JSON.stringify(json);
    //     setDados(txt);
    // }
    
    // const escreverDadosZe = () => {
    //     const json = [{"titulo":"SS40G Ruínas 18/02","lmu":["262546","8277039"],"ref":["",""],"alvo":[263769,8246145],"ao_heading":["",""],"id":10},{"titulo":"SS40G Ruínas 31/10","lmu":["262546","8277039"],"ref":["",""],"alvo":["",""],"ao_heading":["",""],"id":8},{"titulo":"Cascalheira","lmu":["255137","8278290"],"ref":["261110","8277879"],"alvo":["263769","8246145"],"ao_heading":["",""],"id":7},{"titulo":"dados Dummy","lmu":["263215","8276632"],"ref":[261122,8274390],"alvo":[262142,8263825],"ao_heading":[4430,2982.6],"id":6},{"titulo":"SS40G 🚀 5a C RUINAS","lmu":["262546","8277039"],"ref":["261110","8277879"],"alvo":["263769","8246145"],"ao_heading":["2177","3162.1"],"id":5},{"titulo":"SS40G 5a Sto Inacio","lmu":["261212","8266734"],"ref":["260730","8267503"],"alvo":["263769","8246145"],"ao_heading":["",""],"id":3},{"titulo":"SS40G 5a C RUINAS","lmu":["262546","8277041"],"ref":["261110","8277879"],"alvo":["263769","8246145"],"ao_heading":["",""],"id":2}]
    //     const txt  = JSON.stringify(json);
    //     setDados(txt);
    // }

    const checkDadosLegacyPO = (dados:any) => {
        return dados.hasOwnProperty('leitura_po2_')
    }
    
    const checkDadosPO = (dados:any) => {        
        if (dados.hasOwnProperty('config')) {
            return dados.config.hasOwnProperty('posicao_po1')
        } else {
            return dados.hasOwnProperty('posicao_po1')
        }
    }

    const checkDadosZe = (dados:any) => {
        if (dados.hasOwnProperty('config')) {
            return dados.config.hasOwnProperty('heading')
        } else {
            return dados.hasOwnProperty('ao_heading')
        }
    }

    
    const montaItemPO = (d:any) => {
        let item:any = {}
        if (checkDadosLegacyPO(d)) {
            // convertendo dados legacy
            const config = {
                titulo: d.titulo,
                lmu: d.lmu,
                alvo: d.alvo,
                ang1: d.leitura_po1,
                ang1_: d.leitura_po1_, 
                ang2: d.leitura_po2,
                ang2_: d.leitura_po2_,
                posicao_po1: d.posicao_po1,
                observacao_po1: d.observacao_po1,
                posicao_po2: d.posicao_po2,
                observacao_po2: d.observacao_po2
            };
    
            const res = calc.calcRespostaPO(config);
            
            item = {
                config,
                res,
                hora: getHora()
            }
        } else {
            item = {
                config: d.config,
                res: d.res,
                hora: d.hora
            }
        }   
        return item;
    }
    
    const montaItemZe = (d:any) => {
        
        const legacy = d.hasOwnProperty('ao_heading')
        
        let item:any = {}
        if (legacy) {
            // convertendo dados legacy
            const config = {
                titulo: d.titulo,
                lmu: d.lmu,
                ref: d.ref,
                alvo: d.alvo,
                AO: d.ao_heading[0],
                heading: d.ao_heading[1],
            };
    
            const res = calc.calcRespostaZe(config);
            
            item = {
                config,
                res,
                hora: getHora()
            }
        } else {
            item = {
                config: d.config,
                res: d.res,
                hora: d.hora
            }
        }
        
        return item;
    }

    const addDadosBanco = (d:any) => {
            
        if (checkDadosPO(d)) {
            const item = montaItemPO(d);

            db.table('dados_calculo_po')
            .add(item)
            .then(() => {
                console.log('acho que adicionei o item!')
            })
            .then(() => setShowAlert(true))
            return 1;            
        } 
        
        if (checkDadosZe(d)) {
            const item = montaItemZe(d);

            db.table('dados_contaze')
            .add(item)
            .then(() => setShowAlert(true))
            return 1;
        } 
                 
        return 0;
    }

    const importarDados = () => {
        // lendo dados do campo
        const json = JSON.parse(dados);
        
        // chamando funcao para adicionar no formato novo
        if (json.constructor === Array) {
            json.map((item:any) => addDadosBanco(item))
        } else {
            addDadosBanco(json);
        }
    }
    
    const rows = 10;
    return (
        <Style>
            
            <p className='titulo'>CONFIG (v7.11.3)</p>

            <hr className='titulo'/>
            
            <Form className="mx-2">
                
                <Form.Label className="titulo-3">Importar Dados</Form.Label>
                <Form.Control as="textarea" rows={rows} value={dados} onChange={(e:any) => setDados(e.target.value)}/>
                
                <ButtonOk clickClear={clearDados} clickSubmit={importarDados}>Importar Dados</ButtonOk>
                {/* <ButtonOk clickSubmit={escreverDadosPO}>escrever dados PO</ButtonOk> */}
                {/* <ButtonOk clickSubmit={escreverDadosZe}>escrever dados ContaZe</ButtonOk> */}
                {/* <ButtonOk clickClear={clearDados} clickSubmit={escreveDadosDB}>Dados DB</ButtonOk> */}
                
                {/* <ButtonOk clickSubmit={() => setShowAlert(true)}>Alert</ButtonOk> */}
                
            </Form>

            <div className="my-5 mx-2">
                <Alerta show={showAlert} setShow={setShowAlert}>Dados Importados!</Alerta>
            </div>
            
            
        </Style>
    )
}
