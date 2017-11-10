require "hexMath"

function getSelection(x1, y1, x2, y2)
    radius = hex.distance(x1,y1,x2,y2)

    for dx = -radius, radius do
        for dy = math.max(-radius,-dx - radius), math.min(radius,-dx + radius) do
            addToSelection(x1 + dx,y1 + dy)
        end
    end
end

