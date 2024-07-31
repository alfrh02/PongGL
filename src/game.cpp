#include "game.h"

void Game::setup() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  entity.setPosition(glm::vec2(100, 100));
  shader.use();
  shader.setMat4("u_Projection", projection);
  shader2.use();
}

void Game::update(double time, double deltaTime) {
  entity.setColor(glm::vec4(sin(time), cos(time), sin(deltaTime/2), 1.0f));
  //entity.setDirection(glm::vec2(sin(time), cos(time)));
  entity.update(deltaTime);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  shader.use();
  shader.setInt("u_Texture", 0);
  if (!q) {
    entity.draw(shader);
  } else {
    entity.draw(shader);
    entity.drawDebug(shader);
  }
}

void Game::mouseMove(double x, double y) {

}

void Game::mouseScroll(double xoff, double yoff) {

}

void Game::mousePress(int button, int mods) {
  double x, y;
  glfwGetCursorPos(window.handle, &x, &y);
  entity.setDirection(glm::vec2(x, y) - entity.getPosition());
}

void Game::mouseRelease(int button, int mods) {

}

void Game::keyPress(int key, int mods) {
  if (key == GLFW_KEY_Q) {
    q = !q;
  }
}

void Game::keyRelease(int key, int mods) {

}

void Game::windowResize(int width, int height) {
  window.width  = width;
  window.height = height;
  projection = glm::ortho(0.0f, (float)window.width, (float)window.height, 0.0f, -1.0f, 1.0f);
  shader.use();
  shader.setMat4("u_Projection", projection);
  shader2.use();
};
