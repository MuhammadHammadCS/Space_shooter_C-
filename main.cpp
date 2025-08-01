#include "C:\raylib\raylib\src\raylib.h"
#include <vector>
#include <string>
#include <ctime>
#include "iostream"
#include <cstdlib>
#include <algorithm>
#include "Player.hpp"
#include "Enemy.hpp"
#include "button.hpp"
using namespace std;

const int screenWidth = 900;
const int screenHeight = 900;
void ResetGame(Player &player, vector<Enemy *>& enemies, float &spawnTimer1);
int main()
{
    InitWindow(screenWidth, screenHeight, "Space Shooter Game");
    InitAudioDevice();
    SetTargetFPS(60);
    Texture2D background = LoadTexture("Graphics/back3.png");
    Texture2D startpage = LoadTexture("Graphics/start_page1.png");
    Button startbutton("Graphics/start.png", {330, 500}, 0.50);
    Button optionbutton("Graphics/rules.png", {330, 600}, 0.50);
    Button exitbutton("Graphics/exit.png", {330, 700}, 0.50);
    Button bckbutton("Graphics/bcksn.png", {0, 0}, 0.65);
    Button retry("Graphics/retry.png", {150, screenHeight / 2 + 100}, 0.50);
    Button exitbutton1("Graphics/exit.png", {450, screenHeight / 2 + 100}, 0.50);
    Texture2D spacebar = LoadTexture("Graphics/spacebar1.png");
    Texture2D up = LoadTexture("Graphics/up1.png");
    Texture2D down = LoadTexture("Graphics/down1.png");
    Texture2D right = LoadTexture("Graphics/right1.png");
    Texture2D left = LoadTexture("Graphics/left1.png");
    float bgY = 0;
    int current_screen = 0;
    float timePlayed = 0.0f;
    Player player;
    // bool isPlaying = false;
    // bool isGameOver = false;
    float spawnTimer = 0.0f; // Timer
    float spawnDelay = 1.0f; // 1.0f intial spawn logic so that enemies atay rahay even after score = 50
    vector<Enemy *> enemies;
    // 🔁 Main Game Loop
    Music music = LoadMusicStream("Sounds/game_bg.mp3");
    PlayMusicStream(music);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);

        if (timePlayed > 1.0f)
            timePlayed = 1.0f;
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(startpage, 0, 0, WHITE);
        startbutton.Draw();
        exitbutton.Draw();
        optionbutton.Draw();
        if (startbutton.isPressed(mousePosition, mousePressed))
        {
            current_screen = 1;
        }
        else if (exitbutton.isPressed(mousePosition, mousePressed) || exitbutton1.isPressed(mousePosition, mousePressed))
        {
            // UnloadTexture(background);
            // UnloadTexture(startpage);
            // CloseWindow();
            break;
        }
        else if (optionbutton.isPressed(mousePosition, mousePressed))
        {
            current_screen = 2;
        }
        else if (bckbutton.isPressed(mousePosition, mousePressed))
        {
            current_screen = 0;
        }
        if (retry.isPressed(mousePosition, mousePressed)) 
        {
            ResetGame(player, enemies, spawnTimer);
            current_screen = 1;
        }

        // if (player.GetHealth() <= 0)
        // {
        //     current_screen = 3;
        // }
        if (player.GetScore() >= 500)
        {
            current_screen = 4;
        }

        if (current_screen == 1)
        {
            bgY -= 2; // scrolling speed
            // Loop the background
            if (bgY <= -background.height)
            {
                bgY = 0;
            }
            ClearBackground(WHITE);
            DrawTexture(background, 0, (int)bgY, WHITE);
            DrawTexture(background, 0, (int)bgY + background.height, WHITE);
            // Update + Draw player
            player.update();
            player.Draw();

            // Update + Draw enemies
            if (player.IsAlive())
            {
                for (auto &enemy : enemies)
                {
                    enemy->Update();
                    enemy->Draw();
                }
            }

            // if (spawnTimer >= spawnDelay)
            // {
            //     float x = GetRandomValue(0, screenWidth - 60);
            //     float y = GetRandomValue(-600, -60);
            //     enemies.push_back(new EnemyLevel1(x, y));
            //     spawnTimer = 0.0f;
            // }

            // for further use
            //  if (player.IsAlive()) {
            //      spawnTimer += GetFrameTime();
            //      if (spawnTimer >= spawnDelay)
            //      {
            //          float x = GetRandomValue(0, screenWidth - 60);
            //          float y = GetRandomValue(-600, -60);
            //          enemies.push_back(Enemy(x, y));
            //          spawnTimer = 0.0f;
            //      }
            //  }
            spawnTimer += GetFrameTime();
            if (spawnTimer >= spawnDelay)
            {
                float x = GetRandomValue(0, screenWidth - 60);
                float y = GetRandomValue(-600, -60);

                Enemy *enemy;
                if (player.GetScore() >= 0 && player.GetScore() < 100)
                {
                    enemy = new EnemyLevel1(x, y);
                }
                else if (player.GetScore() >= 100 && player.GetScore() < 260)
                {
                    enemy = new EnemyLevel2(x, y);
                }
                else if (player.GetScore() >= 260)
                {
                    enemy = new EnemyLevel3(x, y);
                }

                enemies.push_back(enemy);
                spawnTimer = 0.0f;
            }
            for (auto &bullets : player.bullets)
            {
                bullets.Updateb();
                bullets.Drawb();
            }
            player.CheckForCollisions(enemies);
            player.DeleteInactiveBullets();
            if(!player.IsAlive())
            {
                DrawText("GAME OVER", screenWidth / 2 - 300, screenHeight / 2 - 150, 100, RED);
                DrawText(("YOUR SCORE: " + to_string(player.GetScore())).c_str(), screenWidth / 2 - 150, screenHeight / 2 - 50, 50, WHITE);
                retry.Draw();
                exitbutton1.Draw();
            }
            // std::cout << "Vector size: " << p1.bullets.size() << std::endl;
        }
        else if (current_screen == 2)
        {
            bgY -= 2; // scrolling speed
            // Loop the background
            if (bgY <= -background.height)
            {
                bgY = 0;
            }
            ClearBackground(WHITE);
            DrawTexture(background, 0, (int)bgY, WHITE);
            DrawTexture(background, 0, (int)bgY + background.height, WHITE);
            DrawText("\nRULES", screenWidth / 2, 0, 40, WHITE);
            bckbutton.Draw();
            DrawTexture(spacebar, 25, 100, WHITE);
            DrawText("FIRE", 400, 130, 30, WHITE);
            DrawTexture(up, 100, 200, WHITE);
            DrawText("GO UP", 300, 230, 30, WHITE);
            DrawTexture(down, 100, 300, WHITE);
            DrawText("GO DOWN", 300, 330, 30, WHITE);
            DrawTexture(right, 100, 400, WHITE);
            DrawText("GO RIGHT", 300, 430, 30, WHITE);
            DrawTexture(left, 100, 500, WHITE);
            DrawText("GO LEFT", 300, 530, 30, WHITE);
            DrawText("Enemy 1:\nScore by +10\nHealth by -10\n1 hit required\n", 600, 160, 30, WHITE);
            DrawText("Enemy 2:\nScore by +20\nHealth by -20\n2 hit required\n", 600, 300, 30, WHITE);
            DrawText("Enemy 3:\nScore by +30\nHealth by -30\n3 hit required\n", 600, 450, 30, WHITE);
            DrawText("Mission:\nTo win you need 500 score", 200, 600,30, WHITE);
        }
        // else if (current_screen == 3)
        // {
        //     bgY -= 2; // scrolling speed
        //     // Loop the background
        //     if (bgY <= -background.height)
        //     {
        //         bgY = 0;
        //     }
        //     ClearBackground(WHITE);
        //     DrawTexture(background, 0, (int)bgY, WHITE);
        //     DrawTexture(background, 0, (int)bgY + background.height, WHITE);
        //     DrawText("GAME OVER", screenWidth / 2 - 300, screenHeight / 2 - 150, 100, RED);
        //     DrawText(("YOUR SCORE: " + to_string(player.GetScore())).c_str(), screenWidth / 2 - 150, screenHeight / 2 - 50, 50, WHITE);
        //     retry.Draw();
        //     exitbutton1.Draw();
        // }
        else if (current_screen == 4)
        {
            bgY -= 2; // scrolling speed
            // Loop the background
            if (bgY <= -background.height)
            {
                bgY = 0;
            }
            ClearBackground(WHITE);
            DrawTexture(background, 0, (int)bgY, WHITE);
            DrawTexture(background, 0, (int)bgY + background.height, WHITE);
            DrawText("YOU WON!!!", screenWidth / 2 - 300, screenHeight / 2 - 150, 100, GREEN);
            retry.Draw();
            exitbutton1.Draw();
        }
        EndDrawing();
        
    }
    UnloadTexture(background);
    UnloadTexture(startpage);
    UnloadMusicStream(music); // Unload music stream buffers from RAM
    CloseAudioDevice();
    for (auto &enemy : enemies) 
    {
    delete enemy;
    }
    enemies.clear();
    CloseWindow();
    return 0;
}
void ResetGame(Player &player, vector<Enemy *>& enemies, float &spawnTimer1)
{
    SetTargetFPS(60);
    player.Reset(); // You must implement this in your Player class
    for (auto &enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
    spawnTimer1 = 0.0f;
}