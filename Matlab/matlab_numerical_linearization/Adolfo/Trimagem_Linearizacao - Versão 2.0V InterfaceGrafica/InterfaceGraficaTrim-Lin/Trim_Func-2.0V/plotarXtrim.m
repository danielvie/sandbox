%% Programa de PlotXtrim
%Programa para plotar os valores das variáveis trimadas
%Versão 2.0 - Última Atualização - 07/08/2014 (Adolfo)

%Estado correspondente [Vt alpha beta phi theta psi p q r XN XE XD]
function plotarXtrim(X,U_Trim,J, Turb, Variavel,PopUp)

R2G = 180/pi;
[n1, n2] = size(X);
TituloXtrim = {'Variação do ângulo de Ataque','Variação do ângulo Beta'};
TituloUtrim = {'Manete','dPitch','dYaw','dRoll'};
Ylegenda = {'Vt','AoA(°)','Beta(°)'};
Ulegenda ={'Manete(%)','dPitch(°)','dYaw(°)','dRoll(°)'};
Linha = {'b','r','g','k','m','c','b-*','r-*','g-*','k-*','m-*','c-*'};

% Mask = [2,3,14,15,16,17,18]; %alpha, beta, manete, dpitch,dyaw,droll

Alt = X(:,1,12);
Vt = X(1,:,1);
J_final = length(U_Trim.AoA(1,:));
J_final = length(U_Trim.AoA(:,1)); %para vel no eixo X

if PopUp == 1
   figure() 
end

switch Variavel
    
    case 1        
        
        for j = 1:J_final            
            hold on
%             plot(Alt,U_Trim.AoA(:,j)*R2G,Linha{j});
            plot(Vt,U_Trim.AoA(j,:)*R2G,Linha{j});
            L = ['Alt =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        title('AoA')
%         xlabel('Altitude(m)')
        xlabel('Velocidade(m/s)')
        ylabel('AoA(°)')
        
    case 2        
       
        for j = 1:J_final
            hold on
%             plot(Alt,U_Trim.Beta(:,j)*R2G,Linha{j});
            plot(Vt,U_Trim.Beta(j,:)*R2G,Linha{j});
            L = ['Alt =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        title('Beta')
        xlabel('Velocidade(m/s)')
        ylabel('Beta(°)')
        
    case 3        
        for j = 1:J_final
            hold on
            plot(Vt,U_Trim.dPitch(j,:),Linha{j});
            L = ['Alt =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        hold off
        title('dPitch')
        xlabel('Velocidade(m/s)')
        ylabel('dPitch(°)')
        
    case 4        
        for j = 1:J_final
            hold on
            plot(Vt,U_Trim.dYaw(j,:),Linha{j});
            L = ['Alt =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        hold off
        title('dYaw')
        xlabel('Velocidade(m/s)')
        ylabel('dYaw(°)')
        
    case 5       
        for j = 1:J_final
            hold on
            plot(Vt,U_Trim.dRoll(j,:),Linha{j});
            L = ['V =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        hold off
        title('dRoll')
        xlabel('Velocidade(m/s)')
        ylabel('dRoll(°)')
        
    case 6        
        for j = 1:J_final
            hold on
%             plot(Alt,U_Trim.Manete(:,j),'Color',color{j});
            plot(Vt,Turb(j,:),Linha{j});
            L = ['Alt =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        title('Manete')
        xlabel('Velocidade(m/s)')
        ylabel('Manete(N)')
        hold off
        
        
    case 7        
        for j = 1:J_final
            hold on
            plot(Vt,J(j,:),Linha{j});
            L = ['Alt =',num2str(X(j,1,12))];
            Lee(j) = {L};
        end
        legend(Lee,'Location','NorthWest')
        title('Função Custo')
        xlabel('Velocidade(m/s)')
        ylabel('Custo')
        hold off
        
        %     figure()
        %     hold all
        %     for j = 1:J_final
        %         plot(Vt,Turb(j,:));
        %     end
        %     legend(Lee,'Location','NorthWest')
        %     title('Empuxo vs Velocidade')
        %     xlabel('Velocidade(m/s)')
        %     ylabel('Empuxo(N)')
        %     hold off
        
end

