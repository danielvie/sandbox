%Plotar as análises para diferentes instantes de voo
%Programa para plotar as margens de estabilidade para o controle de
%arfagem/guinada/rolamento

clear all
close all
addpath('..\FuncaoAux')

fprintf('Deseja analisar p/ qual versão BV8 ou Bv9\n')
fprintf('1 - BV9_26_03\n2 - BV9_30_03\n');
Opcao = input('Entre com a opção desejada\n');

if Opcao == 1    
    texto = 'BV9_26_03\';
else
    texto = 'BV9_30_03\';
end

fprintf('Qual situação deseja calcular e avaliar o sistema\n')
fprintf('0-Nominal\n1-Ldelta -50 percento\n2 - Redução de 20 percento na eficiênica da empena\n');
Caso = input('Entre com a opção desejada: ');

Str3 = [texto num2str(Caso)];


fprintf('1 - Plano Longitudinal\n')
fprintf('2 - Plano Lateral-Roll\n')
fprintf('3 - Plano Lateral-Yaw\n')
opcao = input('Entre com o plano que deseja comparar\n');

for i=2:2    
    if i==1
        load([texto 'ssTanqueFull_' num2str(Caso)]);
        Str = 'ssTanqueFull';
    elseif i==2
        load([texto 'ssTanqueHalf_' num2str(Caso)]);
        Str = 'ssTanqueHalf';
    else
        load([texto 'ssTanqueZero_' num2str(Caso)]); 
        Str = 'ssTanqueZero';
    end
    
    switch opcao
        
        case 1
            
            %Cálculo malha fechada/aberta
            figure()
            step(Gf.Pitch(:,:).PitchComplete,10)
            title(['Plano de Arfagem ' Str])
            
            figure()
            bode(GA.Pitch(:,:).PitchComplete)
            PlotMargens(MA.Pitch.Gm,MA.Pitch.Pm,MA.Pitch.wgm,MA.Pitch.wpm,Altitude,Velocidade)
            
            [InstavelPitch.Alt, InstavelPitch.Vel] = find(MA.Pitch.S == 0);
            
        case 2
            figure()
            step(Gf.Roll(:,:).RollComplete,5)
            title(['Plano de Látero-Roll ' Str])
            
            figure()
            bode(GA.Roll(:,:).RollComplete)
            
            PlotMargens(MA.Roll.Gm,MA.Roll.Pm,MA.Roll.wgm,MA.Roll.wpm,Altitude,Velocidade)
            [InstavelRoll.Alt, InstavelRoll.Vel] = find(MA.Roll.S == 0);
            
        case 3
            
            figure()
            initial(Gf.Yaw(:,:).YawComplete,[0 0 0 5*pi/180 0 0 0 0])
            title(['Plano de Látero-Yaw ' Str])
            
            figure()
            bode(GA.Yaw(:,:).YawComplete)
            
            PlotMargens(MA.Pitch.Gm,MA.Pitch.Pm,MA.Pitch.wgm,MA.Pitch.wpm,Altitude,Velocidade)
            [InstavelYaw(i).Alt, InstavelYaw(i).Vel] = find(MA.Yaw.S == 0);
            
        otherwise
            error('Opção inválida')
            
    end
    
    
end