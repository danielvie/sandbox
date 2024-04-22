from dataclasses import dataclass, field
import datetime

# DESCRICAO: 
'''
# estrutura de dados para cara transacao

transacao = {
    valor: float,
    data: date,
    paid_by: enum Participantes,
    for_whom: [enum Participantes],
    type: enum TransactionType // [Expense, Income, MoneyTransfer]
}

# for_whom pode ser usado em modo `avancado`, em que eh possivel distribuir
  o `ownnership` da transacao de forma nao igual

  no tricount, ha a opcao de dividir fazendo proporcao (2:1) ou por 
  inserir o valor manualmente para cada usuario
'''

# TEST DATA

UserList = set()
UserList.add("Daniel") 
UserList.add("Neto") 

@dataclass
class Transacao:
    valor: float = 0.0
    data: datetime.datetime = datetime.datetime.now()
    paid_by: str = "anonymous"
    for_whom: dict = field(default_factory=dict)
    
    def __post_init__(self) -> None:
        for u in UserList:
            self.for_whom[u] = 0.

def AddExpense(T: list[Transacao], name: str, valor: float):
    t = Transacao()
    t.paid_by = name
    t.valor = valor
    T.append(t)

def ComputeBalance(T: list[Transacao]):
    print('entrei em `ComputeBalance`')
    print(T)

if __name__ == "__main__":

    T = []

    AddExpense(T, "Neto", 100.)

    ComputeBalance(T)