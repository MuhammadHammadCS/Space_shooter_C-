#pragma once
#include <raylib.h>

class Bullet {
    private:
        Vector2 position;
        int speed;
        Texture2D b;
        bool active;
    public:
        Bullet(Vector2 position, float speed);
        void Updateb();
        void Drawb();
        Rectangle GetRect();
        bool isActive() const { return active; }
        void deactivate() { active = false; }
};