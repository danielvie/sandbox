%% Output feedback -- Projeto do controlador;
%Gp = Planta
%Q  = Matriz de ponteração da dinâmica
%R  = Matriz do esforço de controle
%K  = Ganho estabilizante inicial


function [J, K_k] = Outputfeedback(Gp,Q,R,K)

% X(1) = 1;
% X(2) = pi/180;
% X(3) = pi/180;
% X(4) = pi/180;

X = eye(4);

A = Gp.A;
B = Gp.B;
C = Gp.C;
alpha =0.001;

K_k = K;

Ac = A-B*K_k*C;

aux = C'*K_k'*R*K_k*C + Q;
P = lyap(Ac,aux);

J_k = trace(P*X);

for i=1:1000
    
    
    Ac = A-B*K_k*C;
    
    aux = C'*K_k'*R*K_k*C + Q;
    P = lyap(Ac,aux);
    S = lyap(Ac,X);
    
    deltaK = inv(R)*B'*P*S*C'*inv(C*S*C') -K_k;  
    
    K_k = K_k + alpha*deltaK;
    
    J = trace(P*X) ;
    
end

end