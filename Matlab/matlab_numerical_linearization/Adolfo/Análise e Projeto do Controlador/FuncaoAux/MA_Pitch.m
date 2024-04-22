%% Cálculo das margens de estabilidade do plano de pitch
%Última modificação 28/04/2015 -- Acrescentei ZOH as dinâmicas de malha aberta

function [Pitch, GA] = MA_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd,Plotar)

t = 0:0.01:2*pi;
x = 9*cos(t);
y = -180 + 45*sin(t);

[i_max, j_max, ~, ~] = size(Plano_Long);
Int = tf(1,[1 0]);
[n, d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);

f = 100;
[n,d] = pade(1/f,1);
ZOH = tf(n,d);

if Plotar ==1
    figure();
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        
        GpitchSS = ss(Plano_Long(Alt,Vel).A(1:4,1:4) ,Plano_Long(Alt,Vel).B(1:4,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
        aux = series(AtSS,GpitchSS);
        K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
        GA(Alt,Vel).PitchComplete = ss(aux.A,aux.B,K*aux.C,0)*ZOH; %Completa -- 28/04/2015
        Gp = At*G_Simple.q(Alt,Vel)*ZOH;
        GA(Alt,Vel).PitchSimple = Gp*Int*tf([Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)],1); %Simplificada
        
        %Cálculo das margens de estabilidade
        
        [Pitch.Gm(Alt,Vel), Pitch.Pm(Alt,Vel),Pitch.wgm(Alt,Vel), Pitch.wpm(Alt,Vel)] = margin(GA(Alt,Vel).PitchComplete);
        S = allmargin(GA(Alt,Vel).PitchComplete);
%         S = allmargin(GA(Alt,Vel).PitchSimple);
        Pitch.S(Alt,Vel) = S.Stable;
        if S.Stable == 0
            aaa = 1;
        end
        if Plotar == 1
            bode(GA(Alt,Vel).PitchComplete)
%             nichols(GA(Alt,Vel).PitchComplete*ZOH,0.1:0.1:100)
        end        
               
    end
    
end
plot(y,x,'r')
end