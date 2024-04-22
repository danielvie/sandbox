%% Cálculo da malha fechada yaw

function Gf = MA_Yaw(AtSS,G_Simple,Plano_Lat,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);
[n,d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);
if Plotar ==1
    figure()
    hold all;
end
for Alt=1:i_max
    
    for Vel=1:j_max
        
        %% Sem fechar a malha de rolamento
%         GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,1), [0 0 0 1],0);
%         aux = series(AtSS,GyawSS);
%         Gf(Alt,Vel).YawComplete = ss(aux.A-aux.B*[0 0 0 Kd.yaw(Alt,Vel) 0 0],aux.B,[0 0 0 1 0 0], 0); %Completo
        
        %% Fechando a malha de rolamento
        GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, eye(4),0);
        aux = series(AtSS,GyawSS);
        K = [0 0 0 Kd.yaw(Alt,Vel) 0 0 0 0; 0 Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) 0 0 0 0 0];
        
        Gf(Alt,Vel).YawComplete = ss(aux.A-aux.B*K,aux.B(:,1)*K(1,:),[0 0 0 1 0 0 0 0], 0); %Completo
        
        Gf(Alt,Vel).YawSimple = feedback(G_Simple.r(Alt,Vel)*At,Kd.yaw(Alt,Vel)); %Simplificado
        if Plotar ==1
            initial(Gf(Alt,Vel).YawComplete,[1 0 0 10 0 0 0 0],5)
        end
    end
end
end
