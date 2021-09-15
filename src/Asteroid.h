#include "SoundBoard.h"

class Asteroid
{

public:
    Asteroid(
        Vector2 position,
        Vector2 vel,
        SoundBoard *soundBoard,
        float spin,
        int size) : pos(position), velocity(vel), spin(spin), rotation(spin), size(size), sounds(soundBoard)
    {
    }
    Vector2 pos{};
    bool isAlive() const { return alive; }
    void explode()
    {
        alive = false;
        sounds->boom();
        explosion.explode(pos);
    }

    Rectangle getCollisionRec()
    {
        return collisionRecFromCenter(pos, size * 0.7);
    }

    void update()
    {
        if (alive)
        {
            rotation += spin;
            pos = Vector2Add(pos, velocity);
        }
        else
        {
            explosion.update();
        }
    }
    void draw()
    {
        if (alive)
        {

            DrawPoly(pos, 7, size, rotation, BLUE);
            if (SHOW_COLLISION_RECTS)
            {
                DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
            }
        }else{
            explosion.draw();
        }
    }

private:
    Vector2 velocity{};
    int spin{};
    int rotation{};
    int size{};
    bool alive{true};
    SoundBoard *sounds;
    Explosion explosion{BLUE};
};
