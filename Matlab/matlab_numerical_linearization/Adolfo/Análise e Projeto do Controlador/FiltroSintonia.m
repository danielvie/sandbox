%%Cálculo do filtro para as velocidades angulares
%Última atualização 12/05/2015
%Feito por: Adolfo Graciano da Silva


% close all
hold on
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
At =1;
[n,d] = pade(1/fa,2);
Delay = tf(n,d);
Int = tf(1,[1 0]);
[n,d] = ss2tf(Plano_Long(Alt,Vel).A(2:3,2:3),Plano_Long(Alt,Vel).B(2:3,2),[0 1],0);%Simplificada
Gq = tf(n,d)*At*Delay;

zetaf = realp('zetaf',0.8);
wnf   = realp('wnf',10*2*pi);

Fro = tf(wnf^2,[1 2*zetaf*wnf wnf^2]); 

M  = [1.35 1.35 1.35];   %Utilizadas no Projeto --- 1
A  = [0.05 0.01 0.01];
wb = [5 4 0.5];


for i = 1:2 
    
    wn = 4; %4
    zeta = 0.7;
%     zeta = 1.2; %Teste
    Wp = tf([1/M(i) wb(i)],[1 wb(i)*A(i)]);
    T = tf(wn^2,[1 2*zeta*wn wn^2])*At;
    Wu = tf(10,1);
    
    Kp = 0.49;
    Ki = 0.01;
    Kd = 0.10;
    
    PD = 1;
    if PD == 1
        CKp = tf(0.49,1);
    else
        CKp = tf([Kp Ki],[1 0]);
    end
    
    CKd = tf(Kd,1);
    
    %Exemplo HinfStruct pg 361 Multivariable feedback
    %
    Wp.u = 'e'; Wp.y = 'z1';
    Wu.u = 'u'; Wu.y ='z3';
    Wt = 1/T; Wt.u = 'y'; Wt.y = 'z2';
    CKp.u = 'e'; CKp.y = 'uKp';
    CKd.u = 'yqf'; CKd.y = 'uKd';
    Fro.u = 'yqr' ; Fro.y = 'yqf';    
    Gq.u = 'u'; Gq.y = 'yq';
    Int.u= 'yq'; Int.y = 'y';
    
    Sum3 = sumblk('yqr = yq + n');
    Sum1 = sumblk('e = r - y');
    Sum2 = sumblk('u = uKp - uKd');
    T0 = connect(Gq,Wp,Wt,Wu,Int,CKp,CKd,Sum1,Sum2,Sum3,Fro,{'r','n'},{'z1','z2','z3'});
    
%     Freqs = [1  10  1000];
%     Gains = [10 -1 1e-4];
%     Req = TuningGoal.Gain('n','u',frd(Gains,Freqs));

%     [St,fSoft,~,Info]     = systune(T0,Req);
        
    [CL,gamma,info] = hinfstruct(T0);
    wnF(i) = info.TunedBlocks.wnf.Value;
    zetaF(i) = info.TunedBlocks.zetaf.Value;
    
    %Plotando os resultados
    
    Gi = feedback(Gq,Kd); %Loop interno
    F = tf(wnF^2,[1 2*zetaF*wnF wnF^2]);
    F = tf(40^2,[1 2*0.6*50 40^2]);
    C = parallel(tf([Kd 0],1)*F,Kp);
    
    
    figure(1)  
%     nichols(C*Gq*Int,tf([Kd Kp],1)*Gq*Int,0:0.1:400)
    bode(C*Gq*Int,tf([Kd Kp],1)*Gq*Int)
    set(gca,'XLim',[1e-2 1e3]);
    U = feedback(C*Int,Gq);
    U2 = feedback(parallel(tf([Kd 0],1),Kp)*Int,Gq);
    figure(2)
    bodemag(U2,C)
    set(gca,'XLim',[1e-2 1e3]);
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