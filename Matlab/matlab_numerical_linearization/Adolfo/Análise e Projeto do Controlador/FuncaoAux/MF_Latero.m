%% Cálculo da malha látero

function Gf = MF_Latero(AtSS,Plano_Lat,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);
[n,d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
if Plotar ==1
    figure()
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        
        GAteste = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, eye(4),0);
        aux = series(AtSS,GAteste);
        
        
        %Malha Fechada
%         Kforward = [1 0; 0 Kp.roll(Alt,Vel)];
        Kforward = Kp.roll(Alt,Vel);
        K = [zeros(1,3) Kd.yaw(Alt,Vel) zeros(1,4); 0 Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) zeros(1,5)];
        Gf(Alt,Vel).Latero = ss(aux.A-aux.B*K,aux.B(:,2)*Kforward,[0 1 zeros(1,6); 0 0 0 1 zeros(1,4)],0);
        if Plotar ==1
%             step(Gf,2)
            pzplot(Gf(Alt,Vel).Latero)
        end
        
        
    end
end
end
