# Barely (a) Game Engine

> *Great things are done by a series of small things brought together.*
>
>*-Vincent Van Gogh*

Very simple game engine that runs games written in Lua.

## Tech

- SFML 2.5
- C++ 17
- Lua 5.4

## Documentation

```lua
-- Engine:Init() is called when the engine is started.
function Engine:Init() end

-- Engine::Update is run every frame
-- deltaTime is time lapsed since last frame in seconds.
function Engine:Update(deltaTime) end

-- Engine:OnKeyDown is called when a key on keyboard is pressed,
-- key is the key code
function Engine:OnKeyDown(key) end

-- Engine:OnKeyDown is called when a key on keyboard is released,
-- key is the key code
function Engine:OnKeyUp(key) end

-- Engine:l_SetPixel(x, y, r, g, b) sets the pixel on cordinates x,y
-- with color r,g,b.
Engine:l_SetPixel(x, y, r, g, b)

--- Engine:l_GetPixel(x, y) returns colors r,g,b of the pixel at x,y.
r, g, b = Engine:l_GetPixel(x, y)
```
