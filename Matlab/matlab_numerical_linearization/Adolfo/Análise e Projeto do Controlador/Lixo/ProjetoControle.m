%% Programa p/ simplificar a função de transferência/Analisar/Projetar
clc
clear all;
close all;
addpath('Trim_Lin_Output')
addpath('FuncaoAux')
addpath('Ganhos')

fprintf('Deseja analisar p/ qual versão BV8 ou Bv9\n')
fprintf('1-BV9_26_03\n2-BV9_30_03\n');
Opcao = input('Entre com a opção desejada\n');

if Opcao == 1
    texto = 'BV9_26_03\';
else
    texto = 'BV9_30_03\'; %TROQUEI PARA BV9Novo
end

fprintf('Deseja analisar e projetar utilizando qual configuração\n')
fprintf('Deseja Analisar tanque\n1-Full\n2-Half\n3-Empty\n');
Opcao = input('Entre com a opção desejada\n');


switch Opcao
    
    case 1
        Str1 = [texto 'ModeloLinear-Full.mat'];
        Str2 = [texto 'LogTrim-Full.mat'];
        Str3 = [texto 'ssTanqueFull'];
    case 2
        Str1 = [texto 'ModeloLinear-Half.mat'];
        Str2 = [texto 'LogTrim-Half.mat'];
        Str3 = [texto 'ssTanqueHalf'];
    case 3
        Str1 = [texto 'ModeloLinear-Zero.mat'];
        Str2 = [texto 'LogTrim-Zero.mat'];
        Str3 = [texto 'ssTanqueZero'];
    otherwise
        error('Opção inválida')
end

load(['Trim_Lin_Output\DadosTrim_Nivelado\' Str1])
load(['Trim_Lin_Output\DadosTrim_Nivelado\' Str2])
[i_max, j_max, ~, ~] = size(Plano_Long);

Altitude   = Log.TrimOptions.H;  %i --- m
Velocidade = Log.TrimOptions.Vt; %j --- m/s

%% Obtenção do modelo simplificado da dinâmica longitudinal/lateral

for i=1:i_max
    
    for j=1:j_max
        
        A_Long = Plano_Long(i,j).A(1:4,1:4);
        B_Long = Plano_Long(i,j).B(1:4,:);
        A_Lat  = Plano_Lat(i,j).A;
        B_Lat  = Plano_Lat(i,j).B;
        
        %% Simplificando p/ a dinâmica de Curto Período plano Longitudinal
        DinLong.Completa = ss(A_Long,B_Long,eye(4),zeros(4,2),...
            'Inputname',{'Manete' 'dPitch'},...
            'OutputName',{'Vt' 'AoA' 'q' 'theta'},...
            'Statename',{'Vt' 'AoA' 'q' 'theta'});
        
        %FT de delta de empena para arfagem
        DinLong.Simple = ss(A_Long(2:3,2:3),B_Long(2:3,2),eye(2),zeros(2,1));
        [n, d] = ss2tf(DinLong.Completa.A,DinLong.Completa.B,[0 0 1 0],[0 0],2);
        G_Completa.q(i,j) = tf(n,d);
        [n,d] = ss2tf(DinLong.Simple.A,DinLong.Simple.B,[0 1],0);
        G_Simple.q(i,j) = tf(n,d);
        
        
        %FT de comando de empuxo para velocidade
        [n, d] = ss2tf(DinLong.Completa.A,DinLong.Completa.B,[1 0 0 0],[0 0],1);
        G_Completa.Vt(i,j) = tf(n,d);
        
        %Teste Lewis
        Aux = DinLong.Completa.A;
        C11 = Aux(2:3,2:3);
        C12 = [Aux(2,1) Aux(2,4); Aux(3,1) Aux(3,4)];
        C21 = [Aux(1,2) Aux(1,3); Aux(4,2) Aux(4,3)];
        C22 = [Aux(1,1) Aux(1,4); Aux(4,1) Aux(4,4)]; 
        N = C22-C21*inv(C11)*C12;
        [n,d] = ss2tf(N,[DinLong.Completa.B(1,1) 0]',[1 0],0);
        Aux = tf(n,d);
        
        [z, p, k] = zpkdata(G_Completa.Vt(i,j));
        s = tf('s');
        %         G_Simple.Vt(i,j) = k*(s - z{1}(3))/((s - p{1}(3))*(s - p{1}(4)));
        G_Simple.Vt(i,j) = k*(s - z{1}(3))/(s^2 -2*real(p{1}(3))*s + real(p{1}(3))^2+imag(p{1}(3))^2);
        
        
        %% Simplificando a dinâmica de rolamento
        
        DinLat.Completa = ss(A_Lat,B_Lat,eye(4),zeros(4,2),...
            'Inputname',{'dYaw' 'dRoll'},...
            'OutputName',{'Beta' 'Phi' 'p' 'r'},...
            'Statename',{'Beta' 'Phi' 'p' 'r'});
        
        [n,d] = ss2tf(DinLat.Completa.A,DinLat.Completa.B,[0 0 1 0],[0 0],2);
        G_Completa.p(i,j) = tf(n,d);
        G_Simple.p(i,j) = tf(DinLat.Completa.B(3,2),[1 -DinLat.Completa.A(3,3)]);
        
        %Dinâmica Látero direcional
        [n,d] = ss2tf(DinLat.Completa.A,DinLat.Completa.B,[0 0 0 1],[0 0],1);
        G_Completa.r(i,j) = tf(n,d);
        A = [A_Lat(1,1) A_Lat(1,4); A_Lat(4,1) A_Lat(4,4)];
        B = [B_Lat(1,1) B_Lat(4,1)]';
        [n, d] = ss2tf(A,B,[0 1],0);
        G_Simple.r(i,j) = tf(n,d);
        
        
        
    end
    
end

%% Projeto do controlador

%Plano Longitudinal
%wa = banda passante do atuador
%zetaA = Amortecimento do atuador
%Gp = planta do sistema sem controlador
%wgm = frequência de cruzamento de ganho
%MF = margem de fase

clear i;
wa = 12*2*pi;
zetaA = 0.7;
Param.Atuador.wa = wa;
Param.Atuador.zetaA = zetaA;
At = tf(wa^2,[1 2*zetaA*wa wa^2]);

%Representação Atuador no Espaço de Estados
aa = [0 1; -wa^2 -2*zetaA*wa];
ba = [0 ;wa^2];
ca = [1 0];
da = 0;

AtSS= ss(aa,ba,ca,da);

%Representação da Turbina em espaço de estados
tauTurb = 1;
TurbSS = ss(-1/tauTurb,1/tauTurb,1,0);


%% Função p/ calcular os ganhos
%Carrega os ganhos quando não é tanque cheio ou vazio

if Opcao == 2
    
    for Alt=1:i_max
        
        for Vel = 1:j_max
            [K, Aux] = GanhosLongitudinal(G_Simple.q(Alt,Vel),At);
            Param.Pitch = Aux;
            Kp.pitch(Alt,Vel) = K(1);
            Kd.pitch(Alt,Vel) = K(2);
            [K, Aux] = GanhosLateralRoll(G_Simple.p(Alt,Vel));
            Param.Roll = Aux;
            Kp.roll(Alt,Vel) = K(1);
            Kd.roll(Alt,Vel) = K(2);
            [Kd.yaw(Alt,Vel), Aux]  = GanhosLateralYawdamper(G_Simple.r(Alt,Vel));
            Param.Roll = Aux;
            Kp.heading(Alt,Vel) = GanhosHeading(9.806,Velocidade(Vel));
            Param.heading = Aux;
            [K, Aux]  = GanhosVelocidade(G_Simple.Vt(Alt,Vel),1,0.7);
            Kp.Vel(Alt,Vel) = K(1);
        end
        
    end
else    
    load(['Ganhos\' texto '\GanhosTanqueHalf.mat'])
end

%% Análise dos Resultados Malha aberta / Malha Fechada


fprintf('\t\t\t\t Análise Malha aberta e Malha fechada\n');
fprintf('Deseja analisar qual eixo\n')
fprintf('1 - Malha aberta eixo longitudinal (atuador - pitch)\n')
fprintf('2 - Malha aberta eixo lateral-direcional (atuador - roll)\n')
fprintf('3 - Malha aberta eixo lateral-direcional (atuador - yawrate)\n')
fprintf('4 - Malha aberta eixo lateral-direcional (valor singular)\n')
fprintf('5 - Malha aberta eixo lateral-direcional (heading)\n')
fprintf('6 - Malha aberta controle de velocidade\n')
fprintf('7 - Todas as anteriores\n');
Opcao2 = input('Entre com a opção desejada  ');

Kturb = 0.0077;
Kh = 1/1000;
Tau_Turb = 1;

switch Opcao2
    
    case 1
        [AltGA, GA.Alt] = MA_LongAlt(AtSS,TurbSS,Kturb,Kh,Plano_Long,Kp,Kd,1);
        MA_Long(AtSS,TurbSS,Kturb,G_Simple,Plano_Long,Kp,Kd,1);
        Gf.Long = MF_Long(TurbSS,AtSS,Plano_Long,Kturb,Kp,Kd,1);
        [MA.Pitch, GA.Pitch] = MA_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd,1);
        Gf.Pitch = MF_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd,1);         
        
    case 2
        [MA.Roll, GA.Roll] = MA_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd,1);
        Gf.Roll = MF_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd,1);
        
    case 3
        [MA.Yaw, GA.Yaw] = MA_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd,1);
        Gf.Yaw = MF_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd,1);
        
    case 4
        MA_latero(AtSS,Plano_Lat,Kp,Kd,0);
        Gf.Latero = MF_Latero(AtSS,Plano_Lat,Kp,Kd,1);
        
    case 5
        MA_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade,0);
        Gf.Heading = MF_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade,0);
        
    case 6
        [MA.VelLoop, GA.VelLoop] = MA_Velocidade(TurbSS,AtSS,G_Simple,Plano_Long,Kturb,Kp,Kd,1);
        Gf.Velocidade = MF_Velocidade(TurbSS,AtSS,G_Simple,Plano_Long,Kturb,Kp,Kd,1);
        
    case 7
        [MA.Pitch, GA.Pitch] = MA_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd,0);
        [MA.Roll, GA.Roll] = MA_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd,0);
        [MA.Yaw, GA.Yaw] = MA_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd,0);
        Gf.Pitch = MF_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd,0);
        Gf.Yaw = MF_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd,0);
        Gf.Roll = MF_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd,0);
        Gf.Latero = MF_Latero(AtSS,Plano_Lat,Kp,Kd,0);
        Gf.Long = MF_Long(TurbSS,AtSS,Plano_Long,Kturb,Kp,Kd,1);
        Gf.Heading = MF_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade,0);        
        
    otherwise
        
end



%% Salvando os dados importantes

if Opcao == 2  % Caso escolha projetar o sistema de controle
    
    save(['Ganhos\' texto '\GanhosTanqueHalf'],'Kp','Kd','Param');
    
end

if Opcao2 == 7 % Caso escolha analisar todos os dados
   
    save(['Analise\' Str3],'GA','Gf','MA','Altitude','Velocidade','G_Completa','G_Simple','Kp','Kd','TurbSS','AtSS');
    
end