clear all
close all

BV8 = load('BV9_30_03/GanhosTanqueHalf');
BV9 = load('BV9_30_03/GanhosTanqueHalf_5');

VB9 = [160 180 200 220 240 250 260];
VB8 = VB9;
Alt = [0 1000 2000 3000 4000];


figure(1)
mesh(Alt,VB8,BV8.Kp.pitch(:,:)')
hold on
mesh(Alt,VB9,BV9.Kp.pitch(:,:)')
title('Kp pitch')
legend('Nominal','BV9')

figure(2)
mesh(Alt,VB8,BV8.Kd.pitch(:,:)')
hold on
mesh(Alt,VB9,BV9.Kd.pitch(:,:)')
title('Kd pitch')
legend('Nominal','BV9')

figure(3)
mesh(Alt,VB8,BV8.Kp.roll(:,:)')
hold on
mesh(Alt,VB9,BV9.Kp.roll(:,:)')
title('Kp roll')

legend('Nominal','BV9')

figure(4)
mesh(Alt,VB8,BV8.Kd.roll(:,:)')
hold on
mesh(Alt,VB9,BV9.Kd.roll(:,:)')
title('Kd roll')
legend('Nominal','BV9')

figure(5)
mesh(Alt,VB8,BV8.Kd.yaw(:,:)')
hold on
mesh(Alt,VB9,BV9.Kd.yaw(:,:)')
title('Kp yaw')
legend('Nominal','BV9')