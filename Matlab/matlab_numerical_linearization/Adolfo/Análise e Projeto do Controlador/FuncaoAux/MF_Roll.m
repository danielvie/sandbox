function Gf = MF_Roll(AtSS,G_Simple,Plano_Lat,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);
Int = tf(1,[1 0]);
[n, d] = ss2tf(AtSS.A,AtSS.B,AtSS.C,0);
At = tf(n,d);
if Plotar ==1
    figure();
    hold all;    
end

for Alt=1:i_max
    
    for Vel=1:j_max
        %Sem considerar o Yaw
%         GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B(:,2), [0 1 0 0 ; 0 0 1 0],[0;0]);
%         aux = series(AtSS,GrollSS);
%         K = [Kp.roll(Alt,Vel) Kd.roll(Alt,Vel)];
%         Gf(Alt,Vel).RollComplete = ss(aux.A-aux.B*[0 K 0 0 0],aux.B*Kp.roll(Alt,Vel),[0 1 0 0 0 0], 0); %Completa
        
        %Considerando o yaw
        GrollSS = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, [0 1 0 0 ; 0 0 1 0; 0 0 0 1],zeros(3,2));
        aux = series(AtSS,GrollSS);
        K = [0 0 0 Kd.yaw(Alt,Vel) 0 0 0 0; 0 Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) 0 0 0 0 0];
        Gf(Alt,Vel).RollComplete = ss(aux.A-aux.B*K,aux.B(:,2)*Kp.roll(Alt,Vel),[0 1 zeros(1,6)], 0); %Completa
        
        %fim
        aux  = feedback(At*G_Simple.p(Alt,Vel),Kd.roll(Alt,Vel));
        Gf(Alt,Vel).RollSimple = feedback(Kp.roll(Alt,Vel)*aux*Int,1);
        
        if Plotar ==1
            step(Gf(Alt,Vel).RollComplete)
            %                 pzmap(Gf(Alt,Vel).RollComplete)
        end
    end
end

end