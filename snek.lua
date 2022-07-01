-- Testing

print("Engine Version: "..Engine["version"])

player = {
    pos = {100, 100},
    vel = {1, 0},
    size = 10,
    dead = false,
    segments = {},
}

function Engine:Init()
    print("Initializing Snek Game")
    for x = 0,319 do
        for y = 0,239 do
            Engine:SetPixel(x,y,0,0,0);
        end
    end
    for x=0,319 do
        Engine:SetPixel(x, 0, 128, 255, 255);
        Engine:SetPixel(x, 239, 128, 255, 255);
    end
    for y=0,239 do
        Engine:SetPixel(0, y, 128, 255, 255);
        Engine:SetPixel(319, y, 128, 255, 255);
    end

    Engine:SetPixel(120, 120, 255, 128, 128);
    player = {
        pos = {100, 100},
        vel = {1, 0},
        size = 10,
        dead = false,
        segments = {},
    }
end


function AddApple()
    x = math.random(0,320)
    y = math.random(0,240)
    Engine:SetPixel(x, y, 255, 128, 128);
end
respawnTimer = 2.0


function Engine:Update(deltaTime)
    if player.dead then
        respawnTimer = respawnTimer - deltaTime
        if respawnTimer > 0 then return end
        Engine:Init()
    end
    player.pos[1] = player.pos[1] + player.vel[1]
    player.pos[2] = player.pos[2] + player.vel[2]

    table.insert(player.segments, {player.pos[1], player.pos[2]})
    if #player.segments > player.size then
        local pos = table.remove(player.segments, 1)
        Engine:SetPixel(pos[1], pos[2], 0, 0 ,0)
    end

    r,g,b = Engine:GetPixel(player.pos[1], player.pos[2])

    -- Apple
    if (r == 255 and g == 128 and b == 128) then
        AddApple()
        player.size = player.size + 10
    end

    if (r == 255 and g == 255 and b == 255) or (r == 128 and g == 255 and b == 255) then
        player.dead = true
        respawnTimer = 2.0
        for _=0,10 do
            x = math.random(player.pos[1]-4,player.pos[1]+4)
            y = math.random(player.pos[2]-4,player.pos[2]+4)
            Engine:SetPixel(x,y, 255,0,0)
        end
    end
    Engine:SetPixel(player.pos[1], player.pos[2], 255,255,255)
end


function Engine:OnKeyDown(key)
    if key == 0 then player.vel = {-1,0} end
    if key == 3 then player.vel = {1,0} end
    if key == 22 then player.vel = {0,-1} end
    if key == 18 then player.vel = {0,1} end
end


function Engine:OnKeyUp(key)
end