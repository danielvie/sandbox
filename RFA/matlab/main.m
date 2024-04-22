tfim = 120;

k = 1;
c = 0.1;
m1 = 1;
m2 = 1;


A = [0, 1, 0, 0;
     -2*k/m1, -2*c/m1, k/m1, c/m1;
     0, 0, 0, 1;
     k/m2, c/m2, -k/m2, -c/m2];

B = [0; 1/m1; 0; 0];

% C = diag([1,0,1,0]);
C = eye(4);

D = zeros(4,1);

eig(A)

% lqr
Ce = [1, 0, 0, 0];

Ae = [ A, zeros(4,1);
      -Ce, 0];

Be = [B;0];

Q  = diag([10,200,1,2000,40]);
R  = 0.02;

Klqr  = lqr(Ae, Be, Q, R);
disp(Klqr);

K  = Klqr(1:4);
Ke = Klqr(5);

yout = sim('model');


% MM = linspace(0.01, 200.0, 50);
% clf;
% for i = 1 : numel(MM) 
% 
%      m2 = MM(i);
%      A = [0, 1, 0, 0;
%           -2*k/m1, -2*c/m1, k/m1, c/m1;
%           0, 0, 0, 1;
%           k/m2, c/m2, -k/m2, -c/m2];
% 
%      sys = ss(A, B, C_, D_);
%      tf_sys = tf(sys);
%      rlocus(tf_sys);
%      % pause(0.5);
%      title(sprintf("valor da massa: %f", m2));
%      hold on;
% end