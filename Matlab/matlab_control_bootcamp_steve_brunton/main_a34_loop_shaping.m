clear all
% close all
clc

sysCar = ss(-1,1,1,0);
% [num, den] = ss2tf(sysCar.a, sysCar.b, sysCar.c, sysCar.d);
% tfCar = tf(num, den);

s = tf('s');
tfCar = 1/(s+0.5);

DesiredLoop = 10/s;
K = DesiredLoop/tfCar;

sysLoop = series(K, sysCar);
sysCL = feedback(sysLoop, 1, -1);

% step(sysCL);
% hold on
% step(sysCar);
% hold off;
% legend('CL', 'OL');

f = 10/(3*s*s + 5*s + 1);
clf();
nyquist(f)
hold on