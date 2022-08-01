function Z = get_z_from_coords(x, y, nsubs, Z0, C)
    % incorporando varias submunicoes
    nx = numel(x);
    ny = numel(y);

    Z = zeros(nx,ny);
    for i = 1:nsubs
        Z = Z + subm.movez(x,y,Z0,C(i,:));
    end
    Z(Z>1) = 1;
end