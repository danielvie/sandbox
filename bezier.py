import numpy as np

def get_bezier(P, N = 100):
    
    # montando matriz B
    B = np.matrix([
        [ 1,  0,  0, 0],
        [-3,  3,  0, 0],
        [ 3, -6,  3, 0],
        [-1,  3, -3, 1],
    ])
    
    # montando matriz T
    ONES = np.ones([N, 1])
    t = np.linspace(0, 1, N)
    T = np.column_stack([ONES, t, t**2, t**3])
    
    # calculando curva
    R = T*B*P
    x = R[:,0].T.tolist()[0]
    y = R[:,1].T.tolist()[0]
    
    return x, y

def custo(xr, yr, P = None):
    
    if hasattr(xr, 'values'):
        xr = xr.values
        
    if hasattr(yr, 'values'):
        yr = yr.values
    
    if not P:
        P = get_P0(xr, yr)
    
    # interpolando Bezier em funcao de `xr`
    xb, yb = get_bezier(P)
    x = xr
    y = np.interp(x, xb, yb)
    
    # calculando custo pelo quadrado da diferenca
    dif = np.subtract(yr, y)
    res = (dif*dif).sum()
    
    # sinal (1: abaixo), (-1: acima)
    sinal = 1
    if dif.sum() < 0.:
        sinal = -1    
    
    # FATOR DE NORMALIZACAO    
    # eq. reta `ax + b`
    x1 = xr[0]
    x2 = xr[-1]
    y1 = yr[0]
    y2 = yr[-1]
    
    a = (y2-y1)/(x2-x1)
    b = y1 - a*x1
    
    xx = xr
    yy = a*xx + b
    
    d0 = yr - yy
    c0 = (d0*d0).sum()
    
    return sinal*res/c0

def get_P0(xr, yr):
    
    if hasattr(xr, 'values'):
        xr = xr.values
        
    if hasattr(yr, 'values'):
        yr = yr.values
    
    p0  = [xr[0], yr[0]]
    p3  = [xr[-1], yr[-1]]
    
    v_  = np.subtract(p3,p0)/3
    p1  = p0 + v_
    p2  = p0 + v_*2
    
    P0 = [p0, p1, p2, p3]
    
    return P0

def grad(xr, yr, P):
    
    # custo nominal
    c = abs(custo(xr, yr, P))
    
    # gradiente
    p0 = P[0]
    p1 = P[1]
    p2 = P[2]
    p3 = P[3]
    
    step = 1.0
    c1 = abs(custo(xr, yr, [p0, p1 + [step, 0.0], p2, p3]))
    c2 = abs(custo(xr, yr, [p0, p1 + [0.0, step], p2, p3]))
    c3 = abs(custo(xr, yr, [p0, p1, p2 + [step, 0.0], p3]))
    c4 = abs(custo(xr, yr, [p0, p1, p2 + [0.0, step], p3]))
    
    g1 = (c1 - c)/step
    g2 = (c2 - c)/step
    g3 = (c3 - c)/step
    g4 = (c4 - c)/step
    
    return g1, g2, g3, g4

def fit_bezier(xr, yr, P0 = None, niter = 25, k0 = 1., sombra = 0):
    '''
    xr....: coordenadas x da curva
    yr....: coordenadas y da curva
    P0....: pontos de bezier
    niter.: nro de iteracoes
    k0....: taxa de aprendizagem inicial
    '''    
    
    if not P0:
        P0 = get_P0(xr, yr)    
    
    # calculando taxa de aprendizagem k_
    k_ = k0
    
    for i in range(20):
        G = grad(xr, yr, P0)
        P = [P0[0],
             P0[1] - np.multiply(G[:2], k_),
             P0[2] - np.multiply(G[2:], k_),
             P0[3]]
        
        x, y = get_bezier(P)
        
        c = custo(xr, yr, P)

        if c < 0.:
            k_ *= 0.5
            break
        
        k_ *= 2.
    
    k = k_
    
    # matriz de custo
    C  = []
    P_ = P0
    
    for i in range(niter):
        P = P_
        
        # calculo gradiente
        G = grad(xr, yr, P)
        
        # condica de erro para cruzamento
        # [TODO]
        
        # montando matriz P_
        P_ = [
            P[0],
            P[1] - np.multiply(G[:2], k),
            P[2] - np.multiply(G[2:], k),
            P[3]
        ]
        
        C.append(custo(xr, yr, P_))
        
        if sombra:
            xs, ys = get_bezier(P_)
            plt.plot(xs, ys, '--', color='gray', alpha=0.4)
    
    return {
        'P': P_,
        'C': C
    }
