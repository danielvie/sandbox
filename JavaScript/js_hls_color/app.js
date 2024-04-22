var res = document.getElementById('res');

function hlsToRgb(h, l, s) {
    let r, g, b;

    if (s == 0) {
        r = g = b = l; // achromatic
    } else {
        const hue2rgb = (p, q, t) => {
            if (t < 0) t += 1;
            if (t > 1) t -= 1;
            if (t < 1 / 6) return p + (q - p) * 6 * t;
            if (t < 1 / 2) return q;
            if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
            return p;
        };

        const q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        const p = 2 * l - q;

        r = hue2rgb(p, q, h + 1 / 3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1 / 3);
    }

    return [r, g, b];
}

function genColor(ang) {
    /* generate color from angle */
    const h = ang / 360;
    // const l = 0.5;
    // const s = 0.5;
    const l = Number(document.getElementById('hls_l').value)/100
    const s = Number(document.getElementById('hls_s').value)/100
    const [r, g, b] = hlsToRgb(h, l, s);

    const rInt = Math.round(r * 255);
    const gInt = Math.round(g * 255);
    const bInt = Math.round(b * 255);

    const color = `#${rInt.toString(16).padStart(2, '0')}${gInt.toString(16).padStart(2, '0')}${bInt.toString(16).padStart(2, '0')}`;

    return color;
}

function getN() {
    const n = Number(document.getElementById('hls_N').value)
    return n
}

function copyToClipboard(text) {
    const el = document.createElement('textarea');
    el.value = text;
    el.setAttribute('readonly', '');
    el.style.position = 'absolute';
    el.style.left = '-9999px';
    
    document.body.appendChild(el);
    el.select();
    
    document.execCommand('copy');
    document.body.removeChild(el);
    
    document.querySelectorAll('.current').forEach(el => {
        el.style.backgroundColor = text
    })
}

function main() {
    res.innerHTML = ''
    const n = getN()
    console.log(n)
    
    for (let v = 0; v < 360; v += 360 / n) {
        const v_int = parseInt(v)
        const color = genColor(v_int)
        
        const cor = document.createElement('div')
        cor.classList = 'cor'
        cor.style = `background-color: ${color}`
        cor.setAttribute('color', color)
        
        const text = document.createElement('div');
        text.classList = 'text'
        text.innerText = `${color} (${v_int})`

        const container = document.createElement('div')
        container.classList = 'container'
        container.appendChild(cor)
        container.appendChild(text)
        
        res.appendChild(container)
    }

    const elements = document.querySelectorAll('.cor')
    
    elements.forEach(el => {
        el.addEventListener('click', () => {
            copyToClipboard(el.getAttribute('color'))
        })
    })

}

main()