function imp = get_impacto_from_po(ang1d, ang2d, po1, po2)
    
    % ajuste de parametros
    if ~exist('po1', 'var')
        po1 = [262672., 8250238.]; % PO1 - formosa
    end
    
    if ~exist('po2', 'var')
        po2 = [266354., 8248861.]; % PO4 - formosa
    end

    % convertendo para escalar
    ang1d = subm.dms2deg(ang1d);
    ang2d = subm.dms2deg(ang2d);
    
    % convertendo para rad
    ang1r = ang1d*pi/180;
    ang2r = ang2d*pi/180;

    % montando vetores visada
    v1o1 = po2 - po1;
    v2o2 = po1 - po2;

    % rotacionando leitura dos POs para alvo `x`
    v1x  = v1o1*subm.rotx(ang1r);
    v2x  = v2o2*subm.rotx(ang2r);

    % calculando inclinacao das retas
    m1   = v1x(2)/v1x(1);
    m2   = v2x(2)/v2x(1);

    if abs(m1 - m2) < 0.00001
        error('ERRO: valores invalidos!');
    end

    % calculando impacto por cruzamento de retas
    x1 = po1(1);
    y1 = po1(2);
    x2 = po2(1);
    y2 = po2(2);

    xi = (y2 - y1 + x1*m1 - x2*m2)/(m1-m2);
    yi = y1 + m1*(xi - x1);

    imp = [xi, yi];
end