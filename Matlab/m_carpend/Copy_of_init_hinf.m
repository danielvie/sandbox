
% definindo modelo
G = get_modelo_carpend();

G.u = 'u';
G.y = {'x', 'dx', 'teta', 'dteta'};

% denifindo controlador
k = realp('k', [1.0,1.0,1.0,1.0]);
C = ss(k);
C.u = {'track', 'dx', 'teta', 'detta'};
C.y = 'u';

% referencia
S = sumblk('track = x - ref');

% custos
wc = 10.0;
W1 = tf([0.001, 1], [1/wc, 0.001]);

% maximo pico de sensitividade
% correspondencia de margem de fase e ganho
% skogestad (pg. 62)
M  = 1.5;

% relacionado com a banda passando do sistema
% W1 = 10.0;

% quanto aceita de erro em regime estacionario
A = 0.1;

s  = tf('s');
% W1 = (s/M + W1)/(s + W1*A);

W1.u = 'track';
W1.y = 'e1';

W2 = ss(0.4);
W2.u = 'u';
W2.y = 'e2';

% medidas
Y1 = sumblk('y1 = track');
Y2 = sumblk('y2 = dx');
Y3 = sumblk('y3 = teta');
Y4 = sumblk('y4 = dteta');

% inputs / outputs
inputs  = {'ref'};
outputs = {'e1', 'e2', 'y1', 'y2', 'y3', 'y4'};

% conectando modelo
T0 = connect(G,C,S,W1,W2,Y1,Y2,Y3,Y4,inputs,outputs);

% calculando ganho
T = hinfstruct(T0);

% lendo ganho
K = getBlockValue(T, 'k');
sim('untitled1');