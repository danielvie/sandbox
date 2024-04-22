%% Testes AIR/OPENFRAME 22_05 e 26_05
close all;
clear all;

R2D = 180/pi;


%% PLOTAR AIR

load('AtuadorAIR')
load('SNGCAIR')
load('EventoAIR')

%Cálculo do pulso de tiro

% Tiro = find(EVENTOS(:,3)>0,100,'first');
Tiro = 5310;
aux= SUP(Tiro:end,2)/1e6;
Tempo = SUP(Tiro:end,1)+aux;
Tempoaux = Tempo-Tempo(1);

I = find(SUP(Tiro:end,11)==1);

At(1,1:8) = zeros(1,8);
size = length(SUP(2:end,11));

for i = 2:size
    
    for j=3:10
        
        if (SUP(i,11) ~= 1 || abs(SUP(i,j)) > 20) %% Pega somente dados validos no checksum e exclui valores maiores que 20 e mantém o valor anterior na variável
            
            At(i,j-2) = At(i-1,j-2);
                        
        else
            if (SUP(i,j) == 0 && SUP(i-1,j) ~=0) %% Se passo pelo checksum e pela outra condição exclui os pontos em que o atuador vai para zero
                
                At(i,j-2) = At(i-1,j-2);
%                 if j==2
%                     Tempo(i)  = ((SUP(i-1,j-1) + SUP(i-1,j)/1e6) - (SUP(i+1,j-1) + SUP(i+1,j)/1e6))/2;
%                 end
            else
                At(i,j-2) = SUP(i,j);
%                 if j==2
%                     Tempo(i)  = (SUP(i,j-1) + SUP(i,j)/1e6);
%                 end
            end
            
        end
    end
    
end


subplot(2,2,1)
plot(-At(:,1))
hold on;
plot(-At(:,5),'r')

subplot(2,2,2)
plot(-At(:,2))
hold on;
plot(-At(:,6),'r')

subplot(2,2,3)
plot(-At(:,3))
hold on;
plot(-At(:,7),'r')

subplot(2,2,4)
plot(-At(:,4))
hold on;
plot(-At(:,8),'r')

break

VarAtuador_aux = SUP(I,:);
Tempo_aux2 = Tempoaux(I);
I2 = find(abs(VarAtuador_aux(:,3))<20);
aux2 = VarAtuador_aux(I2,3);


VarAtuador = VarAtuador_aux(I2,:);
Tempo_At = Tempo_aux2(I2)-22.80;

%% Tratando o GNC
Tiro = 5310;
aux= SNGC(Tiro:end,2)/1e6;
Tempo = SNGC(Tiro:end,1)+aux;
Tempoaux = Tempo-Tempo(1);


I = find(SNGC(Tiro:end,10)>0);
VarSGNC = SNGC(I,:);
Tempo_GNC = Tempoaux(I)-22.80;

%% Figura referente ao teste no AIR
figure(1)
subplot(2,2,1)
plot(Tempo_At,-VarAtuador(:,3))
title('Empena 1')
subplot(2,2,2)
plot(Tempo_At,-VarAtuador(:,4))
title('Comando Empena 2')
subplot(2,2,3)
plot(Tempo_At,-VarAtuador(:,5))
title('Comando Empena 3')
subplot(2,2,4)
plot(Tempo_At,-VarAtuador(:,6))
title('Comando Empena 4')

figure(2)
subplot(2,2,1)
plot(Tempo_At,-VarAtuador(:,7))
title('Lido Empena 1')
subplot(2,2,2)
plot(Tempo_At,-VarAtuador(:,8))
title('Lido Empena 2')
subplot(2,2,3)
plot(Tempo_At,-VarAtuador(:,9))
title('Lido Empena 3')
subplot(2,2,4)
plot(Tempo_At,-VarAtuador(:,10))
title('Lido Empena 4')


figure(3)
subplot(2,2,1)
plot(Tempo_GNC,VarSGNC(:,3)*R2D)
title('Drol')
subplot(2,2,2)
plot(Tempo_GNC,VarSGNC(:,4)*R2D)
title('Dpitch')
subplot(2,2,3)
plot(Tempo_GNC,VarSGNC(:,5)*R2D)
title('Dyaw')
subplot(2,2,4)
plot(Tempo_GNC,VarSGNC(:,9))
title('Manete')

figure(4)
plot(Tempo_At,-VarAtuador(:,3),Tempo_At,-VarAtuador(:,7))
legend('Comando','Lido')




%% Plot OPENFRAME
load('Atuador')
load('SNGCOPENFRAME')
load('EventoOPENFRAME')

Tiro = find(EVENTOS1(:,3)>0,1,'first');

aux= SUP(Tiro:end,2)/1e6;
Tempo = SUP(Tiro:end,1)+aux;
Tempo = Tempo(:,end)-Tempo(1);

figure(1)
subplot(2,2,1)
hold on
plot(Tempo,-SUP(Tiro:end,3),'r');
subplot(2,2,2)
hold on
plot(Tempo,-SUP(Tiro:end,4),'r');
subplot(2,2,3)
hold on
plot(Tempo,-SUP(Tiro:end,5),'r');
subplot(2,2,4)
hold on
plot(Tempo,-SUP(Tiro:end,6),'r');
%

figure(2)
subplot(2,2,1)
hold on
plot(Tempo,-SUP(Tiro:end,7),'r');
subplot(2,2,2)
hold on
plot(Tempo,-SUP(Tiro:end,8),'r');
subplot(2,2,3)
hold on
plot(Tempo,-SUP(Tiro:end,9),'r');
subplot(2,2,4)
hold on
plot(Tempo,-SUP(Tiro:end,10),'r');
%

figure(4)
plot(Tempo,-SUP(Tiro:end,3),Tempo,-SUP(Tiro:end,7));
legend('Comando','Lido')

%
% xlabel('Tempo(s)')
% ylabel('Comando CDB (°)')
% legend('AtuadorAIR VOO1 - Telemetria','Atuador OPENFRAME');
% title('Sinal de Saida do CDB')

%% MANETE e COMANDOS

R2G = 180/3.1415;
figure(3)

subplot(2,2,1)
hold on;
plot(Tempo,SNGC(Tiro:end,3)*R2G,'r')
subplot(2,2,2)
hold on;
plot(Tempo,SNGC(Tiro:end,4)*R2G,'r')
subplot(2,2,3)
hold on;
plot(Tempo,SNGC(Tiro:end,5)*R2G,'r')
subplot(2,2,4)
hold on;
plot(Tempo,SNGC(Tiro:end,9),'r')

legend('AIR','OPENFRAME')


