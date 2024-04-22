
J = 20;
A = [0 1;0 0];
B = [0;1/J];
C = [1 0;0 1];
D = [0;0];

sys = ss(A,B,C,D);


A_ = [A [0;0];1 0 0];
B_ = [B;0];

re = -0.9;
im = 1j;
p1 = re + im;
p2 = re - im;

csys = c2d(sys, 0.01);

K  = acker(A,B,[p1, p2]);

K_ = acker(A_,B_,[p1, p2, -7.8]);

syscl  = ss(A-B*K,B,[1, 0],0);
syscl_ = ss(A_-B_*K_,B_,[1, 0, 0],0);

% rlocus(syscl);
sim('model');