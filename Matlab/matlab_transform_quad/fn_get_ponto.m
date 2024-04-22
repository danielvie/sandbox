function p_ = fn_get_ponto(H, p)

    X   = [reshape(p, [2,1]);1];

    aux = H*X;
    aux = aux/aux(3);

    p_  = aux(1:2);
end