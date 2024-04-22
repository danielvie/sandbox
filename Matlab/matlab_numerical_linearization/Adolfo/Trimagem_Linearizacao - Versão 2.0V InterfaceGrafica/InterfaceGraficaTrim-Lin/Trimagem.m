function [X_Trim, U_Trim, T_turb, Heigth, J] = Trimagem(Mach,Altitude,gamma,dphi,Modelo)

global Estados
%% Carregando as variáveis iniciais
G2R = pi/180; %Constante para transformar de grau para radiano
FE = 10; %Fundo de Escala do Atuador em graus
opcao = Modelo.CondicaoTrim;
Modelo.Eixo =0; %eixo do vento
[Modelo.Inercia, Modelo.Rcm, Modelo.Massa] = Prop_Massa(Modelo.PropMassa,Modelo.BVMassa);

I_final = length(Altitude);
J_final = length(Mach);

U_Trim.AoA      = zeros(I_final,J_final);
U_Trim.Beta     = U_Trim.AoA;
U_Trim.dPitch   = U_Trim.AoA;
U_Trim.dYaw     = U_Trim.AoA;
U_Trim.dRoll    = U_Trim.AoA;
U_Trim.Manete   = U_Trim.AoA;
Heigth          = zeros(I_final,1);
J               = U_Trim.AoA;
T_turb          = U_Trim.AoA;
X_Trim          = zeros(I_final,J_final,12);

%% Iniciando o programa de Trimagem
Progresso = waitbar(0,'Progresso da trimagem');
for i=1:I_final %Altitude
    waitbar(i/I_final,Progresso);
    for j=1:J_final %Velocidade
        
        
        %Carregando os parametros do fminsearch
        OPTIONS = optimset('TolFun',1e-10,'TolX',1e-10,'MaxFunEvals',5e+04,'MaxIter',1e+04);
        
        %Condição inicial p/ trimagem
        %Param(Manete(%), Delta_pitch(grau), delta_yaw, delta_roll, ângulo de ataque (rad), ângulo de derrapagem(rad))
        if (Altitude(i) > 2800 && Mach(i,j) < 0.5)
            X0 = [0.8 5 0 0 16*G2R 1*G2R]; %Baseline8
        else
            X0 = [0.8 2.1 0 0 2*G2R 0*G2R]; %Baseline9
        end
        
        [OptParam, Custo, EXITFLAG, OUTPUT] = fminsearch('RestricaoMov',X0,OPTIONS,Mach(i,j),Altitude(i),gamma(i,j),dphi(i,j),opcao,Modelo);
        
        X_Trim(i,j,:)      = Estados;
        U_Trim.Manete(i,j) = OptParam(1);
        U_Trim.dPitch(i,j) = OptParam(2);
        U_Trim.dYaw(i,j)   = OptParam(3);
        U_Trim.dRoll(i,j)  = OptParam(4);
        U_Trim.AoA(i,j)    = OptParam(5);
        U_Trim.Beta(i,j)   = OptParam(6);
        Heigth(i)          = Altitude(i);
        J(i,j)             = Custo;
        [T_turb(i,j),~, ~, ~, ~]        = turb_mx(Modelo.Rcm, Altitude(i), Mach(i,j), OptParam(1));  %BV9 nova Hassa
        %         [T_turb(i,j),~, ~, ~, ~]        = turb_mx(Modelo.Rcm, Altitude(i), Mach(i,j), OptParam(1),1,1);  %BV9
        %         [T_turb(i,j), ~, ~] = turb_mx(Altitude, Vt, OptParam(1), [0 0 0]'); %BV8
        
    end
end
close(Progresso);
end