%% Cálculo das margens de estabilidade do plano de rolamento

function [Roll, GA] = MA_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);
Int = tf(1,[1 0]);
[n,d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);
[n,d] = pade(1/100,1);
Delay = tf(n,d);
if Plotar ==1
    figure()
    hold all;
end
for Alt=1:i_max
    
    for Vel=1:j_max
        
        %% Não fechando a malha em taxa de yaw
        
        %         GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
        %         aux = series(AtSS,GrollSS);
        %         K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
        %         GA(Alt,Vel).RollComplete = ss(aux.A,aux.B,K*aux.C,0); %Completa espaço de estado
        
        
        %% Fechando a malha em taxa de yaw
        GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, eye(4),zeros(4,2));
        aux = series(AtSS,GrollSS);
        K = [zeros(1,3) Kd.yaw(Alt,Vel) zeros(1,4); 0 Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) zeros(1,5)];
        GA(Alt,Vel).RollComplete = ss(aux.A-aux.B(:,1)*K(1,:),aux.B(:,2),...
            [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)]*[0 1 zeros(1,6); 0 0 1 zeros(1,5)],0);
        
        GA(Alt,Vel).RollSimple   = G_Simple.p(Alt,Vel)*Int*tf([Kd.roll(Alt,Vel) Kp.roll(Alt,Vel)],1)*At;
        
        %Cálculo das margens de estabilidade
        [Roll.Gm(Alt,Vel),Roll.Pm(Alt,Vel),Roll.wgm(Alt,Vel),Roll.wpm(Alt,Vel)] = margin(GA(Alt,Vel).RollComplete);
        S = allmargin(GA(Alt,Vel).RollComplete);
        Roll.S(Alt,Vel) = S.Stable;
        if Plotar ==1
            %             bode(GA(Alt,Vel).RollComplete*Delay,GA(Alt,Vel).RollSimple*Delay); %coloquei o delay dia 11/02
%             nichols(GA(Alt,Vel).RollComplete,GA(Alt,Vel).RollSimple);
            bode(GA(Alt,Vel).RollComplete,GA(Alt,Vel).RollSimple);
        end
    end
    
end

end

%% Teste adolfo conferência para ver se a malha aberta no espaço
%de estados é igual a da FT

%             [n,d] = ss2tf(GrollSS.A,GrollSS.B,[0 1 0 0],0);
%             Ga = tf(n,d);
%             Ga = Ga*At*tf([Kd.roll(Alt,Vel) Kp.roll(Alt,Vel)],1);