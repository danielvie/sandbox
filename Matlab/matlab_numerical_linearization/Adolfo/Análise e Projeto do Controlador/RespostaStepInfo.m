%Programa para calcular os requisitos da resposta temporal
% close all
clear all

i = 0;
Full  = ['ssTanqueFull_' num2str(i)];
Half  = ['ssTanqueHalf_' num2str(i)];
Empty = ['ssTanqueZero_' num2str(i)];

load(Half);

plotTemporal(Gf,1);

