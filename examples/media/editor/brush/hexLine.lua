require "hexMath"

function getSelection(x1, y1, x2, y2)
    d = hex.distance(x1,y1,x2,y2) * 1.0


    delta_x = (x2 - x1)/d
    delta_y = (y2 - y1)/d

    for i = 0,d do
        x = x1 + delta_x * i
        y = y1 + delta_y * i
        x , y = hex.round(x,y)

        addToSelection(x,y)
    end
end
