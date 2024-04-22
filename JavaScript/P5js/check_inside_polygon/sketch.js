
// criando linha no canvas
let linhas = []
linhas.push([196, 240])
linhas.push([133, 532])
linhas.push([293, 617])
linhas.push([566, 612])
linhas.push([581, 439])
linhas.push([523, 313])
linhas.push([361, 219])
linhas.push([395, 407])

// colors
const COLOR_GREEN = [100,180,100]
const COLOR_BLUE = [100,100,190]
const COLOR_ORANGE = [210,105,40]
const COLOR = [140, 140, 140]

// define flag render mouse
let show_render_mouse = false

// select / unselect
let flag_select = false
let pos_ = -1

// update closest continuously
let flag_inf_update = false

// get unique points
function get_unique_points(linhas)
{
    const res = []

    for (let i = 0; i < linhas.length; i++)
    {
        let s1 = get_segment(linhas, i)
        let s2 = get_segment(linhas, i + 1)
        
        if (test_segment_connection(s1, s2))
        {
            res.push(s1[1])
        }
    }
    return res
}

function setup()
{
    createCanvas(1200, 800)
}

function render_grid(space)
{
    stroke(220)
    let s = 0
    let cont = 0

    while (s < width)
    {
        // update space and counter
        s += space
        cont++

        // set weight
        let weight = ((cont % 2) == 0)?4:1
        strokeWeight(weight)
        
        // colunas e linhas
        line(...[s, 0], ...[s, height])
        line(...[0, s], ...[width, s])
    }
}

function render_polygon(linhas)
{
    for (let i = 0; i < linhas.length; i++)
    {
        let seg = get_segment(linhas, i)
        render_segments(seg)
    }
    
    linhas.forEach(el => {
        circle(...el, 15)
    })
}

function render_mouse(linhas)
{
    // render position mouse
    stroke(COLOR_BLUE)
    circle(mouseX, mouseY, 7)
    line(mouseX, mouseY, width, mouseY)
    
    // render cross with polygon
    const X = get_cross_points(linhas)
    X.forEach(el => {
        circle(...el, 15)
    })

}

let flag = false
function notify1(msg)
{
    if (!flag)
    {
        flag = true
        console.log(msg)
    }
}

function subtract(v1, v2)
{
    
    if (v1.length !== v2.length)
    {
        console.log("[SUBTRACT] :: ERROR: v1.length ~= v2.length")
        return 0
    }

    let res = [...v1]
    for (let i = 0; i < v1.length; i++)
    {
        res[i] = v1[i] - v2[i]
    }
    return res
}

function sum(v1, v2)
{
    
    if (v1.length !== v2.length)
    {
        console.log("[SUM] :: ERROR: v1.length ~= v2.length")
        return 0
    }

    let res = [...v1]
    for (let i = 0; i < v1.length; i++)
    {
        res[i] = v1[i] + v2[i]
    }
    return res
}

function get_mouse()
{
    return [mouseX, mouseY]
}

function cross(a, b)
{
    const res = [a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0]]
    return res
}

function test_is_unique(X)
{
    let res = false
    
    const UNIQUE_POINTS = get_unique_points(linhas)
    UNIQUE_POINTS.forEach(el => {
        if (JSON.stringify(el) === JSON.stringify(X))
        {
            res = true
        }
    })
    
    return res
}

function get_cross_points(linhas)
{
    let res = []
    for (let n = 0; n < linhas.length; n++)
    {
        const X = get_cross_mouse_line_to_right(linhas, n)
        
        // check point is unique
        let unique = test_is_unique(X)
        
        if (X.length)
        {
            // check if X exist in res
            let exist = false
            res.forEach(el => {
                if (JSON.stringify(el) === JSON.stringify(X))
                {
                    exist = true
                }
            })

            // if unique, add only once
            if (!(exist && unique))
            {
                res.push(X)
            } 
        }
    }
    
    return res
}

function render_cross(linhas)
{
    const X = get_cross_points(linhas)
    
    X.forEach(el => {
        circle(...el, 10)
    })
}

function get_cross_mouse_line_to_right(linhas, n) 
{
    // coordenadas homogeneas mouse
    let pmouse = get_mouse()
    const vm1 = [...pmouse, 1]
    const vm2 = sum(vm1, [1, 0, 0])
    const Lmouse = cross(vm1, vm2)

    // coordenadas homogeneas do segmento
    const seg = get_segment(linhas, n)
    const vl1 = [...seg[0], 1]
    const vl2 = [...seg[1], 1]
    const Llinha = cross(vl1, vl2)

    // cruzamento linhas
    const X_ = cross(Lmouse, Llinha)
    const X = [X_[0] / X_[2], X_[1] / X_[2]]

    // render ponto X
    const high = max(seg[0][1], seg[1][1])
    const low  = min(seg[0][1], seg[1][1])

    // check if cross is valid Y
    let res = []
    
    const c1 = (X[1] >= low) && (X[1] <= high) 
    const c2 = (X[0] > mouseX)

    if (c1 && c2)
    {
        res = X
    }

    return res
}

function get_segment(linhas, n)
{
    let i1 = n % linhas.length
    let i2 = (n + 1) % (linhas.length)

    return [linhas[i1], linhas[i2]]
}

function render_segments(seg)
{
    line(...seg[0], ...seg[1])
}

function test_segment_connection(seg1, seg2)
{
    const sig = ((seg1[1][1] - seg1[0][1]) * (seg2[1][1] - seg2[0][1])) > 0
    return sig
}

function render_connections(linhas)
{
    for (let i = 0; i < linhas.length; i++)
    {
        let seg1 = get_segment(linhas, i)
        let seg2 = get_segment(linhas, i + 1)
        
        let x1   = seg1[1]
        let x2   = seg2[0]
    
        // test signal points
        let sig = test_segment_connection(seg1, seg2)
        
        let cor = (sig) ? COLOR_GREEN : COLOR_ORANGE
        stroke(cor)
        circle(...x1, 20)
        circle(...x2, 10)
    }
}

function render_lines(linhas)
{
    if (linhas.length == 0)
    {
        return true
    }

    if (linhas.length == 1)
    {
        circle(...linhas[0], 5)
        return true
    }
    
    let el_ = linhas[0]
    circle(...el_, 5)
    for (let i = 1; i < linhas.length; i++)
    {
        let el = linhas[i]
        line(...el_, ...el)
        el_ = el
        circle(...el_, 5)
    }
    return true
}

function main()
{
    // render grid in canvas
    render_grid(100)
    
    // start with at least 3 points
    if (linhas.length < 3)
    {
        stroke(COLOR_GREEN)
        render_lines(linhas)
        return false
    }

    // show update IN/OUT
    // render cross with lines
    stroke(COLOR_BLUE)
    let X = get_cross_points(linhas)

    const status = (X.length % 2 == 0)

    // render polygon
    let weight = (status) ? 2 : 4
    let color  = (status) ?  COLOR_GREEN : COLOR_ORANGE
    stroke(color)
    strokeWeight(weight)
    render_polygon(linhas)
    
    // update mouse position
    text(`${mouseX}, ${mouseY}`, 10, 10, 80, 80)
    
    // render mouse
    if (show_render_mouse)
    {
        render_mouse(linhas)
    }
    
    // update closest continuously
    const poselements = get_pos_order(linhas)
    if (flag_inf_update)
    {
        linhas[poselements[0]] = get_mouse()
    }
    
    const p1 = poselements[0]
    let p2
    
    // check if vizinho esta dentro do cone
    const {pref, ptarg} = get_two_refs()
    const elref1 = get_element(linhas, pref) 
    const elref2 = get_element(linhas, ptarg)

    // render closest
    color  = (flag_select) ? COLOR_ORANGE:COLOR_BLUE
    weight = (flag_select) ? 4:2
    stroke(color)
    strokeWeight(weight)

    // console.log(pos1)
    circle(...elref1, 30)
    circle(...elref2, 30)
}

function get_two_refs() 
{
    const poselements = get_pos_order(linhas)
    const pref = poselements[0]

    const elref1 = get_element(linhas, pref)
    const elnext = get_element(linhas, pref + 1)
    const elback = get_element(linhas, pref - 1)

    const v1 = subtract(elnext, elref1)
    const v2 = subtract(elback, elref1)
    const ang = Math.acos((v1[0] * v2[0] + v1[1] * v2[1]) / calc_dist(v1) / calc_dist(v2)) * 180. / 3.1415926535897932484 / 2.

    const c1 = check_inside_cone(elref1, elnext, ang)

    let ptarg
    if (c1) {
        ptarg = pref + 1
    } else {
        ptarg = pref - 1
    }     

    return { pref, ptarg }
}

function rot(v, ang)
{
    let a   = ang * 3.1415926535897932384 / 180.
    let res = [v[0]*Math.cos(a) - v[1]*Math.sin(a), v[0]*Math.sin(a) + v[1]*Math.cos(a)]

    return res
}

function check_inside_cone(p0, ptarg, ang)
{
   // compute vector ref p0 -> ptarg
   const vref = subtract(ptarg, p0) 
   
   // compute vref with rot esq and dir
   const vref_dir = rot(vref, ang)
   const vref_esq = rot(vref, -ang)
    
   // compute vmouse p0 -> mouse
   const vmouse = subtract(get_mouse(), p0)
   
   // check if mouse is inside
   const c1 = cross(vmouse, vref_esq)[2] < 0
   const c2 = cross(vmouse, vref_dir)[2] > 0
   
   return (c1 && c2)
}

function print(msg)
{
    console.log(msg)
}

function calc_dist(v)
{
    return Math.sqrt(v[0]**2 + v[1]**2)
}

function get_pos_order(linhas)
{
    // calculate distances
    dist = []
    
    let v = []
    linhas.forEach(el => {
        v = subtract(el, get_mouse())
        dist.push((v[0]**2 + v[1]**2))
    })
    
    // ordenando valores
    const normal = [...dist]
    const sorted = dist.sort(function(a,b){return a-b})
    
    // calculando ordem vetor ordenado
    const order = []
    // console.log(sorted)
    for (let i = 0; i < sorted.length; i++)
    {
        order.push(normal.indexOf(sorted[i]))
    }
        
    return order
}


function get_element(linhas, pos)
{
    let i = pos
    
    let cont = 0

    while (i < 0)
    {
        i += linhas.length
        
        if (++cont > 100)
        {
            break
        }
    }
    
    return linhas[i%linhas.length]
}

function get_pos_closest(linhas)
{
    // if there is no position update
    let pos   = pos_
    
    if (flag_select)
    {
        return pos
    }

    // if there is update, keep the calculation
    let dist_ = Infinity

    for (let i = 0; i < linhas.length; i++)
    {
        // lendo elemento
        el = linhas[i]

        // calculando distancia ponto -> mouse
        let pmouse = get_mouse()
        let vec    = subtract(el, pmouse)
        let dist   = vec[0]**2 + vec[1]**2
        
        // atualizando distancia se `el` estiver mais prox
        if (dist_ > dist)
        {
            dist_ = dist
            pos   = i
        }
    }
    
    // atualizando closest
    pos_ = pos
    return pos
}

function get_pos_element(linhas, ponto)
{
    for(let i = 0; i < linhas.length; i++)
    {
        el = linhas[i]
        if (JSON.stringify(el) === JSON.stringify(ponto))
        {
            return el
        }
    }
    return -1
}

function add_new_element() 
{
    const {pref, ptarg} = get_two_refs()

    const pnew = (pref > ptarg) ? pref : ptarg

    const end = linhas.splice(pnew)
    const li  = [...linhas, get_mouse(), ...end]

    linhas = li
}

function delete_element()
{
    pos = get_pos_closest(linhas)
    linhas.splice(pos, 1)
}

function reset_keys()
{
    flag_inf_update = false
    flag_select = false
}

document.onkeydown = (e) => 
{
    const map = {
        'a': add_new_element,
        'c': () => console.log(linhas),
        'm': () => show_render_mouse = !show_render_mouse,
        'd': delete_element,
        'u': () => flag_inf_update = !flag_inf_update,
        's': () => flag_select = !flag_select,
        'Escape': reset_keys,
    }
    
    // const func = map[e.key]
    let func
    if (func = map[e.key])
    {
        func()
    }
}

document.onmousedown = (e) => 
{
    if (e.button == 0)
    {
        // compute distance
        const pos = get_pos_order(linhas)[0]
        const el = linhas[pos]
        const mo = get_mouse()
        const dist = calc_dist(subtract(el, mo))
        
        if (dist > 15) {
            return false
        };

        // update values
        flag_select = true
        flag_inf_update = true
    }
}

document.onmouseup = (e) => 
{
    if (e.button == 0)
    {
        flag_select = false
        flag_inf_update = false
    }
}

function draw() 
{
    // config inicial
    background(242)
    stroke(0)
    strokeWeight(2)
    
    // main function
    main()
}