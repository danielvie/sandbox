import Dexie from 'dexie'

const db = new Dexie('AppContaZe');

db.version(2).stores({
    root: 'id',
    dados_cria_alvo: '++id', 
    dados_calculo_po: '++id', 
    dados_contaze: '++id', 
    dados_pos_tiro: '++id'
});

export default db;