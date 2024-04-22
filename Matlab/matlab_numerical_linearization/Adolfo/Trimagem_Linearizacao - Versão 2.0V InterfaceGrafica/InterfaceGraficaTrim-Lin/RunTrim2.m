function [X_Trim, U_Trim, J, Heigth] = RunTrim2(Mach,Altitude,gamma,dphi,CondTrim,Modelo)

global Estados
%% Carregando as variáveis iniciais
G2R = pi/180; %Constante para transformar de grau para radiano
FE = 10; %Fundo de Escala do Atuador em graus
opcao = CondTrim;
Modelo.Eixo =0; %eixo do vento 
[Modelo.Inercia, Modelo.Rcm, Modelo.Massa] = Prop_Massa(Modelo.PropMassa);

%Condição inicial p/ trimagem
%Param(Manete(%), Delta_pitch(grau), delta_yaw, delta_roll, ângulo de ataque (rad), ângulo de derrapagem(rad))
X0 = [0.56 2.1 0 0 2*G2R 0*G2R];



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
X_Trim          = zeros(I_final,J_final,12);

%% Iniciando o programa de Trimagem
for i=1:I_final %Altitude
    
    for j=1:J_final %Velocidade                       
                
        
        %Carregando os parametros do fminsearch
        OPTIONS = optimset('TolFun',1e-10,'TolX',1e-10,'MaxFunEvals',5e+04,'MaxIter',1e+04);
        [OptParam, Custo, EXITFLAG, OUTPUT] = fminsearch('RestricaoMov',X0,OPTIONS,Mach(i,j),Altitude(i),gamma(i,j),dphi(i,j),opcao,Modelo);
        
        if I_final == 1
            
            %Cálculo do Valor de Empuxo
            [T_turb, ~, ~, ~, ~] = turb_mx(Modelo.Rcm, Altitude, Mach, OptParam(1), 1, 1);
%             [T_turb, ~, ~] = turb_mx(Altitude, Vt, OptParam(1), [0 0 0]');
            
            disp('Valores obtidos pelo programa de Trimagem')
            Variavel = {'Manete(N)-(%)', 'dPitch(°)-(%)',  'dYaw(°)-(%)',    'dRoll(°)-(%)',    'AoA(°)',     'Beta(°)', 'Custo'}';
            ValorAbsoluto = [T_turb(1) OptParam(2) OptParam(3) OptParam(4) OptParam(5)/G2R OptParam(6)/G2R Custo]' ;
            ValorRelativo = [OptParam(1)*100 OptParam(2:4)*100/FE OptParam(5)/G2R OptParam(6)/G2R Custo]';
            table(Variavel,ValorAbsoluto,ValorRelativo)
            disp('Caso o valor da Função custo seja próxima de zero, a trimagem foi um sucesso.')
        end
        
        X_Trim(i,j,:)      = Estados;
        U_Trim.Manete(i,j) = OptParam(1);
        U_Trim.dPitch(i,j) = OptParam(2);
        U_Trim.dYaw(i,j)   = OptParam(3);
        U_Trim.dRoll(i,j)  = OptParam(4);
        U_Trim.AoA(i,j)    = OptParam(5);
        U_Trim.Beta(i,j)   = OptParam(6);
        Heigth(i)          = Altitude;
        J(i,j)             = Custo;
        [T_turb(i,j),~, ~, ~, ~]        = turb_mx(Modelo.Rcm, Altitude, Mach, OptParam(1), 1, 1);  %BV9
%         [T_turb(i,j), ~, ~] = turb_mx(Altitude, Vt, OptParam(1), [0 0 0]'); %BV8
        
    end
end

end