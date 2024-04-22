%% Análise de Robustez do sistema
%Avaliando incertezas parámetricas
close all
%% Carregar Ganho e as FT

load('../Trim_Lin_Output/DadosTrim_Nivelado/BV9_30_03/ModeloLinear-Half.mat')
load('../Analise/BV9_30_03/ssTanqueHalf.mat')

%Ft do Atuador & Integrador & Computador Digital

wn = 72;
zeta = 0.8;
At = tf(wn^2,[1 2*zeta*wn wn^2]);
Int = tf(1,[1 0]);
Ts = 1/100;
[n, d] = pade(Ts,1);
Delay = tf(n,d); %(-s+2/T)/(s+2/T)

Alt = 2; %Alt =[0 1000 2000 3000 4000];
Vel = 4; %Vel =[160 180 200 220 240 250 260];


Groll = G_Simple.p(Alt,Vel);
[n, d] = tfdata(Groll);

Ldelta_aux = n{1}(2);
Lp_aux = d{1}(2);

Ldelta_aux = Ldelta_aux*[1 0.7 1.3 1.3 0.7];
Lp_aux = Lp_aux*[1 0.7 1.3 0.7 1.3];

% Ldelta_aux = Ldelta_aux*[0.5 0.9 1 1.1 2];
% Lp_aux = Lp_aux*[2 1 1 1 0.5];

figure(1)
hold on
figure(2)
hold on
for i=1:length(Lp_aux)
    
    Ldelta = Ldelta_aux(i);
    Lp = Lp_aux(i);    
    Groll = tf(Ldelta,[1 Lp]);
  
    % Malha Aberta
    Ga = Groll*Int*tf([Kd.roll(Alt,Vel) Kp.roll(Alt,Vel)],1)*At*Delay;
    figure(1)
    bode(Ga);
    
    % Malha Fechada
    aux  = feedback(Delay*At*Groll,Kd.roll(Alt,Vel));
    Gf = feedback(Kp.roll(Alt,Vel)*aux*Int,1);
    figure(2)
    step(Gf,2)
    
end
figure(1)
legend('Nominal','Lp&Ld_Down','Lp&Ld_UP','Lp_D&Ld_U','Lp_U&Ld_D')
figure(2)
legend('Nominal','Lp&Ld_Down','Lp&Ld_UP','Lp_D&Ld_U','Lp_U&Ld_D')