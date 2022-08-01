function [Z,C] = sim(x, y, nsubs, sigx, sigy, C0, rot, seed)
    
    ntiros = size(C0, 1);

    % gerando vetor `rot`
    rot_ = zeros(ntiros, 1);
    rot_(1:numel(rot)) = rot(:);
    
    Z = zeros(numel(x), numel(y));
    C = zeros(nsubs*ntiros, 2);
    for i = 1:ntiros
        % montando Z0
        Z0 = subm.get_z0(x,y);
        
        % montando vetor de posicoes C
        ci = subm.get_coords_espalhamento(nsubs, sigx, sigy, C0(i,:), rot_(i), seed);
        
        % calculando impacto
        Z  = Z + subm.get_z_from_coords(x, y, nsubs, Z0, ci);
        
        % guardando posicoes usadas
        ini = (i-1)*nsubs + 1;
        fim = i*nsubs;
        
        C(ini:fim, :) = ci;
    end
    
    Z(Z>1) = 1;
   
end