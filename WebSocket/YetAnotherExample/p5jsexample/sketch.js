
let pos = {
    x: 0,
    y: 0
}

let target = {
    x: 0,
    y: 0
}

const SPEED = 0.05

function setup()
{
    createCanvas(windowWidth, windowHeight)
    
    background(0)
    noStroke()
    fill(255)
}

function draw()
{
    fill(0, 20)
    rect(0, 0, width, height)

    fill(255)
    circle(pos.x, pos.y, 20)
    
    // ease position into target
    pos.x += SPEED * (target.x - pos.x)
    pos.y += SPEED * (target.y - pos.y)
}

function mouseClicked()
{
    setTarget(mouseX, mouseY)
}

function setTarget(tx, ty) {
    target = {
        x: tx,
        y: ty
    }

}