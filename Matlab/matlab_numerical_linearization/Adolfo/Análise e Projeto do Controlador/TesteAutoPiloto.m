%% Teste de um autopiloto
% %Função completa
% 
% [n ,d] = ss2tf(DinLat.Completa.A,DinLat.Completa.B,[0 0 1 0],[0 0],2);
% G_p = tf(n,d);
% 
% Kproll = 0.0242;
% Kdroll = 0.0022;
% Kdyaw = 0.15;
% 
% Kheading = 10;
% K = [0 Kproll Kdroll 0];
% 
% B_roll = DinLat.Completa.B(:,2);
% 
% [n, d] = ss2tf(DinLat.Completa.A-DinLat.Completa.B(:,2)*K,DinLat.Completa.B(:,2)*Kproll,[0 1 0 0],0);
% Gfr3 = tf(n,d);
% 
% Gfr2 = feedback(G_p,Kdroll);
% Gfr2 = feedback(Kproll*tf(1,[1 0])*Gfr2,1);
% 
% figure(5)
% step(Gfr2,Gfr3,10)
% % %% Controlador guinada
% [n ,d] = ss2tf(DinLat.Completa.A,DinLat.Completa.B,[0 0 0 1],[0 0],1);
% G_p = tf(n,d);
%  
% WO = tf([1 0],[1 1]);
%  
% Gfr = feedback(G_p,Kdyaw*WO);
% Gfr2 = feedback(G_p,Kdyaw);
% 
% figure(6)
% pzmap(Gfr,Gfr2)
% 
% figure(7)
% bode(Gfr,Gfr2)
% 
% % Completa acrescentando o washout
% 
% K = [0 0 Kdyaw;
%     Kproll Kdroll 0];
% 
% A_Lat2 = [DinLat.Completa.A zeros(4,1);
%          zeros(1,3) 1 -1];
% B_Lat2 = [DinLat.Completa.B;
%           0 0];
% 
% C = [0 1 0 0 0; 
%     0 0 1 0 0;
%     0 0 0 1 -1];
% 
% [n,d] = ss2tf(A_Lat2-B_Lat2*K*C,B_Lat2(:,2)*Kproll,[0 1 0 0 0],0);
% Kheading = 252/9.8/2;
% 
% G = tf(n,d);
% G1 = G*tf(9.8/252,[1 0]);
% 
% Gf = feedback(G1*Kheading,1);
% 
% step(Gf,10)