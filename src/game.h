#ifndef GAME_H
#define GAME_H

#include <math.h>
#include <stdlib.h>
#include <vector>
#include "graphics/window.h"
#include "entity/entity.h"

#define PADDLE_SIZE  60
#define PADDLE_SPEED 250.0f
#define BALL_SPEED   300.0f

class Game {
  public:
    inline Game(Window w) {
      window = w;
      projection = glm::ortho(0.0f, (float)window.width, (float)window.height, 0.0f, -1.0f, 1.0f);
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

    void resetBall(Entity& entity, bool left);

  private:
    Window window;

    bool debug = false;

    glm::mat4 projection;

    Shader shader = Shader("assets/shaders/vert.vert", "assets/shaders/frag.frag");

    struct Player {
      Entity paddle = Entity(glm::vec2(0), Mesh2D(SQUARE, 0, glm::vec2(10, PADDLE_SIZE)));
      ushort score = 0;
    };

    Player leftPlayer;
    Player rightPlayer;

    Entity ball = Entity(glm::vec2(0), Mesh2D(CIRCLE, 16, glm::vec2(15.0f)));
};

#endif /* GAME_H */
