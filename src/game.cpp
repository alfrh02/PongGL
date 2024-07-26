#include "game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Game::setup() {
  /*
  glGenTextures(1, &texture0);
  glBindTexture(GL_TEXTURE_2D, texture0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load("assets/textures/concrete.png", &width, &height, &nrChannels, 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  */

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  box.setPosition(glm::vec2(100, 100));
  shader.use();
  shader.setMat4("u_Projection", projection);
  shader.setVec2("u_WindowDimensions", glm::vec2(window.width, window.height));
  shader2.use();
}

void Game::update(double deltaTime) {
  //box.setPosition(glm::vec2(sin(deltaTime), cos(deltaTime)));
  //box.setRotation(sin(deltaTime / 10) * 360);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  shader.use();
  if (q) {
    box.draw(shader, GL_POINTS);
  } else {
    box.draw(shader, GL_TRIANGLES);
  }
}

void Game::mouseMove(double x, double y) {
  //int w, h;
  //glfwGetWindowSize(window, &w, &h);
  //glClearColor(x/w, y/h, 0.0f, 1.0f);
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
