%% Programa para avaliar o impacto da inserção do filtro na malha de guinada
%LogTrim -- Ganhos -- InputGanhos
% close all
Alt = 2;
Vel= 6;
g = 9.8;
tau = 2.5;
Fpsi = 1;
Fpitch = 1;
[n,d] = butter(2,2*pi*15,'s');
Fpitch = tf(n,d);
% Fpitch = tf(15*2*pi,[1 15*2*pi]);
wn = 0.25*2*pi;
Fpsi = tf(wn,[1 wn]);
[n,d] = pade(0.01,1);
Delay = tf(n,d);

[n,d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);

figure(1)
hold on;
for Alt =2:2
    for Vel =3:7
        V = Log.Xtrim(Alt,Vel,1);
        Kpsi = V/g/tau;
        aux = feedback(G_Simple.p(Alt,Vel)*At*Delay,Kd.roll(Alt,Vel));
        Gf = feedback(Kp.roll(Alt,Vel)*aux*tf(1,[1 0]),1);
        aux2 = g/V*tf(1,[1 0]);
        Ga = Kpsi*Gf*aux2*Fpsi;        
        bode(Ga)
    end
end

%%
figure(2)
hold on;
for Alt =2:2
    for Vel =3:7
        C = parallel(tf([1 0],1)*Kd.pitch(Alt,Vel)*Fpitch, Kp.pitch(Alt,Vel));
        G = At*Delay*G_Simple.q(Alt,Vel);
        Ga = C*G*tf(1,[1 0]);
        Uf = feedback(C*tf(1,[1 0]),G);
%         C = tf([Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)],1);
%         Ga = C*At*Delay*G_Simple.q(Alt,Vel)*At*tf(1,[1 0])*Fpitch;
        bode(Ga)
    end
end










