load hinfstruct_demo G

% controller
C0 = tunablePID('C', 'pi');

% low pass filter
a  = realp('a', 1);
F0 = tf(a, [1 a]);

% LOOP SHAPING DESIGN

% target crossover
wc = 1000; 
s  = tf('s');
LS = (1 + 0.001*s/wc)/(0.001+s/wc);
bodemag(LS, {1E1, 1E5}); grid;
title('Target loop shape')

% Label the block I/Os
Wn = 1/LS; Wn.u = 'nw'; Wn.y = 'n';
We = LS; We.u = 'e'; We.y = 'ew';
C0.u = 'e'; C0.y = 'u';
F0.u = 'yn'; F0.y = 'yf';

% Specify summing junctions
Sum1 = sumblk('e = r - yf');
Sum2 = sumblk('yn = y + n');

% Connect the blocks together
T0 = connect(G,Wn,We,C0,F0,Sum1,Sum2,{'r','nw'},{'y','ew'});

% TUNNING THE CONTROLLER GAINS
rng('default')
opt = hinfstructOptions('Display','final','RandomStart',5);
T = hinfstruct(T0,opt);

C = getBlockValue(T,'C');
F = getValue(F0,T.Blocks); % propagate tuned parameters from T to F

%% comparacao
clf();
bode(G, {1E1, 1E5}); hold on;
bode(LS, {1E1, 1E5});
bode(G*C*F,'b',{1e1,1e6}), grid,

% bodemag(LS, {1E1, 1E5}); hold on;
% bodemag(LS,'r--', {1E1, 1E5});
grid;
hold off;