function varargout = TrimLinGuide(varargin)
% TRIMLINGUIDE MATLAB code for TrimLinGuide.fig
%      TRIMLINGUIDE, by itself, creates a new TRIMLINGUIDE or raises the existing
%      singleton*.
%
%      H = TRIMLINGUIDE returns the handle to a new TRIMLINGUIDE or the handle to
%      the existing singleton*.
%
%      TRIMLINGUIDE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TRIMLINGUIDE.M with the given input arguments.
%
%      TRIMLINGUIDE('Property','Value',...) creates a new TRIMLINGUIDE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before TrimLinGuide_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to TrimLinGuide_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help TrimLinGuide

% Last Modified by GUIDE v2.5 24-Mar-2015 09:52:53

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @TrimLinGuide_OpeningFcn, ...
    'gui_OutputFcn',  @TrimLinGuide_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before TrimLinGuide is made visible.
function TrimLinGuide_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to TrimLinGuide (see VARARGIN)

% Choose default command line output for TrimLinGuide
handles.output = hObject;

%Carregando as variáveis iniciais
addpath('Trim_Func-2.0V')
addpath('BV9')
addpath('Trim_Func-2.0V\Aero')
handles.CasoIter = 1;
handles.Modelo.Eixo =0;
handles.Modelo.EmpenaMatrix = [1 -1 1; 1 1 1; -1 1 1; -1 -1 1];

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes TrimLinGuide wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = TrimLinGuide_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


aux = get(hObject,'Value');
switch aux
    case 1
        handles.Modelo.aer_cruz_mx = @(V, W, Centro_Massa, xD, d1, d2, d3, d4) aer_cruz_mx8(V, W, Centro_Massa, xD,d1, d2, d3,d4);
        handles.Modelo.BVaero = 8;
        handles.Modelo.BVaeroSF.label = 'aer8_cruz_sf';
    %case 2
     %   handles.Modelo.aer_cruz_mx = @(V, W, Centro_Massa, xD, d1, d2, d3, d4) aer_cruz_mx9(V, W, Centro_Massa, xD, d1, d2, d3,d4);
      %  handles.Modelo.BVaeroSF.label = 'aer9_cruz_sf';
       % handles.Modelo.BVaero = 9;
end

% addpath('BV9');
% handles.TrimText.BDAero = 'BV9';
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2

aux = get(hObject,'Value');
switch aux
    case 1
        baseline = 1;
    case 2
        baseline = 2;        
    case 3
        baseline = 3;
    case 4
        baseline = 4;
    case 5
        baseline = 5;
end
handles.Modelo.BVMassa = baseline;
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes during object creation, after setting all properties.
function InputAlt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to InputAlt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function InputVel_Callback(hObject, eventdata, handles)
% hObject    handle to InputVel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of InputVel as text
%        str2double(get(hObject,'String')) returns contents of InputVel as a double


% --- Executes during object creation, after setting all properties.
function InputVel_CreateFcn(hObject, eventdata, handles)
% hObject    handle to InputVel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function InputRC_Callback(hObject, eventdata, handles)
% hObject    handle to InputRC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of InputRC as text
%        str2double(get(hObject,'String')) returns contents of InputRC as a double


% --- Executes during object creation, after setting all properties.
function InputRC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to InputRC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function InputAC_Callback(hObject, eventdata, handles)
% hObject    handle to InputAC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of InputAC as text
%        str2double(get(hObject,'String')) returns contents of InputAC as a double


% --- Executes during object creation, after setting all properties.
function InputAC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to InputAC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in bt_Trimar.
function bt_Trimar_Callback(hObject, eventdata, handles)
% hObject    handle to bt_Trimar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% Carregar os dados para rodar o programa de trimagem
handles.Alt = str2double(get(handles.InputAlt,'String'));
handles.Vel = str2double(get(handles.InputVel,'String'));
handles.G = str2double(get(handles.InputAC,'String'));
handles.ROC = str2double(get(handles.InputRC,'String'));
Modelo.PropMassa = handles.Modelo.PropMassa;
Modelo.BVMassa = handles.Modelo.BVMassa;
Altitude = handles.Alt;
Vt  = handles.Vel;
ROC = handles.ROC;
G  = handles.G;
[Modelo.Inercia, Modelo.Rcm, Modelo.Massa] = Prop_Massa(Modelo.PropMassa,Modelo.BVMassa);


if (handles.Modelo.Interval == 0)
    Mach       = atm_ISAVel2Mach(Altitude,Vt); %Implementar no Futuro
    gamma      = asin(ROC/Vt);
    dphi       = (G*9.8/Vt);
end

if (handles.Modelo.Interval == 1)
    Altitude  = [0 1000 2000 3000 4000];
    %     Vt = [180 200 220 240 250 260 280];
      Vt = [160 180 200 220 240 250 260];
%     Vt = 150:5:260;
    [Altitude, Mach, gamma, dphi] = condTrim(Altitude,Vt, handles.Modelo.CondicaoTrim,ROC,G);
    
end

%% Executando, plotando e armazendo os resultados da trimagem

% Chamando a rotina para executar a função de trimagem
[X_Trim, U_Trim, T_turb, Heigth, J] = Trimagem(Mach,Altitude,gamma,dphi,handles.Modelo);

if length(J) == 1
    i = handles.CasoIter;
    if (handles.CasoIter~=1)
        stats = handles.stats;
    end
    if handles.CasoIter < 4
        handles.CasoIter = i + 1;
    end
    GR = 180/pi;
    X = squeeze(X_Trim);
    X(2:9) = X(2:9)*GR;
    %     stats(:,i) = {J,U_Trim.Manete,U_Trim.dPitch,U_Trim.dYaw,U_Trim.dRoll,...
    %         X(1),X(2),X(3),X(4),X(5),X(6),X(7),X(8),X(9)};
    
    stats(:,i) = {J,T_turb,U_Trim.dPitch,U_Trim.dYaw,U_Trim.dRoll,...
        X(1),X(2),X(3),X(4),X(5),X(6),X(7),X(8),X(9)};
    
    set(handles.uitable1,'Data',stats);
    handles.stats = stats;
end

handles.X_Trim = X_Trim;
handles.U_Trim = U_Trim;
handles.T_turb = T_turb;
handles.Heigth = Heigth;
handles.J = J;
handles.Altitude = Altitude;
handles.ROC = ROC;
handles.Vt = Vt;
handles.gamma = gamma;
handles.G = G;
handles.dphi = dphi;
handles.Mach = Mach;
handles.Modelo.Inercia = Modelo.Inercia;
handles.Modelo.Rcm = Modelo.Rcm;
handles.Modelo.Massa = Modelo.Massa;

%Atualizar o label referente a trimagem dados
% Str = {'Banco de dados Aerodinâmico --- BV9', 'Propriedades de massa --- Base line 8'};
% Str      = get(handles.TrimagemText,'String');
% Str(1,:) = strcat(Str(1,:),handles.TrimText.BDAero);
% Str(3,:) = strcat(Str(3,:),handles.TrimText.Tanque);
% Str(4,:) = strcat(Str(4,:),handles.TrimText.Condicao);
% Str(5,:) = strcat(Str(5,:),' 0 a 4000m');
% Str(6,:) = strcat(Str(6,:),' 200 a 280m/s');
% Str(2,:) = strcat(Str
% handles.
% set(handles.TrimagemText,'String',Str);
guidata(hObject,handles);


% --- Executes on button press in bt_GravarDados.
function bt_GravarDados_Callback(hObject, eventdata, handles)
% hObject    handle to bt_GravarDados (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Log.TrimOptions.Dia      = ;
Log.TrimOptions.Condicao = handles.TrimText.Condicao;
Log.TrimOptions.Modelo   = handles.Modelo;
Log.TrimOptions.H        = handles.Altitude;
Log.TrimOptions.gamma    = handles.gamma;
Log.TrimOptions.dphi     = handles.dphi;
Log.TrimOptions.G        = handles.G;
Log.TrimOptions.Mach     = handles.Mach;
Log.TrimOptions.Vt       = handles.Vt;
Log.TrimOptions.ROC      = handles.ROC;
Log.Xtrim                = handles.X_Trim;
Log.Utrim                = handles.U_Trim;
Log.Turb                 = handles.T_turb;
Log.Custo                = handles.J;
save('LogTrim','Log');

% --- Executes when selected object is changed in btGroupTanque.
function btGroupTanque_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in btGroupTanque
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

switch get(eventdata.NewValue,'Tag') % Get Tag of selected object.
    case 'rButtonTanque1'
        aux = 1;
        handles.TrimText.Tanque = ' Tanque Cheio';
    case 'rButtonTanque2'
        aux = 2;
        handles.TrimText.Tanque = ' Tanque 3/4';
    case 'rButtonTanque3'
        aux = 3;
        handles.TrimText.Tanque = ' Tanque 1/2';
    case 'rButtonTanque4'
        aux = 4;
        handles.TrimText.Tanque = ' Tanque 1/4';
    case 'rButtonTanque5'
        aux = 5;
        handles.TrimText.Tanque = ' Tanque Vazio';
end

handles.Modelo.PropMassa = aux;
guidata(hObject,handles);


% --- Executes when selected object is changed in btGroupCV.
function btGroupCV_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in btGroupCV
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

switch get(eventdata.NewValue,'Tag') % Get Tag of selected object.
    case 'rButtonReto'
        aux = 1;
        set(handles.InputAlt,'Enable','on');
        set(handles.InputVel,'Enable','on');
        set(handles.InputRC,'Enable','off');
        set(handles.InputAC,'Enable','off');
        set(handles.InputAC,'String', 0);
        set(handles.InputRC,'String', 0);
        handles.TrimText.Condicao = ' Reto Nivelado';
    case 'rButtonCurva'
        aux = 3;
        set(handles.InputAlt,'Enable','on');
        set(handles.InputVel,'Enable','on');
        set(handles.InputRC,'Enable','off');
        set(handles.InputAC,'Enable','on');
        set(handles.InputRC,'String', 0);
        handles.TrimText.Condicao = ' Curva Coordenada';
    case 'rButtonRC'
        aux = 2;
        set(handles.InputAlt,'Enable','on');
        set(handles.InputVel,'Enable','on');
        set(handles.InputRC,'Enable','on');
        set(handles.InputAC,'Enable','off');
        set(handles.InputAC,'String', 0);
        handles.TrimText.Condicao = ' Taxa de Subida';
end

handles.Modelo.CondicaoTrim = aux;
guidata(hObject,handles);


% --- Executes when selected object is changed in btGroupIntervalo.
function btGroupIntervalo_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in btGroupIntervalo
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)
switch get(eventdata.NewValue,'Tag') % Get Tag of selected object.
    case 'radiobutton9' %unica condição
        aux = 0;
    case 'radiobutton10' %Varias condições
        aux = 1;
end
handles.Modelo.Interval = aux;
guidata(hObject,handles);


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over popupmenu1.


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.CasoIter = 1;
set(handles.uitable1,'Data',[]);
guidata(hObject, handles);


% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3
% Get Tag of selected object.

str = get(hObject,'String');
val = get(hObject,'Value');
PopUp = get(handles.PopUpFigura,'Value');
switch str{val}
    case 'AoA'
        aux = 1;
    case 'Beta'
        aux = 2;
    case 'dPitch'
        aux = 3;
    case 'dYaw'
        aux = 4;
    case 'dRoll'
        aux = 5;
    case 'Manete'
        aux = 6;
    case 'Função Custo'
        aux = 7;
end
cla(handles.axes1,'reset');
plotarXtrim(handles.X_Trim,handles.U_Trim,handles.J, handles.T_turb, aux,PopUp)


% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in btLoadLinearizar.
function btLoadLinearizar_Callback(hObject, eventdata, handles)
% hObject    handle to btLoadLinearizar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in btLinearizar.
function btLinearizar_Callback(hObject, eventdata, handles)
% hObject    handle to btLinearizar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% if (FlagTrim == 0)
%
%    return
% end

set(handles.Lista_Altitude,'String',handles.Altitude);
set(handles.Lista_Velocidade,'String',handles.Vt);

[Plano_Long, Plano_Lat, Coef] = Linearizacao(handles.X_Trim,handles.U_Trim,handles.Modelo);
handles.Plano_Long = Plano_Long;
handles.Plano_Lat  = Plano_Lat;
handles.Coef       = Coef;

str = get(handles.textLinearizacao,'String');
str = strcat(str,' Atual');
set(handles.textLinearizacao,'String',str);

guidata(hObject,handles);


% --- Executes on selection change in Lista_Altitude.
function Lista_Altitude_Callback(hObject, eventdata, handles)
% hObject    handle to Lista_Altitude (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Lista_Altitude contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Lista_Altitude
Alt = get(hObject,'Value');
handles.OptSimAlt = Alt;
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function Lista_Altitude_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Lista_Altitude (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Lista_Velocidade.
function Lista_Velocidade_Callback(hObject, eventdata, handles)
% hObject    handle to Lista_Velocidade (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Lista_Velocidade contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Lista_Velocidade
val = get(hObject,'Value');
handles.OptSimVel = val;
guidata(hObject,handles);



% --- Executes during object creation, after setting all properties.
function Lista_Velocidade_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Lista_Velocidade (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

Alt = handles.OptSimAlt;
Vel = handles.OptSimVel;
Pertu = handles.Pertubacao;
handles.Modelo.Eixo =0 ;
X_Trim = squeeze(handles.X_Trim(Alt,Vel,:));
U_Trim = handles.U_Trim;
set(handles.Lista_Pertubacao,'String',{'Rolamento','Arfagem','Guinada','Manete'});

assignin('base','A_Long',handles.Plano_Long(Alt,Vel).A)
assignin('base','B_Long',handles.Plano_Long(Alt,Vel).B)
assignin('base','C_Long',eye(5))
assignin('base','D_Long',zeros(5,2))

assignin('base','A_Lat',handles.Plano_Lat(Alt,Vel).A)
assignin('base','B_Lat',handles.Plano_Lat(Alt,Vel).B)
assignin('base','C_Lat',eye(4))
assignin('base','D_Lat',zeros(4,2))
[handles.y_NL, handles.t_NL, handles.Linear_Long, handles.Linear_Lat] = ComparacaoLinearNaoLinear(X_Trim,U_Trim,handles.Modelo,Alt,Vel,Pertu);
set(handles.Lista_PlotSimLong,'String',{'Vt','AoA','q','Theta','Altitude'});
set(handles.Lista_PlotSimLat,'String',{'Beta','Phi','p e r'});
guidata(hObject,handles);

% --- Executes on selection change in Lista_Pertubacao.
function Lista_Pertubacao_Callback(hObject, eventdata, handles)
% hObject    handle to Lista_Pertubacao (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Lista_Pertubacao contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Lista_Pertubacao
aux = get(hObject,'Value');
switch aux
    case 1
        Pertu = [1  0 0 0]';
    case 2
        Pertu = [0 1 0 0]';
    case 3
        Pertu = [0 0  1 0]';
    case 4
        Pertu = [0 0 0 1]';
        
end
handles.Pertubacao = Pertu;
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function Lista_Pertubacao_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Lista_Pertubacao (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Lista_PlotSimLong.
function Lista_PlotSimLong_Callback(hObject, eventdata, handles)
% hObject    handle to Lista_PlotSimLong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Lista_PlotSimLong contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Lista_PlotSimLong
cla(handles.axes1,'reset');
val = get(hObject,'Value');
X_Trim = squeeze(handles.X_Trim(handles.OptSimAlt,handles.OptSimVel,:));
PlotGraf(handles.y_NL, handles.t_NL, handles.Linear_Long,handles.Linear_Lat,X_Trim,1,val)





% --- Executes during object creation, after setting all properties.
function Lista_PlotSimLong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Lista_PlotSimLong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Lista_PlotSimLat.
function Lista_PlotSimLat_Callback(hObject, eventdata, handles)
% hObject    handle to Lista_PlotSimLat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Lista_PlotSimLat contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Lista_PlotSimLat
cla(handles.axes1,'reset');
val = get(hObject,'Value');
X_Trim = squeeze(handles.X_Trim(handles.OptSimAlt,handles.OptSimVel,:));
PlotGraf(handles.y_NL, handles.t_NL, handles.Linear_Long,handles.Linear_Lat,X_Trim,2,val)

% --- Executes during object creation, after setting all properties.
function Lista_PlotSimLat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Lista_PlotSimLat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Plano_Long = handles.Plano_Long;
Plano_Lat  = handles.Plano_Lat;
Coef       = handles.Coef;
save('ModeloLinear','Plano_Long','Plano_Lat','Coef')


% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in FiguraPopUp.
function FiguraPopUp_Callback(hObject, eventdata, handles)
% hObject    handle to FiguraPopUp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
f = figure();
h = handles.axes1;
copyobj(h,f);


% --- Executes on button press in PopUpFigura.
function PopUpFigura_Callback(hObject, eventdata, handles)
% hObject    handle to PopUpFigura (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of PopUpFigura
