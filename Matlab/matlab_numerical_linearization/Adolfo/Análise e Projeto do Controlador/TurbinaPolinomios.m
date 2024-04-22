%% Avaliação da turbina
clear all
close all

plotManete = 0;
%Email do Boarin dia 20/11/14
% P (Coeficientes do polinomino, X é altitude e Y é o Mach);

P(1,:) = [2.650e-9  -1.040e-4 1.522 -8.033e3];     %Altura 0m,    Mach = 0.55 ISA
P(2,:) = [9.276e-9  -4.925e-4 9.187 -5.922e4];     %Altura 0m,    Mach = 0.75 ISA
P(3,:) = [-1.737e-8 1.089e-3 -2.189e1 1.425e5];    %Altura 0m,    Mach = 0.95 ISA

P(4,:) = [2.590e-9 -1.057e-4 1.592 -8.524e3];      %Altura 2000m, Mach = 0.55 ISA
P(5,:) = [1.568e-9 -4.405e-5 4.277e-1 -1.908e3];   %Altura 2000m, Mach = 0.75 ISA
P(6,:) = [-6.971e-9 4.543e-4 -9.124 5.784e4];      %Altura 2000m, Mach = 0.95 ISA

P(7,:) = [1.171e-9 -3.394e-5 3.642e-1 -1.507e3];   %Altura 4000m, Mach = 0.55 ISA
P(8,:) = [-1.040e-9 9.344e-5 -2.015 1.268e4];      %Altura 4000m, Mach = 0.75 ISA
P(9,:) = [-3.300e-10 3.745e-05 -5.529e-01 1.243e1];%Altura 4000m, Mach = 0.95 ISA     

P(10,:) = [4.155e-9 -1.929e-4 3.205 -1.854e4];     %Altura 0m,    Mach = 0.6 ISA+15
P(11,:) = [3.323e-9 -1.52e-4  2.513  -1.457e4];    %Altura 2000m, Mach = 0.6 ISA+15
P(12,:) = [1.211e-9 -3.964e-5 4.932e-1 -2.392e3];  %Altura 4000m, Mach = 0.6 ISA+15


LegStr = {'A=0, M=0.55, I','A=0, M=0.75, I','A=0, M=0.95, I','A=2000, M=0.55, I','A=2000, M=0.75, I','A=2000, M=0.95, I'...
    'A=4000, M=0.55, I','A=4000, M=0.75, I','A=4000, M=0.95, I','A=0, M=0.6, I+15','A=2000, M=0.6, I+15','A=4000, M=0.95, I+15'};
E = [22334, 21806, 21168, 22885, 22315, 21663,23415,22861,22193,22650,22137, 21657]'; %[P1, P2, P3, P4, P5, P6];

for j = 1:length(E)
    x = 18000;
    i = 1;
    while x <= E(j)
        
        Turb(j).RPM(i) = x;
        Turb(j).Manete(i) = x/E(j);
        Turb(j).y(i) = P(j,:)*[x^3 x^2 x 1]';       
        
        x = x + 100;
        i = i+1;
    end
    j=j+1;
end

% Manete = 0:1/length(RPM):1-1/length(RPM);

figure()
if plotManete == 1
    plot(Turb(1).Manete,Turb(1).y,Turb(2).Manete,Turb(2).y,Turb(3).Manete,Turb(3).y)
    xlabel('Manete')
elseif plotManete == 2
    plot(Turb(1).RPM,Turb(1).y,Turb(2).RPM,Turb(2).y,Turb(3).RPM,Turb(3).y,'Linewidth',2)
    xlabel('RPM corrigido');    
else
    cte = 23000;
    plot(Turb(1).Manete*cte,Turb(1).y,Turb(2).Manete*cte,Turb(2).y,Turb(3).Manete*cte,Turb(3).y,'Linewidth',2)
    xlabel('RPM');  
end
grid on
ylabel('Empuxo (N)')
title('0m - ISA')
legend('Mach 0.55','Mach 0.75','Mach 0.95')

figure()
if plotManete == 1
    plot(Turb(4).Manete,Turb(4).y,Turb(5).Manete,Turb(5).y,Turb(6).Manete,Turb(6).y)
    xlabel('Manete')
elseif plotManete == 2
   plot(Turb(4).RPM,Turb(4).y,Turb(5).RPM,Turb(5).y,Turb(6).RPM,Turb(6).y,'Linewidth',2) 
   xlabel('RPM corrigido')
else
    cte = 23000;
    plot(Turb(4).Manete*cte,Turb(4).y,Turb(5).Manete*cte,Turb(5).y,Turb(6).Manete*cte,Turb(6).y,'Linewidth',2)
    xlabel('RPM'); 
end   
grid on
ylabel('Empuxo (N)')
title('2000 m - ISA')
legend('Mach 0.55','Mach 0.75','Mach 0.95')

figure()
if plotManete == 1
    plot(Turb(7).Manete,Turb(7).y,Turb(8).Manete,Turb(8).y,Turb(9).Manete,Turb(9).y,'Linewidth',2) 
    xlabel('Manete')
elseif plotManete == 2
   plot(Turb(7).RPM,Turb(7).y,Turb(8).RPM,Turb(8).y,Turb(9).RPM,Turb(9).y,'Linewidth',2)
   xlabel('RPM corrigido')   
else
    cte = 23000;
    plot(Turb(7).Manete*cte,Turb(7).y,Turb(8).Manete*cte,Turb(8).y,Turb(9).Manete*cte,Turb(9).y,'Linewidth',2)
    xlabel('RPM'); 
end  
grid on
ylabel('Empuxo (N)')
title('4000 m - ISA')
legend('Mach 0.55','Mach 0.75','Mach 0.95')


figure()
if plotManete == 1
    plot(Turb(10).Manete,Turb(10).y,Turb(11).Manete,Turb(11).y,Turb(12).Manete,Turb(12).y)  
     xlabel('Manete')
else
   plot(Turb(10).RPM,Turb(10).y,Turb(11).RPM,Turb(11).y,Turb(12).RPM,Turb(12).y,'Linewidth',2)
   xlabel('RPM corrigido')
end
grid on
ylabel('Empuxo (N)')
title('Mach 0.6 - Isa + 15')
legend('Altitude 0m', 'Altitude 2000m', 'Altitude 4000m')


figure()
hold all
Avaliar = [1 2 4 5 7 8];  
for j=1:length(Avaliar)
    i = Avaliar(j);
    const = (Turb(i).Manete(3)-Turb(i).Manete(2))*800;
    plot(Turb(i).Manete(1:end-1),diff(Turb(i).y)/const)   
end
grid on
legend(LegStr([Avaliar]))
xlabel('Manete')
ylabel('Kt')

% plot(Manete(1:end-1),diff(y1)/const,Manete(1:end-1),diff(y2)/const,Manete(1:end-1),diff(y3)/const,...
%     Manete(1:end-1),diff(y4)/const,Manete(1:end-1),diff(y5)/const,Manete(1:end-1),diff(y6)/const);
% %     Manete(1:end-1),diff(y7)/const,Manete(1:end-1),diff(y8)/const,Manete(1:end-1),diff(y9)/const);
% xlabel('Manete Trim')
% ylabel('m/s^2 por manete')
% legend('Mach 0.6 - Alt 2','Mach 0.8 - Alt 2','Mach 0.9 - Alt 2','Mach 0.6 - Alt 0','Mach 0.8 - Alt 0','Mach 0.9 - Alt 0')
% title('Derivada do empuxo em função de um delta de manete 0.002')
