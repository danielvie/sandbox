clear all;
mex -g -IC:\SIM\tm_algorithms -IC:\SIM\Projetos\TM300_CDB_set14 ...
    -output aer_cruz_mx aer_cruz_mx.cpp ...
    C:\SIM\Projetos\TM300_CDB_set14\tm_aer.c ...
    C:\SIM\Projetos\TM300_CDB_set14\tm_atmos.c ...
    C:\SIM\tm_algorithms\math_3space.c ...
    C:\SIM\tm_algorithms\math_wrap.c ...
    C:\SIM\tm_algorithms\math_util.c ...
    C:\SIM\tm_algorithms\math_atmos.c;
