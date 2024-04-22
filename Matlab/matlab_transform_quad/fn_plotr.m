function fn_plotr(rx, ry)
%FN_PLOTR Summary of this function goes here
%   Detailed explanation goes here
    
    hold on;
    plot(rx, ry); 
    plot(rx(1:4), ry(1:4), 'o')
    hold off;
    axis equal;
end

