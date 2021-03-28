function Z0 = get_z0(x, y)

    % criando grid `Z0`
    [X,Y]   = meshgrid(x,y);
    Z0       = sqrt(X.^2 + Y.^2);

    % ajustando curva para distancia e normalizando probabilidade
    dist        = 50;
    Z0(Z0>dist) = dist;
    Z0          = dist - Z0;
    Z0          = Z0/dist;
end