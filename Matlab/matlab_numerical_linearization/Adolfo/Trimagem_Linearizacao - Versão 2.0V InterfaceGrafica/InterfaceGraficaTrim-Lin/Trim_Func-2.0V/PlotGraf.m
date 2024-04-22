%%Fun��o para plotar os gr�ficos

function PlotGraf(y_NL,tempo_NL,Linear_Long,Linear_Lat, X_Trim, Opcao,val)
t = tempo_NL;
x = X_Trim;
R2G = 180/pi;

%Carregando as vari�veis

y_NL(:,4:9) = y_NL(:,4:9)*R2G;
Long.Q  = (Linear_Long.data(:,3) + x(8))*R2G;
Long.AOA  = (Linear_Long.data(:,2) + x(2))*R2G;
Long.VT  = (Linear_Long.data(:,1) + x(1));
Long.THETA = (Linear_Long.data(:,4) + x(5))*R2G;
Long.h = (Linear_Long.data(:,5) + x(12));

Lat.P = (Linear_Lat.data(:,3) + x(7))*R2G;
Lat.R = (Linear_Lat.data(:,4) + x(9))*R2G;
Lat.Beta = (Linear_Lat.data(:,1) + x(3))*R2G;
Lat.PHI = (Linear_Lat.data(:,2) + x(4))*R2G;

% Plotando os gr�ficos do modelo n�o-linear


if Opcao == 1
    switch val
        case 1
            VTT = (y_NL(:,1).^2+y_NL(:,2).^2+y_NL(:,3).^2).^0.5;
            f = plot(t,VTT, Linear_Long.time, Long.VT,'--');
            title('Velocidade')
            xlabel('Tempo(s)')
            ylabel('Velocidade(m/s)')
            legend('N�o Linear','Linear')
            set(f,'LineWidth',2)
        case 2
            f= plot(t,atan(y_NL(:,3)./y_NL(:,1))*R2G, Linear_Long.time, Long.AOA,'--');
            title('�ngulo de ataque')
            xlabel('Tempo(s)')
            ylabel('Alpha(�)')
            legend('N�o Linear','Linear')
            set(f,'LineWidth',2)
        case 3
            f = plot(t,y_NL(:,8), Linear_Long.time, Long.Q,'--');
            legend('N�o linear q','Linear q')
            xlabel('Tempo(s)')
            ylabel('Velocidade Angular �/s')
            title('Velocidade angular q')
            set(f,'LineWidth',2)
        case 4
            f= plot(t,y_NL(:,5), Linear_Long.time, Long.THETA,'--');
            title('�ngulo de Arfagem')
            xlabel('Tempo(s)')
            ylabel('Theta(�)')
            legend('N�o Linear','Linear')
            set(f,'LineWidth',2)
            
        case 5
            f= plot(t,-y_NL(:,12),Linear_Long.time, Long.h,'--');
            title('Altitude model n�o linear')
            xlabel('Tempo(s)')
            ylabel('Altitude(m)')
            legend('N�o Linear','Linear')
            set(f,'LineWidth',2)
    end
end

if Opcao == 2
    switch val
        case 1
            VTT = (y_NL(:,1).^2+y_NL(:,2).^2+y_NL(:,3).^2).^0.5;
            f= plot(t,atan(y_NL(:,2)./VTT)*R2G, Linear_Lat.time, Lat.Beta,'--');
            title('�ngulo de derrapagem')
            xlabel('Tempo(s)')
            ylabel('\beta(�)')
            legend('N�o Linear','Linear')
            set(f,'LineWidth',2)
        case 2
            f= plot(t,y_NL(:,4), Linear_Lat.time, Lat.PHI,'--');
            title('�ngulo de Rolamento')
            xlabel('Tempo(s)')
            ylabel('\phi(�)')
            legend('NL','L')
            set(f,'LineWidth',2)
        case 3
            f = plot(t,y_NL(:,7),t,y_NL(:,9), Linear_Lat.time, Lat.P,'--',Linear_Lat.time, Lat.R,'--');
            legend('NL p','NL r','L p','L r')
            xlabel('Tempo(s)')
            ylabel('Velocidade Angular �/s')
            title('Velocidade angular p e r')
            set(f,'LineWidth',2)
    end
end

return

set(0,'DefaultaxesFontSize',12)
figure(1)
plot(t,y_NL(:,1),t,y_NL(:,2),t,y_NL(:,3));
xlabel('Tempo(s)')
ylabel('velocidade(m/s)')
legend('u','v','w');
figure(2)
plot(t,y_NL(:,7)*R2G,t,y_NL(:,8)*R2G,t,y_NL(:,9)*R2G)
xlabel('Tempo(s)')
ylabel('velocidade angular(�/s)')
legend('p','q','r')


fig = figure(3);
plot(t,y_NL(:,4)*R2G,t,y_NL(:,5)*R2G,t,y_NL(:,6)*R2G);
xlabel('Tempo(s)')
ylabel('�ngulo(�)')
legend('phi','theta','psi')
% saveas(fig,'Graficos/CurvaCoordenada/EulerAngle','png')

figure(5)
plot(t,atan(y_NL(:,3)./y_NL(:,1))*R2G);
xlabel('Tempo(s)')
ylabel('�ngulo(�)')
legend('alpha')

figure(4)
plot3(y_NL(:,11),y_NL(:,10),-y_NL(:,12));
ylabel('North(m)')
xlabel('East(m)')
zlabel('Altura(m)')

%Comparando o Modelo N�o-Linear com o Linear
y_NL(:,4:9) = y_NL(:,4:9)*R2G;



Long.Q  = (Linear_Long.data(:,3) + x(8))*R2G;
Long.AOA  = (Linear_Long.data(:,2) + x(2))*R2G;
Long.VT  = (Linear_Long.data(:,1) + x(1));
Long.THETA = (Linear_Long.data(:,4) + x(5))*R2G;
Long.h = (Linear_Long.data(:,5) + x(12));

Lat.P = (Linear_Lat.data(:,3) + x(7))*R2G;
Lat.R = (Linear_Lat.data(:,4) + x(9))*R2G;
Lat.Beta = (Linear_Lat.data(:,1) + x(3))*R2G;
Lat.PHI = (Linear_Lat.data(:,2) + x(4))*R2G;
% Lat.PSI = (Linear_Lat.data(:,5) + x(6))*RG;

switch opcao
    
    case 3 %Pertuba��o Voo Reto din�mica Longitudinal Somente
        
        set(0,'DefaultaxesFontSize',12)
        
        fig = figure(6);
        subplot(2,2,1)
        f = plot(t,y_NL(:,8), Linear_Long.time, Long.Q,'--');
        legend('N�o linear q','Linear q')
        xlabel('Tempo(s)')
        ylabel('Velocidade Angular �/s')
        title('Velocidade angular q')
        set(f,'LineWidth',2)
        
        subplot(2,2,3)
        f= plot(t,y_NL(:,5), Linear_Long.time, Long.THETA,'--');
        title('�ngulo de Arfagem')
        xlabel('Tempo(s)')
        ylabel('Theta(�)')
        legend('N�o Linear','Linear')
        set(f,'LineWidth',2)
        
        subplot(2,2,2)
        f= plot(t,atan(y_NL(:,3)./y_NL(:,1))*R2G, Linear_Long.time, Long.AOA,'--');
        title('�ngulo de ataque')
        xlabel('Tempo(s)')
        ylabel('Alpha(�)')
        legend('N�o Linear','Linear')
        set(f,'LineWidth',2)
        
        subplot(2,2,4)
        VTT = (y_NL(:,1).^2+y_NL(:,2).^2+y_NL(:,3).^2).^0.5;
        f= plot(t,VTT, Linear_Long.time, Long.VT,'--');
        title('Velocidade')
        xlabel('Tempo(s)')
        ylabel('Velocidade(m/s)')
        legend('N�o Linear','Linear')
        set(f,'LineWidth',2)
        
        %         saveas(fig,'Graficos/CurvaCoordenada/Caso3/CR','png')
        
        %         fig = figure(7);
        
        %         f= plot(t,y_NL(:,12),Linear_Long.time, Long.h,'--');
        %         f= plot(t,y_NL(:,12));
        %         title('Altitude model n�o linear')
        %         xlabel('Tempo(s)')
        %         ylabel('Altitude(m)')
        %         set(f,'LineWidth',2)
        %         saveas(fig,'Graficos/CurvaCoordenada/Caso2/Altitude','png')
        
    case 4 %Pertuba��o Voo Reto din�mica Lateral Somente
        
        set(0,'DefaultaxesFontSize',12)
        
        fig = figure(6);
        subplot(2,2,1)
        f = plot(t,y_NL(:,7),t,y_NL(:,9), Linear_Lat.time, Lat.P,'--',Linear_Lat.time, Lat.R,'--');
        legend('NL p','NL r','L p','L r')
        xlabel('Tempo(s)')
        ylabel('Velocidade Angular �/s')
        title('Velocidade angular p e r')
        set(f,'LineWidth',2)
        
        subplot(2,2,3)
        f= plot(t,y_NL(:,4), Linear_Lat.time, Lat.PHI,'--');
        title('�ngulo de Rolamento')
        xlabel('Tempo(s)')
        ylabel('\phi(�)')
        legend('NL','L')
        set(f,'LineWidth',2)
        
        subplot(2,2,2)
        VTT = (y_NL(:,1).^2+y_NL(:,2).^2+y_NL(:,3).^2).^0.5;
        f= plot(t,atan(y_NL(:,2)./VTT)*R2G, Linear_Lat.time, Lat.Beta,'--');
        title('�ngulo de derrapagem')
        xlabel('Tempo(s)')
        ylabel('\beta(�)')
        legend('N�o Linear','Linear')
        set(f,'LineWidth',2)
        
        %         subplot(2,2,4)
        %         f= plot(t,y_NL(:,6), Linear_Lat.time, Lat.PSI,'--');
        %         title('�ngulo de guinada')
        %         xlabel('Tempo(s)')
        %         ylabel('\psi(�)')
        %         legend('N�o Linear','Linear')
        %         set(f,'LineWidth',2)
        %
        %         saveas(fig,'Graficos/CurvaCoordenada/Caso3/CR','png')
        %
        fig = figure(7);
        
        f= plot(t,-y_NL(:,12));
        title('Altitude model n�o linear')
        xlabel('Tempo(s)')
        ylabel('Altitude(m)')
        set(f,'LineWidth',2)
        %         saveas(fig,'Graficos/CurvaCoordenada/Caso3/Altitude','png')
        
        
    case 5 %Pertuba��o da Turbina
        
        set(0,'DefaultaxesFontSize',12)
        
        fig = figure(6);
        subplot(2,2,1)
        f = plot(t,y_NL(:,7),t,y_NL(:,9), Linear_Lat.time, Lat.P,'--',Linear_Lat.time, Lat.R,'--');
        legend('NL p','NL r','L p','L r')
        xlabel('Tempo(s)')
        ylabel('Velocidade Angular �/s')
        title('Velocidade angular p e r')
        set(f,'LineWidth',2)
        
        subplot(2,2,3)
        f= plot(t,y_NL(:,4), Linear_Lat.time, Lat.PHI,'--');
        title('�ngulo de Rolamento')
        xlabel('Tempo(s)')
        ylabel('\phi(�)')
        legend('NL','L')
        set(f,'LineWidth',2)
        
        subplot(2,2,2)
        VTT = (y_NL(:,1).^2+y_NL(:,2).^2+y_NL(:,3).^2).^0.5;
        f= plot(t,atan(y_NL(:,2)./VTT)*R2G, Linear_Lat.time, Lat.Beta,'--');
        title('�ngulo de derrapagem')
        xlabel('Tempo(s)')
        ylabel('\beta(�)')
        legend('N�o Linear','Linear')
        set(f,'LineWidth',2)
    otherwise
end

clear Y logsout ANG PQR aux t y Long




end