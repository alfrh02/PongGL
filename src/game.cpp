#include "game.h"

#define PI      3.14159265359
#define TWO_PI  (3.14159265359*2)
#define HALF_PI (3.14159265359/2)

void Game::setup() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  ball.setPosition(glm::vec2(100, 100));
  paddleLeft.setPosition(glm::vec2(100, window.height/2));
  paddleRight.setPosition(glm::vec2(window.width-100, window.height/2));
  shader.use();
  shader.setMat4("u_Projection", projection);
  shader2.use();
}

void Game::update(double time, double deltaTime) {
  ball.update(deltaTime);
  paddleLeft.update(deltaTime);
  paddleRight.update(deltaTime);

  if (paddleLeft.getPosition().y > window.height-100) {
    paddleLeft.setPosition(glm::vec2(paddleLeft.getPosition().x, window.height-100));
  } else if (paddleLeft.getPosition().y < 100) {
    paddleLeft.setPosition(glm::vec2(paddleLeft.getPosition().x, 100));
  }

  if (paddleRight.getPosition().y > window.height-100) {
    paddleRight.setPosition(glm::vec2(paddleRight.getPosition().x, window.height-100));
  } else if (paddleRight.getPosition().y < 100) {
    paddleRight.setPosition(glm::vec2(paddleRight.getPosition().x, 100));
  }

  glm::vec2 bpos  = ball.getPosition();
  glm::vec2 bdir  = ball.getDirection();
  glm::vec2 bsize = ball.getSize();

  if (bpos.x < 0 + (bsize.x/2) || bpos.x > window.width - (bsize.x/2)) {
    ball.setDirection(-bdir.x, bdir.y);
  }

  if (bpos.y < 0 + (bsize.y/2) || bpos.y > window.height - (bsize.y/2)) {
    ball.setDirection(bdir.x, -bdir.y);
  }

  ball.checkCollision(paddleLeft);
  ball.checkCollision(paddleRight);

  double x, y;
  glfwGetCursorPos(window.handle, &x, &y);
  glm::vec2 dir = glm::normalize((glm::vec2(x, y) - paddleLeft.getPosition()) / paddleLeft.getSize());
  float angle = std::atan2(dir.x, dir.y) - (HALF_PI / 2);
  if (angle > 0 && angle < HALF_PI) {
    std::cout << "RIGHT" << std::endl;
  } else if (angle < 0 && angle > -HALF_PI) {
    std::cout << "BOTTOM" << std::endl;
  } else if (angle < -HALF_PI && angle > -PI) {
    std::cout << "LEFT" << std::endl;
  } else {
    std::cout << "TOP" << std::endl;
  }
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  shader.use();
  shader.setInt("u_Texture", 0);
  ball.draw(shader);
  paddleLeft.draw(shader);
  paddleRight.draw(shader);
  if (q) {
    ball.drawDebug(shader);
    paddleLeft.drawDebug(shader);
    paddleRight.drawDebug(shader);
  }
}

void Game::mouseMove(double x, double y) {

}

void Game::mouseScroll(double xoff, double yoff) {

}

void Game::mousePress(int button, int mods) {
  double x, y;
  glfwGetCursorPos(window.handle, &x, &y);
  ball.setDirection(glm::vec2(x, y) - ball.getPosition());
}

void Game::mouseRelease(int button, int mods) {

}

void Game::keyPress(int key, int mods) {
  switch (key) {
    case GLFW_KEY_W:
      paddleLeft.setDirection(glm::vec2(0.0f, -1.0f));
      break;
    case GLFW_KEY_S:
      paddleLeft.setDirection(glm::vec2(0.0f, 1.0f));
      break;
    case GLFW_KEY_UP:
      paddleRight.setDirection(glm::vec2(0.0f, -1.0f));
      break;
    case GLFW_KEY_DOWN:
      paddleRight.setDirection(glm::vec2(0.0f, 1.0f));
      break;
    case GLFW_KEY_Q:
      q = !q;
      break;
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
