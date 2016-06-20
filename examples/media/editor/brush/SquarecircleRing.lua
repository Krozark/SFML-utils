function drawcircle(x0, y0, radius)
    x = radius;
    y = 0;
    err = 0;

    while (x >= y) do

        addToSelection(x0 + x, y0 + y);
        addToSelection(x0 + y, y0 + x);
        addToSelection(x0 - y, y0 + x);
        addToSelection(x0 - x, y0 + y);
        addToSelection(x0 - x, y0 - y);
        addToSelection(x0 - y, y0 - x);
        addToSelection(x0 + y, y0 - x);
        addToSelection(x0 + x, y0 - y);

        y = y + 1;
        err = err + 1 + 2*y;
        if 2*(err-x) + 1 > 0 then
        
            x = x -1;
            err = err + 1 - 2*x;
        end
    end
end

function getSelection(x1, y1, x2, y2)
    delta_x = x1 - x2
    delta_y = y1 - y2

    radius = math.floor(math.sqrt((delta_x * delta_x) + (delta_y * delta_y)) + 0.5)
    drawcircle(x1,y1,radius)
end

