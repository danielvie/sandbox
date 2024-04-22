%% Programa p/ simplificar a função de transferência/Analisar/Projetar
clc
clear all;
close all;
addpath('C3')
addpath('FuncaoAux')

fprintf('Deseja analisar p/ qual versão BV8 ou Bv9\n')
fprintf('1-BV8\n2-BV9\n');
Opcao = input('Entre com a opção desejada\n');

if Opcao == 1
    
    texto = 'BV8\';
else
    texto = 'BV9\';
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

load(['C3\DadosTrim\' Str1])
load(['C3\DadosTrim\' Str2])
load('C3\FigProj\GanhosTanqueHalf.mat')
[i_max, j_max, ~, ~] = size(Plano_Long);

Altitude   = Log.TrimOptions.H;  %i --- m
Velocidade = Log.TrimOptions.Vt; %j --- m/s
Kr =0;
J=1;
% j_max = 6;


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
% Plano Longitudinal
%wa = banda passante do atuador
%zetaA = Amortecimento do atuador
%Gp = planta do sistema sem controlador
%wgm = frequência de cruzamento de ganho
%MF = margem de fase

clear i;
wa = 10*2*pi;
zetaA = 0.7;
At = tf(wa^2,[1 2*zetaA*wa wa^2]);

%Representação Atuador no Espaço de Estados
aa = [0 1; -wa^2 -2*zetaA*wa];
ba = [0 ;wa^2];
ca = [1 0];
da = 0;

AtSS= ss(aa,ba,ca,da);

%Integrador
Int = tf(1,[1 0]);

%% Função p/ calcular os ganhos

% for Alt=1:i_max
%
%     for Vel = 1:j_max
%         K = GanhosLongitudinal(G_Simple.q(Alt,Vel),At);
%         Kp.pitch(Alt,Vel) = K(1);
%         Kd.pitch(Alt,Vel) = K(2);
%         K = GanhosLateralRoll(G_Simple.p(Alt,Vel));
%         Kp.roll(Alt,Vel) = K(1);
%         Kd.roll(Alt,Vel) = K(2);
%         Kd.yaw(Alt,Vel)  = GanhosLateralYawdamper(G_Simple.r(Alt,Vel));
%         Kp.heading(Alt,Vel) = GanhosHeading(9.806,Velocidade(Vel));
%     end
%
% end


%% Análise dos Resultados Malha aberta / Malha Fechada

fprintf('\t\t\t\t Análise Malha aberta e Malha fechada\n');
fprintf('Deseja analisar qual eixo\n')
fprintf('1 - Malha aberta eixo longitudinal (atuador - pitch)\n')
fprintf('2 - Malha aberta eixo lateral-direcional (atuador - roll)\n')
fprintf('3 - Malha aberta eixo lateral-direcional (atuador - yawrate)\n')
fprintf('4 - Malha aberta eixo lateral-direcional (valor singular)\n')
fprintf('5 - Malha aberta eixo lateral-driecional (heading)\n')
Opcao = input('Entre com a opção desejada  ');

switch Opcao
    
    case 1
        [MA.Pitch, GA.Pitch] = MA_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd);
        Gf.Pitch = MF_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd);
               
    case 2
        [MA.Roll, GA.Roll] = MA_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd);
        Gf.Roll = MF_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd);
       
    case 3
        [MA.Yaw, GA.Yaw] = MA_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd);
        Gf.Yaw = MF_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd);
       
    case 4
        MA_latero(AtSS,Plano_Lat,Kp,Kd);
        Gf.Latero = MF_Latero(AtSS,Plano_Lat,Kp,Kd);        
               
    case 5
        MA_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade);
        Gf.Heading = MF_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade);
        
    otherwise
         
end

figure();
hold all;

for i = 1:1
    
    for Alt=1:i_max
        
        %         h(Alt) = figure(fig);
        %         hold all
        
        for Vel=1:j_max
            
            
            if i==1 %Malha Aberta Longitudinal
                
                GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                aux = series(AtSS,GpitchSS);
                K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                
                GA(Alt,Vel).PitchComplete = ss(aux.A,aux.B,K*aux.C,0); %Completa
                
                Gp = At*G_Simple.q(Alt,Vel);
                GA(Alt,Vel).PitchSimple = Gp*Int*tf([Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)],1); %Simplificada
                
                %Cálculo das margens de estabilidade
                
                [MA.Pitch.Gm(Alt,Vel), MA.Pitch.Pm(Alt,Vel), MA.Pitch.wgm(Alt,Vel), MA.Pitch.wpm(Alt,Vel)] = margin(GA(Alt,Vel).PitchComplete);
                S = allmargin(GA(Alt,Vel).PitchComplete);
                MA.Pitch.S(Alt,Vel) = S.Stable;
                                bode(GA(Alt,Vel).PitchComplete);
                
            elseif i==2 %Malha Fechada Longitudinal
                
                GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                aux = series(AtSS,GpitchSS);
                K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                
                Gf(Alt,Vel).PitchComplete = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(Alt,Vel),[0 0 0 1 0 0], 0); %completa
                
                auxtf = feedback(G_Simple.q(1,6)*At,Kd.pitch(Alt,Vel));
                Gf(Alt,Vel).PitchSimple = feedback(Kp.pitch(Alt,Vel)*auxtf*Int,1); %Simplifcada
                %             pzmap(GfSS_pitch)
                %                 step(Gf(Alt,Vel).PitchComplete,10)
                
            elseif i==3 %Malha Aberta Rolamento
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                GA(Alt,Vel).RollComplete = ss(aux.A,aux.B,K*aux.C,0); %Completa
                GA(Alt,Vel).RollSimple   = G_Simple.p(Alt,Vel)*Int*tf([Kd.roll(Alt,Vel) Kp.roll(Alt,Vel)],1)*At;
                
                %Cálculo das margens de estabilidade
                [MA.Roll.Gm(Alt,Vel),MA.Roll.Pm(Alt,Vel),MA.Roll.wgm(Alt,Vel),MA.Roll.wpm(Alt,Vel)] = margin(GA(Alt,Vel).RollComplete);
                S = allmargin(GA(Alt,Vel).RollComplete);
                MA.Roll.S(Alt,Vel) = S.Stable;
                %                 bode(GA(Alt,Vel).RollComplete);
                
                
            elseif i==4 %Malha Fechada Rolamento
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gf(Alt,Vel).RollComplete = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %Completa
                aux  = feedback(At*G_Simple.p(Alt,Vel),Kd.roll(Alt,Vel));
                Gf(Alt,Vel).RollSimple = feedback(Kp.roll(Alt,Vel)*aux*Int,1);
                step(Gf(Alt,Vel).RollComplete)
                %                 pzmap(Gf(Alt,Vel).RollComplete)
                
            elseif i==5 %Malha Aberta Yawdamper
                
                GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,1), [0 0 0 1],0);
                aux = series(AtSS,GyawSS);
                GA(Alt,Vel).YawComplete = ss(aux.A,aux.B,Kd.yaw(Alt,Vel)*aux.C,0); %Completo
                GA(Alt,Vel).YawSimple = G_Simple.r(Alt,Vel)*At*Kd.yaw(Alt,Vel);    %Simplificado
                
                %Cálculo das margens de estabilidade
                [MA.Yaw.Gm(Alt,Vel),MA.Yaw.Pm(Alt,Vel),MA.Yaw.wgm(Alt,Vel),MA.Yaw.wpm(Alt,Vel)] = margin(GA(Alt,Vel).YawComplete);
                S = allmargin(GA(Alt,Vel).YawComplete);
                MA.Yaw.S(Alt,Vel) = S.Stable;
                bode(GA(Alt,Vel).YawComplete);
                
                
            elseif i==6 %Malha Fechada yawdamper
                
                GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,1), [0 0 0 1],0);
                aux = series(AtSS,GyawSS);
                Gf(Alt,Vel).YawComplete = ss(aux.A-aux.B*[0 0 0 Kd.yaw(Alt,Vel) 0 0],aux.B,[0 0 0 1 0 0], 0); %Completo
                Gf(Alt,Vel).YawSimple = feedback(G_Simple.r(Alt,Vel)*At,Kd.yaw(Alt,Vel)); %Simplificado
                %                 initial(Gf(Alt,Vel).YawComplete,[1 0 0 10 0 0])
                
                
                
                %             elseif i==7 %Malha Aberta Comparação ganho fixo e variável -- Longitudinal
                %
                %
                %                 GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                %                 aux = series(AtSS,GpitchSS);
                %                 K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                %
                %                 GaSS_pitch = ss(aux.A,aux.B,K*aux.C,0); %completa - Variante no tempo os ganhos
                %
                %                 K = [Kd.pitch(4,6) Kp.pitch(4,6)];
                %                 GaSS_fixo = ss(aux.A,aux.B,K*aux.C,0); %completa - ganhos fixos
                %
                %                 bode(GaSS_pitch,GaSS_fixo);
                %
                %
                %             elseif i==8 %Malha Fechada Longitudinal
                %
                %                 GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                %                 aux = series(AtSS,GpitchSS);
                %                 K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                %
                %                 GfSS_pitch = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(Alt,Vel),[0 0 0 1 0 0], 0); %Completa - Variável
                %
                %                 K = [Kd.pitch(4,6) Kp.pitch(4,6)];
                %
                %                 GfSS_fixo = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(4,6),[0 0 0 1 0 0], 0); %Completa - Fixo
                %
                %                 %             pzmap(GfSS_pitch)
                %                 step(GfSS_pitch,GfSS_fixo,10)
                
                
            elseif i==9 %Heading Control Malha Fechada
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gfss = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %completa
                
                A = Gfss.A;
                A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
                A(:,7) = zeros(7,1);
                B = Gfss.B;
                B(7,1) = 0;
                Gheading_SS = ss(A ,B, [zeros(1,6) 1],0);
                K = Kp.heading(Alt,Vel);
                %                 Gf_headingSS = ss(A-B*[zeros(1,6) K],B*K,[0 1 zeros(1,5); zeros(1,6) 1],[0;0]); %Malha Fechada Heading
                Gf(Alt,Vel).heading = ss(A-B*[zeros(1,6) K],B*K,[zeros(1,6) 1],0); %Malha Fechada Heading
                %                 step(Gf(Alt,Vel).heading);
                
            elseif i==10 %Malha Aberta Heading
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gfss = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %Completa
                
                A = Gfss.A;
                A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
                A(:,7) = zeros(7,1);
                B = Gfss.B;
                B(7,1) = 0;
                
                GaSS_heading = ss(A, B*Kp.heading(Alt,Vel), [zeros(1,6) 1],0);
                %                 bode(GaSS_heading)
                
                
                %                 GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 1 0 0],[0;0]);
                %                 aux = series(AtSS,GrollSS);
                %                 A = Gfss.A;
                %                 A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
                %                 A(:,7) = zeros(7,1);
                %                 B = Gfss.B;
                %                 B(7,1) = 0;
                %                 C =[0 1 zeros(1,5); 0 0 1 zeros(1,4); zeros(1,6) 1];
                %                 K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) Kp.heading(Alt,Vel)];
                %                 GaSS_heading = ss(A, B,K*C,0);
                %                 bode(GaSS_heading);
                
                
            elseif i == 11 %Malha Latero-Direcional
                
                %Malha Aberta
                GAteste = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, [0 1 0 0 ; 0 0 1 0; 0 0 0 1],[0 0;0 0; 0 0]);
                aux = series(AtSS,GAteste);
                Kteste = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) 0 ;0 0 Kd.yaw(Alt,Vel)];
                Gass_teste = ss(aux.A,aux.B,Kteste*aux.C,0);
                
                sigma(Gass_teste)
                
                %Malha Fechada
                Kforward = [1 0; 0 Kp.roll(Alt,Vel)];
                K = [zeros(1,3) Kd.yaw(Alt,Vel) zeros(1,4); 0 Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) zeros(1,5)];
                Gf = ss(aux.A-aux.B*K,aux.B*Kforward,[0 1 zeros(1,6); 0 0 0 1 zeros(1,4)],0);
                step(Gf,2)
                
            end
            
            
        end
        
        
        
        
    end
    
end
%


%% Salvando os dados importantes

% save('GanhosTanqueHalf','Kp','Kd');

% save('ssTanqueFull','G_Completa','G_Simple');

% save(['Analise/' Str3],'GA','Gf','MA','Altitude','Velocidade','G_Completa','G_Simple','Kp','Kd');

% savefig(h,'C3\FigProj\MA_Heading');


%% Plotando as Margens de EstabilidadePlotMargens(MA.Pitch.Gm,MA.Pitch.Pm,MA.Pitch.wgm,MA.Pitch.wpm,Altitude,Velocidade)


