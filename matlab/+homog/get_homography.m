function H = get_homography(M0, M)
    % This function will find the homography betweeb 4 points using svd

    x1  = M0(1,1);
    y1  = M0(1,2);
    x2  = M0(2,1);
    y2  = M0(2,2);
    x3  = M0(3,1);
    y3  = M0(3,2);
    x4  = M0(4,1);
    y4  = M0(4,2);

    xp1 = M(1,1);
    yp1 = M(1,2);
    xp2 = M(2,1);
    yp2 = M(2,2);
    xp3 = M(3,1);
    yp3 = M(3,2);
    xp4 = M(4,1);
    yp4 = M(4,2);

    A = [
        -x1  -y1  -1   0    0    0   x1*xp1   y1*xp1   xp1;
         0    0    0 -x1   -y1  -1   x1*yp1   y1*yp1   yp1;
        -x2  -y2  -1   0    0    0   x2*xp2   y2*xp2   xp2;
         0    0    0 -x2   -y2  -1   x2*yp2   y2*yp2   yp2;
        -x3  -y3  -1   0    0    0   x3*xp3   y3*xp3   xp3;
         0    0    0 -x3   -y3  -1   x3*yp3   y3*yp3   yp3;
        -x4  -y4   -1  0    0    0   x4*xp4   y4*xp4   xp4;
         0    0    0  -x4  -y4  -1   x4*yp4   y4*yp4   yp4
     ];

    [~,~,V] = svd(A);

    H=V(:,end);
    H=reshape(H,3,3);
end