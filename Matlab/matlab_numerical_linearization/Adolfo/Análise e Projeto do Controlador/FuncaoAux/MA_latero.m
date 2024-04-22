%% Cálculo das margens de estabilidade do plano látero sigma

function MA_latero(AtSS,Plano_Lat,Kp,Kd,Plotar)

[i_max, j_max, ~, ~] = size(Plano_Lat);

if Plotar ==1
    figure();
    hold all;
end

for Alt=1:i_max
    
    for Vel=1:j_max
        
        GAteste = ss(Plano_Lat(Alt,Vel).A ,Plano_Lat(Alt,Vel).B, [0 1 0 0; 0 0 1 0; 0 0 0 1],zeros(3,2));
        
        aux = series(AtSS,GAteste);
        Kteste = [0 0 Kd.yaw(Alt,Vel);Kp.roll(Alt,Vel) Kd.roll(Alt,Vel) 0];
        Gass_teste = ss(aux.A,aux.B,Kteste*aux.C,0);
        
        if Plotar ==1
%             sigma(Gass_teste,aux)
%             sigma(aux(1,2),aux(2,2),aux(3,2))
%             sigma(aux(1,1),aux(2,1),aux(3,1))
%             legend('Phi','p','r') 
            sigma(Gass_teste(1,2),Gass_teste(2,2))
            sigma(Gass_teste(1,1),Gass_teste(2,1))
            legend('Ail2yawrate','Ail2Roll','Rudder2yawrate','Rudder2Roll')          
        end
        
        
    end
    
end