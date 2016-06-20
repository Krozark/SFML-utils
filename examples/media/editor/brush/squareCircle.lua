function getSelection(x1, y1, x2, y2)
    delta_x = x1 - x2
    delta_y = y1 - y2
    radius = math.floor(math.sqrt((delta_x * delta_x) + (delta_y * delta_y)) + 0.5)
    
    for y = y1 - radius, y1 + radius do
        for x = x1 - radius, x1 + radius do
            delta_x = x1 - x
            delta_y = y1 - y
            d = math.floor(math.sqrt((delta_x * delta_x) + (delta_y * delta_y)) + 0.5)
            if(d <= radius) then
                addToSelection(x,y)
            end
        end
    end
end

