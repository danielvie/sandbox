function u = fn_controle(t,x,K,wr)
    
    if t > 4.0        
        wr(1) = -2.0;
    end
    
    if t > 8.0
        wr(1) = 4.0;
    end
    
    u  = -K*(x - wr);
    