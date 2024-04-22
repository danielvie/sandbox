%% Cálculo da malha fechada heading

function Gf = MF_Heading(AtSS,Plano_Lat,Kp,Kd,Velocidade,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);
if Plotar ==1
    figure()
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        
        GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
        aux = series(AtSS,GrollSS);
        K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
        Gfss = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %completa
        
        A = Gfss.A;
        A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
        A(:,7) = zeros(7,1);
        B = Gfss.B;
        B(7,1) = 0;
        %         Gheading_SS = ss(A ,B, [zeros(1,6) 1],0);
        K = Kp.heading(Alt,Vel);
        %                 Gf_headingSS = ss(A-B*[zeros(1,6) K],B*K,[0 1 zeros(1,5); zeros(1,6) 1],[0;0]); %Malha Fechada Heading
        Gf(Alt,Vel).heading = ss(A-B*[zeros(1,6) K],B*K,[zeros(1,6) 1],0); %Malha Fechada Heading
        if Plotar == 1
            step(Gf(Alt,Vel).heading);
        end
    end
end
end
