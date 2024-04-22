% Linearizing Around a Fixed Point [Control Bootcamp]
% https://www.youtube.com/watch?v=1YMTkELi3tE

%{
    1. find fixed pts
        `x_hat` em que f(x_hat) = 0
    2. linearize about `x_hat`
        df/dx

    ex. equacoes diferenciais: 
        x1_dot = f1(x1, x2) = x1*x2
        x2_dot = f2(x1, x2) = x1^2 + x2^2

    jacobian: 
        df/dx = [df1/dx1 df1/dx2; df2/dx1 df2/dx2]
        df/dx = [x2, x1; 2*x1, 2*x2]

    * Hartman–Grobman theorem (linearisation theorem)

    Ex.: Pendulum
    
    theta_dotdot = -g/L * sin(theta) - dtheta_dot
    
    assumindo `g/L` como sendo `1`
    
    theta_dotdot = -sin(theta) - dtheta_dot

    
    state space:
    x1    = theta
    x2    = theta_dot
    
    dF/dX = [x2; -sin(x1) - d]
    
    x_hat = [0;0], [pi;0]

    A down:
        Ad = [0, 1; -1 -d]; 
        
        A up
        Ai = [0, 1; 1 -d];    
%}
        
d  = 0.1;
Ad = [0, 1; -1 -d]; 
Ai = [0, 1;  1 -d];    

eig(Ad)
eig(Ai)