#include "Player.hpp"
#include "Enemy.hpp"
#include "algorithm"
using namespace std;
const int screenWidth = 900;
const int screenHeight = 900;
    Player::Player()
    {
        img = LoadTexture("Graphics/ship.png");
        position.x = 400;
        position.y = 800;
        speed = 7.0f;
        health = 100;
        score = 0;
        isAlive = true;
        explosionTexture = LoadTexture("Graphics/explosion.png"); // make sure this exists
        //position = {300, 650};
    }
    void Player::update()
    {

        if (!isAlive)
        {
            explosionFrameCounter++;
            if (explosionFrameCounter >= 10) 
            {
                explosionFrame++;
                explosionFrameCounter = 0;
            }
            if (explosionFrame >= 5) 
            {
                explosionFrame = 4;
            }
            return; // Skip movement and firing when dead
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            position.x -= speed;
        }
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            position.x += speed;
        }
        else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            position.y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            position.y += speed;
        }
        if(IsKeyPressed(KEY_SPACE))
        {
            FireBullet();
            PlaySound(hit);
        }

        if (position.x < 0)
        {
            position.x = 0;
        }
        if (position.x + img.width > screenWidth)
        {
            position.x = screenWidth - img.width;
        }
        if (position.y + img.height > screenHeight)
        {
            position.y = screenHeight - img.height;
        }
        if (position.y < 0)
        {
            position.y = 0;
        }
        // if (health <= 0) 
        // {
        //     // Game over logic, maybe change screen or stop game
        // }

    };

    void Player::DrawHealthBar() const {
        float barWidth = 75;
        float barHeight = 10;
        float x = position.x + img.width - 20;
        float y = position.y + 10; // just above the ship

        float healthPercent = (float)health / 100;

        DrawRectangle(x, y, barWidth, barHeight, RED); // Background (empty)
        DrawRectangle(x, y, barWidth * healthPercent, barHeight, GREEN); // Current health
        DrawRectangleLines(x, y, barWidth, barHeight, BLACK); // Outline
    }

    void Player::Draw() const
    {
        // DrawTextureV(img, position, WHITE);
        // string heal = "Health : " + to_string(health);
        // DrawText(heal.c_str(), 20, 20, 30, GREEN);
        // DrawHealthBar();
        // DrawText(("Score : " + to_string(score)).c_str(), screenWidth - 180, 20, 30, YELLOW);

        if (isAlive) 
        {
            DrawTextureV(img, position, WHITE);
            DrawHealthBar();
        } 
        else if(!isAlive)
        {
            // Explosion animation (assuming 5 horizontal frames, update as needed)
            int frameWidth = explosionTexture.width / 5;
            int frameHeight = explosionTexture.height;
            Rectangle srcRec = { (float)(explosionFrame * frameWidth), 0, (float)frameWidth, (float)frameHeight };
            Rectangle destRec = { position.x, position.y, (float)frameWidth, (float)frameHeight };
            DrawTexturePro(explosionTexture, srcRec, destRec, {0, 0}, 0.0f, WHITE);
        }
    
        // UI
        if (isAlive) 
        {
            string heal = "Health : " + to_string(health);
            DrawText(heal.c_str(), 20, 20, 30, GREEN);
            DrawText(("Score : " + to_string(score)).c_str(), screenWidth - 180, 20, 30, YELLOW);
        } 
        // else 
        // {
        //      DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2, 40, RED);
        // }

    };

    //getter for isAlive
    bool Player::IsAlive()
    { 
        return isAlive; 
    }

    void Player::FireBullet()
    {
        bullets.push_back(Bullet({ position.x + img.width / 2 - 2, position.y }, -6.0));
    }

    void Player::DeleteInactiveBullets()
    {
        for(auto it = bullets.begin(); it!= bullets.end();)
        {
            //Deletes the inactive bullets (the one out of the screen)
            if(!it -> isActive())
            {
                it = bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    Rectangle Player::GetRect()
    {
        return {position.x, position.y, (float)img.width, (float)img.height};
    }

    void Player::CheckForCollisions(vector<Enemy*>& enemies)
    {
        for(auto& bullet: bullets)
        {
            auto it = enemies.begin();
            while(it != enemies.end())
            {
                //Checks for the collision and deletes the enemy
                if(CheckCollisionRecs((*it)->GetRect(), bullet.GetRect())) // The issue is it is an iterator to a pointer (Enemy*), so it->GetRect() is incorrect. it-> tries to access a member of the iterator itself. Since the iterator points to a pointer, you need to dereference it first
                {
                    // it = enemies.erase(it);
                    // bullet.deactivate();
                    // AddScore(10);
                    (*it)->TakeDamage(1); // Apply 1 damage
                    bullet.deactivate();

                    if (!(*it)->IsActive()) 
                    {
                        if (!(*it)->IsActive()) 
                        {
                            AddScore((*it)->GetScoreValue()); // ✅ Now adds correct score based on enemy type
                            delete *it;
                            it = enemies.erase(it);  // Only erase if dead
                        }
                        // delete *it;
                        // it = enemies.erase(it);  // Only erase if dead
                    } 
                    else 
                    {
                        ++it;
                    }

                    break; // Exit after handling this collision
                }
                else
                {
                    ++it;
                }
            }
        }
        //deletes the bullet after hitting the enemy
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                           [](const Bullet& b) { return !b.isActive(); }),
            bullets.end()
        );

        auto it = enemies.begin();
        while (it != enemies.end())
        {
            if (CheckCollisionRecs((*it)->GetRect(), GetRect()))
            {
                // TakeDamage(10); // Reduce health by 10
                // it = enemies.erase(it); // Destroy enemy
                PlaySound(boom);
                TakeDamage((*it)->GetDamageOnCollision()); // Reduce health by 10
                it = enemies.erase(it); // Destroy enemy
            }
            else
            {
                ++it;
            }
        }
    }

    void Player::TakeDamage(int dmg)
    {
        health -= dmg;
        if (health <= 0 && isAlive) 
        {
            // vector<Enemy*> enemies;
            health = 0;
            isAlive = false;
            explosionFrame = 0;
            explosionFrameCounter = 0;
            // enemies.clear();
        }

    }

    Vector2 Player::GetPosition() 
    {
        return { position.x , position.y };
    };

    int Player::GetHealth()
    {
        return health;
    }

    void Player::AddScore(int points)
    {
        score += points;
    }

    int Player::GetScore() const {
        return score;
    }

    // void Player::TakeDamage(int dmg)
    // {
    //     health -= dmg;
    // }
    void Player::Reset() {
    health = 100;
    score = 0;
    position = {450, 800}; // or wherever the start pos is
    bullets.clear();
    // Reset any other necessary state
    isAlive = true;
    }

    Player::~Player()
    {
        UnloadTexture(img);
        UnloadTexture(explosionTexture);
        UnloadSound(hit);
        UnloadSound(lose);
    }