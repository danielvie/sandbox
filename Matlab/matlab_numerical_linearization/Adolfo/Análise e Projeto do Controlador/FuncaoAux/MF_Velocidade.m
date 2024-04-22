function  Gf = MF_Velocidade(Turbina,Atss,G_Simple,Plano_Long,Kturb,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Long);
Atuador = append(Turbina,Atss);
[n,d] = ss2tf(Turbina.A,Turbina.B,Turbina.C,Turbina.D);
Turbina = tf(n,d);
opt = stepDataOptions;
opt.StepAmplitude = 10;

Kh = 1/1800;

if Plotar ==1
    figure();
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        
        %Cálculo Malha Fechada
        
%         Plano_Long(Alt,Vel).A(5,2) = -Plano_Long(Alt,Vel).A(5,2); %já
%         está corrigido na nova linearização
%         Plano_Long(Alt,Vel).A(5,4) = -Plano_Long(Alt,Vel).A(5,4);
        
        Gp = ss(Plano_Long(Alt,Vel).A,Plano_Long(Alt,Vel).B,eye(5),zeros(5,2));
        Gp = series(Atuador,Gp,[1 2],[1 2]);
        Gf(Alt,Vel).VelSimple = feedback(Kturb*Turbina*G_Simple.Vt(Alt,Vel),1); %Simplificada 
        
        K = [Kturb zeros(1,7); 0 0 Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) Kh*Kp.pitch(Alt,Vel) zeros(1,3)];
        C = [1 zeros(1,7)];
        %         Kf = [Kturb 0; 0 Kh*Kp.pitch(Alt,Vel)];
        Kf = [Kturb; 0];
        Gf(Alt,Vel).VelComplete = ss(Gp.A-Gp.B*K,Gp.B*Kf,C,0);
              
        
        if Plotar ==1
            step(Gf(Alt,Vel).VelComplete,0.01:40,opt);
%           pzmap(Gf(Alt,Vel).VelSimple)
        end   
        
      
        
    end
end
