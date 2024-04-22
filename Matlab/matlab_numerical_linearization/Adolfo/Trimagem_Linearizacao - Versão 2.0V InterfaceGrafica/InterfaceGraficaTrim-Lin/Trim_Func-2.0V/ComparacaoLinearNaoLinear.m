function [y_NL, t, only_long, only_lat] = ComparacaoLinearNaoLinear(X_Trim,U_Trim,Modelo,Alt,Vel,Pertu)
    open_system('EQmovSimulink');
    %Carregandos as variáveis de simulação
    Aux_Modelo.EmpenaMatrix = [1 -1 1; 1 1 1; -1 1 1; -1 -1 1];
    Aux_Modelo.Eixo = 1; %corpo
    Aux_Modelo.Rcm = Modelo.Rcm;
    Aux_Modelo.Eixo = 1; %corpo
    Aux_Modelo.Massa = Modelo.Massa;
    Aux_Modelo.Inercia = Modelo.Inercia;
    ManeteStep  = 0.05;    
    x = X_Trim;
    Controle = [U_Trim.Manete(Alt,Vel) U_Trim.dPitch(Alt,Vel) U_Trim.dYaw(Alt,Vel)  U_Trim.dRoll(Alt,Vel)];
    x0 = [x(1)*cos(x(2))*cos(x(3)) x(1)*sin(x(3)) x(1)*sin(x(2))*cos(x(3)) x(4:11)' -x(12)];
    
    assignin('base','Aux_Modelo',Aux_Modelo)
    
    label = Modelo.BVaeroSF.label;
    %Configurando as simulações simulação não-linear    
    open_system('EQmovSimulink');
    set_param('EQmovSimulink/aerodin/Sfunction','FunctionName',label)
    set_param('EQmovSimulink/Referencia/Converte4emp','value','[1 -1 1; 1 1 1; -1 1 1; -1 -1 1]'); 
    set_param('EQmovSimulink/Referencia/EmpenaTrim','value',['[',num2str(Controle(2:4)),']']);    
    set_param('EQmovSimulink/Integrator','InitialCondition',['[',num2str(x0),']']);     
    set_param('EQmovSimulink/Referencia/ManeteTrim','value',num2str(Controle(1)));   
    set_param('EQmovSimulink/Cg','value',['[',num2str(Modelo.Rcm'),']']);
    set_param('EQmovSimulink/Referencia/RefManete','After',num2str(ManeteStep))
    set_param('EQmovSimulink/Referencia/dpitch','Gain',num2str(Pertu(2)))
    set_param('EQmovSimulink/Referencia/dyaw','Gain',num2str(Pertu(3)))
    set_param('EQmovSimulink/Referencia/droll','Gain',num2str(Pertu(1)))
    set_param('EQmovSimulink/Referencia/dT','Gain',num2str(Pertu(4)))
    config.SimulationMode = 'normal';
    config.Saveoutput = 'on';
    config.OutputSavename = 'X_Estados';
    
    
    %Configurando as simulações simulação linear
    assignin('base','Aux_Modelo',Aux_Modelo)
    open_system('SimulinkLinear1');
    set_param('SimulinkLinear1/dpitch','Gain',num2str(Pertu(2)))
    set_param('SimulinkLinear1/dyaw','Gain',num2str(Pertu(3)))
    set_param('SimulinkLinear1/droll','Gain',num2str(Pertu(1)))
    set_param('SimulinkLinear1/dT','Gain',num2str(Pertu(4)))
    set_param('SimulinkLinear1/RefManete','After',num2str(ManeteStep))    
    configLinear.SimulationMode = 'normal';
    configLinear.Saveoutput = 'on';
    configLinear.OutputSavename = ['only_long', 'only_lat'] ;
    
    if Pertu(4) == 1;
      set_param('SimulinkLinear1/Constante','Value','-1');
      set_param('EQmovSimulink/Referencia/Constante','Value','-1');
    else
      set_param('SimulinkLinear1/Constante','Value','1');
      set_param('EQmovSimulink/Referencia/Constante','Value','1')
    end
    
    
%     if B == 4
%         config.StopTime = '20';
%         configLinear.StopTime = '20';
%         set_param('EQmovSimulink/Referencia/Constante','value',num2str(-1));
%         set_param('SimulinkLinear1/Constante','value',num2str(-1));
%     else
%         config.StopTime = '10';
%         configLinear.StopTime = '10';
%         set_param('EQmovSimulink/Referencia/Constante','value',num2str(1));
%         set_param('SimulinkLinear1/Constante','value',num2str(1));
%     end
    
    y    = sim('EQmovSimulink',config);
    t    = y.get('X_Estados').time;
    y_NL = y.get('X_Estados').signals.values;
    clear y;
    
    
    y =  sim('SimulinkLinear1',configLinear);
    
    only_long = y.get('logsout').get('only_long').Values;
    only_lat  = y.get('logsout').get('only_lat').Values;
    only_long.time = y.get('logsout').get('only_lat').Values.Time;
    clear y;
    
    
end