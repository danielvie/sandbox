%% Script para carregar os dados referentes a simulação Simulink

%Referente ao tanque Half
load('../../Dados_Input_Ganhos/BV9_30_03/ssTanqueHalf_0');
load('../../Trim_Lin_Output/DadosTrim_Nivelado/BV9_30_03/ModeloLinear-Half');
load('../../Trim_Lin_Output/DadosTrim_Nivelado/BV9_30_03/LogTrim-Half');
load('../../Ganhos/BV9_30_03/GanhosTanqueHalf');

wa = AtSS.B(2)^0.5;
zetaA = -AtSS.A(2,2)/2/wa;

Alt = 1;
Vel = 6;
