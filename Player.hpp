#pragma once 
#include "raylib.h"
#include "iostream"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <vector>

using namespace std;
class Player
{
    private:
    Vector2 position;
    float speed;
    Texture2D img;
    int health;
    int score;
    Texture2D explosionTexture;
    bool isAlive;
    int explosionFrame = 0;
    int explosionFrameCounter = 0;

    public:
    Player();
    ~Player();
    Sound hit = LoadSound("Sounds/laser.mp3");
    Sound lose = LoadSound("Sounds/xpSound.mp3");
    Sound boom = LoadSound("Sounds/boom1.mp3");
    void update();
    void DrawHealthBar() const;
    void Draw() const;
    Vector2 GetPosition();
    int GetHealth();
    bool IsAlive();
    void AddScore(int score);
    int GetScore() const;
    void TakeDamage(int dmg);
    vector<Bullet> bullets;
    void FireBullet();
    Rectangle GetRect();
    void Reset();
    void CheckForCollisions(std::vector<Enemy*>& enemies);
    void DeleteInactiveBullets();
    
};