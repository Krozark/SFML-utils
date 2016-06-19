function bresenham(x1, y1,x2, y2)
    delta_x = x2 - x1
    ix = delta_x > 0 and 1 or -1
    delta_x = 2 * math.abs(delta_x)

    delta_y = y2 - y1
    iy = delta_y > 0 and 1 or -1
    delta_y = 2 * math.abs(delta_y)

    addToSelection(x1, y1)

    if delta_x >= delta_y then
        error = delta_y - delta_x / 2

        while x1 ~= x2 do
            if (error >= 0) and ((error ~= 0) or (ix > 0)) then
                error = error - delta_x
                y1 = y1 + iy
            end

            error = error + delta_y
            x1 = x1 + ix

            addToSelection(x1, y1)
        end
    else
        error = delta_x - delta_y / 2

        while y1 ~= y2 do
            if (error >= 0) and ((error ~= 0) or (iy > 0)) then
                error = error - delta_y
                x1 = x1 + ix
            end

            error = error + delta_x
            y1 = y1 + iy

            addToSelection(x1, y1)
        end
    end
end

function getSelection(x1, y1, x2, y2)
    bresenham(x1, y1, x2, y2)    
end
