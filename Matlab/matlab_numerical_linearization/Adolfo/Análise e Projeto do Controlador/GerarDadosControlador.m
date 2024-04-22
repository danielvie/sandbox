%% Programa p/ simplificar a fun��o de transfer�ncia/Analisar/Projetar
clc
clear all;
close all;
addpath('Trim_Lin_Output')

fprintf('Deseja gerar os dados p/ qual vers�o\n')
fprintf('1-BV9-Caso2\n2-BV9_30_03\n');
Opcao = input('Entre com a op��o desejada\n');

if Opcao == 1
    texto = 'BV9-CG\'; %Prop Excel
else
    texto = 'BV9_30_03\'; %TROQUEI PARA BV9 --- Prop PPT
end

fprintf('Deseja analisar e projetar utilizando qual configura��o\n')
fprintf('Deseja Analisar tanque\n1-Full\n2-Half\n3-Empty\n');
Opcao = input('Entre com a op��o desejada\n');


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
        error('Op��o inv�lida')
end

Caminho = ['Trim_Lin_Output\DadosTrim_Nivelado\' Str1];
load(['Trim_Lin_Output\DadosTrim_Nivelado\' Str1])
load(['Trim_Lin_Output\DadosTrim_Nivelado\' Str2])
[i_max, j_max, ~, ~] = size(Plano_Long);

Altitude   = Log.TrimOptions.H;  %i --- m
Velocidade = Log.TrimOptions.Vt; %j --- m/s

%% Para gerar os casos n�o nominais
%Caso 1 - Redu��o da efici�ncia da empena em rolamento
Caso = 0;
switch Caso
    case 0
        aux = 1;
    case 1
        for i=1:i_max
            for j=1:j_max
                Plano_Lat(i,j).B(3,2) = Plano_Lat(i,j).B(3,2)*0.5;
            end
        end
        
    case 2
        for i=1:i_max
            for j=1:j_max
                Plano_Lat(i,j).B = Plano_Lat(i,j).B*0.8;
                Plano_Lat(i,j).A(1,1) = Plano_Lat(i,j).A(1,1)*0.9; %Yb
                Plano_Lat(i,j).A(4,1) = Plano_Lat(i,j).A(4,1)*0.8; %Nbeta
                Plano_Lat(i,j).A(3,1) = Plano_Lat(i,j).A(4,1)*1.1; %Lbeta
                Plano_Long(i,j).B(:,2) = Plano_Long(i,j).B(:,2)*0.8; %Empena 
                Plano_Long(i,j).A(3,2) = Plano_Long(i,j).A(3,2)*0.9; %Malpha
                Plano_Long(i,j).A(2,2) = Plano_Long(i,j).A(2,2)*0.9; %Zalpha
            end
        end
end

%% Obten��o do modelo simplificado da din�mica longitudinal/lateral

for i=1:i_max
    for j=1:j_max
        
        A_Long = Plano_Long(i,j).A(1:4,1:4);
        B_Long = Plano_Long(i,j).B(1:4,:);
        A_Lat  = Plano_Lat(i,j).A;
        B_Lat  = Plano_Lat(i,j).B;
        
        %Simplificando p/ a din�mica de Curto Per�odo plano Longitudinal
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
        
        
        %Simplificando a din�mica de rolamento
        DinLat.Completa = ss(A_Lat,B_Lat,eye(4),zeros(4,2),...
            'Inputname',{'dYaw' 'dRoll'},...
            'OutputName',{'Beta' 'Phi' 'p' 'r'},...
            'Statename',{'Beta' 'Phi' 'p' 'r'});
        
        [n,d] = ss2tf(DinLat.Completa.A,DinLat.Completa.B,[0 0 1 0],[0 0],2);
        G_Completa.p(i,j) = tf(n,d);
        G_Simple.p(i,j) = tf(DinLat.Completa.B(3,2),[1 -DinLat.Completa.A(3,3)]);
        
        %Din�mica L�tero direcional
        [n,d] = ss2tf(DinLat.Completa.A,DinLat.Completa.B,[0 0 0 1],[0 0],1);
        G_Completa.r(i,j) = tf(n,d);
        A = [A_Lat(1,1) A_Lat(1,4); A_Lat(4,1) A_Lat(4,4)];
        B = [B_Lat(1,1) B_Lat(4,1)]';
        [n, d] = ss2tf(A,B,[0 1],0);
        G_Simple.r(i,j) = tf(n,d);
        
    end
    
end
%Gerando a din�mica do atuador (empena e turbina)

%wa = banda passante do atuador
%zetaA = Amortecimento do atuador
%Gp = planta do sistema sem controlador
%wgm = frequ�ncia de cruzamento de ganho
%MF = margem de fase

wa = 12*2*pi;
zetaA = 0.7;
Param.Atuador.wa = wa;
Param.Atuador.zetaA = zetaA;
At = tf(wa^2,[1 2*zetaA*wa wa^2]);

%Representa��o Atuador no Espa�o de Estados
aa = [0 1; -wa^2 -2*zetaA*wa];
ba = [0 ;wa^2];
ca = [1 0];
da = 0;
AtSS= ss(aa,ba,ca,da);

%Representa��o da Turbina em espa�o de estados
tauTurb = 1;
TurbSS = ss(-1/tauTurb,1/tauTurb,1,0);


fprintf('Modelo gerado a partir da seguinte configura��o\n')
fprintf('%s\n', Str1);
fprintf('Caso - %d \n', Caso);
Gravar = input('Deseja gravar ?');

if Gravar == 1
    save(['Dados_Input_Ganhos\' [Str3 '_' num2str(Caso)] ],'Altitude','Velocidade','G_Completa','G_Simple','TurbSS','AtSS',...
        'Plano_Lat','Plano_Long','Caso','Caminho');
end