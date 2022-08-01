function Z = movez(x, y, Z0, ci)
    % Z0: grid de probabilidade padrao em [0, 0]
    % ci: linha de coordenadas [x, y] para movimento
    % x : vetor `x` de indices
    % y : vetor `y` de indices
    

    % movendo probabilidade no mapa
    dx = x(2) - x(1);
    dy = y(2) - y(1);
    ix = round(ci(1)/dx);
    iy = round(ci(2)/dy);

    Z  = circshift(Z0, [iy, ix]);
    
    % removendo parte que passa da fronteira
%     if ix > 0
%         Z(:,1:ix) = 0;
%     else
%         Z(:,end+ix:end) = 0;
%     end
%     
%     if iy > 0
%         Z(1:iy,:) = 0;
%     else
%         Z(end+iy:end,:) = 0;
%     end