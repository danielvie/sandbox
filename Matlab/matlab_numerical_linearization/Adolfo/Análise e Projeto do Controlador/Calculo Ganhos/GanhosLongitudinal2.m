%% Controle Longitudinal

function [K, Pitch] = GanhosLongitudinal2(Gq,AtSS)

wb = 4;
M = 1.35;
A = 0.05;
wn = 4;
zeta = 0.7;

Kp = realp('Kp',0.5);
Kd = realp('Kd', 0.1);

[n,d] = pade(1/100,1);
Delay = tf(n,d);

Wp = tf([1/M wb],[1 wb*A]);
T = tf(wn^2,[1 2*zeta*wn wn^2]);
Wu = tf(0,1);
Int = tf(1,[1 0]);
CKp = tf(Kp,1);
CKd = tf(Kd,1);

Gq = AtSS*Gq*Delay;

Wp.u = 'e'; Wp.y = 'z1';
Wu.u = 'u'; Wu.y ='z3';
Wt = 1/T; Wt.u = 'y'; Wt.y = 'z2';
CKp.u = 'e'; CKp.y = 'uKp';
CKd.u = 'yq'; CKd.y = 'uKd';
Gq.u = 'u'; Gq.y = 'yq';
Int.u= 'yq'; Int.y = 'y';
Sum1 = sumblk('e = r - y');
Sum2 = sumblk('u = uKp - uKd');
T0 = connect(Gq,Wp,Wt,Wu,Int,CKp,CKd,Sum1,Sum2,{'r'},{'z1','z2','z3'});

[CL,gamma,info] = hinfstruct(T0);

K(1) = info.TunedBlocks.Kp.Value;
K(2) = info.TunedBlocks.Kd.Value;

%Parâmetros Projeto
Pitch.wcg = 0;
Pitch.MF = 0;

end