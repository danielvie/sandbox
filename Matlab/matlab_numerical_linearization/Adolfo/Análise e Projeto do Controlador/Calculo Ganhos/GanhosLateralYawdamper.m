%% Controle Lateral - Yawdamper

function [K, Yaw] = GanhosLateralYawdamper(Gyaw)

%Amortecimento no plano de guinada 
zeta = 0.7;  %Nominal
% zeta = 0.55; % Menos Amortecido
% zeta = 0.85; %Mais amortecido;

[n, d] = tfdata(Gyaw);
a = n{1}(2);
b = n{1}(3);
c = d{1}(2);
d = d{1}(3);

teste = roots([a^2 (2*a*c-4*zeta^2*b) (c^2 - 4*zeta^2*d)]);

if(teste(1)>0)
   K = teste(1);
%    wn = (d+b*K)^0.5;
else
   K = teste(2); 
%    wn = (d+b*K)^0.5;
end

wn = (d+b*K)^0.5;

Yaw.zeta = zeta;
Yaw.wn = wn;
end