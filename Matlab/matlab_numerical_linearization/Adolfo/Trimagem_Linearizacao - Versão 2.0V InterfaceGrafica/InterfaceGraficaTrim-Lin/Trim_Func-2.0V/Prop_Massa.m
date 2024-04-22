%% Versão 1.0 - Última Atualização - 16/07/2014 (Adolfo)

function [J, Rcm, Massa] = Prop_Massa(opcao,BaseLine)

switch BaseLine
    
    case 1
        %% Baseline 8
        M   = [800 768.25 736.5 704 673];
        Jxx = [33 31.9 30 29 26.5] ;
        Jyy = [758 752 747 742 736];
        Jzz = [759 754 749 744 738];
        Jxz = [22.5 22.8 22.87 22.7 22.21];
        Xcm = [-2.091 -2.087 -2.083 -2.078 -2.072];        
        Ycm = zeros(1,5);
        Zcm = zeros(1,5);
        
    case 2
        %% Basline 9 - 02/03/2015
        M   = [807 792 778.4 754.5 731.5];
        Jxx = [28.5 28.4 28.3 27.8 27.28] ;
        Jyy = [968 966.5 965 963 961];
        Jzz = [970 968.5 967 965 963];
        Jxz = [0.6 0.7 0.89  0.85 0.8];
        Xcm = [-2.166 -2.17 -2.174 -2.1795 -2.185];
        Ycm = zeros(1,5);
        Zcm = zeros(1,5);
        
    case 3
        %% Baseline 9 - 26/03/2015 (Excel Renato)
        M   = [850 830.8 812 793 774];
        Jxx = [29.3 28.9 28.63 28.24 27.6] ;
        Jyy = [901 898.5 897 895.4 893.7];
        Jzz = [903 901 899 897 895.8];
        Jxz = [0.8 1.13 1.06  0.9 0.48];
        Xcm = [-2.124 -2.129 -2.132 -2.136 -2.139];        
        Ycm = zeros(1,5);
        Zcm = zeros(1,5);
        
    case 4
        %% Baseline 9 - 26/03/2015 (PowerPoint Renato)
        M   = [850 830.8 822 793 775];
        Jxx = [29.3 28.9 28.63 28.24 27.6] ;
        Jyy = [1038 1036.5 1035 1033.5 1032];
        Jzz = [1040 1038.5 1037 1035.5 1034];
        Jxz = [0.6 0.73 0.86  0.63 0.4];
        Xcm = [-2.125 -2.129 -2.132 -2.136 -2.140];        
        Ycm = zeros(1,5);
        Zcm = zeros(1,5);
    case 5
        %% Baseline 9 - 28/04/2015 (PowerPoint Renato) -- Caso nãonominal Cg - 10cm
        M   = [850 830.8 822 793 775];
        Jxx = [29.3 28.9 28.63 28.24 27.6] ;
        Jyy = [1038 1036.5 1035 1033.5 1032];
        Jzz = [1040 1038.5 1037 1035.5 1034];
        Jxz = [0.6 0.73 0.86  0.63 0.4];
        Xcm = [-2.125 -2.129 -2.132 -2.136 -2.140] + 0.05;        
        Ycm = zeros(1,5);
        Zcm = zeros(1,5);
        
end
Massa = M(opcao);
J = [Jxx(opcao) 0 -Jxz(opcao); 0 Jyy(opcao) 0; -Jxz(opcao) 0 Jzz(opcao)];
Rcm =[Xcm(opcao) Ycm(opcao) Zcm(opcao)]';
end


