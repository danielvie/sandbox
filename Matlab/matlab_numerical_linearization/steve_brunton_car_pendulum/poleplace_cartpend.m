clear all
close all
clc
%% modelo
init;

%% autovalores
eig(A)

%% analise da controlabilidade
rank(ctrb(A,B))

%% pole placement

P = [-1.0, -1.1, -1.2, -1.3];

K = place(A,B,P);

%% lqr
Q = diag([10,2,4,3]);
R = 0.1;

K = lqr(A,B,Q,R);


tspan = 0:.001:20;

% x = [x, x_dot, theta, theta_dot]
x0 = [-1; 0; pi+.2; 0]; % initial condition
wr = [3; 0; pi; 0]; % reference position
% u  =@(x)-K*(x - wr); % control law
u  =@(x) ctrl(x,K,wr); % control law
[t,x] = ode45(@(t,x)pendcart(x,m,M,L,g,d,u(x)),tspan,x0);

animate_cart(t, x, m, M, L);

plot(t,x)
leg = legend('x', '$\dot{x}$', '$\theta$', '$\dot{\theta}$');
set(leg,'Interpreter','latex');
