function deg = dms2deg(dms)
    
    if isscalar(dms)
        dms = [dms, 0, 0];
    end

    deg = dms(1) + dms(2)/60 + dms(3)/3600;

end