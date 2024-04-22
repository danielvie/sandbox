function plotTemporal(Gf,Malha)
% Alt = 0:1000:4000;
Vel = [160 180 200 220 240 250 260];

RiseTime = zeros(5,7);
OverShoot = RiseTime;
SettlingTime = RiseTime;



for k =1:5
    for j =1:7
        if Malha == 1
            G(k,j) = stepinfo(Gf.Roll(k,j).RollComplete);
        end
        if Malha == 2
            G(k,j) = stepinfo(Gf.Pitch(k,j).PitchSimple);
        end
        
        RiseTime(k,j) = G(k,j).RiseTime;
        OverShoot(k,j) = G(k,j).Overshoot;
        SettlingTime(k,j) = G(k,j).SettlingTime;
        
    end
end

figure()
title('Tempo de Subida')
plot(Vel,RiseTime','LineWidth',2);
xlabel('V(m/s');
ylabel('Tempo de subida(s)');
legend('0','1000','2000','3000','4000')

figure()
title('Overshoot')
plot(Vel,OverShoot','LineWidth',2);
legend('0','1000','2000','3000','4000')
ylabel('Máximo pico(%)')
xlabel('V(m/s');

figure()
title('Tempo de assentamento','LineWidth',2)
plot(Vel,SettlingTime');
legend('0','1000','2000','3000','4000')
ylabel('Tempo de assentamento(s)')
xlabel('V(m/s');

end
