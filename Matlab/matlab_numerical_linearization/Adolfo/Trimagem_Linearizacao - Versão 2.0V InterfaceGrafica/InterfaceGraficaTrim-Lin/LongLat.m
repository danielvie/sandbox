function[A_Long,B_Long,A_Lat,B_Lat] = LongLat(Plano_Long,Plano_Lat)
[i_max, j_max] =size(Plano_Long);
auxiliar =0;
for i = 1:i_max
    
    for j = 1:j_max
        
        
        if auxiliar == 1
            
            A_Long = Plano_Long(i,j).A(1:4,1:4);
            B_Long = Plano_Long(i,j).B(1:4,:);
%             DinLong = ss(A_Long,B_Long,eye(4),zeros(4,2),...
%                 'Inputname',{'Manete' 'dPitch'},...
%                 'OutputName',{'Vt' 'AoA' 'q' 'theta'},...
%                 'Statename',{'Vt' 'AoA' 'q' 'theta'}); %criando o sistema em espaço de estados
            
        else
            A_Long = Plano_Long(i,j).A;
            B_Long = Plano_Long(i,j).B;
%             DinLong = ss(A_Long,B_Long,eye(5),zeros(5,2),...
%                 'Inputname',{'Manete' 'dPitch'},...
%                 'OutputName',{'Vt' 'AoA' 'q' 'theta' 'h'},...
%                 'Statename',{'Vt' 'AoA' 'q' 'theta' 'h'}); %criando o sistema em espaço de estados
            
        end
        
        %  A_Long(5,:) = [sin(gamma) x(1)*cos(gamma) 0 -x(1)*cos(gamma) 0]; %Acrescentando a altitude a posteriori   
        
    end
    
end
title('Plano Longitudinal')
%% Dinâmica Lateral - Tratamento


for i=1:i_max
    
    for j=1:j_max
        
        A_Lat = Plano_Lat(i,j).A;
        B_Lat = Plano_Lat(i,j).B;
        
%         %Criando o sistema em espaço de estados
%         DinLat = ss(A_Lat,B_Lat,eye(4),zeros(4,2),...
%             'Inputname',{'dYaw' 'dRoll'},...
%             'OutputName',{'Beta' 'phi' 'p' 'r'},...
%             'Statename',{'Beta' 'phi' 'p' 'r'});        
       
        
    end
end

end