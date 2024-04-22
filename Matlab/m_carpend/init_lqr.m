% definindo modelo
G = get_modelo_carpend();

Q = diag([10,.1,.1,.1]);
R = 0.1;

K = lqr(G.A, -G.B, Q, R);

sim('untitled1');