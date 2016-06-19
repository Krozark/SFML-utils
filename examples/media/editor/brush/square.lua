function getSelection(x1, y1, x2, y2)
    for y = math.min(y1,y2), math.max(y1,y2) do
        for x = math.min(x1,x2), math.max(x1,x2) do
            addToSelection(x,y)
        end
    end
end

