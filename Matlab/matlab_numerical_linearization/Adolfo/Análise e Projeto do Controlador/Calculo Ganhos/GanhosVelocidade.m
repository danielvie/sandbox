% An�lise e projeto da malha de controle de velocidade
%Gpc - Ft de transfer�ncia de um comando de turbina p/velocidade


function [K, Vel] = GanhosVelocidade(Gpc,opcao,valor)
close all
%% Teste para escrever a planta fora das condi��s n�o-nominais
[n ,d] = tfdata(Gpc);
Kt = n{1}(2); %Ganho da Turbina (m/s^2)
a  = d{1}(2); %Arrasto
tau = 1; %Constante de tempo
Turbina = tf(1,[1 1]);

%% C�lculo do ganho da turbina baseado em tr�s m�tricas de desempenho
%amortecimento                                     -- 1 
%frequ�ncia natural de oscila��o (rad/s)           -- 2
%Erro em regime estacion�rio (%)                   -- 3
%M�todo margem de fase e wcg                       -- 4
%M�todo LQR                                        -- 5
%M�todo cancelamento do polo pelo zero controlador -- 6
 
switch (opcao)
    case 1
        K = 1/tau;
        zeta = valor;
        aux = a^2 + K^2 + 2*a*K;
        Kp = (aux/(4*zeta^2) - a)/(K*Kt); 
        Ki =0;
        Vel.zeta = zeta;
    case 2
        
        wn = valor;        
        Kp = (wn^2-a)/(Kt/tau);
        Ki =0;
        Vel.wn = wn;       
        
    case 3
        
        Erro = valor;
        Kp = (1 - Erro)/(1 + Erro*Kt/a);
        Ki =0;
        Vel.Erro = Erro;
        
    case 4
        
        wcg = 0.14;
        MF = 85;
        phi = (-180+MF)*pi/180;
        aux = cos(phi) + 1i*sin(phi);
        Gp = tf(Kt,[1 a]);
        Num = evalfr(Gp*Turbina,1i*wcg);
        Kp = real(aux/Num);
        Ki = -imag(aux/Num)*wcg;
        
    case 5
        
        A = [-a 0; -1 0];
        B = [Kt 0]';
        q22 = 10;
        r = 0.05;
        Q = [0 0 ; 0 1/q22^2];
        R = 1/r^2;
        
        K = lqr(A,B,Q,R);
        Kp = K(1);
        Ki = -K(2);
%         Turbina = 1;
    case 6
%         Kp = 0.0032;
        Kp = 0.0055;
        Ki = Kp*0;
end

K = [Kp Ki];
C = minreal(tf([Kp Ki],[1 0]));
Gp = tf(Kt,[1 a]);
% Gf = feedback(Turbina*Gp*C,1);
% figure()
% pzmap(Gf);
% figure()
bode(Turbina*Gp*C)
% figure()
% step(Gf,50);

end

