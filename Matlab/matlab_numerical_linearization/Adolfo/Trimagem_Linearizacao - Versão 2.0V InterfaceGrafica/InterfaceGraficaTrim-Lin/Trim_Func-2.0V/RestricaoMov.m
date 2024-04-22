%% Cálculo das Restrições e da função custo
%Programa de Trimagem 6DOF 

function J = RestricaoMov(Opt,Mach,Altitude,Gamma,Dphi,opcao,Modelo)
global Estados;
%Opt=[Manete,Empena(Elevator),Empena(Rudder),Empena(Aileron), Alpha,Beta]

if  Opt(1) > 1 
    Rest = 100000;
elseif Opt(1) < 0.8
   Rest = 10000;
else
   Rest =0; 
end

[Vt, ~, ~, ~] = atm_ISAMach2Vel(Altitude,Mach);

switch opcao
    %% Restrição VOO RETO NIVELADO
    case 1
     
        UR = [Opt(1) Opt(2) Opt(3) Opt(4)]; %[dT dpitch dyaw droll alpha beta]
        alpha = Opt(5);
        beta = Opt(6);
        p = 0;
        q = 0;
        r = 0;
        theta = alpha;
        phi = 0;
        psi = 0;
        XN = 0;
        XE = 0;
        XD = Altitude;
        
    %% Restrição Taxa de subida constante    
    case 2
        
        UR = [Opt(1) Opt(2) Opt(3) Opt(4)];
        alpha = Opt(5);
        beta = Opt(6);
        gamma = Gamma; %Flight path angle
        phi = 0;
        psi = 0;
        p = 0;
        q = 0;
        r = 0;
        XN = 0;
        XE = 0;
        XD = Altitude;

        %Calculo da restrição de theta (equação caderno adolfo) -- Lewis
        a = cos(alpha)*cos(beta);
        b = sin(phi)*sin(beta) + cos(phi)*sin(alpha)*cos(beta);
        aux = a*b + sin(gamma)*(a^2 - sin(gamma)^2 + b^2)^0.5;
        aux2 = a^2 - sin(gamma)^2;
        theta = atan(aux/aux2); %Lembrar de calcular o sinal de theta como lewis % propos
        
    %% Restrição para curva com altitude constante    
    case 3
       
       UR = [Opt(1) Opt(2) Opt(3) Opt(4)];
       beta = Opt(6);
       alpha = Opt(5);
       gamma = 0; %Flight path angle
       psi = 0;
       XN = 0;
       XE = 0;
       XD = Altitude;
       
       %Cálculo da Restrição de Phi
       G = Dphi*Vt/9.8;  %Força centripeta 
       a = G*cos(beta)/(cos(alpha)-G*sin(alpha)*sin(beta));
       phi = atan(a);
       
       %Calculo da restrição de theta (equação caderno adolfo) -- Lewis
       %-Adicionada 10/07/2014
       a = cos(alpha)*cos(beta);
       b = sin(phi)*sin(beta) + cos(phi)*sin(alpha)*cos(beta);
       aux = a*b + sin(gamma)*(a^2 - sin(gamma)^2 + b^2)^0.5;
       aux2 = a^2 - sin(gamma)^2;
       theta = atan(aux/aux2); %Lembrar de calcular o sinal de theta como lewis % propos
       
       
       %Cálculo de p,q,r
       p = -tan(theta)*Dphi*cos(theta); %rascunho conferir
       r = Dphi*cos(alpha)/(sin(phi)*a+cos(phi)); %BUG Retirar
       r = Dphi*cos(theta)/(sin(phi)*tan(phi)+cos(phi));
       q = tan(phi)*r; %29/09 Troque pelo tan(phi) ao invés de a
       
   otherwise
        error('Sair- Não foi inserida uma opção válida')
end


%% Criando os Vetores de Estados com as restrições


if Modelo.Eixo == 0
   
    XR = [Vt alpha beta phi theta psi p q r XN XE XD]'; 
    [xdot, ~,~,~] = EOMCompleta(1,XR,UR,Modelo);
    J = 1*xdot(1)^2 +  100*(xdot(2)^2 + xdot(3)^2) + 10*(xdot(7)^2 + xdot(8)^2 + xdot(9)^2) + Rest;
    
    if J < 1e-8
       teste = 1;
    end
    
% %     assignin('base','Estados', XR);
%     assignin('caller','Estados', XR);
Estados = XR;
    
elseif Modelo.Eixo == 1
    
    XR = [u w v phi theta psi p q r XN XE XD]; %[u w q theta] 
    [xdot, ~,~,~] = EOMCompleta(1,XR,UR,Modelo);
    J = xdot(1)^2 + xdot(2)^2 + xdot(3)^2 + 100*(xdot(7)^2 + xdot(8)^2 + xdot(9)^2) + Rest; %Custo eixo do corpo    
      
end

end
%Fim