%Programa para calcular a derivada do estado para ser utilizada no programa
%de linearização como feito no Lewis and Steven (Aircraft Control and
%Simulation)

function dydx = LinModelYu(tempo, estados, controle, i, j,dx,Modelo)
    %delta(fi)/delta(xj) pertubou a função fi(linha) utilizando o elemento
    %xj(coluna)
    
    t = controle(j);
    controle(j) = t-dx;
    
    [~, dfForca,~,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd1 = dfForca(i);
    controle(j) = t+dx;
    estados(j) = t+dx;
    [~, dfForca,~,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd2 = dfForca(i);
    
    dydx = (xd2 - xd1)/(2*dx);
   
    
        %% Teste de obtenção dos coeficientes adimensionais (Lembrar de separar da matriz D depois, criar uma rotina E)
%     if (i==8 && j==2) %Obtenção do Malpha
%         aux = 1;
%         t = estados(j); 
%         estados(j) = t-dx;
%         ma1 = M(2); %teste p/ os coeficientes aerodinâmicos
%         xd2 = M(2);
%         ma2 = M(2); %teste p/ os coeficientes aerodinâmicos
%         Malpha = (ma1-ma2)/(2*dx); %teste p/ os coeficientes aerodinâmicos falta dividir pela inércia
%     end
    
end