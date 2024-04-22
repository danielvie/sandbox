% Gerando o arquivo .h para armazenar as tabelas a serem usadas na
% pilotagem.
% Interpolação com 2 entradas: vel e altitude
clear;clc;close all

% load('Ganhos.mat');
load('BV9_30_03/GanhosTanqueHalf_2.mat');


vel = [160 180 200 220 240 250 260];
alt = 0:1000:4000;

n_vel = length(vel);
n_alt = length(alt);

try      
	fid=fopen('ap_tab.h','wt');
    if fid<0
    	error('error opening file');
    end
        
    fprintf(fid,'%s\n','#ifndef AP_TAB_H');
    fprintf(fid,'%s\n\n','#define AP_TAB_H');

    fprintf(fid,'%s\n','#ifdef __cplusplus');
    fprintf(fid,'%s\n','extern "C" {');
    fprintf(fid,'%s\n\n','#endif');

    fprintf(fid,'%s\n',' float64_t const KP_pitch[]={');
    fprintf(fid,'  %d, %d,\n',n_vel, n_alt);
            
    for i=1:n_vel
    	fprintf(fid,' %4.1f,',vel(i));
    end
    fprintf(fid,'%s\n','/* vel[m/s] */');

    for i=1:n_alt
    	fprintf(fid,' %4.1f,',alt(i));
    end
    fprintf(fid,'%s\n','/* alt[m] */');
         
    for i_alt = 1:n_alt
        for i_vel = 1:n_vel
        	fprintf(fid,' %10.6f,',Kp.pitch(i_alt,i_vel));
        end
        fprintf(fid,'/* alt = %6.1f */\n', alt(i_alt));
    end
    fprintf(fid,'};\n\n');
    
    fprintf(fid,'%s\n',' float64_t const KD_pitch[]={');
    fprintf(fid,'  %d, %d,\n',n_vel, n_alt);
            
    for i=1:n_vel
    	fprintf(fid,' %4.1f,',vel(i));
    end
    fprintf(fid,'%s\n','/* vel[m/s] */');

    for i=1:n_alt
    	fprintf(fid,' %4.1f,',alt(i));
    end
    fprintf(fid,'%s\n','/* alt[m] */');
         
    for i_alt = 1:n_alt
        for i_vel = 1:n_vel
        	fprintf(fid,' %10.6f,',Kd.pitch(i_alt,i_vel));
        end
        fprintf(fid,'/* alt = %6.1f */\n', alt(i_alt));
    end
    fprintf(fid,'};\n\n');

    fprintf(fid,'%s\n',' float64_t const KP_roll[]={');
    fprintf(fid,'  %d, %d,\n',n_vel, n_alt);
            
    for i=1:n_vel
    	fprintf(fid,' %4.1f,',vel(i));
    end
    fprintf(fid,'%s\n','/* vel[m/s] */');

    for i=1:n_alt
    	fprintf(fid,' %4.1f,',alt(i));
    end
    fprintf(fid,'%s\n','/* alt[m] */');
         
    for i_alt = 1:n_alt
        for i_vel = 1:n_vel
        	fprintf(fid,' %10.6f,',Kp.roll(i_alt,i_vel));
        end
        fprintf(fid,'/* alt = %6.1f */\n', alt(i_alt));
    end
    fprintf(fid,'};\n\n');

    fprintf(fid,'%s\n',' float64_t const KD_roll[]={');
    fprintf(fid,'  %d, %d,\n',n_vel, n_alt);
            
    for i=1:n_vel
    	fprintf(fid,' %4.1f,',vel(i));
    end
    fprintf(fid,'%s\n','/* vel[m/s] */');

    for i=1:n_alt
    	fprintf(fid,' %4.1f,',alt(i));
    end
    fprintf(fid,'%s\n','/* alt[m] */');
         
    for i_alt = 1:n_alt
        for i_vel = 1:n_vel
        	fprintf(fid,' %10.6f,',Kd.roll(i_alt,i_vel));
        end
        fprintf(fid,'/* alt = %6.1f */\n', alt(i_alt));
    end
    fprintf(fid,'};\n\n');

    fprintf(fid,'%s\n',' float64_t const KD_yaw[]={');
    fprintf(fid,'  %d, %d,\n',n_vel, n_alt);
            
    for i=1:n_vel
    	fprintf(fid,' %4.1f,',vel(i));
    end
    fprintf(fid,'%s\n','/* vel[m/s] */');

    for i=1:n_alt
    	fprintf(fid,' %4.1f,',alt(i));
    end
    fprintf(fid,'%s\n','/* alt[m] */');
         
    for i_alt = 1:n_alt
        for i_vel = 1:n_vel
        	fprintf(fid,' %10.6f,',Kd.yaw(i_alt,i_vel));
        end
        fprintf(fid,'/* alt = %6.1f */\n', alt(i_alt));
    end
    fprintf(fid,'};\n\n');

    fprintf(fid,'%s\n','#ifdef __cplusplus');
    fprintf(fid,'%s\n','}');
    fprintf(fid,'%s\n\n','#endif');

    fprintf(fid,'%s /* AP_TAB_H*/\n\n','#endif');
 
    fclose(fid);
      
catch ME
	fclose(fid);
    error(ME.message);
end
