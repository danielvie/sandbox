%% Programa para realizar a redução de dados da Turbina
%Data ultima atualização 08/05/2015
%Feito por Adolfo
close all

n = 35000;
Tamanho = length(TurbinaEnsaio(2:n,2));
Media = mean(TurbinaEnsaio(2:n,2));

Ta = diff(TurbinaEnsaio(2:3));
Tempo = 0:Ta:(Tamanho-1)*Ta;
Ts = timeseries(TurbinaEnsaio(2:n,2)-Media,Tempo);

ti = find(TurbinaEnsaio(:,1)>0,1,'first');

aux = idealfilter(Ts,[0.001 1],'pass');

figure(1)
plot(TurbinaEnsaio(ti:n,1),TurbinaEnsaio(ti:n,2),TurbinaEnsaio(ti:n,1),TurbinaEnsaio(ti:n,4));
xlabel('Tempo(s)')
ylabel('RPM')
legend('Lido','Comandado')
figure(2)
plot(Tempo,aux.Data+Media,'LineWidth',2)
hold on
% plot(Tempo,TurbinaEnsaio(2:n,2),'r');
xlabel('Tempo(s)')
ylabel('RPM')
legend('Lido Filtrado','Lido')
plot(Tempo,TurbinaEnsaio(2:n,4))
axis([230 370 17800 19100]);

%Plot das linhas para avaliar o tempo de resposta
aux = 18500 + 200*0.632;
plot([230 380],[aux aux],'r')
aux = 18700 - 200*0.632;
plot([230 380],[aux aux],'r')
aux = 18700 + 100*0.632;
plot([230 380],[aux aux],'r')
aux = 18800 - 100*0.632;
plot([230 380],[aux aux],'r')



break;

figure(3)
hold on
Maxi = max(TurbinaEnsaio(2:n,4));
plot(Tempo(1:end-1),diff(aux.Data+Media)/Ta,'r',Tempo,TurbinaEnsaio(2:n,4)/Maxi*100);
axis([0 800 -300 300]);

figure(4)
plot(Tempo,TurbinaEnsaio(2:n,4),Tempo,aux.Data+Media)

figure(6)
N = 100;
b = downsample(aux.Time,N);

plot(b(1:end-1),diff(downsample(aux.Data+Media,N))/(Ta*N),Tempo,TurbinaEnsaio(2:60288,4)/Maxi*100)
axis([0 800 -300 300]);