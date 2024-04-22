import * as math from "mathjs";

export const calcula_alvo = (pos:number[], dist:number, azi:number) => {
    
    // reescrevendo NaN por 0.0
    const pos_  = pos.map((v:number) => (isNaN(v))?0.0:v);
    const dist_ = isNaN(dist)?0.0:dist;
    const azi_  = isNaN(azi)?0.0:azi;
        
    // vetor apontando para o norte com o comprimento da distancia
    let vnorte = [0., dist_]
    
    // convertando azimute para 'rad'
    let ang  = azi_ * Math.PI / 3200.0

    // aplicando rotacao no vetor de referencia no valor do azimute
    let vrot = [vnorte[1] * Math.sin(ang), vnorte[1] * Math.cos(ang)]
    
    // incorporando posicao inicial ao vetor 'vrot'
    let alvo = [pos_[0] + vrot[0], pos_[1] + vrot[1]]
    
    return alvo;

}

export const calcula_ang = (v1:number[], v2:number[]) => 
{
    
    const prodv:any = math.dot(v1, v2)
    const n1:any    = math.norm(v1)
    const n2:any    = math.norm(v2)
    
    // calculando valor do angulo
    let ang = math.acos(prodv/n1/n2)

    // sinal 
    if ((v1[0]*v2[1] - v2[0]*v1[1]) > 0.) 
    {
        ang = -ang
    }

    return ang

}

export const calcula_azi = (ini:number[], fim:number[]) => {

    const vref  = [0., 1.]
    const v = [fim[0] - ini[0], fim[1] - ini[1]];
    // calculando angulo por produto escalar
    let azi = Math.acos((v[0]*vref[0] + v[1]*vref[1])/Math.sqrt(v[0]*v[0] + v[1]*v[1]))
    
    // calculando sinal angulo
    const sinal = vref[0]*v[1] - v[0]*vref[1]
    
    if (sinal > 0.) {
        azi = 2*Math.PI - azi;
    }    

    return azi
}

export const calcula_azi_deg = (ini:number[], fim:number[]) => {
    return calcula_azi(ini, fim)*180./Math.PI
}

export const calcula_azi_mils = (ini:number[], fim:number[]) => {
    const azi = calcula_azi(ini, fim)*3200/Math.PI
    return azi 
}

// FUNCAO PARA CALCULO DO PONTO DE IMPACTO POR VISUALIZACAO DO PO
export const dms2deg = (dms:string[]) => {
    const d   = parseFloat(dms[0]) || 0.
    const m   = parseFloat(dms[1]) || 0.
    const s   = parseFloat(dms[2]) || 0.

    const deg = d + m/60. + s/3600.
    return deg
}

export const calcula_impacto = (config:any) => {

    // conversao deg -> rad
    const d2r = math.pi/180;

    // lendo valores de angulos po's
    let apo1:number  = parseFloat(config.ang1) || 0.
    let apo1_:number = dms2deg(config.ang1_)
    let apo2:number  = parseFloat(config.ang2) || 0.
    let apo2_:number = dms2deg(config.ang2_)

    // lendo posicoes de PO e OBSERVADORES
    const posicao_po1    = config.posicao_po1; 
    const observacao_po1 = config.observacao_po1; 
    const posicao_po2    = config.posicao_po2; 
    const observacao_po2 = config.observacao_po2; 

    // combinando leituras
    if ((apo1 === 0) || (apo1_ === 0)) {
        apo1  = (apo1 + apo1_)*2.0;
        apo1_ = 0.0;
    } 
    if ((apo2 === 0) || (apo2_ === 0)) {
        apo2  = (apo2 + apo2_)*2.0;
        apo2_ = 0.0;
    }
    const p1d = (apo1 + apo1_)/2.0;
    const p2d = (apo2 + apo2_)/2.0;
    
    // convertendo para radianos
    const p1r = p1d*d2r;
    const p2r = p2d*d2r;

    // vetores de visao po1 e po2
    const v1o1:any = math.subtract(posicao_po1,observacao_po1);
    const v2o2:any = math.subtract(posicao_po2,observacao_po2);

    // rotacionando vetor para direcao do impacto
    let aux0 =  v1o1[0]*math.cos(p1r) + v1o1[1]*math.sin(p1r);
    let aux1 = -v1o1[0]*math.sin(p1r) + v1o1[1]*math.cos(p1r);
    const v1x  = [aux0, aux1];
    
    aux0     =  v2o2[0]*math.cos(p2r) + v2o2[1]*math.sin(p2r);
    aux1     = -v2o2[0]*math.sin(p2r) + v2o2[1]*math.cos(p2r);
    const v2x  = [aux0, aux1];

    // calculando a inclinacao das retas
    const m1   = v1x[1]/v1x[0]
    const m2   = v2x[1]/v2x[0]

    if (Math.abs(m1 - m2) < 0.00001) {
        console.log('ERRO: valores invalidos!')
        let impacto = [NaN, NaN]
        return impacto;
    }

    // posicoes dos PO's
    const x1   = posicao_po1[0];
    const y1   = posicao_po1[1];
    const x2   = posicao_po2[0];
    const y2   = posicao_po2[1];

    // calculando x,y de impacto
    const xi   = (y2 - y1 + x1*m1 - x2*m2)/(m1-m2)
    const yi   = y1 + m1*(xi - x1)

    // montando vetor de impacto
    let impacto:any = [xi.toFixed(1), yi.toFixed(1)]
    
    // testando direcao do impacto
    let bla:any = math.subtract(posicao_po1, impacto)
    const dire:any = math.dot(bla,v1x)
    if (dire < 0.){
        console.log('ERRO: as linhas de visada nao se cruzam!')
        impacto = [NaN, NaN]
    }

    return impacto;
}

export const calcula_desvios = (lmu:number[], alvo:number[], impacto:number[]) => {
    // Calcula desvio de alcance e lateral
    let vetor_imp:number[]  = [impacto[0] - lmu[0], impacto[1] - lmu[1], 0];
    let vetor_alvo:number[] = [alvo[0] - lmu[0], alvo[1] - lmu[1], 0];
    let dist:any = math.norm(vetor_alvo);
    
    const cross_vet:any = math.cross(vetor_imp, vetor_alvo);
    
    let desvio_lat:any = cross_vet[2]/dist;

    let desvio_alc:any = math.dot(vetor_imp, vetor_alvo)/dist - dist;

    let desvio     = math.norm([desvio_alc, desvio_lat]);

    let res:any = {};
    if (isNaN(desvio_alc)) {
        
        res['alcance'] = -1.0;
        res['lateral'] = -1.0;
        res['total']   = -1.0;
        
        return res;
    }

    res['alcance'] = desvio_alc.toFixed(2);
    res['lateral'] = desvio_lat.toFixed(2);
    res['total']   = desvio.toFixed(2);

    return res;
}

export const calcula_distancia = (pos1:number[], pos2:number[]) => {
    const dif:any  = math.subtract(pos1, pos2);
    const dist:any = math.norm(dif)

    return dist;
}

export const atmos_isa = (h:number) => {
    //    Input required by atmosisa is:
    //     H      :a numeric array of M geopotential height in meters. 
    //
    //     Output calculated for the International Standard Atmosphere are: 
    //     T      :a numeric array of M temperature in kelvin.
    //     a      :a numeric array of M speed of sound in meters per second.
    //     P      :a numeric array of M air pressure in pascal.
    //     rho    :a numeric array of M air density in kilograms per meter cubed.
    //
    //      [T, a, P, rho] = atmos(1000)
    //
    //      [T, a, P, rho] = atmos([1000 11000 20000])
    //
    //   Copyright 2000-2010 The MathWorks, Inc.
    //
    //   Reference:  U.S. Standard Atmosphere, 1976, U.S. Government Printing 
    //   Office, Washington, D.C.

    const g     = 9.80665;
    const gamma = 1.4;
    const R     = 287.0531;
    const L     = 0.0065;
    const hts   = 11000;
    const htp   = 20000;
    const rho0  = 1.225;
    const P0    = 101325;
    const T0    = 288.15;
    
    const H0 = 0;
    
    if ( h > htp ){
        h = htp;
    }
    
    if ( h <  H0 ){
        h = H0;
    }
    
    let expon;
    let T;
    if ( h > hts ){
        T = T0 - L*hts; 
        expon = Math.exp(g/(R*T)*(hts - h)); 
    } else {
        T = T0 - L*h; 
        expon = 1.0;  
    }
    
    let a = Math.sqrt(T*gamma*R);

    let theta = T/T0;

    let gLR = (g/(L*R))
    let P = P0*Math.pow(theta,gLR)*expon;
    let rho = rho0*Math.pow(theta,(gLR-1.0))*expon;

    let res:any = {};

    res['temp'] = T;
    res['pressao'] = P;
    res['rho'] = rho;
    res['vsom'] = a;
    return res;
}

// deg -> UTM
export function deg2utm( lat_in:number, lon_in:number ){
	let la = lat_in;
	let lo = lon_in;

	let pi = Math.PI;	

    let sa = 6378137.000000 ; 
    let sb = 6356752.314245;

	let e2         = Math.sqrt((sa*sa) - (sb*sb))/sb;
	let e2cuadrada = e2*e2;
	let c          = ( sa*sa ) / sb;
	
	let lat = la * ( pi / 180 );
	let lon = lo * ( pi / 180 );

	let Huso   = Math.trunc( ( lo / 6 ) + 31);
	let S      = ( ( Huso * 6 ) - 183 );
	let deltaS = lon - ( S * ( pi / 180 ) );

	let a       = Math.cos(lat) * Math.sin(deltaS);
	let epsilon = 0.5 * Math.log( ( 1 +  a) / ( 1 - a ) );
	let nu      = Math.atan( Math.tan(lat) / Math.cos(deltaS) ) - lat;
	let v       = ( c / Math.sqrt( 1 +  e2cuadrada * Math.cos(lat) * Math.cos(lat) ) ) * 0.9996;

	let ta   = ( e2cuadrada / 2 ) * epsilon * epsilon * Math.cos(lat) * Math.cos(lat);
	let a1   = Math.sin( 2 * lat );
	let a2   = a1 * Math.cos(lat) * Math.cos(lat);
	let j2   = lat + ( a1 / 2 );
	let j4   = ( ( 3 * j2 ) + a2 ) / 4;
	let j6   = ( ( 5 * j4 ) + ( a2 * Math.pow(Math.cos(lat),2) ) ) / 3;
	let alfa = ( 3 / 4 ) * e2cuadrada;
	let beta = ( 5 / 3 ) * Math.pow(alfa,2);
	let gama = ( 35 / 27 ) * Math.pow(alfa,3);
	let Bm   = 0.9996 * c * ( lat - alfa * j2 + beta * j4 - gama * j6 );
	let xx   = epsilon * v * ( 1 + ( ta / 3 ) ) + 500000;
	let yy   = nu * v * ( 1 + ta ) + Bm;

	if ( yy<0 ) {
		yy = 9999999 + yy;
    }

    const res:any = {
        en: [xx, yy],
        zona: Huso,
        hemis: (la < 0)?'S':'N'
    }

	return res;
}

// UTM -> DEG
export function utm2deg( xx:number, yy:number, utmzone:number = 23, hemis:string = 'S') {

    let x = xx;
    let y = yy;
    let zone = utmzone;

    let sa = 6378137.000000 ; 
    let sb = 6356752.314245;
    
    let e2 = Math.sqrt((sa*sa) - (sb*sb))/sb;
    let e2cuadrada = e2*e2;
    let c = (sa*sa)/sb;

    let X = x - 500000;
    let Y = y;

    if (hemis === 'S' || hemis === 's')
        Y = y - 10000000;

    let S   = ( ( zone*6. ) - 183. ); 
    let lat = Y / ( 6366197.724*0.9996 );                                    
    
	let v   = ( c / Math.sqrt( 1 +  e2cuadrada * Math.cos(lat) * Math.cos(lat) ) ) * 0.9996;

    let a         = X / v;
    let a1        = Math.sin( 2 * lat );
    let a2        = a1 * Math.pow(Math.cos(lat),2);
    let j2        = lat + ( a1 / 2 );
    let j4        = ( ( 3 * j2 ) + a2 ) / 4;
    let j6        = ( ( 5 * j4 ) + ( a2 * Math.pow(Math.cos(lat),2)) ) / 3;
    let alfa      = ( 3/4 ) * e2cuadrada;
    let beta      = ( 5/3 ) * alfa*alfa;
    let gama      = ( 35/27 ) * Math.pow(alfa,3);
    let Bm        = 0.9996*c*( lat - alfa * j2 + beta * j4 - gama * j6 );
    let b         = ( Y - Bm ) / v;
    let Epsi      = e2cuadrada*a*a/2*Math.pow(Math.cos(lat),2);
    let Eps       = a * ( 1 - ( Epsi / 3 ) );
    let nab       = ( b * ( 1 - Epsi ) ) + lat;
    let senoheps  = ( Math.exp(Eps) - Math.exp(-Eps) ) / 2;
    let Delt      = Math.atan(senoheps / (Math.cos(nab) ) );
    let TaO       = Math.atan(Math.cos(Delt) * Math.tan(nab));
    let longitude =  Delt*180/Math.PI + S;

    let latitude = (lat + ( 1 + e2cuadrada*Math.pow(Math.cos(lat),2) - 3/2*e2cuadrada*Math.sin(lat)*Math.cos(lat)*( TaO - lat ))*(TaO - lat))*180/Math.PI;

    let Lat = latitude;
    let Lon = longitude;

    return [Lat, Lon];
}

export const calcRespostaPO = (config:any) => {
    const impacto = calcula_impacto(config)
    const desvios = calcula_desvios(config.lmu, config.alvo, impacto)
    
    let dist:number = -1.0;
    if (isNaN(desvios.alcance) === false)
    {
        const a = impacto[0] - config.lmu[0];
        const b = impacto[1] - config.lmu[1];

        dist = Math.sqrt(a*a + b*b);
        dist = Math.round(dist*10)/10;
    }
    
    return {
        impacto,
        desvios,
        dist
    };
}

export const calcRespostaZe = (config:any) => {
    const DR        = calcula_azi_mils(config.lmu, config.ref)
    let heading_  = DR - parseFloat(config.AO)
    heading_ = (heading_ > 0.)?heading_:(6400 + heading_)

    const dheading_ = heading_ - parseFloat(config.heading) 
    const DGT       = calcula_azi_mils(config.lmu, config.alvo)

    return {
        DR: DR,
        heading: heading_,
        dheading: dheading_,
        DGT: DGT
    }
}