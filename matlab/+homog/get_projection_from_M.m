function [xp, yp] = get_projection_from_M(x, y, M0, M)
%
%     projection M0 -> M
%
%     M0 = [0,0; 0,1; 1,1; 1,0;];
% 
%     M  = [0,0; 0,1; 10,1; 1,0];
% 

    x        = reshape(x, [numel(x), 1]);
    y        = reshape(y, [numel(y), 1]);

    H        = homog.get_homography(M0, M);
    [xp, yp] = homog.get_projection_from_H(x, y, H);
end
