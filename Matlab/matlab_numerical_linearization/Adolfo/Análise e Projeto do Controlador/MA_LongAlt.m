%% Cálculo das margens de estabilidade do plano de pitch
%considerando a malha de velocidade fechada

function [AltGA, GA] = MA_Long2100(AtSS,TurbSS,Kturb, Kh, Plano_Long,Kp,Kd,Plotar)

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
        GpitchSS = ss(Plano_Long(Alt,Vel).A, Plano_Long(Alt,Vel).B, eye(5),zeros(5,2));
        aux = append(TurbSS,AtSS);
        aux = series(aux,GpitchSS);
%         K = [Kd.pitch(2100,Vel) Kp.pitch(2100,Vel)];       
        K = [Kturb zeros(1,7); 0 0 Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) zeros(1,4)];
        
        %Fechando a malha na Turbina/ Arfagem
        GaAux = ss(aux.A-aux.B*K,aux.B(:,2),[0 0 0 0 1 0 0 0],0);
        
        %Abrindo a malha em altitude
        GA(Alt,Vel).AltGAComplete = ss(GaAux.A,GaAux.B,Kh*GaAux.C,0); %Completa       
        
        %Cálculo das margens de estabilidade
        
        [AltGA.Gm(Alt,Vel), AltGA.Pm(Alt,Vel),AltGA.wgm(Alt,Vel), AltGA.wpm(Alt,Vel)] = margin(GA(Alt,Vel).AltGAComplete);
        S = allmargin(GA(Alt,Vel).AltGAComplete);        
        AltGA.S(Alt,Vel) = S.Stable;
        if S.Stable == 0
            aaa = 1;
        end
        if Plotar == 1
            bode(GA(Alt,Vel).AltGAComplete)          
        end
        
    end
    
end
plot(y,x,'r')
end