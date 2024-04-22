function [VelLoop, GA] = MA_Velocidade(Turbina,Atss,G_Simple,Plano_Long,Kturb,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Long);

if Plotar ==1
    figure();
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max  

        
        %Cálculo Malha Aberta considerando a malha de \theta e \q
        
        GA(Alt,Vel).VelSimple   = Kturb*Turbina*G_Simple.Vt(Alt,Vel);      
                            
        Gp = ss(Plano_Long(Alt,Vel).A,Plano_Long(Alt,Vel).B,eye(5),0);
        At = append(Turbina,Atss);
        Gp = series(At,Gp);
        Kh = 1/1800;
        K =[Kturb zeros(1,7); 0 0 Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) Kh*Kp.pitch(Alt,Vel) zeros(1,3)];
        GA(Alt,Vel).VelComplete = ss(Gp.A-Gp.B(:,2)*K(2,:),Gp.B(:,1),Kturb*[1 zeros(1,7)],0);
        S = allmargin(GA(Alt,Vel).VelSimple);
        VelLoop.S(Alt,Vel) = S.Stable;
               
        
        %% Teste calculo do máximo valor singular da malha
        
%         C = eye(5);
%         Kh = 1/1800;
%         At = append(Turbina,Atss);
%         Gp = ss(Plano_Long(Alt,Vel).A,Plano_Long(Alt,Vel).B,eye(5),0);
%         Gp = series(At,Gp);
%         K =[Kturb zeros(1,7); 0 0 Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel) Kh*Kp.pitch(Alt,Vel) zeros(1,3)];
%         P = ss(Gp.A,Gp.B,K*eye(8),0);
        
%         P1 = ss(Gp.A,Gp.B(:,1),K(1,:)*C(1),0);
%         P2 = ss(Gp.A,Gp.B(:,1),K(1,:)*C(2),0);
%         P3 = ss(Gp.A,Gp.B(:,1),K(1,:)*C(3),0);
%         P4 = ss(Gp.A,Gp.B(:,1),K(1,:)*C(4),0);
%         P5 = ss(Gp.A,Gp.B(:,1),K(1,:)*C(5),0);
%         
%         P6 = ss(Gp.A,Gp.B(:,2),K(2,:)*C(1),0);
%         P7 = ss(Gp.A,Gp.B(:,2),K(2,:)*C(2),0);
%         P8 = ss(Gp.A,Gp.B(:,2),K(2,:)*C(3),0);
%         P9 = ss(Gp.A,Gp.B(:,2),K(2,:)*C(4),0);
%         P10 = ss(Gp.A,Gp.B(:,2),K(2,:)*C(5),0);
%         bode(P1)        
%         sigma(P)

        if Plotar ==1
            aux = Turbina*tf(Plano_Long(Alt,Vel).B(1,1),[1 Plano_Long(Alt,Vel).A(1,1)])*Kturb; 
            bode(GA(Alt,Vel).VelComplete,GA(Alt,Vel).VelSimple,aux)
%             bode(GA(Alt,Vel).VelSimple)
        end
        
    end
end
