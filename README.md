# Space_shooter_C-
Space Shooter Game in C++ using OOP

**Group Members**

Abdullah		24k-0859 (Group Leader)

Hammad		24k-0544

Abdul Majid		24k-0895

**Submission Date** 

11th May 2025 

**1\. Executive Summary** 

• **Overview**: A 2D space shooter game developed in C++ with Raylib, showcasing OOP principles. The game features:

- Polymorphic enemy classes (`EnemyLevel1`, `EnemyLevel2`, `EnemyLevel3`) with unique health/damage values.  
- Player controls (WASD/arrows), bullet firing (spacebar), and collision systems.  
- Dynamic UI (health bar, score) and game states (start menu, gameplay, win/loss screens).

• **Key Findings**: 

- Achieved polymorphism via abstract `Enemy` base class and virtual functions (`GetDamageOnCollision()`, `GetScoreValue()`).  
- Implemented resource management (textures, sounds) with RAII (e.g., `UnloadTexture` in destructors).  
- Used composition for `Player`\-`Bullet` interactions and aggregation for `Enemy` collections.

**2\. Introduction** 

• **Background**: The project demonstrates OOP concepts in game development, emphasizing:

- **Inheritance**: Enemy hierarchy (`Enemy` → `EnemyLevel1/2/3`).  
- **Encapsulation**: Private members (e.g., `Player::position`) with public methods.  
- **Polymorphism**: Enemy behaviors via overridden `Update()` and abstract methods.

• **Project Objectives**: 

- Build a modular game with scalable enemy/player systems.  
- Integrate Raylib for graphics/audio while maintaining clean OOP design.

**3\. Project Description** 

• **Scope**: 

- **Core Mechanics**:  
  * Player movement/shooting (`Player::FireBullet()`).  
  * Enemy spawning with difficulty scaling (score-based `EnemyLevel` selection).  
  * AABB collision detection (`CheckCollisionRecs`).  
- **Features**:  
  * Health system (`Player::TakeDamage()`).  
  * Explosion animations (sprite sheets).  
  * Scrolling background and sound effects.

• **Technical Overview**: 

- **Language**: C++17.  
- **Library**: Raylib 4.5 (graphics, audio, input).  
- **Toolchain**: Visual Studio Code (Windows).

**4\. Methodology** 

• **Approach**: 

- **Iterative Development**: Weekly sprints (player → enemies → UI → polish).  
- **Testing**: Unit tests for collision logic; playtesting for balance.

• **Roles and Responsibilities**: 

- **Abdullah** \- Enemy Class, Ship collision.  
- **Hammad**: Player Class, driver program.  
- **Abdul Majid**: Bullet Class, scoring, collision logic.

 **5\. Project Implementation** 

        • **Design and Structure**: The project follows a modular, object-oriented design with clear separation of responsibilities. The structure is organized into classes that handle specific game elements, ensuring maintainability and scalability. 

 **Class Hierarchy & Relationships**

- **Core Classes**:  
  * `Entity` **(Base Class)**:  
    * Provides common attributes (`position`, `speed`, `active` state).  
    * Inherited by `Player`, `Enemy`, and `Bullet` for shared functionality.  
  * `Player`:  
    * Handles movement (WASD/arrow keys), shooting (`FireBullet()`), and health management.  
    * Aggregates `Bullet` objects (composition).  
  * `Enemy` **(Abstract Base Class)**:  
    * Defines virtual methods (`GetDamageOnCollision()`, `GetScoreValue()`).  
    * Derived classes (`EnemyLevel1`, `EnemyLevel2`, `EnemyLevel3`) implement polymorphic behaviors.  
  * `Bullet`:  
    * Manages trajectory, collision, and active state.  
- **Utility Classes**:  
  * `Button`:  
    * Handles UI buttons (start, exit) with collision detection (`isPressed()`).  
    * Supports scaling and texture resizing.  
- **Game Flow**:  
  * **States**: Menu (`current_screen = 0`), Gameplay (`1`), Rules (`2`), Game Over (`3`), Win (`4`).  
  * **Game Loop**:  
    * **Update**: Processes input, collisions, and enemy spawning.  
    * **Render**: Draws textures, UI, and animations (60 FPS).

  • **Functionalities Developed**: 

 **1\. Player System**

- **Movement**:  
  * Smooth controls via `KEY_WASD` or arrow keys.  
  * Screen boundary checks (e.g., `position.x = clamp(0, screenWidth)`).  
- **Shooting**:  
  * Spacebar triggers `FireBullet()`, spawning bullets from player position.  
  * Bullets are managed in a `vector<Bullet>` with auto-cleanup (`DeleteInactiveBullets()`).  
- **Health & UI**:  
  * Health bar (visualized via `DrawHealthBar()`).  
  * Explosion animation on death (sprite sheet with frame tracking).

 **2\. Enemy System**

- **Polymorphic Enemies**:  
  * `EnemyLevel1`: 1 HP, 10 damage, 10 score.  
  * `EnemyLevel2`: 2 HP, 20 damage, 20 score.  
  * `EnemyLevel3`: 3 HP, 30 damage, 30 score.  
- **Spawning Logic**:  
  * Enemies spawn based on player score (e.g., `EnemyLevel2` at `score >= 100`).  
  * Randomized positions (`GetRandomValue()`).

 **3\. Collision & Combat**

- **Bullet-Enemy**:  
  * AABB collision (`CheckCollisionRecs`).  
  * Bullets deactivate on hit; enemies take damage (`TakeDamage()`).  
- **Player-Enemy**:  
  * Collision reduces player health by enemy-specific damage.  
  * Triggers explosion sound (`PlaySound(boom)`).

 **4\. UI & Game States**

- **Menu Screens**:  
  * Start, Rules, and Exit buttons (`Button` class).  
  * Scrolling background for visual polish.  
- **Win/Loss Conditions**:  
  * **Game Over**: `Player::health <= 0`.  
  * **Win**: `Player::score >= 500`.

 **5\. Resource Management**

- **Textures/Sounds**:  
  * Loaded on startup (`LoadTexture()`).  
  * Freed in destructors (e.g., `~Player()` unloads `img`, `explosionTexture`).  
- **Memory Safety**:  
  * Enemy objects stored in `vector<Enemy*>` with manual cleanup (`delete` in `ResetGame()`).

  • **Challenges Faced**: 

- **Collision Bugs**: Fixed iterator invalidation in `CheckForCollisions`.  
- **Texture Errors**: Validated asset paths via `LoadTexture` checks.

**6\. Results** 

• **Project Outcomes**: 

- Functional game with 3 enemy types, scoring, and health systems.  
- Achieved 60 FPS on mid-range hardware.  
    
    
    
  • **Screenshots and Illustrations**:   
  ![][image1]   
  ![][image2]  
  • **Testing and Validation**:   
- Validated enemy spawn logic (score thresholds: 100, 260).  
- Confirmed collision accuracy via debug logs. 

**7\. Conclusion** 

• **Summary of Findings**: Successfully applied OOP principles to create an engaging game. It provided experience in class hierarchy design, game logic.

• **Final Remarks**: This project deepened our understanding of C++, OOP and game development. Future improvements could include power ups, final boss enemies etc. 

