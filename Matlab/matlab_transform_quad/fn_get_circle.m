function [cx, cy] = fn_get_circle(raio, C)

    % criando valor padrao para 'C'
    if nargin == 1
        C = [0, 0];
    end

    % montando vetor de angulos em radianos
    ang = linspace(0,2*pi, 1000);
    
    % gerando curvas
    cx  = raio*cos(ang);
    cy  = raio*sin(ang);
    
    % deslocando coordenadas
    cx  = cx + C(1);
    cy  = cy + C(2);
    
end