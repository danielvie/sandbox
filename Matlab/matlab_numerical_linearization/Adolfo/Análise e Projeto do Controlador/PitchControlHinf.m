%Programa PitchControl-Hinf
%Programa construído para sintonizar os parâmetros da malha de arfagem
%Elaborado por: Adolfo Graciano da Silva
%Última Modificação -- Data: 14/05/2015


%Wp -- Função sensitividade
%Wt -- Função sensitividade complementar
%T  -- Modelo de referência
%Wu -- Peso para o sinal de controle

close all
clear all
% load('Dados_Input_Ganhos/BV9_30_03/ssTanqueHalf_0')
load('Dados_Input_Ganhos/BV9_30_03/ssTanqueHalf_0')
%Ponto de operação
Alt = 2; %Alt [0 1000 2000 3000 4000]
Vel = 6; %Vel [160 180 200 220 240 250 260]

%Elipse de exclusão
t = 0:0.01:2*pi;
x = 9*cos(t);
y = 180 + 45*sin(t);

%Modelos --> Atuadores/Turbo-Jato/Míssil
Tau = 1;
zetaA = 0.8;
wA = 72.4;
fa = 100; %Taxa de amostragem
Engine = ss(-Tau, 1,1,0);
Empena = ss([0 1;-wA^2 -2*zetaA*wA],[0 wA^2]',[1 0],0);
Gp = ss(Plano_Long(Alt,Vel).A,Plano_Long(Alt,Vel).B(:,2),eye(5),zeros(5,1));
% Gp = ss(Plano_Long(Alt,Vel).A,Plano_Long(Alt,Vel).B,[1 0 0 0 0; 0 0 1 0 0; 0 0 0 1 0],zeros(3,2));
% aux = append(Engine,Empena);
% Gp2 = series(aux,Gp,[1 2],[1 2]);

aux = append(Empena);
Gp2 = series(aux,Gp);

%FT planta/atuador/ZOH
At = tf(72^2,[1 2*0.7*72 72^2]); %atuador FT
[n,d] = pade(1/fa,2);
Delay = tf(n,d);
Int = tf(1,[1 0]);
[n,d] = ss2tf(Plano_Long(Alt,Vel).A(2:3,2:3),Plano_Long(Alt,Vel).B(2:3,2),[0 1],0);%Simplificada
Gq = tf(n,d)*At*Delay;
% Gq = tf([105.3 88.33],[1 1.994 65.81])*At*Delay; %half tanque BV8
% Gq = tf([106.2 82.07],[1 1.865 34.87])*At*Delay; %half tanque BV9 Aero/BV8 Massa


%% Plotar os valores singulares para ter uma ideia da dinâmica planta
% figure()
% pzmap(Gp2)
%
% figure()
% sigma(Gp2(1,2),Gp2(2,2),Gp2(3,2),Gp2(4,2),Gp2(5,2));
% % sigma(Gp(3,2),Gp2(3,2));
% % sigma(Gp(1,1),Gp2(1,1));
% legend('Vel','alpha','q','pitch','h')
% title('Elevator Input')
%
% figure()
% sigma(Gp2(1,1),Gp2(2,1),Gp2(3,1),Gp2(4,1),Gp2(5,1));
% legend('Vel','alpha','q','pitch','h')
% title('Throttle Input')
%%


%Parâmetros de sintonia Função sensitividade complementar
M  = [1.35 1.35 1.35]; %Utilizadas no Projeto --- 1
wb = [5 4 0.5];% Nominal
% M  = [1.25 1.25 1.25];
% wb = [5 7 0.5]; %Rapido
A  = [0.05 0.01 0.01];

%Param -- Modelo de referência/Wt
wn = 4;
zeta = 0.7;

%Parâmetros sintonia relatório
% wb = [4    10   0.5];
% A  = [0.01 0.01 0.01];
%
for i = 1:2
    
    Wu = tf(1,1);
    Wp = tf([1/M(i) wb(i)],[1 wb(i)*A(i)]);
    T = tf(wn^2,[1 2*zeta*wn wn^2]);
    Wt = 1/T;
    
    %     T = tf(wn^2,[1 2*zeta*wn wn^2]); %modicicação 13/05;
    %     Wt = T; %modificação 13/05
    
    Kp = realp('Kp',0.5);
    Ki = realp('Ki',0.05);
    Kd = realp('Kd', 0.1);
    
    PD = 1;
    if PD == 1
        CKp = tf(Kp,1);
    else
        CKp = tf([Kp Ki],[1 0]);
    end
    
    CKd = tf(Kd,1);
    
    %Exemplo HinfStruct pg 361 Multivariable feedback
    %
    Wp.u = 'e'; Wp.y = 'z1';
    Wu.u = 'u'; Wu.y ='z3';
    Wt.u = 'y'; Wt.y = 'z2';
%     Wt.u = 'r'; Wt.y = 'wty'; %modificação dia 13/05
    CKp.u = 'e'; CKp.y = 'uKp';
    CKd.u = 'yq'; CKd.y = 'uKd';
    Gq.u = 'u'; Gq.y = 'yq';
    Int.u= 'yq'; Int.y = 'y';
    Sum1 = sumblk('e = r - y');
    Sum2 = sumblk('u = uKp - uKd');
%     Sum3 = sumblk('z2 = wty - y');
    
    %P1 generalizada utilizada no projeto
    T0 = connect(Gq,Wp,Wt,Wu,Int,CKp,CKd,Sum1,Sum2,{'r'},{'z1','z2','z3'});
%     T0 = connect(Gq,Wp,Wt,Int,CKp,CKd,Sum1,Sum2,{'r'},{'z1','z2'});
    
    %P2 generalizada com modelo de referência
    %     T0 = connect(Gq,Wp,Wt,Int,CKp,CKd,Sum1,Sum2,Sum3,{'r'},{'z1','z2'}); %modificação dia 13/05
    
    %P2 generalizada com modelo de referência
    %     T0 = connect(Gq,Wp,Wt,Wu,Int,CKp,CKd,Sum1,Sum2,Sum3,{'r'},{'z1','z2','z3'}); %modificação dia 13/05
    
    
    %    P = augw(Gq*Int,Wp,[],Wt*tf(50^2,[1 2*50 50^2]));
    % Teste= hinfsyn(P);
    
    %Bloco artigo Robust Control Design NASA
    %
    %     We = tf([0.1 5.973],[1 0.176]);
    %     Wu = tf([1 35],[1 70]); Wu.u = 'u'; Wu.y = 'z1'; %para minimizar esforço de controle
    %     Wn = tf(0.1,1); Wn.u = 'n'; Wn.y ='yqn'; %Ruido
    %     Wt = T*At*Delay; Wt.u = 'r'; Wt.y = 'wty';
    %     SumZ2 = sumblk('aux = wty - y');
    %     We.u = 'aux'; We.y = 'z2';
    %     CKp.u = 'e'; CKp.y = 'uKp';
    %     CKd.u = 'yqr'; CKd.y = 'uKd';
    %     Gq.u = 'u'; Gq.y = 'yq';
    %     Int.u= 'yq'; Int.y = 'y'; %integrando para obter a variavel pitch
    %     Sum1 = sumblk('e = r - y'); %sinal do erro
    %     Sum2 = sumblk('u = uKp - uKd'); %sinal de controle
    %     Sum3 = sumblk('yqr = yq + yqn'); %somando ruido a medida q
    %     %
    
    %     T0 = connect(Gq,Wt,We,Wn,Wu,Int,CKp,CKd,Sum1,Sum2,Sum3,SumZ2,{'r','n'},{'z2','z1'});
    
    [CL,gamma,info] = hinfstruct(T0);
    Kdc(i) = info.TunedBlocks.Kd.Value;
    Kpc(i) = info.TunedBlocks.Kp.Value;
    
    
    %Plotando os resultados
    
    Gi = feedback(Gq,Kdc(i)); %Loop interno
    
    %     PD =0;
    %     Kic = Kpc/2;
    if PD == 1
        C = tf([Kdc(i) Kpc(i)],1);
        Gf = feedback(Gi*Kpc(i)*Int,1);
    else
        Kic(i) = info.TunedBlocks.Ki.Value;
        C = tf([Kdc(i) Kpc(i) Kic(i)],[1 0]);
        Gf = feedback(Gi*tf([Kpc(i) Kic(i)],[1 0])*Int,1);
    end
    
    figure(1)
    nichols(C*Gq*Int,0:0.1:100)
    hold on
    
    figure(2)
    bode(Gf);
    hold on
    
    figure(3)
    step(Gf,10)
    hold on
    
    figure(4)
    pzmap(Gf)
    hold on
    
    figure(5)
    bode(C*Gq*Int,0:0.1:100)
    hold on
    
    figure(6)
    lsim(Gf,[0:0.01:10],[0:0.01:10]);
    hold on
end

%%
figure(1)
hold on
plot(y,x,'r')
legend('Caso 1','Caso 2')

figure(2)
hold on
bode(T,'r--');
legend('Caso 1','Caso 2','Modelo de referência')
figure(3)
hold on
step(T,10)
legend('Caso 1','Caso 2','Modelo de referência')



