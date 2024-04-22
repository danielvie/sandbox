%% Cálculo das margens de estabilidade do plano de pitch
%considerando a malha de velocidade fechada

function [Pitch, GA] = MA_Long(AtSS,TurbSS,Kturb, G_Simple,Plano_Long,Kp,Kd,Plotar)

t = 0:0.01:2*pi;
x = 9*cos(t);
y = -180 + 45*sin(t);


%Criado o modelo do Atuador no espaço de estados
[i_max, j_max, ~, ~] = size(Plano_Long);
Int = tf(1,[1 0]);
[n, d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);


%Modelo de Atraso da computação digital
f = 100;
[n,d] = pade(1/100,1);
ZOH = tf(n,d);

if Plotar ==1
    figure();
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        %Calculo da malha aberta em arfagem Completa e Simplifica
        GpitchSS = ss(Plano_Long(Alt,Vel).A(1:4,1:4), Plano_Long(Alt,Vel).B(1:4,:), eye(4),zeros(4,2));
        aux = append(TurbSS,AtSS);
        aux = series(aux,GpitchSS);
        K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];       
        
        
        %Fechando a malha na Turbina
        GaAux = ss(aux.A-aux.B(:,1)*[Kturb zeros(1,6)],aux.B(:,2),[0 0 1 zeros(1,4); 0 0 0 1 zeros(1,3)],0);
        
        %Abrindo a malha em arfagem
        GA(Alt,Vel).PitchComplete = ss(GaAux.A,GaAux.B,K*GaAux.C,0); %Completa
        Gp = At*G_Simple.q(Alt,Vel);
        GA(Alt,Vel).PitchSimple = Gp*Int*tf([Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)],1); %Simplificada
        
        %Cálculo das margens de estabilidade
        
        [Pitch.Gm(Alt,Vel), Pitch.Pm(Alt,Vel),Pitch.wgm(Alt,Vel), Pitch.wpm(Alt,Vel)] = margin(GA(Alt,Vel).PitchComplete);
        S = allmargin(GA(Alt,Vel).PitchComplete);
        SSimple = allmargin(GA(Alt,Vel).PitchSimple);
        Pitch.S(Alt,Vel) = S.Stable;
        if S.Stable == 0
            aaa = 1;
        end
        if Plotar == 1
            bode(GA(Alt,Vel).PitchComplete, GA(Alt,Vel).PitchSimple)
            %             nichols(GA(Alt,Vel).PitchComplete*ZOH,0.1:0.1:100)
        end
        
    end
    
end
plot(y,x,'r')
end