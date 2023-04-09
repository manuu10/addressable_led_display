class Vec2i
{
public:
    int x;
    int y;
    Vec2i add(Vec2i other)
    {
        return {
            x : x + other.x,
            y : y + other.y
        };
    }
    bool inScreenBounds(int xMax, int yMax)
    {
        return x >= 0 && y >= 0 && y < yMax && x < xMax;
    }
    bool outOfRightEdge(int xMax)
    {
        return x >= xMax;
    }
    bool outOfBottomEdge(int yMax)
    {
        return y >= yMax;
    }
    bool outOfLeftEdge()
    {
        return x < 0;
    }
    bool outOfTopEdge()
    {
        return y < 0;
    }
};