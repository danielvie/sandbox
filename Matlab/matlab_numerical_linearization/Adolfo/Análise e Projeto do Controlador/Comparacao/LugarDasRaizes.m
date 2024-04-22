%% Programa p/ plotar o lugar das raízes dada uma variação nos coeficientes aerodinâmicos
%[Vt alpha beta phi theta psi p q r North East Altura]
close all
clear all
clc

legenda = {'BV9 - 30/03'};

clear A;
A = load('../DadosInput_Output/DadosTrim/BV9_30_03/ModeloLinear-Half.mat');
PlanoLong = A.Plano_Long;
PlanoLat = A.Plano_Lat;
Coef = A.Coef;
clear A;

disp('Entre com a altitude e velocidade desejada')
[n,d] = size(PlanoLong(1,:));
for i =1:d
    Vstr = num2str(round(PlanoLong(1,i).A(5,4)));
    disp([Vstr '  ' num2str(i)])
end
Vel = input('Opção -- ');
R2D = 180/pi;

fprintf('\t\t\t\t\t\tPrograma p/ comparar dois bancos de dados -- Modelo Linear\n')
disp('[0 1000 2000 3000 4000] = [1 2 3 4 5]')
Alt = input('Opção -- ');






%% Plano Longitudinal (i,j) = (alt, vel)
%Carregando os dados referentes ao plano longitudinal

for i =1:5
    
    for j=1:7
        
        Malpha(i,j) = Coef(i,j).Ya(1); %Momento em q dado um alpha
        Mq(i,j)     = Coef(i,j).Ya(2); %Momento de amortecimento em q dado uma taxa em q
        Zalpha(i,j) = Coef(i,j).Ya(3); %Força em z dado um alpha
        Zq(i,j)     = Coef(i,j).Ya(4);
        Lbeta(i,j)  = Coef(i,j).Ya(5); %Momento em x dado um beta
        Nbeta(i,j)  = Coef(i,j).Ya(6); %Momento em z dado um beta
        Ybeta(i,j)  = Coef(i,j).Ya(7); %Força em y dado um beta
        Nr(i,j)     = Coef(i,j).Ya(8); %Momento de amortecimento em z dado um r 
        Mdelta(i,j) = Coef(i,j).Yb(1); %Momento em y dada uma deflexão de empena
        Zdelta(i,j) = Coef(i,j).Yb(2); %Força em z dada uma deflexão de empena
        Vt(j) = PlanoLong(i,j).A(5,4);
    end
    
end

%Variando o coeficiente aerodinâmico associado ao Malpha ou Mdelta
figure(1)
hold on;
figure(2)
hold on;
for i=1:11
    
    Amd = PlanoLong(Alt,Vel).A(1:4,1:4);     
    Bmd = PlanoLong(Alt,Vel).B(1:4,:); 
    Amd(3,2) = Amd(3,2)*(0.5 + (i-1)*0.1);     %Malpha
%     Bmd(3,2) = Bmd(3,2)*(0.5 + (i-1)*0.1);   %Mdelta
%     Amd(3,3) = Amd(3,3)*(0.5 + (i-1)*0.1);   %Malpha
    Long = ss(Amd,Bmd,eye(4),zeros(4,2));
  
    Mdelta1 = Mdelta(Alt,Vel);
    Zdelta1 = Zdelta(Alt,Vel);
    Malpha1 = Malpha(Alt,Vel)*(0.5 + (i-1)*0.1);
    Zalpha1 = Zalpha(Alt,Vel);  
    Mq1 = Mq(Alt,Vel);
    
    %Modelo Analitico Simplificado
    q = tf([Mdelta1 (Malpha1*Zdelta1-Zalpha1*Mdelta1)/Vt(Vel)],...
        [1 -(Zalpha1/Vt(Vel)+Mq1) Mq1*Zalpha1/Vt(Vel) - Malpha1]); 
    figure(1)
    pzmap(Long);    
    figure(2)
    pzmap(q);
end
break;

figure(2)
hold on
for i=1:11
    Amd = PlanoLong(Alt,Vel).A(1:4,1:4);
    Amd(3,3) = Amd(3,3)*(0.5 + (i-1)*0.1);
    Long = ss(Amd,PlanoLong(Alt,Vel).B(1:4,:),eye(4),zeros(4,2));
    pzmap(Long);
end

break
Long = ss(PlanoLong(Alt,Vel).A(1:4,1:4),PlanoLong(Alt,Vel).B(1:4,:),eye(4),zeros(4,2));


figure()
pzplot(Long1,Long2)
legend(legenda)

Dpitch1 = ss(PlanoLong1(Alt,Vel).A(1:4,1:4),PlanoLong1(Alt,Vel).B(1:4,2),[0 0 1 0],0);
Dpitch2 = ss(PlanoLong2(Alt,Vel).A(1:4,1:4),PlanoLong2(Alt,Vel).B(1:4,2),[0 0 1 0],0);

figure()
step(Dpitch1,Dpitch2,0:0.01:10)
legend(legenda)
%% Plano Lateral (i,j) = (alt, vel)

Lat1 = ss(PlanoLat1(Alt,Vel).A(1:4,1:4),PlanoLat1(Alt,Vel).B(1:4,:),eye(4),zeros(4,2));
Lat2 = ss(PlanoLat2(Alt,Vel).A(1:4,1:4),PlanoLat2(Alt,Vel).B(1:4,:),eye(4),zeros(4,2));

figure()
pzmap(Lat1,Lat2)
legend(legenda)


%% Calcular a comparação das FTs - Longitudinal - Polos e Zeros
color = {'b','r','g','k','c','m','y'};
for Alt=1:4
    figure(10)
    hold all
    for Vel=1:7
        Long2 = ss(PlanoLong2(Alt,Vel).A(1:4,1:4),PlanoLong2(Alt,Vel).B(1:4,:),eye(4),zeros(4,2));
        pzmap(Long2,color{Vel})
    end
    aux=1;
    legend('160','180','200','220','240','250','260')
%     pause()
end


%% Calcular a comparação das FTs - Lateral - Polos e Zeros
for Alt=1:4    
    figure(11)
    hold all
    for Vel=1:7        
        Lat2 = ss(PlanoLat2(Alt,Vel).A(1:4,1:4),PlanoLat2(Alt,Vel).B(1:4,:),eye(4),zeros(4,2));
        pzmap(Lat2,color{Vel})        
    end
%     pause()
    aux=1;    
end

%% Plot dos coeficientes dinâmicos
Alt = [0 1000 2000 3000 4000];
Vel = [160 180 200 220 240 250 260];
Malpha = zeros(5,7);
for i =1:5
    
    for j=1:7
        
        Malpha(i,j) = Coef(i,j).Ya(1); %Momento em q dado um alpha
        Mq(i,j)     = Coef(i,j).Ya(2); %Momento de amortecimento em q dado uma taxa em q
        Zalpha(i,j) = Coef(i,j).Ya(3); %Força em z dado um alpha
        Zq(i,j)     = Coef(i,j).Ya(4);
        Lbeta(i,j)  = Coef(i,j).Ya(5); %Momento em x dado um beta
        Nbeta(i,j)  = Coef(i,j).Ya(6); %Momento em z dado um beta
        Ybeta(i,j)  = Coef(i,j).Ya(7); %Força em y dado um beta
        Nr(i,j)     = Coef(i,j).Ya(8); %Momemnto de amortecimento em z dado um r
        
    end
    
end

plot(Alt,Malpha(:,5));
mesh(Vel,Alt,Malpha);