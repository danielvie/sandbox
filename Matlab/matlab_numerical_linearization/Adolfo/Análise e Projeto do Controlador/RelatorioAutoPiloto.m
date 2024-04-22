%Programa para criar os resultados do relatório do autopiloto
close all
load('Trim_Lin_Output/DadosTrim_Nivelado/BV9Relatorio/ModeloLinear-Half')
addpath('Analise\BV9_30_03');
Alt = 2; %1000m
Vel = 6; %250m/s

%Constantes Turbo-Jato
Tau = 1;

%Constantes do atuador elétrico
zetaA = 0.7;
wnA = 72.;

%% Modelo da planta + atuadores / Longitudinal
Kp = 0.4950;
Kd = 0.1070;
Engine = ss(-Tau, 1,1,0);
At = tf(wnA^2,[1 2*zetaA*wnA wnA^2]);
T = 0.01;
ZOH = tf([-1 2/T],[1 2/T]);
Empena = ss([0 1;-wnA^2 -2*zetaA*wnA],[0 wnA^2]',[1 0],0);
Gp = ss(Plano_Long(Alt,Vel).A(1:4,1:4),Plano_Long(Alt,Vel).B(1:4,:),eye(4),zeros(4,2),...
    'Inputname',{'Manete' 'dPitch'},...
    'OutputName',{'Vt' 'AoA' 'q' 'theta'},...
    'Statename',{'Vt' 'AoA' 'q' 'theta'});

%Malha Aberta
GpS = ss(Gp.A(2:3,2:3),Gp.B(2:3,2),[0 1],0);
C = tf([Kd Kp],1);
fa =100;
[n,d] = pade(1/fa,2);
ZOH = tf(n,d);
GA = C*ZOH*At*GpS*tf(1,[1 0]);
figure(1)
hold on
nichols(GA,0:0.01:100);

%Malha Fechada
Gi = feedback(ZOH*At*GpS,Kd);
Gf = feedback(Kp*Gi*tf(1,[1 0]),1);
figure(2)
hold on;
step(Gf,10);



%% Fazendo o doublet
clear U T
dt = 0.001;
A = 0;
B = 1;
C = B + dt;
D = C + 1.5/5;
E = D + dt;
F = E + 1.5/5;
G = F + dt;
H = G + 5;

u0 = zeros(length(A:dt:B),1);
u1 = ones(length(C:dt:D),1);
u2 = -ones(length(E:dt:F),1);
u3 = zeros(length(G:dt:H),1);

T = [A:dt:B C:dt:D E:dt:F G:dt:H];
U = [u0' u1' u2' u3'];

%% Plano Longitudinal
figure()
pzmap(Gp)
figure()
impulse(Gp,10)
figure()
[y,t] = lsim(Gp(:,2),U,T);
subplot(2,1,1)
plot(t,250+y(:,1),'LineWidth',2)
xlabel('Tempo(s)')
ylabel('Vel(m/s)')
legend('Velocidade')

subplot(2,1,2)
plot(t,1+y(:,2),t,y(:,3),t,y(:,4),'LineWidth',2)
xlabel('Tempo(s)')
ylabel('\alpha e \theta (°) e q (°/s)')
legend('\alpha','q','\theta')

figure()
[y1,t1] = step(Gp(:,2),10);
GpS = ss(Gp.A(2:3,2:3),Gp.B(2:3,2),eye(2),0);
[y2,t2] = step(GpS,10);
subplot(2,1,1)
plot(t1,y1(:,2),'--',t2,y2(:,1),'LineWidth',2);
ylabel('Alpha(°)')
xlabel('Tempo(s)')
legend('Completa','Simplificada')
subplot(2,1,2)
plot(t1,y1(:,3),'--',t2,y2(:,2),'LineWidth',2);
ylabel('q(°/s)')
xlabel('Tempo(s)')
legend('Completa','Simplificada')

figure()
bode(Gp(3,2),GpS(2))
legend('Completa','Simplificada')

%% Plano Lateral Yaw
close all

Gp = ss(Plano_Lat(Alt,Vel).A(1:4,1:4),Plano_Lat(Alt,Vel).B(1:4,:),eye(4),zeros(4,2),...
    'Inputname',{'dYaw' 'dRoll'},...
    'OutputName',{'AoS' 'Phi' 'p' 'r'},...
    'Statename',{'AoS' 'Phi' 'p' 'r'});
figure()
pzmap(Gp)
figure()
impulse(Gp,10)

%Yaw
A_Lat = Gp.A;
B_Lat = Gp.B(:,1);
A = [A_Lat(1,1) A_Lat(1,4); A_Lat(4,1) A_Lat(4,4)];
B = [B_Lat(1,1); B_Lat(4,1)];

[n,d] = ss2tf(A,B,[0 1],0);
GpS = tf(n,d);
GpS2 = tf([B_Lat(4,1) (B_Lat(1,1)*A_Lat(4,1)-B_Lat(4,1)*A_Lat(1,1))],...
    [1 -(A_Lat(1,1) +  A_Lat(4,4)) (A_Lat(1,1)*A_Lat(4,4)-A_Lat(4,1)*A_Lat(1,4))]);

figure()
pzmap(GpS,Gp(4,1))
figure()
subplot(1,2,1)
impulse(GpS,Gp(4,1))
legend('Simplificada','Completa')
subplot(1,2,2)
bode(GpS,Gp(4,1))
legend('Simplificada','Completa')

%Roll

GpR = tf(Gp.B(3,2),[1 -Gp.A(3,3)]);
Kp = 7.2^2/Gp.B(3,2);
Kd = (2*0.75*7.2 + Gp.A(3,3))/Gp.B(3,2);


%% GainScheduling Figuras
close all
V = [1 1 7 7 6];
H = [1 5 1 5 2];
figure()
hold on
for i=1:5
    G = ss(Plano_Long(H(i),V(i)).A(1:4,1:4),Plano_Long(H(i),V(i)).B(1:4,2),[0 0 1 0],zeros(1,1));
    %     lsim(G,U,T)
    %     step(G,10)
    pzmap(G,'b')
end
legend('H = 0 V = 160','H = 4000 V = 160','H = 0 V = 260','H = 4000 V = 260','H = 1000 V = 250')

H = [0 4 0 4 1];
V = [160 160 260 260 250];
figure()
plot(H,V,'o')

%% GainScheduling Longitudinal
color ={'b','r','k','c','g'};
figure()
hold
for i=2:2
    for j=1:7
        G = ss(Plano_Long(i,j).A(1:4,1:4),Plano_Long(i,j).B(1:4,:),eye(4),zeros(4,2));
        pzmap(G)
    end
end
legend('H=0','H=1000','H=2000','H=3000','H=4000')

%% GainScheduling Látero
close
figure()
hold
for i=1:5
    for j=1:7
        G = ss(Plano_Lat(i,j).A(1:4,1:4),Plano_Lat(i,j).B(1:4,:),eye(4),zeros(4,2));
        pzmap(G)
    end
end
% legend('H=0','H=1000','H=2000','H=3000','H=4000')
% legend('V=160','V=180','V=200','V=220','V=240', 'V=250', 'V=260')

%% GainScheduling Margens de estabilidade Longitudinal - Pitch MA
close all
clear all

i = 6;
Full  = ['ssTanqueFull_' num2str(i)];
Half  = ['ssTanqueHalf_' num2str(i)];
Empty = ['ssTanqueZero_' num2str(i)];

t= 0:0.01:2*pi;
x = 45*cos(t) - 180;
y = 9*sin(t);

load(Full)
subplot(1,2,1)
% nichols(GA(:,:).Pitch.PitchComplete,[0.01:0.01:200]);
nichols(GA(:,:).Pitch.PitchSimple,[0.01:0.01:200]);
title('Tanque Cheio')
hold on
plot(x,y,'r')

% if isempty(find(MA.Pitch.S == 0,1))== 0
%     [n,d] = find(MA.Pitch.S == 0)
%     pause();
% end

load(Empty)
subplot(1,2,2)
hold on
% nichols(GA(:,:).Pitch.PitchComplete,[0.01:0.01:200]);
nichols(GA(:,:).Pitch.PitchSimple,[0.01:0.01:200]);
title('Tanque Vazio')
hold on
plot(x,y,'r')

% if isempty(find(MA.Pitch.S == 0,1))==0
%     [n,d] = find(MA.Pitch.S == 0)
%     pause();
% end

load(Half)
figure()
% nichols(GA(:,:).Pitch.PitchComplete,[0.01:0.01:200]);
nichols(GA(:,:).Pitch.PitchSimple,[0.01:0.01:200]);
title('Tanque Metade')
hold on
plot(x,y,'r')

% if isempty(find(MA.Pitch.S == 0,1))==0
%     [n,d] = find(MA.Pitch.S == 0)
%     pause();
% end

%% GainScheduling Resposta Malha Fechada Longitudinal - Arfagem MF
close all
load(Full)
subplot(2,1,1)
% step(Gf(:,:).Pitch.PitchComplete,10);
step(Gf(:,:).Pitch.PitchSimple,10);
title('Tanque Cheio')

load(Empty)
subplot(2,1,2)
hold on
% step(Gf(:,:).Pitch.PitchComplete,10);
step(Gf(:,:).Pitch.PitchSimple,10);
title('Tanque Vazio')

load(Half)
figure()
% step(Gf(:,:).Pitch.PitchComplete,10);
step(Gf(:,:).Pitch.PitchSimple,10);

%% GainScheduling Margens de estabilidade Latéro - Rolamento MA
close all

t= 0:0.01:2*pi;
x = 45*cos(t) - 180;
y = 9*sin(t);

load(Full)
subplot(1,2,1)
nichols(GA(:,:).Roll.RollComplete,[0.01:0.01:200]);
title('Tanque Cheio')
hold on
plot(x,y,'r')

load(Empty)
subplot(1,2,2)
hold on
nichols(GA(:,:).Roll.RollComplete,[0.01:0.01:200]);
title('Tanque Vazio')
hold on
plot(x,y,'r')

load(Half)
figure()
nichols(GA(:,:).Roll.RollComplete,[0.01:0.01:200]);
title('Tanque Metade')
hold on
plot(x,y,'r')



%% GainScheduling Resposta Malha Fechada Látero - Rolamento MF
close all
load(Full)
subplot(2,1,1)
step(Gf(:,:).Roll.RollComplete,3);
title('Tanque Cheio')

load(Empty)
subplot(2,1,2)
hold on
step(Gf(:,:).Roll.RollComplete,3);
title('Tanque Vazio')

load(Half)
figure()
step(Gf(:,:).Roll.RollComplete,3);

%% GainScheduling Margens de estabilidade Latéro - Yaw-damper MA

close all
t= 0:0.01:2*pi;
x = 45*cos(t) - 180;
y = 9*sin(t);

load(Full)
subplot(1,2,1)
nichols(GA(:,:).Yaw.YawComplete,[0.1:0.01:200]);
title('Tanque Cheio')
hold on
plot(x,y,'r')

load(Empty)
subplot(1,2,2)
hold on
nichols(GA(:,:).Yaw.YawComplete,[0.1:0.01:200]);
title('Tanque Vazio')
hold on
plot(x,y,'r')

load(Half)
figure()
nichols(GA(:,:).Yaw.YawComplete,[0.1:0.01:200]);
title('Tanque Metade')
hold on
plot(x,y,'r')



%% GainScheduling Resposta Malha Fechada Latéro - Yaw-Damper MF
close all
X0 = [-0.1 0 0 3 zeros(1,4)];

load(Full)
subplot(2,1,1)
initial(Gf(:,:).Yaw.YawComplete,X0,3);
title('Tanque Cheio')

load(Empty)
subplot(2,1,2)
hold on
initial(Gf(:,:).Yaw.YawComplete,X0,3);
title('Tanque Vazio')

load(Half)
figure()
initial(Gf(:,:).Yaw.YawComplete,X0,3);

%% Plotar as margens de estabilidade
close all
label = {'0','1000','2000','3000','4000'};

load(Half)
figure(1)
plot(Velocidade,20*log10(MA.Pitch.Gm)','-x','LineWidth',2)
legend(label)
xlabel('Velocidade(m/s)')
ylabel('Margem de Ganho (dB)')
title('Arfagem')

figure(2)
plot(Velocidade,MA.Pitch.Pm','-x','LineWidth',2)
xlabel('Velocidade(m/s)')
ylabel('Margem de Fase(°)')
title('Arfagem')
legend(label)
figure(3)
plot(Velocidade,MA.Pitch.S','-x','LineWidth',2)
xlabel('Velocidade(m/s)')

figure(4)
plot(Velocidade,20*log10(MA.Roll.Gm)','-x','LineWidth',2)
xlabel('Velocidade(m/s)')
ylabel('Margem de Ganho(dB)')
title('Rolamento')
legend(label)
figure(5)
plot(Velocidade,MA.Roll.Pm','-x','LineWidth',2)
xlabel('Velocidade(m/s)')
ylabel('Fase(°)')
legend(label)
title('Rolamento')
figure(6)
plot(Velocidade,MA.Roll.S','-x','LineWidth',2)
xlabel('Velocidade(m/s)')

figure(7)
plot(Velocidade,20*log10(MA.Yaw.Gm)','-x','LineWidth',2)
xlabel('Velocidade(m/s)')
ylabel('Margem de Ganho(dB)')
title('Yaw-Damper')
legend(label)
figure(8)
plot(Velocidade,MA.Yaw.Pm','-x','LineWidth',2)
xlabel('Velocidade(m/s)')
ylabel('Fase(°)')
legend(label)
title('Yaw-Damper')
figure(9)
plot(Velocidade,MA.Yaw.S','-x','LineWidth',2)
xlabel('Velocidade(m/s)')


%% Plotar os ganhos
close all

load(Half)
Vel = [160 180 200 220 240 250 260]';
Alt = 0:1000:4000;
figure(1)
mesh(Vel,Alt,Kp.roll)
xlabel('Velocidade(m/s)')
ylabel('Altitude(m)')
zlabel('Kp')
title('Ganho proporcional malha de rolamento')

figure(2)
mesh(Vel,Alt,Kd.roll)
xlabel('Velocidade(m/s)')
ylabel('Altitude(m)')
zlabel('Kd')
title('Ganho derivativo malha de rolamento')

figure(3)
mesh(Vel,Alt,Kp.pitch)
xlabel('Velocidade(m/s)')
ylabel('Altitude(m)')
zlabel('Kp')
title('Ganho proporcional malha de arfagem')

figure(4)
mesh(Vel,Alt,Kd.pitch)
xlabel('Velocidade(m/s)')
ylabel('Altitude(m)')
zlabel('Kd')
title('Ganho derivativo malha de arfagem')

figure(5)
mesh(Vel,Alt,Kd.yaw)
xlabel('Velocidade(m/s)')
ylabel('Altitude(m)')
zlabel('Kd')
title('Ganho derivativo malha de yaw')

