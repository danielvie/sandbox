function [xp, yp] = get_projection_from_H(x, y, H)
    
    aux = [x, y, ones(numel(x), 1)]*H;
    
    xp  = aux(:,1)./aux(:,3);
    yp  = aux(:,2)./aux(:,3);
end