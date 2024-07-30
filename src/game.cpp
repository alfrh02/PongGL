#include "game.h"

void Game::setup() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  box.setPosition(glm::vec2(100, 100));
  box.loadTexture("assets/textures/concrete.png");
  shader.use();
  shader.setMat4("u_Projection", projection);
  shader.setVec2("u_WindowDimensions", glm::vec2(window.width, window.height));
  shader2.use();
}

void Game::update(double deltaTime) {

}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  shader.use();
  shader.setInt("u_Texture", 0);
  if (q) {
    box.draw(shader, GL_POINTS);
  } else {
    box.draw(shader, GL_TRIANGLES);
  }
}

void Game::mouseMove(double x, double y) {

}

void Game::mouseScroll(double xoff, double yoff) {

}

void Game::mousePress(int button, int mods) {

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
