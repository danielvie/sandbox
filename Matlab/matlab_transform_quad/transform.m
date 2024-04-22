
% r1x = [0, 1, 1, 0, 0];
% r1y = [0, 0, 1, 1, 0];
% 
A  = [0,0];
B  = [1,0];
C  = [1,1];
D  = [0,1];

M  = [A;B;C;D];

A_ = [0,0];
B_ = [6,-0.5];
C_ = [5,8];
D_ = [1.5,7];

M_  = [A_;B_;C_;D_];
% 
% r2x = [A(1), B(1), C(1), D(1), A(1)];
% r2y = [A(2), B(2), C(2), D(2), A(2)];

% computando homography matrix


% P(1:2, :) = [-M(1,1)]

% syms x1 y1 x1_ y1_

% M  = [x1 , y1];
% M_ = [x1_, y1_];

P  = zeros(8,9);

for i = 1:4
    ii = (i-1)*2 + 1;
    
    P(ii:ii+1, :) = [-M(i,1) -M(i,2) -1 0 0 0 M(i,1)*M_(i,1) M(i,2)*M_(i,1) M_(i,1);
                      0 0 0 -M(i,1) -M(i,2) -1 M(i,1)*M_(i,2) M(i,2)*M_(i,2) M_(i,2)];
end

H  = reshape(P\[0,0,0,0,0,0,0,1]', [3,3])';

[U,S,V] = svd(P);
V  = V';
H  = reshape(V(end, :), [3,3])';
% testando ponto B

disp('teste A (0, 0) -> (0.0, 0.0)');
disp(fn_get_ponto(H, A)');

disp('teste B (1, 0) -> (6.0, -0.5)');
disp(fn_get_ponto(H, B)');

disp('teste C (1, 1) -> (5.0,  8.0)');
disp(fn_get_ponto(H, C)');

disp('teste D (0, 1) -> (1.5,  7.0)');
disp(fn_get_ponto(H, D)');
