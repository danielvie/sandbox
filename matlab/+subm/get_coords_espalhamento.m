function C = get_coords_espalhamento(nsubs, sigmax, sigmay, C0, rot, seed)
    
    if ~exist('seed', 'var')
        seed = -1;
    end
    
    if seed == -1
        seed = randi(1000000);
        fprintf('seed: %d\n', seed);
    end

    % montando vetor de posicoes C
    rng(seed);
    C = [randn(nsubs,1)*sigmax, randn(nsubs,1)*sigmay];

    % rotacionando C
    ang = rot*pi/180.;
    C   = C * [cos(ang), -sin(ang);sin(ang), cos(ang)];

    % deslocando coordenadas para o centro de tiro
    C   = C + C0;
end