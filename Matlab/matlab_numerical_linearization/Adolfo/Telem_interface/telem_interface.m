function varargout = telem_interface(varargin)
% TELEM_INTERFACE MATLAB code for telem_interface.fig
%      TELEM_INTERFACE, by itself, creates a new TELEM_INTERFACE or raises the existing
%      singleton*.
%
%      H = TELEM_INTERFACE returns the handle to a new TELEM_INTERFACE or the handle to
%      the existing singleton*.
%
%      TELEM_INTERFACE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TELEM_INTERFACE.M with the given input arguments.
%
%      TELEM_INTERFACE('Property','Value',...) creates a new TELEM_INTERFACE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before telem_interface_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to telem_interface_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help telem_interface

% Last Modified by GUIDE v2.5 25-May-2015 17:22:51

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @telem_interface_OpeningFcn, ...
                   'gui_OutputFcn',  @telem_interface_OutputFcn, ...
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
%--------------------------------------------------------------------------
function telem_interface_update(eventdata, handles)
   
set(findobj(handles.uipanel_list,'Style','checkbox'),'Visible','off');

contents = cellstr(get(handles.listbox1,'String'));
if isempty(contents)
    return;
end

directory = getappdata(handles.figure1,'directory');

filename = contents{get(handles.listbox1,'Value')};
filename = [directory '\' filename];
TS =  mount_telem_log(filename);

setappdata(handles.figure1, 'TS', TS);

% R2D = 180/pi;
% 
% llo = [-5.9244 -35.1567];
% LLA = TSC.dadosInuUTC.Data(:,25:27); %rad rad m
% LLA(:,1:2) = LLA(:,1:2)*R2D;
% href = -LLA(1,3);
% Pn = lla2flat(LLA, llo, 0, href);
% 
% LLA_WPTS = TSC.GNCOutTel.Data(:,10:12); %deg deg m
% WPTS = lla2flat(LLA_WPTS, llo, 0, href);
% WPTS(:,3) = -WPTS(:,3);
% 
% setappdata(handles.figure1, 'Pn', Pn);
% setappdata(handles.figure1, 'WPTS', WPTS);

OutList = TS.DataInfo.UserData;
n = length(OutList);

OutCheckBox  = cell(n,1);
      
y = 740;
for i=1:n
	OutCheckBox{i} = uicontrol(handles.uipanel_list,'Style','checkbox',...
                'String', OutList{i},...
                'Value',0, ...
                'Visible', 'on', ...
                'FontSize',9, ...
                'ForegroundColor','b', ...
                'Position',[2 y 250 20], ...
                'Callback',{@OutCheckBox_Callback});
        y = y - 20;
end
    
setappdata(handles.figure1, 'OutCheckBox', OutCheckBox);
setappdata(handles.figure1, 'OutList', OutList);

set(handles.uipanel_list, 'Visible', 'on');

%--------------------------------------------------------------------------
% --- Executes just before telem_interface is made visible.
function telem_interface_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to telem_interface (see VARARGIN)

% Choose default command line output for telem_interface
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

haxes = subplot(1,1,1, 'Parent', handles.uipanel_plot);
cla(haxes, 'reset');

isub = 0;
setappdata(handles.figure1, 'isub', isub);

colors = ['b','r','m','k','g','c'];
setappdata(handles.uipanel_plot, 'colors', colors);

% set(handles.radiobutton_horiz, 'Value', 1);
% set(handles.radiobutton_vert, 'Value', 0);

% set(handles.uipanel_list, 'Visible', 'off');

directory = pwd;
setappdata(handles.figure1, 'directory', directory);
list0 = dir(directory);
I = find([list0.isdir]==1);
list0 = {list0(I).name};

if exist([directory '\telem_log_config.txt'],'file');
    list0 = list0(3:length(I));
end

set(handles.listbox0, 'String', list0);
set(handles.listbox0, 'Value', 1);

list = dir('*.txt');
for i=1:length(list)
	if strcmp(list(i).name,'telem_log_config.txt')
        list(i) = [];
	end
end
list1 = {list.name};
set(handles.listbox1, 'String', list1);

movegui(handles.figure1,'center');
telem_interface_update(eventdata, handles);

% UIWAIT makes telem_interface wait for user response (see UIRESUME)
% uiwait(handles.figure1);
%==========================================================================
% --- Executes on selection change in checkboxes.
function OutCheckBox_Callback(hObject, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1
handles = guidata(hObject);
OutList = getappdata(handles.figure1,'OutList');

index = find(strcmp(OutList, get(hObject,'String')));

if get(hObject,'Value')
    plot_var(handles, index);
else        
    haxes = get(handles.uipanel_plot,'Children');
    hplots = cell2mat(get(haxes,'Children'));
    delete(findobj(hplots, 'DisplayName', char(OutList(index))));
    
    haxes = get(handles.uipanel_plot,'Children');
    delete(findobj(haxes, 'String',OutList(index)));

end
%==========================================================================
function plot_var(handles,index)

% OUT_CONFIG = getappdata(handles.figure1,'OUT_CONFIG');
% OUT_VAR = getappdata(handles.figure1,'OUT_VAR');
OutList = getappdata(handles.figure1,'OutList');
TS = getappdata(handles.figure1,'TS');

haxes = subplot(1,1,1, 'Parent', handles.uipanel_plot);
       
set(haxes,'NextPlot','add');
set(haxes,'ColorOrder',[0 0 1],'LineStyleOrder','-|--|:|-.');

colors = ['y','b','g','r','c','m','k'];
icolor = index;
if icolor > length(colors);
    icolor = 1;
end
plot(TS.Time,TS.Data(:,index), ...
    'DisplayName', OutList(index),...
    'Color', colors(icolor),...
    'LineWidth',1.5);
% line_handles = line(TS.Time,TS.Data(:,index));

xlabel(haxes, 'time(s)');

hplots = get(haxes,'Children');
LEG = get(hplots,'DisplayName');
legend(haxes,LEG);
h = legend(haxes, 'boxoff');
grid(haxes, 'on');
zoom(haxes, 'on');
%==========================================================================
% --- Executes on button press in pushbutton_limpar.
function pushbutton_limpar_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_limpar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)% --------------------------------------------------------------------
% --- Executes during object creation, after setting all properties.

set(findobj(handles.uipanel_list,'Style','checkbox'),'Value',0);
haxes = subplot(1,1,1, 'Parent', handles.uipanel_plot);
cla(haxes, 'reset');
% --------------------------------------------------------------------
% --- Outputs from this function are returned to the command line.
function varargout = telem_interface_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
% --------------------------------------------------------------------
function FileMenu_Callback(hObject, eventdata, handles)
% hObject    handle to FileMenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% --------------------------------------------------------------------
function OpenMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to OpenMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
file = uigetfile('*.fig');
if ~isequal(file, 0)
    open(file);
end
% --------------------------------------------------------------------
function PrintMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to PrintMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
printdlg(handles.figure1)
% --------------------------------------------------------------------
function CloseMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to CloseMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
selection = questdlg(['Close ' get(handles.figure1,'Name') '?'],...
                     ['Close ' get(handles.figure1,'Name') '...'],...
                     'Yes','No','Yes');
if strcmp(selection,'No')
    return;
end
delete(handles.figure1)
% --------------------------------------------------------------------
% --- Executes during object creation, after setting all properties.
function figure1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% --------------------------------------------------------------------

% --- Executes when selected object is changed in uipanel_traj.
function uipanel_traj_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in uipanel_traj 
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

Pn = getappdata(handles.figure1,'Pn');
WPTS = getappdata(handles.figure1,'WPTS');

X = Pn(:,1)/1000;
Y = Pn(:,2)/1000;
H = -Pn(:,3);
D = sqrt(X.^2+Y.^2);
R = sqrt(WPTS(:,2).^2+ WPTS(:,1).^2);

% xmax = ceil(max(R))/1000;   
% ymax = ceil(max(WPTS(:,3))) + 100;

a = subplot(1,1,1, 'Parent', handles.uipanel_plot);
hold(a, 'off');

switch get(hObject,'Tag')
    
    case 'radiobutton_horiz'   
              
        plot(a,Y,X, WPTS(:,2)/1000,WPTS(:,1)/1000,'ro-',...
            'LineWidth',2,...
            'MarkerEdgeColor','k',...
            'MarkerFaceColor','r',...
            'MarkerSize',7);
        
        xlabel(a, 'East (km)');
        ylabel(a, 'North(km)');
        axis(a, 'equal');
%         xlim(a, [0 xmax]);
        grid(a, 'on');
        zoom(a,'on');     
  
    
    case 'radiobutton_vert'
           
        plot(a,D,H, R(:,1)/1000, WPTS(:,3),'ro',...
            'LineWidth',2,...
            'MarkerEdgeColor','k',...
            'MarkerFaceColor','r',...
            'MarkerSize',7);

%         xlim(a, [0 xmax]);
%         ylim(a, [0 ymax]);
        xlabel(a, 'dist horiz (km)');
        ylabel(a, 'alt(m)');
        grid(a, 'on');
        zoom(a, 'on');
end
hold(a, 'off');
%==================================================================
% --- Executes on selection change in listbox1.
function listbox1_Callback(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: contents = cellstr(get(hObject,'String')) returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1

set(findobj(handles.uipanel_list,'Style','checkbox'),'Visible','on');

% contents = cellstr(get(hObject,'String'));
% filename = contents{get(hObject,'Value')};
% [~, name, ~] = fileparts(filename);

% OUT_CONFIG = getappdata(handles.figure1,'OUT_CONFIG');
% list_sub = {OUT_CONFIG.sub};
% isub = find(strcmp(name,list_sub));
% if isempty(isub)
%     isub = 0;
% end
% setappdata(handles.figure1, 'isub', isub);

% setappdata(handles.figure1, 'isub', 0);
% set(handles.radiobutton_horiz, 'Value', 1);
% set(handles.radiobutton_vert, 'Value', 0);
telem_interface_update(eventdata, handles);
%=====================================================================
% --- Executes on selection change in listbox0.
function listbox0_Callback(hObject, eventdata, handles)
% hObject    handle to listbox0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox0 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox0

set(findobj(handles.uipanel_list,'Style','checkbox'),'Visible','off');

directory = getappdata(handles.figure1,'directory');

contents = cellstr(get(hObject,'String'));
S = contents{get(hObject,'Value')};

if strcmp(S,'.')
    return
end

if strcmp(S,'..')
    directory = fileparts(directory);
else
    directory = [directory '\' S];
end

setappdata(handles.figure1, 'directory', directory);

list = dir(directory);
I = find([list.isdir]==1);
list0 = {list(I).name};

if exist([directory '\telem_log_config.txt'],'file');
    list0 = list0(3:length(I));
end
set(handles.listbox0, 'String', list0);
set(handles.listbox0, 'Value', 1);

list_txt = dir([directory '\*.txt']);
list_txt = {list_txt.name}; 
if isempty(list_txt)
    set(handles.listbox1, 'String', list_txt);
    return
end

I = find(~strcmp('telem_log_config.txt',list_txt));
list_txt = list_txt(I);
file_list = list_txt;
list1 = file_list;
if length(list0) == 2 % the last level
    OUT_CONFIG = getappdata(handles.figure1,'OUT_CONFIG');
    list_sub = {OUT_CONFIG.sub};
    nsub = length(list_sub);
    list1 = cell(1,nsub);
    k=0;
    for i = 1:nsub;
        file = [list_sub{i} '.txt'];
        j = find(strcmp(file,file_list));
        if ~isempty(j)
            k = k+1;
            list1{k} = file_list{j};
        end;
    end
    list1 = list1(1:k);
end
set(handles.listbox1, 'String', list1);
%=====================================================================
% --- Executes during object creation, after setting all properties.
function listbox0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
%=====================================================================
% --- Executes during object creation, after setting all properties.
function listbox1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
%=====================================================================
