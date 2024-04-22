%% Calculo da Jacobiana de D - Somente da aceleração, mais especificamente a normal ao corpo (por enquanto)
%Versão 1.0 - Última Atualização - 16/07/2014 (Adolfo) 

function D = jacobianD(t,x,u,Modelo)

D = zeros(1,1);
aux = zeros(3,4);
tolmin = 0.001;
min_dv = 0.0001;
del = 0.01;
dmin = 0.1;


for j =2:2 %Percorre coluna %2:2
    dv0 = max( abs(del*u(j)), dmin ); %tamanho da perturbação inicial
    dv1 = 1.1*dv0;
    for i =1:3 % Percorre Linha 8:8
        tol = 0.1;
        FlagAtingiu = 0;
        a0 = LinModelYu(t,x,u,i,j,dv0,Modelo);
        a1 = LinModelYu(t,x,u,i,j,dv1,Modelo);
        b0 = min(abs(a0), abs(a1));
        d0 = abs(a0 -a1); %variação do xdot da variavel perturbada
        k=0;
        new_dv = dv0;
        while (k < 100 && FlagAtingiu == 0)
            new_dv = 0.5*new_dv; %diminui o tamanho da perturbação
            if new_dv <= min_dv*u(j) %caso a perturbação seja menor que a minima tolerencia de variação dos estados
                fprintf('Tolerância mínima não atingida Jacobiano D -- Linha %f , Coluna %f\n',i,j);
                break;
            else
                a1 = a0;
                a0 = LinModelYu(t,x,u,i,j,new_dv,Modelo);
                b1 = b0;
                b0 = min(abs(a0), abs(a1));
                d1 = d0;
                d0 = abs(a1 - a0);
                
                while d0 < tol*b0 && d1 <= tol*b1 %Teste dia 15/07
                    tol = tol*0.5; %modifique era 0.8 14/07
                    if tol <= tolmin
                        tol = tolmin;
                        FlagAtingiu  = 1 ; %Tolerância Mínima Atingida
                        break;
                    end
                end
                k = k + 1;
            end
            
        end
        if (j == 2 || j ==3 || j==4)
            aux(i,j) = a1*180/pi; %Multiplicando o coeficiente p deixar todas as unidades em 1/s^2/rad ou m/s^2/rad
        else
            aux(i,j) = a1;
        end
    end
    
end
%% Escrevendo no Formato [Vt alpha q theta | beta phi p r |psi]
D = aux(3,2);
end

