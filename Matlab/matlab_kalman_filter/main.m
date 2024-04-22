% Kalman filter Helio Kuga

% propagacao do estado
% X_dot = F * X

% propagacao covariancia continua:
% P_k = F * P * P * F' + G * Q * G'

% propagacao covariancia discreta:
% P_k = Phi_k_ * P_k_ * Phi_k_' + Gamma_k * Q_k * Gamma_k'

% CONDICAO INICIAL
% w   = N(0,q) = N(0, 0.01)
% v_k = N(0,r_k) = N(0, 0.01)

% construcao das matrizes

% K_k = P_k * H_k' * (H_k * P_k * H_k' + R_k)^-1;
% P_k = (eye(1) - K_k*H_k) * P_k;
% x_k = x_k_ + K_k * (y_k - H_k * x_k);

X0 = 1.5;
P0 = 1.0;
dt = 1.0;

x_bar = X0;
p_bar = P0;
h     = 2.0;
Y = [2.1, 5.44, 14.77];

K     = [];
y_Hx  = [];
X_bar = [];
P_bar = [];
X_hat = [];
P_hat = [];

for i = 1:numel(Y)
    % fase de atualizacao 0
    y = Y(i);

    k = 2 * p_bar / (4*p_bar + 0.01);
    x_hat = x_bar + k * (y - h * x_bar);
    p_hat = (1 - 2*k) * p_bar;
      
    K     = [K(:); k];
    y_Hx  = [y_Hx(:); y - h * x_bar];
    X_hat = [X_hat(:); x_hat];
    P_hat = [P_hat(:); p_hat];
    
    % fase de propagacao 1
    C1 = x_hat / exp(0);
    C2 = (p_hat + 0.005) / exp(0);

    X_bar = [X_bar(:); x_bar];
    P_bar = [P_bar(:); p_bar];
    
    x_bar = C1 * exp(dt);
    p_bar = C2 * exp(2*dt) - 0.005;
end

t = table(X_bar, P_bar, K, y_Hx, X_hat, P_hat);
disp(t);