%% Teste projeto do controlador

% Plano Longitudinal
%wa = banda passante do atuador
%zetaA = Amortecimento do atuador
%Gp = planta do sistema sem controlador
%wcg = frequência de cruzamento de ganho
%MF = margem de fase

Vel = 6;
Alt = 2;

clear i;
wa = 7*2*pi;
zetaA = 0.7;
At = tf(wa^2,[1 2*zetaA*wa wa^2]);

%Estado de espaço representação Atuador
aa = [0 1; -wa^2 -2*zetaA*wa];
ba = [0 ;wa^2];
ca = [1 0];
da = 0;

AtSS= ss(aa,ba,ca,da);

%Integrador
Int = tf(1,[1 0]);

for Alt=1:i_max
    
    for Vel = 1:j_max
        K = GanhosLongitudinal(G_Simple.q(Alt,Vel),At);
        Kp.pitch(Alt,Vel) = K(1);
        Kd.pitch(Alt,Vel) = K(2);
        K = GanhosLateralRoll(G_Simple.p(Alt,Vel));
        Kp.roll(Alt,Vel) = K(1);
        Kd.roll(Alt,Vel) = K(2);
        Kd.yaw(Alt,Vel)  = GanhosLateralYawdamper(G_Simple.r(Alt,Vel));
        Kp.heading(Alt,Vel) = GanhosHeading(9.806,Velocidade(Vel));
    end
    
end


fig=1;

for i =3:3
            
    for Alt=1:i_max
        
        figure(fig)
        hold all
        
        for Vel=1:j_max
            
            
            if i==1 %Malha Aberta Longitudinal
                
                GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                aux = series(AtSS,GpitchSS);
                K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                
                GaSS_pitch = ss(aux.A,aux.B,K*aux.C,0); %completa
                
                Gp = At*G_Simple.q(Alt,Vel);
                Ga_pitch = Gp*Int*tf([Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)],1); %Simplificada
                %             bode(GaSS_pitch(Alt,Vel),Ga_pitch(Alt,Vel));
                
                
                %Cálculo das margens de estabilidade
                [Gm(Alt,Vel),Pm(Alt,Vel),Wcg(Alt,Vel),Wcp(Alt,Vel)] = margin(Gass_roll); 
                bode(GaSS_pitch);
                
            elseif i==2 %Malha Fechada Longitudinal
                
                GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                aux = series(AtSS,GpitchSS);
                K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                
                GfSS_pitch = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(Alt,Vel),[0 0 0 1 0 0], 0); %completa
                
                auxtf = feedback(G_Simple.q(1,6)*At,Kd.pitch(Alt,Vel));
                Gf_pitch = feedback(Kp.pitch(Alt,Vel)*auxtf*Int,1); %Simplifcada
                %             pzmap(GfSS_pitch)
                step(GfSS_pitch,10)
                
            elseif i==3 %Malha Aberta Rolamento
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 1 0 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gass_roll = ss(aux.A,aux.B,K*aux.C,0); %completa
                %             Ga_roll = G_Simple.p(Alt,Vel)*Int*tf([Kd.roll Kp.roll],1)*At;
                
                %Cálculo das margens de estabilidade                
                [Gm(Alt,Vel),Pm(Alt,Vel),Wcg(Alt,Vel),Wcp(Alt,Vel)] = margin(Gass_roll);                
                bode(Gass_roll);
                
                
            elseif i==4 %Malha Fechada Rolamento
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 1 0 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gfss = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %completa
                aux  = feedback(At*G_Simple.p(Alt,Vel),Kd.roll(Alt,Vel));
                Gf_roll = feedback(Kp.roll(Alt,Vel)*aux*Int,1);
                step(Gfss,Gf_roll,5)
%                 pzmap(Gfss)
                
            elseif i==5 %Malha Aberta Yawdamper
                
                GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,1), [0 0 0 1],0);
                aux = series(AtSS,GyawSS);
                GaSS_yaw = ss(aux.A,aux.B,Kd.yaw(Alt,Vel)*aux.C,0); %Completo
                Ga_yaw = G_Simple.r(Alt,Vel)*At*Kd.yaw(Alt,Vel);    %Simplificado
                
                %Cálculo das margens de estabilidade
                [Gm(Alt,Vel),Pm(Alt,Vel),Wcg(Alt,Vel),Wcp(Alt,Vel)] = margin(Gass_roll); 
                bode(GaSS_yaw);
                
                
            elseif i==6 %Malha Fechada yawdamper
                
                GyawSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,1), [0 0 0 1],0);
                aux = series(AtSS,GyawSS);
                Gfss_yaw = ss(aux.A-aux.B*[0 0 0 Kd.yaw(Alt,Vel) 0 0],aux.B,[0 0 0 1 0 0], 0); %Completo
                Gf_yaw(Alt,Vel) = feedback(G_Simple.r(Alt,Vel)*At,Kd.yaw(Alt,Vel)); %Simplificado
                initial(Gfss_yaw,[1 0 0 10 0 0])
                
                    
            
            elseif i==7 %Malha Aberta Comparação ganho fixo e variável -- Longitudinal
                
                
                GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                aux = series(AtSS,GpitchSS);
                K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                
                GaSS_pitch = ss(aux.A,aux.B,K*aux.C,0); %completa - Variante no tempo os ganhos
                
                K = [Kd.pitch(4,6) Kp.pitch(4,6)];
                GaSS_fixo = ss(aux.A,aux.B,K*aux.C,0); %completa - ganhos fixos
                
                bode(GaSS_pitch,GaSS_fixo);
                
                
            elseif i==8 %Malha Fechada Longitudinal
                
                GpitchSS = ss(Plano_Long(Alt,Vel).A ,Plano_Long(Alt,Vel).B(:,2), [0 0 1 0 ; 0 0 0 1],[0;0]);
                aux = series(AtSS,GpitchSS);
                K = [Kd.pitch(Alt,Vel) Kp.pitch(Alt,Vel)];
                
                GfSS_pitch = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(Alt,Vel),[0 0 0 1 0 0], 0); %Completa - Variável
                
                K = [Kd.pitch(4,6) Kp.pitch(4,6)];
                
                GfSS_fixo = ss(aux.A-aux.B*[0 0 K 0 0],aux.B*Kp.pitch(4,6),[0 0 0 1 0 0], 0); %Completa - Fixo
               
                %             pzmap(GfSS_pitch)
                step(GfSS_pitch,GfSS_fixo,10)
               
                
            elseif i==9 %Heading Control Malha Fechada
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 1 0 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gfss = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %completa
                                
                A = Gfss.A;
                A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
                A(:,7) = zeros(7,1);
                B = Gfss.B;
                B(7,1) = 0;
                Gheading_SS = ss(A ,B, [zeros(1,6) 1],0);
                K = Kp.heading(Alt,Vel);
%                 Gf_headingSS = ss(A-B*[zeros(1,6) K],B*K,[0 1 zeros(1,5); zeros(1,6) 1],[0;0]); %Malha Fechada Heading
                Gf_headingSS = ss(A-B*[zeros(1,6) K],B*K,[zeros(1,6) 1],0); %Malha Fechada Heading
                step(Gf_headingSS);
               
            elseif i==10 %Malha Aberta Heading
                
                GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 1 0 0],[0;0]);
                aux = series(AtSS,GrollSS);
                K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
                Gfss = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %Completa
                                
                A = Gfss.A;
                A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
                A(:,7) = zeros(7,1);
                B = Gfss.B;
                B(7,1) = 0;
                
                GaSS_heading = ss(A, B*Kp.heading(Alt,Vel), [zeros(1,6) 1],0);
                bode(GaSS_heading)
                
                
%                 GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 1 0 0],[0;0]);
%                 aux = series(AtSS,GrollSS);
%                 A = Gfss.A;
%                 A(7,1:7) = [0 9.8/Velocidade(Vel) 0 0 0 0 0];
%                 A(:,7) = zeros(7,1);
%                 B = Gfss.B;
%                 B(7,1) = 0;
%                 C =[0 1 zeros(1,5); 0 0 1 zeros(1,4); zeros(1,6) 1];
%                 K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) Kp.heading(Alt,Vel)];
%                 GaSS_heading = ss(A, B,K*C,0);
%                 bode(GaSS_heading);
                
            end
                        
        end
           
              
        legend('200','210','220','230','240','250','260','290')
        title(['Altitude ' num2str(Altitude(Alt)) ' (m)'] )
        hold off
        fig = fig + 1;
    end
    
end

figure()
mesh(Altitude,Velocidade,Kd.roll'*180/pi)
xlabel('Altitude(m)')
ylabel('Velocidade(m/s)')
zlabel('Kd -- Roll (1/s)')

close all
PlotMargens(Gm,Pm,Wcg,Wcp,Altitude,Velocidade)

