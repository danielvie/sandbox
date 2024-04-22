%% Calculo da Jacobiana de A
% Versão 1.0 - Última Atualização - 16/07/2014 (Adolfo)

function [A,Y] = jacobianA(t,x,u,Modelo)

    % Criando a Matriz A
    A      = zeros(12,12);

    tolmin = 0.001;
    min_dv = 0.0001;
    del    = 0.05; 
    dmin   = 0.1; 

    %% Percorre coluna
    for j = 1:12 
        
        % tamanho da perturbação inicial
        dv0 = max( abs( del*x(j) ), dmin ); 
        dv1 = 1.1*dv0;
        
        if j == 12
            dv0 = x(j) + 20.0;
            dv1 = 1.1*dv0;
        end

        % Percorre linha
        for i = 1:12 
            tol = 0.1;
            FlagAtingiu = 0;
            [a0,Coef] = LinModelX(t,x,u,i,j,dv0,Modelo);
            [a1,Coef] = LinModelX(t,x,u,i,j,dv1,Modelo);
            b0 = min(abs(a0), abs(a1));
            d0 = abs(a0 -a1); % variação do xdot da variavel perturbada
            k = 0;
            new_dv = dv0;
            
            while (k < 100 && FlagAtingiu == 0)
                % diminui o tamanho da perturbação -- Reduz a pertubação inicial pela metade a cada iteração
                new_dv = 0.5*new_dv;     
                % caso a perturbação seja menor que a minima tolerencia (0.0001% do estado) de variação dos estados
                if new_dv <= min_dv*x(j) 
                    fprintf('Tolerância mínima não atingida Jacobiano A -- Linha %f , Coluna %f\n',i,j);
                    break;
                else
                    a1 = a0;
                    [a0,Coef] = LinModelX(t,x,u,i,j,new_dv,Modelo);
                    b1 = b0;
                    b0 = min(abs(a0), abs(a1))+1e-12;
                    d1 = d0;
                    d0 = abs(a1 - a0);
                    
                    while d0 < tol*b0 && d1 <= tol*b1 % Teste dia 15/07
                        tol = tol*0.5; % modifique era 0.8 14/07
                        if tol <= tolmin
                            tol = tolmin;
                            FlagAtingiu  = 1 ; % Tolerância Mínima Atingida
                            break;
                        end
                    end
                    k = k + 1;
                end
            end
            A(i,j) = a1;
            % invertendo o sinal da altitude
            if i == 12
                A(i,j) = -a1;
            end     
            
            
            if i == 9 && j == 3
                aux = 1;
            end
            
            % Inserido código para obter os coeficientes
            % [Malpha Mq, Zalpha Zq, Lbeta, Nbeta, Ybeta, Nr]
            if j == 2 && i == 8 
                Y(1) = Coef(2); % Malpha
                Y(3) = Coef(6); % Zalpha
            elseif j == 8 && i == 8
                Y(2) = Coef(2); % Mq
                Y(4) = Coef(6); % Zq
            elseif j == 3 && i == 7
                Y(5) = Coef(1); % Lbeta
            elseif j == 3 && i == 9
                Y(6) = Coef(3); % Nbeta  
                Y(7) = Coef(5); % Ybeta
            elseif j == 9 && i == 9
                Y(8) = Coef(3); % Nr
            elseif j == 7 && i ==7 
                Y(9) = Coef(1); % Lp
            end
            
        end
    end


    %% Escrevendo no Formato [Vt alpha beta phi theta psi p q r Xn Ye Zd] --> [Vt alpha q theta h | beta phi p r |psi] Coloque o h

    % Longitudinal
    aux = zeros(12,12); % Testando aux(9,9)
    aux(:,1:2) = A(:,1:2); % Vt alpha 
    aux(:,3) = A(:,8); % q
    aux(:,4) = A(:,5); % theta
    aux(:,5) = A(:,12); % altitude

    % Lateral
    aux(:,6)  = A(:,3); % beta
    aux(:,7)  = A(:,4); % phi
    aux(:,8)  = A(:,7); % p
    aux(:,9)  = A(:,9); % r
    aux(:,10) = A(:,6); % psi

    aux2        = zeros(12,12);
    aux2(1:2,:) = aux(1:2,:);
    aux2(3,:)   = aux(8,:);
    aux2(4,:)   = aux(5,:);
    aux2(5,:)   = aux(12,:);
    aux2(6,:)   = aux(3,:);
    aux2(7,:)   = aux(4,:);
    aux2(8,:)   = aux(7,:);
    aux2(9,:)   = aux(9,:);
    aux2(10,:)  = aux(6,:);

    A = aux2;

    % SAIDAS: [A,Y]
end