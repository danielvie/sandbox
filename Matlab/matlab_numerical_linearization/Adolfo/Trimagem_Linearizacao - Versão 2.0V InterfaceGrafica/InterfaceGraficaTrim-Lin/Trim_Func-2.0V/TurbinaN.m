%Calculo do Empuxo
%Dados Boarin email do dia 21/05/2014 -- Arquivo Dados para 6DOF.xls
%Dados somente para Mach 0.75
function empuxo = TurbinaN(dT,h)

dt = dT*100;
    
    if h >= 200 && h < 1500

        Emp = [0 16.4468, 61.1604,108.221,157.2105,207.2918,258.6777,312.4338,410.4184,512.9465,620.9693,715.9622,811.2151,897.2266,987.8557,1082.7355,1185.5532,1295.7743,1414.5698,1539.0868,1670.0159,1810.1344,1956.7073,2106.0579,2264.7707,2422.4862,2584.0891,2754.7467,2927.7647,3103.9803;];
        Manete = [70, 72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100;];
        empuxo = interp1(Manete,Emp,dt);
    
    elseif h >=1500 && h<2000
        Emp = [0 577.0431288	1576.982481	3115.788892];
        Manete = [70 80 90 100];
        empuxo = interp1(Manete,Emp,dt);
     
    elseif h>=2000 && h<2500
       Emp = [1.542297243	623.1886774	1619.026524	3120.294074];
       Manete = [70 80 90 100]; 
       empuxo = interp1(Manete,Emp,dt); 
    
    
    elseif h>=2500 && h<3000
       Emp = [31.92442829	662.4988806	1612.135844	3122.309077];
       Manete = [70 80 90 100]; 
       empuxo = interp1(Manete,Emp,dt); 
        
    elseif h >= 3000 && h< 3500
       Emp = [89.24951226	713.7805335	1713.05345	3104.279808];
       Manete = [70 80 90 100]; 
       empuxo = interp1(Manete,Emp,dt);          
        
    elseif h>=3500 && h<=4000
       Emp = [114.1549882	737.5347221	1735.606307	3081.586765];
       Manete = [70 80 90 100];
       empuxo = interp1(Manete,Emp,dt);  
    
    else
        error('Não existe a tabela do empuxo para a altura especificada');
 
        
    end
end
