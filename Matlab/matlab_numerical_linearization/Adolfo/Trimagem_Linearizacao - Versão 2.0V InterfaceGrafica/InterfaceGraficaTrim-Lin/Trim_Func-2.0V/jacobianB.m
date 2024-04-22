%% Criando a Jacobiana de B
%Versão 1.0 - Última Atualização - 16/07/2014 (Adolfo)

function [B,Y] = jacobianB(t,x,u,Modelo)

% B = zeros(9,4);
B= zeros(12,4);
tolmin = 0.001;
min_dv = 0.0001;
% min_dv = 0.00001;
del = 0.05;
dmin = 0.1;


for j =1:4 %Percorre coluna
    dv0 = max( abs(del*u(j)), dmin ); %tamanho da perturbação inicial
    dv1 = 1.1*dv0;
    for i =1:12 % Percorre Linha era 9
        tol = 0.1;
        FlagAtingiu = 0;
        [a0,Coef] = LinModelU(t,x,u,i,j,dv0,Modelo);
        [a1,Coef] = LinModelU(t,x,u,i,j,dv1,Modelo);
        b0 = min(abs(a0), abs(a1));
        d0 = abs(a0 -a1); %variação do xdot da variavel perturbada
        k=0;
        new_dv = dv0;
        while (k < 100 && FlagAtingiu == 0)
            new_dv = 0.5*new_dv; %diminui o tamanho da perturbação
            if new_dv <= min_dv*u(j) %caso a perturbação seja menor que a minima tolerencia de variação dos estados
                fprintf('Tolerância mínima não atingida Jacobiano B -- Linha %f , Coluna %f\n',i,j);
                break;
            else
                a1 = a0;
                [a0,Coef] = LinModelU(t,x,u,i,j,new_dv,Modelo);
                b1 = b0;
                b0 = min(abs(a0), abs(a1));
                d1 = d0;
                d0 = abs(a1 - a0);
                
                while d0 < tol*b0 && d1 <= tol*b1 %Teste dia 15/07
                    tol = tol*0.5;
                    if tol <= tolmin
                        tol = tolmin;
                        FlagAtingiu = 1;
                        break;
                    end
                end
                k = k + 1;
            end
        end
        if (j == 2 || j ==3 || j==4)
            B(i,j) = a1*180/pi; %Multiplicando o coeficiente p deixar todas as unidades em 1/s^2/rad ou m/s^2/rad
        else
            B(i,j) = a1;
        end
        
        %Criando código para pegar os coeficientes
        %[Mdelta,Zdelta,Ndelta,Ydelta, DeltaYaw/Roll,Ldelta,DeltaRoll/Yaw]
        if j == 2 && i == 8
            Y(1) = Coef(2)*180/pi; %Mdelta
            Y(2) = Coef(6)*180/pi; %Zdelta
        elseif j == 3 && i == 7
            Y(5) = Coef(1)*180/pi; %Acoplamento deltaYaw -> Roll
        elseif j == 3 && i == 9
            Y(3) = Coef(3)*180/pi; %Ndelta
            Y(4) = Coef(5)*180/pi; %Ydelta
        elseif j == 4 && i == 7
            Y(6) = Coef(1)*180/pi; %Ldelta
        elseif j == 4 && i == 9 
            Y(7) = Coef(3)*180/pi; %Acoplamento deltaRoll -> Yaw
            
        end
        
    end
    
end
%% Escrevendo no Formato [Vt alpha q theta | beta phi p r |psi]
aux2        = zeros(12,4);
aux2(1:2,:) = B(1:2,:);
aux2(3,:)   = B(8,:);
aux2(4,:)   = B(5,:);
aux2(5,:)   = B(12,:); %Altitude
aux2(6,:)   = B(3,:);
aux2(7,:)   = B(4,:);
aux2(8,:)   = B(7,:);
aux2(9,:)   = B(9,:);
aux2(10,:)  = B(6,:);
B = aux2;
end