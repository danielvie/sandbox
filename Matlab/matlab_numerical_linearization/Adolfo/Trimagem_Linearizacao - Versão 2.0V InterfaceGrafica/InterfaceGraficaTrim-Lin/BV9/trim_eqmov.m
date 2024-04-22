
R2D = 180/pi;
D2R = pi/180;

time = 0.08;

manete = 0;
alt = 415.5;

d_deg = [0; 0; 0; 0];
d_rad = d_deg * D2R;

p = 0 * D2R;
q = -0.264; %* D2R;
r = 0 * D2R;

u = 311.65;
v = 0;
w = -13.9;

phi = 0 * D2R;
theta = -0.0417; %* D2R;
psi = 0 * D2R;

W = [p; q; r];
V = [u; v; w];
Euler = [phi; theta; psi];

vel = norm(V);

Rcm = [0 0 0]';

[thurst, Mturb, Hturb] = turb_mx(alt, vel, manete, Rcm);

[alfa_rad, beta_rad, mach, rho, Faer, Maer] = ...
    aer_cruz_mx(V, W, CM, alt, d_rad(1), d_rad(2), d_rad(3), d_rad(4));

Fb = Faer+[thurst;0;0];
Mb = Maer + Mturb;
[W_dot, V_dot, Euler_dot, Pn_dot] = eqmov(W, V, Euler, Fb, Mb, J, Hturb, mass);
