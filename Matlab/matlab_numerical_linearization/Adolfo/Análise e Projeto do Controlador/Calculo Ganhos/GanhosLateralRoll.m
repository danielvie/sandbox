%% Controle Lateral - Rolamento

function [K, Roll] = GanhosLateralRoll(Groll)

%Controle de Rolamento
%Lembrar de limitar a taxa de rolamento

%Variação dos parâmetros
% tr = 0.4; %Lento
tr = 0.25; %Nominal

zeta = 0.75;
wn = 1.8/tr;
[n, d] = tfdata(Groll);

L = n{1}(2);
Lp = d{1}(2);

K(1) = wn^2/L;
K(2) = (2*zeta*wn - Lp)/L;

Roll.tr = tr;
Roll.zeta = zeta;
Roll.wn = wn;
end