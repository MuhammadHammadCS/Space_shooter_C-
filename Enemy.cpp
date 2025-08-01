// #include "Enemy.hpp"
// const int screenWidth = 900;
// const int screenHeight = 900;

// Enemy::Enemy(float x, float y)
//     {
//         img = LoadTexture("Graphics/enemy.png");
//         position = { x, y };
//         speed = 2.5f;
//         active = true;
//     }

//     void Enemy::Update() {
//         position.y += speed;

//         // Reset if off-screen or deactivate (optional logic)
//         if (position.y > screenHeight) {
//             position.y = -img.height;
//             position.x = GetRandomValue(0, screenWidth - img.width);
//         }
//     }

//     void Enemy::Draw() const
//     {
//         if (active)
//         {
//             DrawTextureV(img, position, WHITE);
//         }
//     }

//     Rectangle Enemy::GetRect()
//     {
//         return { position.x, position.y, (float)img.width, (float)img.height};
//     }

//     void Enemy::Deactivate() { active = false; }
//     bool Enemy::IsActive() const { return active; }

//     // Enemy::~Enemy()
//     // {
//     //     UnloadTexture(img);
//     // }


#include "Enemy.hpp"
const int screenWidth = 900;
const int screenHeight = 900;

// Base Enemy Constructor
Enemy::Enemy(float x, float y)
{
    position = { x, y };
    speed = 2.5f;
    active = true;
    // health = 1;  // Default health
}

void Enemy::Update()
{
    position.y += speed;
    if (position.y > screenHeight) {
        position.y = -img.height;
        position.x = GetRandomValue(0, screenWidth - img.width);
    }
}

void Enemy::Draw() const
{
    if (active)
    {
        DrawTextureV(img, position, WHITE);
    }
}

Rectangle Enemy::GetRect()
{
    return { position.x, position.y, (float)img.width, (float)img.height };
}

void Enemy::Deactivate() { active = false; }

bool Enemy::IsActive() const { return active; }

void Enemy::TakeDamage(int damage) 
{
    health -= damage;
    if (health <= 0) {
        Deactivate();
    }
}

// --- Level 1 Enemy ---
EnemyLevel1::EnemyLevel1(float x, float y) : Enemy(x, y)
{
    img = LoadTexture("Graphics/enemy.png");
    health = 1;  // Level 1 enemies die after 1 hit
}

void EnemyLevel1::Update() 
{
    Enemy::Update();  // Use base class update
}



// --- Level 2 Enemy ---
EnemyLevel2::EnemyLevel2(float x, float y) : Enemy(x, y)
{
    img = LoadTexture("Graphics/enemy1.png");
    health = 2;  // Level 2 enemies die after 2 hits
}

void EnemyLevel2::Update()
{
    Enemy::Update();  // Use base class update
}



// --- Level 3 Enemy ---
EnemyLevel3::EnemyLevel3(float x, float y) : Enemy(x, y)
{ 
    img = LoadTexture("Graphics/enemy2.png");
    health = 3;  // Level 3 enemies die after 3 hits
}

void EnemyLevel3::Update()
{
    Enemy::Update();  // Use base class update
}

Enemy::~Enemy()
{
    UnloadTexture(img);
}