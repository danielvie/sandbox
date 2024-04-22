function TS =  mount_telem_log(filename)
% clc;
% clear;

[~, name, ~] = fileparts(filename);

A = importdata(filename,'\t',1);

var_str = A.textdata(1,:);

var_str(1:2) = [];

i_CHS = find(strcmp('CHS',var_str));
I = find(A.data(:,i_CHS) < 1);
if ~isempty(I)
    A.data(I,:) = [];
end;

i_uSeconds = find(strcmp('uSeconds',var_str));

I = find(A.data(:,i_uSeconds-1)+ 1e-6*A.data(:,i_uSeconds) > ...
    A.data(end,i_uSeconds-1)+ 1e-6*A.data(end,i_uSeconds) );
A.data(I,:) = [];

t0 = A.data(1,i_uSeconds-1)+ 1e-6*A.data(1,i_uSeconds);
TIME = A.data(:,i_uSeconds-1)+ 1e-6*A.data(:,i_uSeconds) - t0;

var_str(1:i_uSeconds) = [];
A.data(:,1:i_uSeconds) = [];

i_CHS = find(strcmp('CHS',var_str));
var_str(i_CHS) = [];
A.data(:,i_CHS) = [];
   
TS = timeseries(A.data,TIME, 'Name', name);
TS.DataInfo.UserData = var_str;
TS.DataInfo.Unit = '';
TS.name = filename;
    
