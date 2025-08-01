#pragma once
#include "raylib.h"

class Button{
    private:
    Texture2D button;
    Vector2 position;
    public:
    Button(const char* imagepath, Vector2 position, float scale);
    void Draw() const;
    bool isPressed(Vector2 mousePos, bool mousePressed);
    ~Button();

};