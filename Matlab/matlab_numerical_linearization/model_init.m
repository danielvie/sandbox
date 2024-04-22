

s = tf('s');

G = 1/(s*s+3*s+1.5);

[num, den] = tfdata(G,'v');
[A,B,C,D] = tf2ss(num,den);
Gss = ss(A,B,C,D);


step(feedback(G, 1));