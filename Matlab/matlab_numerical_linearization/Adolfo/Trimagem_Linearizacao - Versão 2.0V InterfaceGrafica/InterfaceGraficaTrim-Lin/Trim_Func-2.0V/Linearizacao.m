%% Programa de Lineariza��o N�merica
%Linearizando o sistema de equa��es n�o lineares a partir do ponto de
%trimagem
%Vers�o 1.0 - �ltima Atualiza��o - 16/07/2014 (Adolfo) 
%Vers�o 2.0 - �ltima Atualiza��o - 07/08/2014 (Adolfo)

% Estados = [Vt alpha beta phi theta psi p q r XN XE XD]'
% j =  Velocidade
function [Plano_Long, Plano_Lat,Coef] = Linearizacao(X_Trim,U_Trim,Modelo)
    t=1;
    Progresso = waitbar(0,'Progresso da Lineariza��o');  
    [i_max, j_max, ~] = size(X_Trim);

    % Plano_Long.A = zeros(j_max,i_max,4,4);
    % Plano_Long.B = zeros(j_max,i_max,4,2);
    % Plano_Long.C = zeros(j_max,i_max,1,4); %Lineariza��o da medida de acelera��o no corpo
    % Plano_Long.D = zeros(j_max,i_max,1,1); %Lineariza��o da medida de acelera��o no corpo
    % 
    % Plano_Lat.A = zeros(5,5,4,4);
    % Plano_Lat.B = zeros(5,5,4,2);

    for i=1:i_max
    waitbar(i/i_max,Progresso);
    %     [Modelo.Inercia, Modelo.Rcm, Modelo.Massa] = Prop_Massa(j); N�o
    %     existem mais
        
        for j=1:j_max
            
            Controle = [U_Trim.Manete(i,j) U_Trim.dPitch(i,j) U_Trim.dYaw(i,j)...
                        U_Trim.dRoll(i,j)  U_Trim.AoA(i,j)    U_Trim.Beta(i,j)];
            
            [dfdx, YA] = jacobianA(t,X_Trim(i,j,:),Controle,Modelo);
            [dfdu, YB] = jacobianB(t,X_Trim(i,j,:),Controle,Modelo);
            dydx = jacobianC(t,X_Trim(i,j,:),Controle,Modelo);
            dydu = jacobianD(t,X_Trim(i,j,:),Controle,Modelo);
            
            %Cria��o do sistema no espa�o de estados para o plano longitudinal
            
    %         Plano_Long(i,j).A(:,:) = dfdx(1:4,1:4);
            Plano_Long(i,j).A(:,:) = dfdx(1:5,1:5);
            Plano_Long(i,j).B(:,:) = dfdu(1:5,1:2);
            Plano_Long(i,j).C(:,:) = dydx;
            Plano_Long(i,j).D(:,:) = dydu;
            
            %Cria��o do sistema no espa�o de estados para o plano lateral
            
            Plano_Lat(i,j).A(:,:) = dfdx(6:9,6:9);
            Plano_Lat(i,j).B(:,:) = dfdu(6:9,3:4);
            
            %% Cria��o dos Coeficientes
            
            %[Malpha, Mq, Zalpha Zq, Lbeta, Nbeta, Ybeta, Nr,Lp] = YA
            %[Mdelta,Zdelta,Ndelta,Ydelta, DeltaYaw/Roll,Ldelta,DeltaRoll/Yaw] 
            %p = tf(Ldelta , [1 -Lp]);
            %q = tf([Vt*Mdelta (Zdelta*Malpha - Zalpha*Mdelta) ],[Vt -(Zalpha + Vt*Mq) (Mq*Zalpha - Vt*Malpha)]);
            %r = tf([Vt*Ndelta (Ydelta*Nbeta - Ybeta*Ndelta) ],[Vt -(Ybeta+Vt*Nr) (Vt*Nbeta+Nr*Ybeta)]);
            
            Coef(i,j).Ya = YA; 
            Coef(i,j).Yb = YB; 
    
        
            
        end
        
    end
    close(Progresso);
end