function main()
    
    g1 = get_tfunc(10);
    g2 = get_tfunc(600);
    
%     plt_ny(g1,1);
    
%     plt_ny(g2,2);
    
    plt_step(g1*48.000001, 3);
%     plt_gain(g1, 4);
%     plt_rlocus(g1, 5);
end

function G = get_tfunc(k)
    s = tf('s');
    G = k/(s+2)/(s+4)/(s+6);
end

function plt_gain(G,fnum)
    if nargin == 1
        fnum = 1;
    end
    
    figure(fnum);
    margin(G);
end

function plt_ny(G,fnum)
    if nargin == 1
        fnum = 1;
    end
    
    figure(fnum);
    nyquist(G, linspace(0,100,1000));
end

function plt_rlocus(G,fnum)
    if nargin == 1
        fnum = 1;
    end
    
    figure(fnum);
    rlocus(G, linspace(0,100,1000));
end

function plt_step(G,fnum)
    if nargin == 1
        fnum = 1;
    end
    
    figure(fnum);
    step(feedback(G, 1));
end