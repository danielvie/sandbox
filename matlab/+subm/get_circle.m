function [x,y] = get_circle(raio, c0, N)

    if ~exist('c0', 'var')
        c0 = [0, 0];
    end
    
    if ~exist('N', 'var')
        N = 100;
    end

    ang = linspace(0,2*pi,N);
    x = raio*cos(ang) + c0(1);
    y = raio*sin(ang) + c0(2);
    
end