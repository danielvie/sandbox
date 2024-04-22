function dy = fn_eq_diferencial(x,m,M,L,g,d,u)
        
    Sy = sin(x(3));
    Cy = cos(x(3));
    D  = m*L*L*(M + m*(1-Cy^2));
    
    dy  = zeros(4,1);
    
    dy(1) = x(2);
    dy(2) = (1/D)*(-m^2*L^2*g*Cy*Sy + m*L^2*(m*L*x(4)^2*Sy - d*x(2))) + m*L*L*(1/D)*u;
    dy(3) = x(4);
    dy(4) = (1/D)*((m+M)*m*g*L*Sy - m*L*Cy*(m*L*x(4)^2*Sy - d*x(2))) - m*L*Cy*(1/D)*u;

end