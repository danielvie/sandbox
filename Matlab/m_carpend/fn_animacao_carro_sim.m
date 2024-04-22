function fn_animacao_carro_sim(out)
    if nargin == 0
        out = evalin('base', 'out');
    end
    
    x_ = out.logsout.get('y').Values;
    
    t = x_.Time;
    x = x_.Data;

    passo = 200;
    m = 1.0;
    M = 5.0;
    L = 2.0;

    fn_animacao_carro(t, x, m, M, L, passo);
end