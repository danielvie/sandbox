%% Cálculo da malha fechada

function Gf = MF_Pitch(AtSS,G_Simple,Plano_Long,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Long);
Int = tf(1,[1 0]);
[n, d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);
if Plotar ==1
    figure();
    hold all;
end

% j_max =5;

for Alt=1:i_max
    
    for Vel=1:j_max
        
        GpitchSS = ss(Plano_Long(Alt,Vel).A(1:4,1:4) ,Plano_Long(Alt,Vel).B(1:4,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
        aux = series(AtSS,GpitchSS);
        K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
        
        Gf(Alt,Vel).PitchComplete = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(Alt,Vel),[0 0 0 1 0 0], 0); %completa
        
        auxtf = feedback(G_Simple.q(Alt,Vel)*At,Kd.pitch(Alt,Vel));
        Gf(Alt,Vel).PitchSimple = feedback(Kp.pitch(Alt,Vel)*auxtf*Int,1); %Simplifcada
        %             pzmap(GfSS_pitch)
        if Plotar ==1
            step(Gf(Alt,Vel).PitchComplete,10)
%             pzmap(Gf(Alt,Vel).PitchComplete);
%             bode(Gf(Alt,Vel).PitchComplete)
        end
    end
end
end