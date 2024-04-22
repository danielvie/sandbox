%% Programa para calcular a derivada do estado para ser utilizada no programa
% Vers�o 1.0 - �ltima Atualiza��o - 16/07/2014 (Adolfo)  

%de lineariza��o como feito no Lewis and Steven (Aircraft Control and
%Simulation)

function [dfdx, Y] = LinModelX(tempo, estados, controle, i, j,dx,Modelo)
    %delta(fi)/delta(xj) pertubou a fun��o fi(linha) utilizando o elemento
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
    
    %Inserindo o c�digo para obter os CoefAerodin�mico 
         if j == 2 && i == 12
             aux = 2;
          end
    Y =  (xCoef2-xCoef1)/(2*dx);       
    
end