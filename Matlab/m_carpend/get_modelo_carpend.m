function G = get_modelo_carpend()

    m = 1.0;
    M = 5.0;
    L = 2.0;
    g = -10.0;
    d = 1.0;

    s = 1; % Pendulum up (s=1)

    A = [0          1                0 0;
         0       -d/M           -m*g/M 0;
         0          0                0 1;
         0 -s*d/(M*L) -s*(m+M)*g/(M*L) 0];

    B = [0; 1/M; 0; s*1/(M*L)];

    C = eye(4);

    D = zeros(size(C,1), size(B,2));
    
    G = ss(A,B,C,D);
end