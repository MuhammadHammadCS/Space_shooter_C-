#include "button.hpp"

Button::Button(const char* imagepath, Vector2 position, float scale)
{
    Image image = LoadImage(imagepath);
    int oWidth = image.width;
    int oHeight = image.height;

    int newWidth = static_cast<int>(oWidth * scale);
    int newHeight = static_cast<int>(oHeight * scale);

    ImageResize(&image , newWidth , newHeight);
    button = LoadTextureFromImage(image);
    UnloadImage(image);
    this->position = position;
}

void Button:: Draw() const{
    DrawTextureV(button,position,WHITE);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect = {position.x , position.y , static_cast<float>(button.width) , static_cast<float>(button.height)};
    if(CheckCollisionPointRec(mousePos, rect) && mousePressed)
    {
        return true;
    }
    return false;
}

Button::~Button()
{
    UnloadTexture(button);
}