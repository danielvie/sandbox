%% Teste de robustez malha de velocidade
clear all
close all

Kt  = ureal('Kt',16,'Range',[7 25]);
Tau = ureal('Tau',1,'Range',[0.5 2.5]);
a   = ureal('a',0.03,'Range',[0.02 0.06]);

% Kp = 0.0235;
% Kp = 0.0104;

Kp = 0.1/20; %Baseado Kp = DeltaU/Emax

%% Função Sensibilidade Complementar

M = 1;
% A = 0.25;
A = 0.1;
wb = 0.1;

Wp = tf([1/M wb],[1 wb*A]);

%Criação da FT
Turbina = tf(1,[Tau 1]);
G       = tf(Kt,[1 a]);

%Escalonando

Gp = Turbina*G;

Gp1 = tf(1,[0.5 1])*tf(7,[1 0.04]);
Gp2 = tf(1,[0.5 1])*tf(25,[1 0.02]);
Gp3 = tf(1,[2.5 1])*tf(7,[1 0.04]);
Gp4 = tf(1,[2.5 1])*tf(25,[1 0.02]);

G1 = minreal((Gp2-Gp.Nominal)/Gp.Nominal);

Gpt = parallel(Gp,-Gp.Nominal)/Gp.Nominal;
Wi = tf(1,1);

bodemag(Gp,Gp1,'r',Gp2,'k',Gp3,'k',Gp4,'r',Gp.Nominal,'r')

Gf = feedback(Kp*Gp.Nominal,1);
S = feedback(1,Kp*Gp.Nominal);

bode(Gf,S*Wp,Kp*Gp.Nominal)

%% Planta Generalizada
% [n,d] = tfdata(Gp.Nominal);
% G = tf(n{1},d{1});
% 
% P11 = [Wp; 0];
% P12 = [-Wp*G; Wi*G];
% % P12 = [-Wp*G; G1*G];
% % P21 = G1;
% P21 = Wi;
% P22 = -G;
% 
% P = [P11 P12; P21 P22];
Kp = realp('Kp',5);
% [C,gamma,info] = hinfstruct(P,Kp);

%% Outro método de escrever a planta generalizada
Gn = tf(Kt.Nominal,[1 a.Nominal]);
Turbinan = tf(1,[Tau.Nominal 1]);
Gn = Gn*Turbinan;

Gn.u = 'u'; Gn.y = 'y';
CKp = tf(Kp,1); CKp.u = 'e'; CKp.y = 'u';
Sum = sumblk('e = r - y');
KP.y = 'u'; KP.u = 'e';
Wp.u = 'e'; Wp.y = 'z1';
Wi.u = 'y'; Wi.y = 'z2';

P = connect(Gn,CKp,Sum,Wp,Wi,{'r'},{'z1','z2'});

[C,gamma,info] = hinfstruct(P);

S = feedback(1,C.Value*Gp.Nominal);

Gf = feedback(C.Value*Gp,1);
Gft = feedback(Kp*Gp,1);

figure()
bode(Gp.Nominal*C)
figure()
step(Gf,Gf.Nominal,'r')
figure()
pzmap(Gf,Gf.Nominal,'r')  
figure()
bode(S*Wp,Gf.Nominal*G1);