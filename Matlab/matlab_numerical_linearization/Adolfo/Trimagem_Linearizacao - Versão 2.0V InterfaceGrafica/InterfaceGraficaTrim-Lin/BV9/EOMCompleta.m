%% Versão 1.0 - Atualização - 16/07/2014 (Adolfo)
%Adaptei o programa do Hassan p/ as minhas necessidades

function [x_dot, Forca_Accel,Coef,Forca] = EOMCompleta(t,X,U,Modelo)

Inercia = Modelo.Inercia;
Centro_Massa = Modelo.Rcm;
Massa = Modelo.Massa;

% Inercia =[Modelo.Inercia(1,1) 0 0; 0 Modelo.Inercia(2,2) 0; 0 0 Modelo.Inercia(3,3)];

alpha = X(2);
beta  = X(3);

if Modelo.Eixo == 0 %vento
    u = X(1)*cos(alpha)*cos(beta);
    w = X(1)*sin(alpha)*cos(beta);
    v = X(1)*sin(beta);
else
    u = X(1);
    v = X(2);
    w = X(3);
end


phi     = X(4);
theta   = X(5);
psi     = X(6);
p       = X(7);
q       = X(8);
r       = X(9);
%  xN      = X(10);
%  xE      = X(11);
xD      = X(12);

manete  = U(1);
d_pitch = U(2);
d_yaw   = U(3);
d_roll  = U(4);


%Nova conversão

delta1 =   d_pitch - d_yaw + d_roll;
delta2 =   d_pitch + d_yaw + d_roll;
delta3 = - d_pitch + d_yaw + d_roll;
delta4 = - d_pitch - d_yaw + d_roll;

d_rad =[delta1; delta2; delta3; delta4]*pi/180;
%%Fim


W = [p; q; r];
V = [u; v; w];
Euler = [phi; theta; psi];

Vt = norm(V);
dum = Vt^2;

%% Cálculo do empuxo e momento provocado pela turbina e aerodinâmica
[~, ~,Mach,Faer, Maer] = ...
    Modelo.aer_cruz_mx(V, W, Centro_Massa, xD, d_rad(1), d_rad(2), d_rad(3), d_rad(4));

% [alfa_rad, beta_rad, mach, Faer, Maer] = ...
%     aer_cruz_mx(V, W, Rcm, alt, d_rad(1), d_rad(2), d_rad(3), d_rad(4));
%Completar os argumentos para função do booster
% alija_boost_on =1;
% turb_on =1;

[T_turb, rpm, ~, Mturb, Hturb] = turb_mx(Centro_Massa, xD, Mach, manete);

%     turb_mx(Centro_Massa, xD, Mach, manete, alija_boost_on, turb_on);
%     %Nova hassan tirou o alija_boster, turbon
% [T_turb, Mturb, Hturb] = turb_mx(xD, Vt, manete, Centro_Massa); %Antiga
Mturb =[0 0 0]';
Hturb =[0 0 0]';


%% Cálculo do momento e empuxo excercido sobre o veículo
Fb = Faer + [T_turb;0;0];
Mb = Maer + Mturb;
[W_dot, V_dot, Euler_dot, Pn_dot] = eqmov(W, V, Euler, Fb, Mb, Inercia, Hturb, Massa);
x_dot = [V_dot; Euler_dot; W_dot; Pn_dot];

%% Calculando as derivadas no Eixo do vento
Vtdot    = (u*x_dot(1)+v*x_dot(2) +w*x_dot(3))/Vt;  %Vdot
alphadot = (u*x_dot(3) - w*x_dot(1))/(u^2+w^2);     %alphadot
betadot  = (x_dot(2)*Vt-v*Vtdot)/(dum*cos(X(3)));   %betadot

x_dot(1) = Vtdot;
x_dot(2) = alphadot;
x_dot(3) = betadot;

%% Calculo da aceleração medida na triade do acelerômetro
Xa = [0 0 0]'; %Distância do acelerometro até cg do veículo
go = 9.8066;
Forca_Accel = Fb + cross(Xa,[p q r]')/go;

%% Calculo dos coeficientes separadamente
%Inserido 08/09

%Cálculo dos coeficentes de aceleração angular e a aceleração linear
%advindos da aerodinâmica
Coef(1) = Maer(1)/Inercia(1,1);
Coef(2) = Maer(2)/Inercia(2,2);
Coef(3) = Maer(3)/Inercia(3,3);
Coef(4:6) = Faer/Massa;

Forca   =  [Faer; [T_turb;0;0]];
end
