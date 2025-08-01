// #pragma once
// #include "raylib.h"

// class Enemy
// {
//     private:
//     Vector2 position;
//     float speed;
//     Texture2D img; 
//     bool active;

//     public:
//     Enemy(float x, float y);
//     void Update();
//     void Draw() const;
//     Rectangle GetRect();
//     void Deactivate();
//     bool IsActive() const;
// };



#pragma once
#include "raylib.h"

class Enemy
{
protected:
    Vector2 position;
    float speed;
    Texture2D img;
    bool active;
    int health;

public:
    Enemy(float x, float y);  // Base constructor
    virtual void Update();  // Update enemy logic
    virtual void Draw() const;
    Rectangle GetRect();  // Collision box for enemy
    void Deactivate();
    bool IsActive() const;
    void TakeDamage(int damage);  // Take damage from bullets

    virtual int GetDamageOnCollision() const = 0;  // Abstract function to get damage on collision
    virtual int GetScoreValue() const = 0;

    virtual ~Enemy();
};

// Level 1 Enemy
class EnemyLevel1 : public Enemy
{
public:
    EnemyLevel1(float x, float y);
    void Update() override;
    int GetDamageOnCollision() const override { return 10; }  // Health damage for level 1
    int GetScoreValue() const override { return 10; }
};

// Level 2 Enemy
class EnemyLevel2 : public Enemy
{
public:
    EnemyLevel2(float x, float y);
    void Update() override;
    int GetDamageOnCollision() const override { return 20; }  // Health damage for level 2
    int GetScoreValue() const override { return 20; }
};

// Level 3 Enemy
class EnemyLevel3 : public Enemy
{
public:
    EnemyLevel3(float x, float y);
    void Update() override;
    int GetDamageOnCollision() const override { return 30; }  // Health damage for level 3
    int GetScoreValue() const override { return 30; }
};