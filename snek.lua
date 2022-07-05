local buffers
local blurtable = {
    0.0, 0.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 6.0, 0.0,
}
local fine = Texture(64,73)
local text = Texture(96,64)

function Engine:Init()
    buffers = { front = Texture(320,240), back = Texture(320,240)}
    fine:LoadFile("thisisfine.png")
    text:LoadFile("thisisfine2.png")
end

function swapBuffer()
    buffers.back, buffers.front = buffers.front, buffers.back
end

local clock = 0.0
function Engine:Update(deltaTime)
    math.sin(clock)
    clock = clock + deltaTime
    for x=0,319 do
        c = math.random(0,255)
        buffers.front:SetPixel(x, 239, c,c*0.5,0.0)
    end
    local r = math.random(-2,3)
    for x=0,319 do
        for y=0,238 do
            c = {r=0,g=0,b=0}
            r,g,b = buffers.front:GetPixel(x+math.random(-1,1), y+math.random(0,3))
            c.r = r * 0.99
            c.g = g * 0.99
            c.b = b * 0.99
            buffers.back:SetPixel(x, y, c.r, c.g, c.b)
        end
    end
    Engine:Draw(buffers.front,0,0)
    Engine:Draw(fine, 120-32,239-70)
    Engine:Draw(text, 100,110+math.floor(math.sin(clock*4)*10))
    swapBuffer();
end


function Engine:OnKeyDown(key)
end


function Engine:OnKeyUp(key)
end