local fine = Texture(64,73)
local text = Texture(96,64)
local t

function Engine:Init()
    fine:LoadFile("thisisfine.png")
    text:LoadFile("thisisfine2.png")

    t = Font()
end

local buffers = { front = Texture(320,180), back = Texture(320,180) }
function swapBuffer()
    buffers.back, buffers.front = buffers.front, buffers.back
end

local clock = 0.0
function Engine:Update(deltaTime)
    math.sin(clock)
    clock = clock + deltaTime
    for x=0,319 do
        c = math.random(0,255)
        buffers.front:SetPixel(x, 179, c,c*0.5,0.0)
    end
    local r = math.random(-2,3)
    for x=0,319 do
        for y=0,179 do
            c = {r=0,g=0,b=0}
            r,g,b = buffers.front:GetPixel(x+math.random(0,1), y+math.random(0,1))
            c.r = r * 0.999
            c.g = g * 0.999
            c.b = b * 0.999
            buffers.back:SetPixel(x, y, c.r, c.g, c.b)
        end
    end
    Engine:Draw(buffers.front,0,0)
    Engine:Draw(fine, 120-32,100)
    Engine:Draw(text, 100,40+math.floor(math.sin(clock*4)*10))
    swapBuffer();
end


function Engine:OnKeyDown(key)
end


function Engine:OnKeyUp(key)
end