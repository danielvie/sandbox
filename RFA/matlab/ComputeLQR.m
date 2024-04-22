function [K, Ke] = ComputeLQR(m1, m2, c, k)

    A = [0, 1, 0, 0;
         -2*k/m1, -2*c/m1, k/m1, c/m1;
         0, 0, 0, 1;
         k/m2, c/m2, -k/m2, -c/m2];
    
    B = [0; 1/m1; 0; 0];
    
    % C = eye(4);
    % D = zeros(4,1);
    
    % lqr
    Ce = [1, 0, 0, 0];
    
    Ae = [ A, zeros(4,1);
          -Ce, 0];
    
    Be = [B;0];
    
    Q  = diag([10,200,1,2000,40]);
    R  = 0.02;
    
    Klqr  = lqr(Ae, Be, Q, R);
    
    K  = Klqr(1:4);
    Ke = Klqr(5);
end