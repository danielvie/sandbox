%Plots Auxiliares

load('LogTrim');

X = Log.Xtrim;
U_Trim = Log.Utrim;
Turb = Log.Turb;

R2G = 180/pi;
[n1, n2] = size(X);
TituloXtrim = {'Variação do ângulo de Ataque','Variação do ângulo Beta'};
TituloUtrim = {'Manete','dPitch','dYaw','dRoll'};
Ylegenda = {'Vt','AoA(°)','Beta(°)'};
Ulegenda ={'Manete(%)','dPitch(°)','dYaw(°)','dRoll(°)'};
Linha = {'b','r','g','k','m','c','b-*','r-*','g-*','k-*','m-*','c-*'};


Alt = X(:,1,12);
Vt = X(1,:,1);
J_final = size(Alt); %Para congelar Alt
figure()


for j = 1:J_final
    hold on
%     plot(Vt,Turb(j,:),Linha{j});
    plot(Vt,Turb(j,:));
%     L = ['Alt =',num2str(X(j,1,12))];
%     Lee(j) = {L};
end
% legend(Lee,'Location','NorthWest')
title('Empuxo vs Velocidade')
xlabel('Velocidade(m/s)')
ylabel('Empuxo(N)')