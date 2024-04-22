%% Inicio do Programa de Linearização

function [Plano_Long,Plano_Lat,Coef] =  f_Linear(X_Trim,U_Trim,Modelo)
% %% -------------------Linearização das EOM -----------------------------%%
% 
[Plano_Long, Plano_Lat, Coef] = Linearizacao(X_Trim,U_Trim,Modelo);

% %% Comparando o Modelo Não-Linear com o modelo Linear
% while true
%     
%     fprintf('Deseja comparar o modelo linearizado com o modelo não-linear? 1 - Sim / 2 - Não\n\n')
%     C = input('Opção --- ');
%     
%     switch C
%         
%         case 1
%             
%             if opcaoT == 2
%                 
%                 fprintf('Para qual altitude\n')
%                 
%                 for k=1:size(Heigth)
%                     fprintf('Opção %d -- %d m\n',k,Heigth(k));
%                 end
%                 
%                 i = input('Opção --- ');
%                 fprintf('Para qual velocidade\n');
%                 
%                 for k=1:length(Vt_Tab)
%                     fprintf('Opção %d -- %d ms^-1\n',k,Vt_Tab(k));
%                 end
%                 
%                 j = input('Opção --- ');
%                 
%                 
%             else
%                 j =1;
%                 i =1;
%             end
%             
%             A_Long = Plano_Long(i,j).A(1:4,1:4);
%             A_Long = Plano_Long(i,j).A;
%             B_Long = Plano_Long(i,j).B(1:4,1:2);
%             B_Long = Plano_Long(i,j).B;
%             C_Long = eye(5);
%             D_Long = zeros(5,2);
%             A_Lat = Plano_Lat(i,j).A;
%             B_Lat = Plano_Lat(i,j).B;
%             C_Lat = eye(4);
%             D_Lat = zeros(4,2);
%             
%             
%             fprintf('Em qual eixo deseja perturbar(excitar)\nOpção 1-Eixo de Rolamento -- 1°\nOpção 2-Eixo de Arfagem -- 1°\nOpção 3-Eixo de Guinada -- 1°\nOpção 4 - Turbina\n');
%             B = input('Opção --- ');
%             
%             switch B
%                 case 1
%                     Ref = [0  0 0 1*1]';
%                     opcao = 4;
%                                         
%                 case 2
%                     Ref = [0 1*1 0 0]';
%                     opcao =3;
%                     
%                 case 3
%                     Ref = [0 0  1*1 0]';
%                     opcao =4;
%                     
%                 case 4 
%                     Ref = [1 0 0 0]';
%                     opcao =3;
%                     
%                 otherwise
%                     error('Opção Inválida')
%                     
%             end
%         case 2
%             fprintf('Fim do programa');
%             break
%         otherwise
%             error('Opção Inválida')
%     end
%     
%     Modelo.EmpenaMatrix = [1 -1 1; 1 1 1; -1 1 1; -1 -1 1];
%     Modelo.Eixo = 1; %corpo
%     ManeteStep = 0.01;
%     
%     x = squeeze(X_Trim(i,j,:));
%     
%     Controle = [U_Trim.Manete(i,j) U_Trim.dPitch(i,j) U_Trim.dYaw(i,j)  U_Trim.dRoll(i,j)];
%     
%     x0 = [x(1)*cos(x(2))*cos(x(3)) x(1)*sin(x(3)) x(1)*sin(x(2))*cos(x(3)) x(4:12)'];
%     
%     %%
%     %% Rodando a Simulação o Modelo Não Linear
%     close all;
%     
%     config.SimulationMode = 'normal';
%     config.Saveoutput = 'on';
%     config.OutputSavename = 'X_Estados';
%     
%     configLinear.SimulationMode = 'normal';
%     configLinear.Saveoutput = 'on';
%     configLinear.OutputSavename = ['only_long', 'only_lat'] ;
%     
%     if B == 4
%         config.StopTime = '20';
%         configLinear.StopTime = '20';
%         Sinal = -1;
%     else
%         config.StopTime = '10';
%         configLinear.StopTime = '10';
%         Sinal = 1;
%     end
%    
%     y = sim('EQmovSimulink',config);
%    
%     
%     t    = y.get('X_Estados').time;
%     y_NL = y.get('X_Estados').signals.values;
%     
%     clear y;
%     
%     y =  sim('SimulinkLinear1',configLinear);
%     
%     only_long = y.get('logsout').get('only_long').Values;
%     only_lat  = y.get('logsout').get('only_lat').Values;
%     only_long.time = y.get('logsout').get('only_lat').Values.Time;
%     clear y;
%     
%     run('PlotGraf')
% end
% 
% 
% 
% %% Salvando os arquivos relativos as funções de transferência
% 
% save('ModeloLinear','Plano_Long','Plano_Lat')
% Log.Xtrim              = X_Trim;
% Log.Utrim              = U_Trim;
% Log.TrimOptions.H      = Altitude_Tab;
% Log.TrimOptions.Vt     = Vt_Tab;
% Log.TrimOptions.dphi   = dphi_Tab;
% Log.TrimOptions.ROC  = ROC_Tab;
% Log.TrimOptions.gamma  = gamma_Tab;
% Log.TrimOptions.Modelo = Modelo;
% save('LogTrim','Log')

end