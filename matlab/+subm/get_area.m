function A = get_area(x, y, Z)

    % calculando area numerica
    dx = x(2) - x(1);
    dy = y(2) - y(1);
    a  = dx*dy;
    A  = sum(sum(Z > 0))*a;
end