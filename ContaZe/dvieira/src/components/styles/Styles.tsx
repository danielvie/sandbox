import styled from 'styled-components';

export const Style = styled.div`
    .titulo {
        color: #3c80c0;
        font-size: 1.8em;
        font-family: monospace;
        text-align: center;
        padding:0;
        margin:0;
        margin-top: 10px;
    }
    
    .titulo-2 {
        color: #848484;
        font-size: 1.5em;
        font-family: monospace;
        text-align: center;
        padding:5px;
        margin:0;
        margin-top: 1em;
        margin-bottom: 1em;
        background-color: #f5f5f5;
        display: block;

        border: 0;
        border-top: 2px solid #999;

    }

    .titulo-3 {
        color: #848484;
        font-size: 1.5em;
        font-family: monospace;
        /* text-align: center; */
        padding:5px;
        margin:0;
        margin-top: 1em;
        display: block;
    }
    
    hr {
        margin-top: 1em;
        margin-bottom: 1em;
        border: 0;
        border-top: 2px solid #3c80c0;
    } 
    
    hr.titulo {
        margin-bottom: 0.5em;
    }
    
    hr.titulo-2 {
        margin-top: 1em;
        margin-bottom: 0;
    }
    
    hr.fim {
        margin-top: 0.4em;
        margin-bottom: 0;
    }

    .btn-icon {
        font-size: 1.8em;
        padding: 1px 1px;
        background-color: white;
        border-color: white;
        color: #444;
        position:relative;
        top:5px;
    }
    
    .btn-del {
        /* color: #dc3545; */
        color: #888;
        margin-top: 5px;
    }


    .btn-red {
        color: #dd4f11;
    }

    .btn-blue {
        color: #3c80c0;
    }

    .btn-ok {
        margin-left: 0.2em;
    }
    
    .btn-linha {
        text-align: center;
        margin-top: 10px;        
    }
    
    .div-btn-sel-po {
        margin: 0 auto;
        text-align: center;
    }

    .style-angulos-alvo {
        margin: 0 auto;
        margin-top: 2px;
        text-align: center;
        font-family: monospace;
        font-size: 12px;
        color: gray;
    }

    .bg-gray {
        background-color: #4799E6;
        color: white;
        padding: 2px 4px;
        margin-top: 2px;
    }

    .linha-db {
        
        &+.linha-db{
            margin-top: 15px;
        }
    }

    .form-group {
        /* margin-bottom: 0.5em; */
    }

    .resposta {
        font-family: monospace;
        font-size: 1.1em;
        margin: 10px 8px;
        padding: 10px;
        background-color: #fdfdfd;
        border: 1px solid #ddd;
        border-radius: 4px;
    }

    .resposta p {
        margin-bottom: 0;

        +p {
            margin-top: 4px;
        }
    }

    .input-linha {
        margin-top: 2px;
    }

    .input-linha .col {
        padding-left: 17px;
    }

    .ft-bold { font-weight: bold; }

    .ft-10 { font-size: 10px; }
    
    .ft-11 { font-size: 11px; }
    
    .ft-12 { font-size: 12px; }
   
    .ft-13 { font-size: 13px; }
    
    .ft-14 { font-size: 14px; }
    
    .ft-15 { font-size: 15px; }

    .ft-16 { font-size: 16px; }

    .ft-17 { font-size: 17px; }

    .ft-18 { font-size: 18px; }

    .ft-19 { font-size: 19px; }

    .ft-20 { font-size: 20px; }

    .ft-21 { font-size: 21px; }
    
    .ft-monospace {font-family: monospace;}

    .co-white { color: white; }

`

export const StylesRoot = styled.div`
    .nav-pills {
        background-color: #f5f5f5;
        padding: 5px 5px;
        /* border-bottom: 1px solid #818181; */

        -webkit-box-shadow: 1px 1px 6px 2px rgba(0,0,0,0.45);
        -moz-box-shadow: 1px 1px 6px 2px rgba(0,0,0,0.45);
        box-shadow: 1px 1px 6px 2px rgba(0,0,0,0.45);
    }
    .nav-link.active {
      /* background-color: #007bff; */
    }
    
    .nav-link {
      /* 007bff */
      /* color: #333; */
      color: #818181;

      &:hover {
        color: white;
      }
    }

    .tab-content .row {
      padding: 0 5px;
    }
`

export const StyleInput = styled.div`
    
    .form-label {
        font-family: monospace;
        font-size: 14px;
    }

    .coluna-cpy-del {
        display: table-cell;
        vertical-align: bottom;
    }

    .input-label {
        font-size:10px;
        margin-left: 1em;
    }

    .input-row {
        margin-left: -5px;
    }
            
    .input-multi {
        margin-top: 5px;
    }
    
    .input-multi .col {
        padding-left: 13px;
    }
    
    .input-placeholder {
        font-size: 16px;
    }
    
`

export const StyleDados = styled.div`

    .dados-titulo {
        font-size: 16px;
        font-weight: bold;
        margin-bottom: 4px;
    }

    .dados-desvio-total {
        font-weight: bold;
        color: #3c80c0;
    }

    .row-dados {
        margin: 0;
        padding: 0;
    }
    
    .dados-btn-item {
        color: #888;
        background-color: #fdfdfd;
        border-color: #cacaca;
        margin: 0;
        padding: 3px 7px;
        margin-left: 0px;
        font-size: 23px;
        &+.dados-btn-item {
            margin-left: 5px;
        }
    }

    .dados-btn {
        margin:0;
        padding:0;
        top: 2px;
        right:10px;
    }

    .dados-footer {
        font-size: 10px;
        color: #666;
        margin-top: 5px !important;
    }

    .dados-switch {

    }
`