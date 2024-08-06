#ifndef SCENE_H
#define SCENE_H

#include "../graphics/window.h"

class Scene {
  public:
    virtual void setup() {}
    virtual void update(double time, double deltaTime, unsigned long long frameCount) {}
    virtual void render() {}

    virtual void mouseMove(double x, double y) {}
    virtual void mouseScroll(double xoff, double yoff) {}
    virtual void mousePress(int button, int mods) {}
    virtual void mouseRelease(int button, int mods) {}
    virtual void keyPress(int key, int mods) {}
    virtual void keyRelease(int key, int mods) {}

    virtual void windowResize(int width, int height) {}

  protected:
    Window* window;
};

#endif /* SCENE_H */
