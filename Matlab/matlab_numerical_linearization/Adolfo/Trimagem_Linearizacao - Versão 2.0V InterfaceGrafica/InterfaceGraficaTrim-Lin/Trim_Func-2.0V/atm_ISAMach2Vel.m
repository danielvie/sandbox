function [V ro Pteste T] = atm_ISAMach2Vel(Z,M)
%ATM_ISA Summary of this function goes here

% Modificado em 28/07/2014 (Guido) p/ obter Mach dado Alt e Velocidade


%   Detailed explanation goes here

%   Definindo constantes ao nível do mar
P00 = 101325;
T00 = 288.15;
ro00 = 1.225;
g0 = 9.80655;
H0 = 0;
r0 = 6356766;
M0 = 28.9644;
Lmb = -0.0065;
R = 8314.32;
mi00 = 0.000017894;

%   Calculando variáveis na altitude desejada
H = (g0/g0)*((r0*Z)/(r0+Z));
P = P00*((T00/(T00+Lmb*(H-H0)))^((g0*M0)/(R*Lmb)));
Pteste = P/P00;
T = T00+Lmb*(H-H0);
ro = (P*M0)/(R*T);
mi = mi00*(((T/T00)^(3/2))*((T00+110)/(T+110)));
a = sqrt(1.4*(R/M0)*T);

%   Calculando variáveis em função doa velocidade
V = M*a;
Q = (ro*V^2)/2;
P0 = P*((1+((1.4-1)/2)*(M^2))^(1.4/(1.4-1)));
T0 = T*(1+((1.4-1)/2)*(M^2));
ro0 = ro*((1+((1.4-1)/2)*(M^2))^(1/(1.4-1)));
mi0 = mi00*(((T0/T00)^(3/2))*((T00+110)/(T0+110)));

end

