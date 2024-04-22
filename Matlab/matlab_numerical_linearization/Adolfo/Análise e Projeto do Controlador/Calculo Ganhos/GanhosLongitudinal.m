%% Controle Longitudinal

function [K, Pitch] = GanhosLongitudinal(Gq,AtSS)

[n,d] = ss2tf(AtSS.A,AtSS.B,[1 0],0);
At = tf(n,d);
[n,d] = pade(1/100,1);
Delay = tf(n,d);
Int = tf(1,[1 0]);
Gp = At*Gq*Int*Delay;
wcg = 11.3; %wcg 15.8                 %insira a frequência de cruzamento de corte
MF = 49.5;  %insira a margem de fase /Era 52.4;
phi = (-180+MF)*pi/180;
aux = cos(phi) + 1i*sin(phi);
Num = evalfr(Gp,1i*wcg);

%Cálculo dos ganhos
K(1) = real(aux/Num); %Kp
K(2) = imag(aux/Num)/wcg; %Kd

%Parâmetros Projeto
Pitch.wcg = wcg; 
Pitch.MF = MF;

end