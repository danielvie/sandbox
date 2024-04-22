function fn_animacao_carro(t, state, m, M, L, passo)
    if nargin == 5
        passo = 100;
    end

    figure(1);
    
    % dimensions
    W  = 1*sqrt(M/5);  % cart width
    H  = .5*sqrt(M/5); % cart height
    wr = .2;          % wheel radius
    mr = .3*sqrt(m);  % mass radius
    
    % chao
    plot([-10 10],[0 0],'k','LineWidth',2), hold on
    
    % gerando graficos e guardando referencia
    r1 = rectangle('Position',[0,0,0,0],'Curvature',.1,'FaceColor',[.5 0.5 1],'LineWidth',1.5); % Draw cart
    r2 = rectangle('Position',[0,0,0,0],'Curvature',1,'FaceColor',[0 0 0],'LineWidth',1.5); % Draw wheel
    r3 = rectangle('Position',[0,0,0,0],'Curvature',1,'FaceColor',[0 0 0],'LineWidth',1.5); % Draw wheel
    p1 = plot(0,0,'k','LineWidth',2); % Draw pendulum
    r4 = rectangle('Position',[0,0,0,0],'Curvature',1,'FaceColor',[1 0.1 .1],'LineWidth',1.5);
    
    hold off;
    h = gcf;
    h.Position(3:4) = [1000, 400];
    
    for k = 1:passo:length(t)
        x  = state(k,1);
        theta = state(k,3);

        % positions
        y     = wr/2 + H/2; % cart vertical position
        pendx = x + L*sin(theta);
        pendy = y - L*cos(theta);
        
        r1.Position = [x-W/2,y-H/2,W,H];
        r2.Position = [x-.9*W/2,0,wr,wr];
        r3.Position = [x+.9*W/2-wr,0,wr,wr];
        r4.Position = [pendx-mr/2,pendy-mr/2,mr,mr];
        p1.XData = [x pendx];
        p1.YData = [y pendy];

        axis([-5 5 -2.5 3.0]);
        axis equal
        
        pause(0.1);
        drawnow
        

    end
end