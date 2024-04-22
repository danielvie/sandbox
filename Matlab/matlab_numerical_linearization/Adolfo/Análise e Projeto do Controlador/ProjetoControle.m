%% Programa p/ simplificar a função de transferência/Analisar/Projetar
clc
% clear all;
close all;

addpath('FuncaoAux')
addpath('Calculo Ganhos')

fprintf('Deseja analisar p/ qual versão\n')
fprintf('1-BV9-Caso2\n2-BV9_30_03\n');
Opcao = input('Entre com a opção desejada\n');

if Opcao == 1
    texto = 'BV9_26_03\';
else
    texto = 'BV9_30_03\'; %TROQUEI PARA BV9Novo
end

fprintf('\nDeseja analisar e projetar utilizando qual configuração\n')
fprintf('Deseja Analisar tanque\n1-Full\n2-Half\n3-Empty\n');
Opcao = input('Entre com a opção desejada\n');

switch Opcao    
    case 1      
        Str3 = [texto 'ssTanqueFull_'];
    case 2       
        Str3 = [texto 'ssTanqueHalf_'];
    case 3      
        Str3 = [texto 'ssTanqueZero_'];
    otherwise
        error('Opção inválida')
end

fprintf('Qual situação deseja calcular e avaliar o sistema\n')
fprintf('0 - Nominal\n1 - Ldelta -50 percento\n2 - Redução de 50 percento das eficiências das empenas\n');
fprintf('3 - CG 20cm para trás\n'); 
Caso = input('Entre com a opção desejada: ');

Casoaux = Caso;
% Casoaux = 6;
Str3 = [Str3 num2str(Casoaux)];
load(['Dados_Input_Ganhos\' Str3]);

i_max = length(Altitude);
j_max = length(Velocidade);
%% Função p/ calcular os ganhos
%Carrega os ganhos quando não é tanque cheio ou vazio

if Opcao == 2 && Casoaux ~= 12
    
    for Alt=1:i_max
        
        for Vel = 1:j_max
            [K, Aux] = GanhosLongitudinal(G_Simple.q(Alt,Vel),AtSS);
            [K2, Aux2] = GanhosLongitudinal2(G_Simple.q(Alt,Vel),AtSS);
            Param.Pitch = Aux;
            Kp.pitch(Alt,Vel) = K(1);
            Kd.pitch(Alt,Vel) = K(2);
            
            %Teste 23/04 ganhoslongitudinal 2
            Kpaux(Alt,Vel) = K2(1);
            Kdaux(Alt,Vel) = K2(2);
            
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
    Casoaux = 6;
    load(['Ganhos\' texto '\GanhosTanqueHalf_' num2str(Casoaux)])
%     load(['Ganhos\' texto '\GanhosTanqueHalf'])
end

%% Análise dos Resultados Malha aberta / Malha Fechada

fprintf('\n\n\t\t\t\t Análise Malha aberta e Malha fechada\n');
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
        Gf.Long = MF_Long(TurbSS,AtSS,Plano_Long,Kturb,Kh,Kp,Kd,1);
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
        Gf.Long = MF_Long(TurbSS,AtSS,Plano_Long,Kturb,Kh,Kp,Kd,1);
        Gf.Heading = MF_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade,0);        
    otherwise
        
end



%% Salvando os dados importantes

Casoaux = 6;
Str3 = [Str3 num2str(6)];

if Opcao == 2  % Caso escolha projetar o sistema de controle    
    save(['Ganhos\' texto '\GanhosTanqueHalf_' num2str(Casoaux)],'Kp','Kd','Kturb','Kh','Param');    
end

if Opcao2 == 7 % Caso escolha analisar todos os dados   
    save(['Analise\' Str3],'GA','Gf','MA','Altitude','Velocidade','G_Completa','G_Simple','Kp','Kd','TurbSS','AtSS');    
end