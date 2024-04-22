const PI = 3.1415926535897932384
const r1 = 130
const r2 = 100
const r3 = 40
const m1 = 40
const m2 = 15
const m3 = 15
let a1 = PI/4
let a2 = PI/8
let a3 = PI/8

let path2 = []
let path3 = []
const speed_factor = 2

function setup()
{
    createCanvas(600, 600)
}

function draw() 
{
    background(242)
    
    stroke(0)
    strokeWeight(2)

    a1 += 0.011 * speed_factor
    a2 -= 0.036 * speed_factor
    a3 += 0.054 * speed_factor

    translate(300, 300)
    
    let x1 = r1 * sin(a1)
    let y1 = r1 * cos(a1)

    let x2 = x1  + r2 * sin(a2)
    let y2 = y1  + r2 * cos(a2)

    let x3 = x2  + r3 * sin(a3)
    let y3 = y2  + r3 * cos(a3)

    line(0,0,x1,y1)
    fill(0)
    ellipse(x1, y1, m1, m1)

    line(x1,y1,x2,y2)
    ellipse(x2, y2, m2, m2)
    
    line(x2,y2,x3,y3)
    ellipse(x3, y3, m3, m3)

    path2.push([x2, y2])
    path3.push([x3, y3])
    
    // stroke(88)
    // let x_ = path2[0][0]
    // let y_ = path2[0][1]

    // for (let index = 0; index < path2.length; index++) {
    //     const pos = path2[index];
    //     line(pos[0], pos[1], x_, y_)
    //     x_ = pos[0]
    //     y_ = pos[1]
        
    // }
    
    stroke(102)
    x_ = path3[0][0]
    y_ = path3[0][1]
    for (let index = 0; index < path3.length; index++) {
        const pos = path3[index];
        line(pos[0], pos[1], x_, y_)
        x_ = pos[0]
        y_ = pos[1]
        
    }
    // line(mouseX, mouseY, pmouseX, pmouseY);
}