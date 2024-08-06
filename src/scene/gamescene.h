#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"

class GameScene: public Scene {
  public:
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
};

#endif /* GAMESCENE_H */
