local f = io.open("green.bmp", "rb")


if f ~= nil then 
    while (true) do
        local b = f:read("a")
        print(b)
    end
end
