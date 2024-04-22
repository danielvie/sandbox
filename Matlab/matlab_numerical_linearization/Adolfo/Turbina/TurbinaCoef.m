%% Programa para calcular a derivada parcial do dEmpuxo/dRotação
%Data 15/05/2015
%Kc = - Constante de conversão de lbf p/ N
%Fe = Constante para degradar o empuxo;
%e1->18000 - 19000 e2-> 19000 - 20000 e3-> 20000-21000 e4-> 18000 - 21000
clear all
fE = 0.8;

%P/ V = 230m/s e H = 1000m
RPM(1) = 1800; %18000
RPM(2) = 2250; %19000
RPM(3) = 2850; %20000
RPM(4) = 3500; %21000
E(1,1) = RPM(2)-RPM(1); E(2,1) = RPM(3)-RPM(2); E(3,1) = RPM(4)-RPM(3); E(4,1) = RPM(4)-RPM(1);
% e1(1,1) = RPM(2)-RPM(1); e2(1,1) = RPM(3)-RPM(2); e3(1,1) = RPM(4)-RPM(3); e4(1,1) = RPM(4)-RPM(1);

%P/ V = 230m/s e H = 2000m
RPM(1) = 1720; %18000
RPM(2) = 2150; %19000
RPM(3) = 2630; %20000
RPM(4) = 3400; %21000
E(1,2) = RPM(2)-RPM(1); E(2,2) = RPM(3)-RPM(2); E(3,2) = RPM(4)-RPM(3); E(4,2) = RPM(4)-RPM(1);
% e1(2,1) = RPM(2)-RPM(1); e2(2,1) = RPM(3)-RPM(2); e3(2,1) = RPM(4)-RPM(3); e4(2,1) = RPM(4)-RPM(1);

%P/ V = 250m/s e H = 1000m
RPM(1) = 1900; %18000
RPM(2) = 2300; %19000
RPM(3) = 2900; %20000
RPM(4) = 3600; %21000
E(1,3) = RPM(2)-RPM(1); E(2,3) = RPM(3)-RPM(2); E(3,3) = RPM(4)-RPM(3); E(4,3) = RPM(4)-RPM(1);
% e1(1,2) = RPM(2)-RPM(1); e2(1,2) = RPM(3)-RPM(2); e3(1,2) = RPM(4)-RPM(3); e4(1,2) = RPM(4)-RPM(1);

%P/ V = 250m/s e H = 2000m
RPM(1) = 1750; %18000
RPM(2) = 2150; %19000
RPM(3) = 2650; %20000
RPM(4) = 3400; %21000
E(1,4) = RPM(2)-RPM(1); E(2,4) = RPM(3)-RPM(2); E(3,4) = RPM(4)-RPM(3); E(4,4) = RPM(4)-RPM(1);
% e1(2,2) = RPM(2)-RPM(1); e2(2,2) = RPM(3)-RPM(2); e3(2,2) = RPM(4)-RPM(3); e4(2,2) = RPM(4)-RPM(1);


dRPM = 1000;
m = 850;

for i = 1:4
    if i ~=4
        Kt(i,:) = E(i,:)/dRPM*fE;
    else
        Kt(i,:) = E(i,:)/(3*dRPM)*fE;
    end
end

KtS = Kt/m;
