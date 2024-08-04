#include "game.h"

#define PI       3.14159265359
#define TWO_PI  (3.14159265359*2)
#define HALF_PI (3.14159265359/2)

void Game::setup() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  ball.setPosition(window.width/2, window.height/2);
  ball.setDirection(1.0f, 0.0f);
  ball.setSpeed(BALL_SPEED);

  leftPlayer.paddle.setPosition(glm::vec2(100, window.height/2));
  leftPlayer.paddle.setSpeed(PADDLE_SPEED);

  rightPlayer.paddle.setPosition(glm::vec2(window.width-100, window.height/2));
  rightPlayer.paddle.setSpeed(PADDLE_SPEED);

  shader.use();
  shader.setMat4("u_Projection", projection);
}

void Game::update(double time, double deltaTime, unsigned long long frameCount) {
  ball.update(deltaTime);

  leftPlayer.paddle.update(deltaTime);
  rightPlayer.paddle.update(deltaTime);

  if (leftPlayer.paddle.getPosition().y > window.height-(PADDLE_SIZE/2)) {
    leftPlayer.paddle.setPosition(leftPlayer.paddle.getPosition().x, window.height-(PADDLE_SIZE/2));
  } else if (leftPlayer.paddle.getPosition().y < PADDLE_SIZE/2) {
    leftPlayer.paddle.setPosition(leftPlayer.paddle.getPosition().x, PADDLE_SIZE/2);
  }

  if (rightPlayer.paddle.getPosition().y > window.height-(PADDLE_SIZE/2)) {
    rightPlayer.paddle.setPosition(rightPlayer.paddle.getPosition().x, window.height-(PADDLE_SIZE/2));
  } else if (rightPlayer.paddle.getPosition().y < PADDLE_SIZE/2) {
    rightPlayer.paddle.setPosition(rightPlayer.paddle.getPosition().x, PADDLE_SIZE/2);
  }

  glm::vec2 bpos  = ball.getPosition();
  glm::vec2 bdir  = ball.getDirection();
  glm::vec2 bsize = ball.getSize();

  if (bpos.y < 0 + (bsize.y/2) || bpos.y > window.height - (bsize.y/2)) {
    ball.setDirection(bdir.x, -bdir.y);
  }

  if (bpos.x < 0 + (bsize.x/2)) {
    leftPlayer.score++;
    resetBall(ball, true);
    std::cout << leftPlayer.score << " - " << rightPlayer.score << std::endl;
  } else if (bpos.x + (bsize.x/2) > window.width) {
    rightPlayer.score++;
    resetBall(ball, false);
    std::cout << leftPlayer.score << " - " << rightPlayer.score << std::endl;
  }

  ball.checkCollision(leftPlayer.paddle);
  ball.checkCollision(rightPlayer.paddle);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  shader.use();
  shader.setInt("u_Texture", 0);
  ball.draw(shader);
  leftPlayer.paddle.draw(shader);
  rightPlayer.paddle.draw(shader);
  if (debug) {
    ball.drawDebug(shader);
    leftPlayer.paddle.drawDebug(shader);
    rightPlayer.paddle.drawDebug(shader);
  }
}

void Game::mouseMove(double x, double y) {
  //ball.setPosition(x, y);
}

void Game::mouseScroll(double xoff, double yoff) {

}

void Game::mousePress(int button, int mods) {
  //double x, y;
  //glfwGetCursorPos(window.handle, &x, &y);
  //ball.setDirection(glm::vec2(x, y) - ball.getPosition());
}

void Game::mouseRelease(int button, int mods) {

}

void Game::keyPress(int key, int mods) {
  switch (key) {
    case GLFW_KEY_W:
      leftPlayer.paddle.setDirection(glm::vec2(0.0f, -1.0f));
      break;
    case GLFW_KEY_S:
      leftPlayer.paddle.setDirection(glm::vec2(0.0f, 1.0f));
      break;
    case GLFW_KEY_UP:
      rightPlayer.paddle.setDirection(glm::vec2(0.0f, -1.0f));
      break;
    case GLFW_KEY_DOWN:
      rightPlayer.paddle.setDirection(glm::vec2(0.0f, 1.0f));
      break;
    case GLFW_KEY_GRAVE_ACCENT:
      debug = !debug;
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
};

void Game::resetBall(Entity& entity, bool left) {
  entity.setPosition(window.width/2, window.height/2);
  if (left) {
    entity.setDirection((float)(rand() % 100) * -1, (float)(rand() % 100));
  } else {
    entity.setDirection((float)(rand() % 100), (float)(rand() % 100));
  }
}
