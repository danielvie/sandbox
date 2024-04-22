%Programa para calcular a derivada do estado para ser utilizada no programa
%de linearização como feito no Lewis and Steven (Aircraft Control and
%Simulation)

function [dfdx, Y] = LinModelU(tempo, estados, controle, i, j,du,Modelo)
    %delta(fi)/delta(xj) pertubou a função fi(linha) utilizando o elemento
    %xj(coluna)
    %controle =[dT d_pitch d_yaw d_roll]

    t = controle(j);
    controle(j) = t-du;
    [xdot, ~,Coef,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd1 = xdot(i);
    xCoef1 = Coef; %inserido  
    controle(j) = t+du;
    [xdot, ~,Coef,~] = EOMCompleta(tempo,estados,controle,Modelo);
    xd2 = xdot(i);
    xCoef2 = Coef; %inserido 
    dfdx = (xd2 - xd1)/(2*du);
    
    %Inserindo Código para obter os coeficientes
    if j==3 && i == 7
       aux =1; 
    end
    
    Y =  (xCoef2-xCoef1)/(2*du); 
end