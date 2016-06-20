hex = hex or {}

function hex.distance(x1, y1, x2, y2)
     radius = math.abs(x1 - x2) + math.abs(y1 - y2) + math.abs((-x1 - y1) - (-x2 - y2))
     return math.floor(radius / 2)
end

function hex.round(x,y)
    z = -y - x

    rx = math.floor(x + 0.5)
    ry = math.floor(y + 0.5)
    rz = math.floor(z + 0.5)

    diff_x = math.abs(rx - x)
    diff_y = math.abs(ry - y)
    diff_z = math.abs(rz - z)

    if (diff_x > diff_y) and (diff_x > diff_z) then
        rx = -ry - rz
    elseif (diff_y > diff_z) then
        ry = -rx - rz
    end

    return rx, ry
end

