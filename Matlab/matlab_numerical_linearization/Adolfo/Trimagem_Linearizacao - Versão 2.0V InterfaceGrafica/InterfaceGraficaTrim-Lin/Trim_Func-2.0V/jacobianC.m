%Calculo da Jacobiana de C - Somente da acelera��o, mais especificamente a normal ao corpo (por enquanto)
%Vers�o 1.0 - �ltima Atualiza��o - 16/07/2014 (Adolfo)

function C = jacobianC(t,x,u,Modelo)

%Criando a Matriz C - (Vt alpha q theta).
C = zeros(1,4);

aux = zeros(1,9);

tolmin = 0.001;
min_dv = 0.0001;
del = 0.01;
dmin = 0.1;


for j =1:9 %%Percorre coluna
    dv0 = max( abs(del*x(j) ), dmin ); %tamanho da perturba��o inicial
    dv1 = 1.1*dv0;
    for i = 3:3 %Percorre linha (ax; ay; az)' Percorre somente Z por enquanto acelera��o medida no corpo
        tol = 0.1;
        FlagAtingiu = 0;
        a0 = LinModelYx(t,x,u,i,j,dv0,Modelo);
        a1 = LinModelYx(t,x,u,i,j,dv1,Modelo);
        b0 = min(abs(a0), abs(a1));
        d0 = abs(a0 -a1); %varia��o do xdot da variavel perturbada
        k=0;
        new_dv = dv0;
        while (k < 100 && FlagAtingiu == 0)
            new_dv = 0.5*new_dv; %diminui o tamanho da perturba��o
            if new_dv <= min_dv*x(j) %caso a perturba��o seja menor que a minima tolerencia de varia��o dos estados
                fprintf('Toler�ncia m�nima n�o atingida Jacobiano C -- Linha %f , Coluna %f\n',i,j);
                break;
            else
                a1 = a0;
                a0 = LinModelYx(t,x,u,i,j,new_dv,Modelo);
                b1 = b0;
                b0 = min(abs(a0), abs(a1));
                d1 = d0;
                d0 = abs(a1 -a0);
                while d0 < tol*b0 && d1 <= tol*b1 %Teste dia 15/07
                    tol = tol*0.5;
                    if tol <= tolmin
                        tol = tolmin;
                        FlagAtingiu  = 1 ; %Toler�ncia M�nima Atingida
                        break;
                    end
                end
                k = k + 1;
            end
            
        end
        aux(1,j) = a1;
    end
    
end


%% Escrevendo no Formato [Vt alpha q theta | beta phi p r |psi h]
C(1,1:2) = aux(1,1:2);
C(1,3)   = aux(1,8);
C(1,4)   = aux(1,5);

%%

end


