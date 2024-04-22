%% Teste calculo da robustez do guiamento
close all
Alt = 2;
Vel =4;

aux = [-0.0002678 4.131e-6 1.103e-5 0]'; %parte da altitude
% aux = [0 0 0 0]';
A = [Plano_Long(Alt,Vel).A aux;
     0 -250 0 250 0];
B = [Plano_Long(Alt,Vel).B(:,2) ; 0];

Galtitudess = ss(A ,B, [0 0 1 0 0; 0 0 0 1 0; 0 0 0 0 1],[0;0;0]);
aux = series(AtSS,Galtitudess);
Kh = 1/1800;
% Kh =1;
K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) Kh*Kp.pitch(Alt,Vel)];
%Malha Aberta -- Acho que está errado
Ga = ss(aux.A,aux.B,K*aux.C,0);
figure()
bode(Ga)


%teste de calcular o ganho de malha aberta após fechar a malha em atitude
K2 = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) 0];
Gf = ss(aux.A-aux.B*[0 0 K2 0 0],aux.B*Kp.pitch(Alt,Vel),[0 0 0 1 0 0 0], 0); %Altura
Ga = ss(Gf.A,Gf.B,1*[0 0 0 0 1 0 0],0);
bode(Ga)

%Malha Fechada
Kh = 1/1800;
K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) Kh*Kp.pitch(Alt,Vel)];
Gf = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kh*Kp.pitch(Alt,Vel),[0 0 0 0 1 0 0; 0 0 0 1 0 0 0], 0); %Altura
     

figure()
step(1000*Gf,40)