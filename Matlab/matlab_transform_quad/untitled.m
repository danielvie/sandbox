
% a


s = tf('s');

K    = 10;
G10  = K/(s+2)/(s+4)/(s+6);
K    = 100;
G100 = K/(s+2)/(s+4)/(s+6);

figure(1)
clf()
% nyquist(G10);
% hold on;
rlocus(G100);
hold off;

figure(2)
clf()
step(feedback(G10, 1))
hold on
step(feedback(G100*4.85, 1))
hold off