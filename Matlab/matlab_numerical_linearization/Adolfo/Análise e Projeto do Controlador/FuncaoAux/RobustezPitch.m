%% Análise de Robustez do sistema do sistema de arfagem considerando as incertezas paramétricas
%Avaliando incertezas parámetricas
close all;
clear all;
%% Carregar Ganho e as FT

load('../Trim_Lin_Output/DadosTrim_Nivelado/BV9_30_03/ModeloLinear-Half.mat')
load('../Analise/BV9_30_03/ssTanqueHalf.mat')
%Carregando os coeficientes
t = 0:0.01:2*pi;
x = 9*cos(t);
y = -180 + 45*sin(t);

%Ft do Atuador & Integrador & Computador Digital
wn = 72;
zeta =0.8;
At = tf(wn^2,[1 2*zeta*wn wn^2]);
Int = tf(1,[1 0]);
Ts = 1/100;
[n, d] = pade(Ts,1);
Delay = tf(n,d); %(-s+2/T)/(s+2/T)

for i=1:4
    for j=1:7
        Alt = i;
        Vel = j;
        %[Malpha, Mq, Zalpha Zq, Lbeta, Nbeta, Ybeta, Nr,Lp] = YA
        %[Mdelta,Zdelta,Ndelta,Ydelta, DeltaYaw/Roll,Ldelta,DeltaRoll/Yaw]
        MdeltaN = Coef(Alt,Vel).Yb(1);
        ZdeltaN = Coef(Alt,Vel).Yb(2);
        MalphaN = Coef(Alt,Vel).Ya(1);
        MqN     = Coef(Alt,Vel).Ya(2);
        ZalphaN = Coef(Alt,Vel).Ya(3);
        VtN = 200;
        
        Gpitch = G_Simple.q(Alt,Vel);
        
        Mdelta = ureal('Mdelta',MdeltaN,'Percentage',[-20 20]);
        Zdelta = ureal('Zdelta',ZdeltaN,'Percentage',[-20 20]);
        Malpha = ureal('Malpha',MalphaN,'PlusMinus',[-10 10]);
        Zalpha = ureal('Zalpha',ZalphaN,'Percentage',[-20 20]);
        Vt = ureal('Vt',VtN,'Percentage',[-5 5]);
        Mq = ureal('Mq',MqN,'Percentage',[-40 40]);
        
        
        %% Função de Transferência forma analítica literatura
        q = tf([Vt*Mdelta (Zdelta*Malpha - Zalpha*Mdelta) ],[Vt -(Zalpha + Vt*Mq) (Mq*Zalpha - Vt*Malpha)]);
        
        %% Malha Aberta
        figure(1)
        C = tf([Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)],1);
        Ga = C*series(At*Delay,q)*tf(1,[1 0]);
        nichols(Ga);
        hold on
        plot(y,x,'r');
        nichols(Ga.nominal,'r')
        
        %% Malha Fechada
        figure(2)
        Gfin = feedback(At*Delay*q,Kd.pitch(Alt,Vel));
        Gf = feedback(Kp.pitch(Alt,Vel)*Gfin*tf(1,[1 0]),1);
        step(Gf,10)
        grid on
        pause()
    end
end
%% Análise de Sensitivadade

% Ndelta = 96.72;
% Ydelta = -46.53;
% Nbeta = 77.13;
% Ybeta = -62.26;
% Vt = 250;
% Nr = -0.866;
%
% Ndelta = Ndelta*[0.5 0.9 1 1.1 2];
% Ydelta = Ydelta*ones(1,5);
% Nbeta  = Nbeta*ones(1,5);
% Ybeta  = Ybeta*ones(1,5);
% Nr     = Nr*ones(1,5);
% Vt     = Vt*ones(1,5);
%
% figure()
% hold all
% for i = 1:5
%
%     r = tf([Ndelta(i) (Ydelta(i)*Nbeta(i) - Ybeta(i)*Ndelta(i))/Vt(i) ],[1 -(Ybeta(i)/Vt(i)+Nr(i)) (Nbeta(i)+Nr(i)*Ybeta(i)/Vt(i))]);
%     Ga = Kd.yaw(Alt,Vel)*At*Delay*r;
%     bode(Ga);
%
% end
% legend('0.5', '0.9','Nominal', '1.1', '2');
