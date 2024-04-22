%Programa para calcular a derivada do estado para ser utilizada no programa
%de linearização como feito no Lewis and Steven (Aircraft Control and
%Simulation)

function dydx = LinModelYx(tempo, estados, controle, i, j,dx,Modelo)
    %delta(fi)/delta(xj) pertubou a função fi(linha) utilizando o elemento
    %xj(coluna)

    t = estados(j);
    estados(j) = t-dx;
    [~, dfForca,~,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd1 = dfForca(i);
    estados(j) = t+dx;
    [~, dfForca,~,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd2 = dfForca(i);
    dydx = (xd2 - xd1)/(2*dx);
  
  
    
end