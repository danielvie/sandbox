%% Programa para plotar as margens de estabilidade

function PlotMargens(Gm,Pm,wpm,wcg,Altitude,Velocidade)
%wcg frequência de cruzamento de ganho
figure()
hold all

for i=1:length(Velocidade)
    plot(Altitude,20*log10(Gm(:,i)));
    xlabel('Altitude')
    ylabel('Margem de Ganho (dB)')
    title('Margem de ganho')
    Vstr(i,:) = num2str(Velocidade(i));
end
legend(Vstr)
hold off

figure()
hold all
for i=1:length(Velocidade)
    plot(Altitude,Pm(:,i));
    xlabel('Altitude')
    ylabel('Margem de Fase (°)')
    title('Margem de fase')
end
legend(Vstr)
hold off

figure()
hold all
for i=1:length(Velocidade)
    plot(Altitude,(pi/180)*Pm(:,i)./wcg(:,i)*1000);
    xlabel('Altitude')
    ylabel('Delay (ms)')
    title('Atraso de tempo para instabilizar a malha')   
end
legend(Vstr)
hold off

end