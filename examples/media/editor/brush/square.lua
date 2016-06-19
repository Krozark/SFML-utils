function getSelection(x_min,x_max,y_min,y_max)
    for y = y_min, y_max, 1 do
        for x = x_min, x_max, 1 do
            addToSelection(x,y)
        end
    end
end

