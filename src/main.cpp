#include <iostream>

#include "graphics/window.h"
#include "game.h"

Window window = createWindow();
Game game(window);

void mouseMove(GLFWwindow* window, double x, double y) {
  game.mouseMove(x, y);
}

void mouseScroll(GLFWwindow* window, double xoff, double yoff) {
  game.mouseScroll(xoff, yoff);
}

void processMouse(GLFWwindow* window, int button, int action, int mods) {
  if      (action == GLFW_PRESS)   game.mousePress(button, mods);
  else if (action == GLFW_RELEASE) game.mouseRelease(button, mods);
}

void processKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if      (action == GLFW_PRESS)   game.keyPress(key, mods);
  else if (action == GLFW_RELEASE) game.keyRelease(key, mods);
}

void processFramebufferSize(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  game.windowResize(width, height);
}

int main() {
  if (window.handle == NULL) {
    printf("Failed to initialise GLFWwindow\n");
    glfwTerminate();
    return -1;
  }

  setWindowCallbacks(window.handle, mouseMove, mouseScroll, processMouse, processKeyboard, processFramebufferSize);

  double oldTime = 0.0;
  game.setup();
  while (!glfwWindowShouldClose(window.handle)) {
    glfwPollEvents();
    game.update(glfwGetTime(), glfwGetTime() - oldTime);
    oldTime = glfwGetTime();
    game.render();
    glfwSwapBuffers(window.handle);
  }

  glfwTerminate();
}
