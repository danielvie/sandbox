function [x,y] = get_line_from_v1v2(v1, v2, ang_deg, dist)
    
    if ~exist('dist', 'var')
        dist = norm(v2 - v1);
    end

    ang_deg = subm.dms2deg(ang_deg);
    
    % calculando `v0`
    v0      = v2 - v1;
    v0      = v0/norm(v0)*dist;
    
    ang_rad = ang_deg*pi/180.;
    
    v       = v0*subm.rotx(ang_rad) + v1;
    
    % montando vetores `x` e `y`
    x = [v1(1), v(1)];
    y = [v1(2), v(2)];
    
end