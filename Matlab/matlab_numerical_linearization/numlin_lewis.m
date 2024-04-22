clear all;

name  = input('Enter Name of State Eqns. File: ', 's');
tfile = input('Enter Name of Trim File: ', 's');

tmp   = dlmread(tfile, ',');
n     = tmp(1);
m     = tmp(2);
x     = tmp(3:n+2);
u     = tmp(n+3:m+n+2);
tol   = 1e-6;
time  = 0.;

mm    = input('Number of control inputs to be used? : ');
dx    = 0.1*x;

for i = 1:n
    if dx(i) == 0.0
        dx(i) = 0.1;
    end
end

last  = zeros(n,1);
a     = zeros(n,n);

for j = 1:n
    xt = xt
    for i = 1:10
        
        % derivative 1
        xt(j) = x(j) + dx(j);
        xd1 = feval(name, time, xt, u);
        
        % derivative 2
        xt(j) = x(j) - dx(j);
        xd2 = feval(name, time, xt, u);

        % escrevendo coluna Aj
        a(:,j) = (xd1 - xd2)'/(2*dx(j));
        
        % condicao de saida
        if max(abs(a(:,j) - last)./abs(a(:,j) + 1e-12)) < tol
            break;
        end
        
        % se nao sair, reduzir o passo pela metade
        dx(j) = 0.5*dx(j);
        
        % ultima linha
        last  = a(:,j);
    end
    
    % column = j
    iteration = i;
    if iteration == 10
        disp('not converged on A, columns', num2str(j));
    end
end
disp(A);