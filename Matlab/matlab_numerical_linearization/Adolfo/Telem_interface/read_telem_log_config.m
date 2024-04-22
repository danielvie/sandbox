A = importdata('telem_log_config.txt',' ',0);
[nsub,~] = size(A.textdata);
OUT_CONFIG(1:nsub) = struct('sub','','nvars',0, 'on',0);


for i=1:nsub
    OUT_CONFIG(i).sub = A.textdata(i);
    OUT_CONFIG(i).on = A.data(i);
end
