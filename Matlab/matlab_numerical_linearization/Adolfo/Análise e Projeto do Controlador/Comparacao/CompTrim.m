%% Programa p/ comparar os pontos p/ diferentes baselines
%[Vt alpha beta phi theta psi p q r North East Altura]
close all
clc
A = load('BV8Tcheio.mat');
Log1 = A.Log;
clear A;
A = load('BV9Tcheio.mat');
Log2 = A.Log;
clear A;


R2D = 180/pi;
legendaFig = {'BV8Tcheio','BV9Tcheio'};

fprintf('\t\t\t\t\t\tPrograma p/ comparar dois bancos de dados\n')
disp('Deseja comparar com a velocidade ou altitude')
disp('Opção 1 - Velocidade')
disp('Opção 2 - Altura')

opcao = input('Entre com a opção desejada\n');

%% Usuário escolhe a opção desejada

if opcao ==1 
    fprintf('\t\t\t\t\t\tEscolha a opção da velocidade:\n')
    disp('Vel (m/s) [200 220 240 250 260 280 290] = [1 2 3 4 5 6 7 8]')
    aux = input('Opção ');
    
    Vel  = aux;
    Alt1 = 1:length(Log1.Xtrim(:,Vel,12));
    Alt2 = 1:length(Log2.Xtrim(:,Vel,12));
    Vel1 =aux;
    Vel2 =aux;
    xlab2 = Log2.Xtrim(Alt1,Vel1,12);
    xlab1 = Log1.Xtrim(Alt2,Vel2,12);
    L = ['Vel = ',num2str(Log1.Xtrim(1,Vel,1)),' m/s'];
    legenda ='Altitude(m)';
else
    fprintf('\t\t\t\t\t\tEscolha a opção da altitude:\n')
    disp('[0 1000 2000 3000 4000] = [1 2 3 4 5]')
    aux = input('Opção ');
    Alt  = aux;
    Vel1 = 1:length(Log1.Xtrim(Alt,:,12));
    Vel2 = 1:length(Log2.Xtrim(Alt,:,12)); 
    Alt1 = aux;
    Alt2 = aux;
    xlab2 = Log2.Xtrim(Alt1,Vel1,1);
    xlab1 = Log1.Xtrim(Alt2,Vel2,1);
    L = ['Altura = ',num2str(Log1.Xtrim(Alt,1,12)),' m'];
    legenda ='Velocidade(m/s)';    
end

%% Guardando as variavéis
Alpha1 = Log1.Utrim.AoA(Alt1,Vel1);
Alpha2 = Log2.Utrim.AoA(Alt2,Vel2);
Beta1 = Log1.Utrim.Beta(Alt1,Vel1);
Beta2 = Log2.Utrim.Beta(Alt2,Vel2);
Dpitch1 = Log1.Utrim.dPitch(Alt1,Vel1);
Dpitch2 = Log2.Utrim.dPitch(Alt2,Vel2);
Dyaw1 = Log1.Utrim.dYaw(Alt1,Vel1);
Dyaw2 = Log2.Utrim.dYaw(Alt2,Vel2);
Droll1 = Log1.Utrim.dRoll(Alt1,Vel1);
Droll2 = Log2.Utrim.dRoll(Alt2,Vel2);
Manete1 = Log1.Utrim.Manete(Alt1,Vel1);
Manete2 = Log2.Utrim.Manete(Alt2,Vel2);


%% Plotar figuras p/ diferentes baselines
figure()
plot(xlab1,Alpha1*R2D,xlab2,Alpha2*R2D)
legend([legendaFig(1),legendaFig(2)])
xlabel(legenda)
ylabel('Alpha(°)')
title(['Ângulo de ataque p/ ' L])

figure()
plot(xlab1,Beta1*R2D,xlab2,Beta2*R2D)
legend([legendaFig(1),legendaFig(2)])
xlabel(legenda)
ylabel('Beta(°)')
title(['Ângulo de derrapagem p/ ' L])

figure()
plot(xlab1,Dpitch1,xlab2,Dpitch2)
legend([legendaFig(1),legendaFig(2)])
xlabel(legenda)
ylabel('Elevator(°)')
title(['Ângulo p/' L])

figure()
plot(xlab1,Dyaw1,xlab2,Dyaw2)
legend([legendaFig(1),legendaFig(2)])
xlabel(legenda)
ylabel('Rudder(°)')
title(['Ângulo p/' L])

figure()
plot(xlab1,Droll1,xlab2,Droll2)
legend([legendaFig(1),legendaFig(2)])
xlabel(legenda)
ylabel('Aileron(°)')
title(['Ângulo p/' L])


figure()
plot(xlab1,Manete1,xlab2,Manete2)
legend([legendaFig(1),legendaFig(2)])
xlabel(legenda)
ylabel('Manete(0-1)')
title(['Turbina - Valor da manete p/' L])

clear all

