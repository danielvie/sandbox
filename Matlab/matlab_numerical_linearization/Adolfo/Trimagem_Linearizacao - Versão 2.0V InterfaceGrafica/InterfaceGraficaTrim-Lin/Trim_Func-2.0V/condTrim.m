%% Condições de Trimagem

% - Opção 1 -- Trimando p/ gamma = 0 e dPhi = 0
% - Opção 2 -- Trimando p/ gamma = X e dPhi = 0
% - Opção 3 -- Trimando p/ gamma =0  e dPhi = X

function [Altitude_Tab, Mach_Tab, gamma_Tab, dphi_Tab] = condTrim(Altitude,Velocidade,CondTrimagem,ROC,G)

opcao = CondTrimagem;
Altitude_Tab = Altitude;
I_final = length(Altitude_Tab);
Vt_Tab = Velocidade;
J_final = length(Vt_Tab);
Mach_Tab = zeros(5,J_final);
gamma_Tab = Mach_Tab;
dphi_Tab  = Mach_Tab;
Phi = [0 15 30 45 60]*pi/180;


switch opcao
    
    case 1       
        for i=1:I_final
            for j=1:J_final
                Mach_Tab(i,j)  = atm_ISAVel2Mach(Altitude_Tab(i),Vt_Tab(j));
            end
        end
        
    case 2        
%         ROC      = input('Entre com a taxa de subida (m/s) --- ');
        for i=1:I_final
            for j=1:J_final
                Mach_Tab(i,j)  = atm_ISAVel2Mach(Altitude_Tab(i),Vt_Tab(j));
                gamma_Tab(i,j) = asin(ROC/Vt_Tab(j));
            end
        end
        
    case 3      
%         G        = input('Entre com a aceleração centrípeta, está por unidade em (gs) --- ');
        for i=1:I_final
            for j=1:J_final
                Mach_Tab(i,j)  = atm_ISAVel2Mach(Altitude_Tab(i),Vt_Tab(j));
                dphi_Tab(i,j)  = (G*9.8/Vt_Tab(j));
            end
        end
        
    case 4        
        alt        = input('Entre com a altitude desejada (m) --- ');
        for i=1:I_final
            for j=1:J_final
                Altitude_Tab(i,j)   = alt; 
                Mach_Tab(i,j)       = atm_ISAVel2Mach(Altitude_Tab(i),Vt_Tab(j));
                dphi_Tab(i,j)       = (tan(Phi(i))*9.8/Vt_Tab(j));
            end
        end
        
        
end


end