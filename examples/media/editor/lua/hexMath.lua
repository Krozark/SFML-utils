hex = hex or {}

function hex.distance(x1, y1, x2, y2)
     radius = math.abs(x1 - x2) + math.abs(y1 - y2) + math.abs((-x1 - y1) - (-x2 - y2))
     return math.floor(radius / 2 + 0.5)
end
