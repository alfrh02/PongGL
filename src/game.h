#ifndef GAME_H
#define GAME_H

#include <math.h>
#include <stdlib.h>
#include <vector>
#include "graphics/window.h"
#include "entity/entity.h"

class Game {
  public:
    inline Game(Window w) {
      window = w;
      projection = glm::ortho(0.0f, (float)window.width, (float)window.height, 0.0f, -1.0f, 1.0f);
    }

    void setup();
    void update(double time, double deltaTime);
    void render();

    void mouseMove(double x, double y);
    void mouseScroll(double xoff, double yoff);
    void mousePress(int button, int mods);
    void mouseRelease(int button, int mods);
    void keyPress(int key, int mods);
    void keyRelease(int key, int mods);

    void windowResize(int width, int height);

  private:
    Window window;

    bool q = false;

    glm::mat4 projection;

    Shader shader = Shader("assets/shaders/vert.vert", "assets/shaders/frag.frag");
    Shader shader2 = Shader("assets/shaders/vert.vert", "assets/shaders/flatcolor.frag");

    Entity ball = Entity(glm::vec2(0), Mesh2D(CIRCLE, 16, glm::vec2(15.0f)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    Entity paddleLeft  = Entity(glm::vec2(0), Mesh2D(SQUARE, 0, glm::vec2(10, 150)));
    Entity paddleRight = Entity(glm::vec2(0), Mesh2D(SQUARE, 0, glm::vec2(10, 150)));

    std::vector<Entity> entities;
};

#endif /* GAME_H */
