%% Cálculo da malha fechada do plano longitudinal
%Nesse script considera-se o sistema MIMO - Velocidade e Arfagem
%simultaneamente

function Gf = MF_Long(Turbina,AtSS,Plano_Long,Kturb,Kh,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Long);
Atuador = append(Turbina,AtSS);
if Plotar ==1
    figure();
    hold all;
end

% j_max =5;

for Alt=1:i_max
    
    for Vel=1:j_max
        
        Gp = ss(Plano_Long(Alt,Vel).A,Plano_Long(Alt,Vel).B,eye(5),zeros(5,2));
        Gp = series(Atuador,Gp,[1 2],[1 2]);
        
        K = [Kturb zeros(1,7); 0 0 Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) Kh*Kp.pitch(Alt,Vel) zeros(1,3)];
        C = [1 zeros(1,7); 0 0 0 0 1 0 0 0];
        %         Kf = [Kturb 0; 0 Kh*Kp.pitch(Alt,Vel)];
        Kf = [Kturb; Kh*Kp.pitch(Alt,Vel)];
        Gf(Alt,Vel).VelComplete = ss(Gp.A-Gp.B*K,Gp.B*Kf,C,0);
        
%         Teste Adolfo - Para avaliar a sensibilidade ao ganho da turbina%
        Hab = 0;
        if (Alt == 4 && Vel == 1 && Hab == 1)
            j =[0.5 1 2];
            close all;
            figure()
            hold on;
            for i=1:3
                %Mudando os ganhos
                Kp1.pitch(Alt,Vel) = Kp.pitch(Alt,Vel);
                Kturb1 = j(i)*Kturb;
                K = [Kturb1 zeros(1,7); 0 0 Kd.pitch(Alt,Vel) Kp1.pitch(Alt,Vel) Kh*Kp1.pitch(Alt,Vel) zeros(1,3)];
                C = [1 zeros(1,7); 0 0 0 0 1 0 0 0];
                %         Kf = [Kturb 0; 0 Kh*Kp.pitch(Alt,Vel)];
                Kf = [Kturb1; Kh*Kp1.pitch(Alt,Vel)];
                Gf(Alt,Vel).VelComplete = ss(Gp.A-Gp.B*K,Gp.B*Kf,C,0);                
                pzplot(Gf(Alt,Vel).VelComplete);
            end
            break;
        end
        
        if Plotar ==1
            %             step(Gf(Alt,Vel).VelComplete,10)
            pzplot(Gf(Alt,Vel).VelComplete);
            %             bode(Gf(Alt,Vel).PitchComplete)
        end
    end
end
end