%% Cálculo das margens de estabilidade do plano de guinada

function [Yaw, GA] = MA_Yaw (AtSS,G_Simple,Plano_Lat,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);
Int = tf(1,[1 0]);
[n,d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);

if Plotar ==1
    figure()
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        
        %% Não fechando a malha em rolamento
        %         GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,1), [0 0 0 1],0);
        %         aux = series(AtSS,GyawSS);
        %         GA(Alt,Vel).YawComplete = ss(aux.A,aux.B,Kd.yaw(Alt,Vel)*aux.C,0); %Completo
        
        
        %Fechando a malha em Roll e abrindo a malha em Yaw
        GyawSS2 = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, eye(4),zeros(4,2));
        aux2 = series(AtSS,GyawSS2);
        
        K = [zeros(1,3) Kd.yaw(Alt,Vel) zeros(1,4); 0 Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) zeros(1,5)];
        GA(Alt,Vel).YawComplete = ss(aux2.A-aux2.B(:,2)*K(2,:),aux2.B(:,1),K(1,4)*[0 0 0 1 0 0 0 0],0);
        
        %Considerando a dinâmica simplificada
        GA(Alt,Vel).YawSimple = G_Simple.r(Alt,Vel)*At*Kd.yaw(Alt,Vel);    %Simplificado
        
        %Cálculo das margens de estabilidade
        [Yaw.Gm(Alt,Vel),Yaw.Pm(Alt,Vel), Yaw.wgm(Alt,Vel),Yaw.wpm(Alt,Vel)] = margin(GA(Alt,Vel).YawComplete);
        S = allmargin(GA(Alt,Vel).YawComplete);
        Yaw.S(Alt,Vel) = S.Stable;
        if Plotar == 1
%             bode(GA(Alt,Vel).YawComplete,GA(Alt,Vel).YawSimple);
            nichols(GA(Alt,Vel).YawComplete,GA(Alt,Vel).YawSimple);
        end
    end
end

end