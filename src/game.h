#ifndef GAME_H
#define GAME_H

#include <math.h>
#include <stdlib.h>
#include <vector>
#include "graphics/window.h"
#include "entity/entity.h"
#include "scene/gamescene.h"

#define PADDLE_SIZE       60
#define PADDLE_SPEED      250.0f
#define BALL_SPEED        250.0f
#define BALL_RESOLUTION   12
#define BALL_WINDUP_SPEED 8 // amount of pixels BALL_SPEED increases by per second
#define RESET_MARGIN      200

// NO COMPUTER
//#define NO_COMPUTER

// EASY
//#define AI_FRAMERATE 0.3

// MEDIUM
#define AI_FRAMERATE 0.15
#define AI_CENTRES_SELF

// HARD
//#define AI_FRAMERATE 0.1
//#define AI_CENTRES_SELF

// IMPOSSIBLE
//#define AI_FRAMERATE 0.1
//#define AI_CENTRES_SELF

class Game {
  public:
    inline Game(Window w) {
      m_Window = w;
    }
    ~Game();

    void setup();
    void update(double time, double deltaTime, unsigned long long frameCount);
    void render();

    void mouseMove(double x, double y);
    void mouseScroll(double xoff, double yoff);
    void mousePress(int button, int mods);
    void mouseRelease(int button, int mods);
    void keyPress(int key, int mods);
    void keyRelease(int key, int mods);

    void windowResize(int width, int height);

  private:
    void resetBall(Entity& entity, bool left);

    double m_Time, m_DeltaTime;
    unsigned long long m_FrameCount;

    Window m_Window;

    bool m_Debug = false, m_Paused = false, m_Rainbow = false;

    Shader m_Shader = Shader("assets/shaders/vert.vert", "assets/shaders/frag.frag");

    struct Player {
      Entity paddle = Entity(glm::vec2(0), Mesh2D(SQUARE, 0, glm::vec2(10, PADDLE_SIZE)));
      ushort score = 0;
    };

    Player m_LeftPlayer;
    Player m_RightPlayer;

    Entity m_Ball = Entity(glm::vec2(0), Mesh2D(CIRCLE, BALL_RESOLUTION, glm::vec2(15.0f)));
};

#endif /* GAME_H */
