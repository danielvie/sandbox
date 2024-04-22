%% Controle de Heading

function [K, Heading] = GanhosHeading(gravidade,Vel)


tau1 = 10/4; %constante de tempo --- 10 segundos de tempo de assentamento

%Cálculo dos ganhos
K = Vel/gravidade/tau1;
Heading.tau1 = tau1;

end