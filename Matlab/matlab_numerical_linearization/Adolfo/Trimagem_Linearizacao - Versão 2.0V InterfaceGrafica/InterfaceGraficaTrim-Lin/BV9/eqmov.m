function [W_dot, V_dot, Euler_dot, Pn_dot] = eqmov(W, V, Euler, Fb, Mb, J, Hturb, mass)

p = W(1);
q = W(2);
r = W(3);

phi = Euler(1);
theta = Euler(2);
psi = Euler(3);

cphi = cos(phi);
sphi = sin(phi);
ctheta = cos(theta);
stheta = sin(theta);
cpsi = cos(psi);
spsi = sin(psi);
    
% Lewis página 46

g = 9.8066;
G_vet = [0; 0; g];

Cnb = [         ctheta*cpsi             ctheta*spsi                 -stheta
        -cphi*spsi+sphi*stheta*cpsi  cphi*cpsi+sphi*stheta*spsi   sphi*ctheta
         sphi*spsi+cphi*stheta*cpsi -sphi*cpsi+cphi*stheta*spsi   cphi*ctheta];
     
Cbn = Cnb';

OMEGA = [ 0 -r  q
          r  0 -p
         -q  p  0];
     
ETA = [ 1  stheta*sphi/ctheta  stheta*cphi/ctheta
        0           cphi                -sphi
        0       sphi/ctheta         cphi/ctheta];
    
% Force Equation
V_dot = (Fb/mass) - OMEGA*V + Cnb*G_vet;

% Atitude Equation;
Euler_dot = ETA*W;

% Momento Equation
W_dot = J\(-OMEGA*(J*W) + Mb ) - OMEGA*Hturb;

% Navigation Equation
Pn_dot = Cbn*V;

