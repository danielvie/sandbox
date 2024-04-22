%% Programa para calcular a derivada do estado para ser utilizada no programa
% Versão 1.0 - Última Atualização - 16/07/2014 (Adolfo)  

%de linearização como feito no Lewis and Steven (Aircraft Control and
%Simulation)

function [dfdx, Y] = LinModelX(tempo, estados, controle, i, j,dx,Modelo)
    %delta(fi)/delta(xj) pertubou a função fi(linha) utilizando o elemento
    %xj(coluna)

    t = estados(j);
    estados(j) = t - dx;
    [xdot, ~,Coef,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd1 = xdot(i);
    xCoef1 = Coef; %inserido    
    estados(j) = t + dx;
    [xdot, ~,Coef,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd2 = xdot(i);
    xCoef2 = Coef; %inserido 
    dfdx = (xd2 - xd1)/(2*dx);
    
    %Inserindo o código para obter os CoefAerodinâmico 
         if j == 2 && i == 12
             aux = 2;
          end
    Y =  (xCoef2-xCoef1)/(2*dx);       
    
end