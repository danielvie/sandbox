%PlotarGraficos da Inercia/Massa
close all;
color = ['b','r','k'];
for i=1:4
    for j=1:5
        [J, Rcm(:,i,j), Massa(i,j)] = Prop_Massa(j,i);
        Jxx(i,j) = J(1,1);
        Jyy(i,j) = J(2,2);
        Jzz(i,j) = J(3,3);
        
    end
    figure(1)
    hold on;
    plot(Massa(i,:),color(i))    
    figure(2)
    plot(Jxx(i,:),color(i))
    hold on;
    figure(3)
    plot(Jyy(i,:),color(i))
    hold on;
    figure(4)
    plot(Jzz(i,:),color(i))
    hold on;    
    figure(5)
    plot(squeeze(Rcm(1,i,:)),color(i))
    hold on;    
    
    
end

figure(1)
legend('Baseline 8', 'Baseline 9 - 02/03/2015', 'Baseline 9 - 26/03/2015')
title('Massa')
ylabel('Massa(kg))')
grid on

figure(2)
legend('Baseline 8', 'Baseline 9 - 02/03/2015', 'Baseline 9 - 26/03/2015')
title('Jxx')
ylabel('kgm^2')
grid on

figure(3)
legend('Baseline 8', 'Baseline 9 - 02/03/2015', 'Baseline 9 - 26/03/2015')
title('Jyy')
ylabel('kgm^2')
grid on

figure(4)
legend('Baseline 8', 'Baseline 9 - 02/03/2015', 'Baseline 9 - 26/03/2015')
title('Jzz')
ylabel('kg m^2')
grid on

figure(5)
legend('Baseline 8', 'Baseline 9 - 02/03/2015', 'Baseline 9 - 26/03/2015')
title('Centro de Massa')
ylabel('xcg(m)')
grid on