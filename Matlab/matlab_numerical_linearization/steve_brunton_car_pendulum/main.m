clear all
close all
clc

m = 1.0;
M = 5.0;
L = 2.0;
g = -10.0;
d = 1.0;

tspan = 0:.1:30;
y0 = [0;0;pi;.5];

[t,y] = ode45(@(t,y)cartpend(y,m,M,L,g,d,0), tspan, y0);

px = -1;
py = -1;
h  = 0;
figure(1);
for k = 1:length(t)
    drawpend(y(k,:), m, M, L);
    
    if px == -1
        h  = gcf();
        px = h.Position(1);
        py = h.Position(2);        
    end
    
    set(h,'Position',[px, py, 1000, 400]);
end
figure(2);
plot(t,y);
grid on;