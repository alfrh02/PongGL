#include "game.h"

void Game::setup() {
  glfwSetInputMode(m_Window.handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  m_Ball.setPosition(m_Window.width/2, m_Window.height/2);
  m_Ball.setDirection(1.0f, 0.0f);
  m_Ball.setSpeed(BALL_SPEED);

  m_LeftPlayer.paddle.setPosition(glm::vec2(100, m_Window.height/2));
  m_LeftPlayer.paddle.setSpeed(PADDLE_SPEED);

  m_RightPlayer.paddle.setPosition(glm::vec2(m_Window.width-100, m_Window.height/2));
  m_RightPlayer.paddle.setSpeed(PADDLE_SPEED);

  m_Shader.use();
  m_Shader.setMat4("u_Projection", glm::ortho(0.0f, (float)m_Window.width, (float)m_Window.height, 0.0f, -1.0f, 1.0f));
}

Game::~Game() {
  if (m_LeftPlayer.score > m_RightPlayer.score) {
    std::cout << "Left Player wins!" << std::endl;
  } else if (m_LeftPlayer.score < m_RightPlayer.score) {
    std::cout << "Right Player wins!" << std::endl;
  } else {
    std::cout << "Tie!" << std::endl;
  }
}

void Game::update(double time, double deltaTime, unsigned long long frameCount) {
  if (time > m_TimeCapt + 1) {
    m_FPS = m_TimeCaptFrameCount;
    m_TimeCapt = time;
    m_TimeCaptFrameCount = 0;
  } else {
    m_TimeCaptFrameCount++;
  }

  if (m_Paused) return;

  m_Time = time;
  m_DeltaTime = deltaTime;
  m_FrameCount = frameCount;

  m_Shader.setFloat("u_Time", time);
  m_Ball.update(deltaTime);
  m_Ball.setSpeed(m_Ball.getSpeed() + (8.0*deltaTime));

  m_LeftPlayer.paddle.update(deltaTime);
  m_RightPlayer.paddle.update(deltaTime);

  if (m_LeftPlayer.paddle.getPosition().y > m_Window.height-(PADDLE_SIZE/2)) {
    m_LeftPlayer.paddle.setDirection(0.0f, 0.0f);
    m_LeftPlayer.paddle.setPosition(m_LeftPlayer.paddle.getPosition().x, m_Window.height-(PADDLE_SIZE/2));
  } else if (m_LeftPlayer.paddle.getPosition().y < PADDLE_SIZE/2) {
    m_LeftPlayer.paddle.setPosition(m_LeftPlayer.paddle.getPosition().x, PADDLE_SIZE/2);
    m_LeftPlayer.paddle.setDirection(0.0f, 0.0f);
  }

  if (m_RightPlayer.paddle.getPosition().y > m_Window.height-(PADDLE_SIZE/2)) {
    m_RightPlayer.paddle.setPosition(m_RightPlayer.paddle.getPosition().x, m_Window.height-(PADDLE_SIZE/2));
    m_RightPlayer.paddle.setDirection(0.0f, 0.0f);
  } else if (m_RightPlayer.paddle.getPosition().y < PADDLE_SIZE/2) {
    m_RightPlayer.paddle.setPosition(m_RightPlayer.paddle.getPosition().x, PADDLE_SIZE/2);
    m_RightPlayer.paddle.setDirection(0.0f, 0.0f);
  }

  glm::vec2 bpos  = m_Ball.getPosition();
  glm::vec2 bdir  = m_Ball.getDirection();
  glm::vec2 bsize = m_Ball.getSize();

  if (bpos.y < 0 + (bsize.y/2) || bpos.y > m_Window.height - (bsize.y/2)) {
    m_Ball.setDirection(bdir.x, -bdir.y);
  }

  if (bpos.x < 0 - bsize.x) {
    m_RightPlayer.score++;
    resetBall(m_Ball, true);
    std::cout << m_LeftPlayer.score << " - " << m_RightPlayer.score << std::endl;
  } else if (bpos.x - bsize.x > m_Window.width) {
    m_LeftPlayer.score++;
    resetBall(m_Ball, false);
    std::cout << m_LeftPlayer.score << " - " << m_RightPlayer.score << std::endl;
  }

  #ifndef NO_COMPUTER
  int fps = (frameCount+1)/time;
  fps *= AI_FRAMERATE;
  if (((frameCount+1) % fps) / (fps-1)) {
    if (bdir.x > 0.0) {
      if (m_RightPlayer.paddle.getPosition().y > bpos.y) {
        m_RightPlayer.paddle.setDirection(glm::vec2(0.0f, -1.0f));
      } else if (m_RightPlayer.paddle.getPosition().y < bpos.y) {
        m_RightPlayer.paddle.setDirection(glm::vec2(0.0f, 1.0f));
      } else {
        m_RightPlayer.paddle.setDirection(glm::vec2(0));
      }
    #ifndef AI_CENTRES_SELF
    } else {
      m_RightPlayer.paddle.setDirection(glm::vec2(0));
    }
    #else
    } else {
      if (m_RightPlayer.paddle.getPosition().y > m_Window.height/2) {
        m_RightPlayer.paddle.setDirection(glm::vec2(0.0f, -1.0f));
      } else if (m_RightPlayer.paddle.getPosition().y < m_Window.height/2) {
        m_RightPlayer.paddle.setDirection(glm::vec2(0.0f, 1.0f));
      }
    }
    #endif
  }
  #endif

  m_Ball.checkCollision(m_LeftPlayer.paddle);
  m_Ball.checkCollision(m_RightPlayer.paddle);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  m_Shader.use();

  drawBitmapString(m_Shader, std::to_string(m_LeftPlayer.score),  glm::vec2(m_Window.width/4,                  m_Window.height/5), glm::vec4(glm::vec3(0.1f), 1.0f), glm::vec2(48.0f));
  drawBitmapString(m_Shader, std::to_string(m_RightPlayer.score), glm::vec2(m_Window.width - m_Window.width/4, m_Window.height/5), glm::vec4(glm::vec3(0.1f), 1.0f), glm::vec2(48.0f));

  m_Shader.setInt("u_Texture", 0);
  if (m_Debug) {
    drawBitmapString(m_Shader, std::to_string((int)m_FPS), glm::vec2(0), glm::vec4(1.0f), glm::vec2(16.0f), 0.0f, false);
    drawBitmapString(m_Shader, std::to_string(m_Time), glm::vec2(0, 16), glm::vec4(1.0f), glm::vec2(16.0f), 0.0f, false);

    m_Shader.setInt("u_Wireframe", 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    m_Ball.drawDebug(m_Shader);
    m_LeftPlayer.paddle.drawDebug(m_Shader);
    m_RightPlayer.paddle.drawDebug(m_Shader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_Shader.setInt("u_Wireframe", 0);
  } else {
    m_Ball.draw(m_Shader);
    m_LeftPlayer.paddle.draw(m_Shader);
    m_RightPlayer.paddle.draw(m_Shader);
  }
  drawLine(m_Shader, glm::vec4(1.0f), glm::vec2(m_Window.width/2, 0), glm::vec2(m_Window.width/2, m_Window.height));
}

void Game::mouseMove(double x, double y) {
  //m_Ball.setPosition(x, y);
}

void Game::mouseScroll(double xoff, double yoff) {

}

void Game::mousePress(int button, int mods) {
  //double x, y;
  //glfwGetCursorPos(m_Window.handle, &x, &y);
  //m_Ball.setDirection(glm::vec2(x, y) - m_Ball.getPosition());
}

void Game::mouseRelease(int button, int mods) {

}

void Game::keyPress(int key, int mods) {
  switch (key) {
    /* CONTROLS */
    case GLFW_KEY_W:
      m_LeftPlayer.paddle.setDirection(glm::vec2(0.0f, -1.0f));
      break;
    case GLFW_KEY_S:
      m_LeftPlayer.paddle.setDirection(glm::vec2(0.0f, 1.0f));
      break;
    #ifdef NO_COMPUTER
    case GLFW_KEY_UP:
      m_RightPlayer.paddle.setDirection(glm::vec2(0.0f, -1.0f));
      break;
    case GLFW_KEY_DOWN:
      m_RightPlayer.paddle.setDirection(glm::vec2(0.0f, 1.0f));
      break;
    #endif

    /* FUNCTIONS */
    case GLFW_KEY_GRAVE_ACCENT:
      m_Debug = !m_Debug;
      break;
    case GLFW_KEY_F1:
      m_Paused = !m_Paused;
      break;
    case GLFW_KEY_R:
      m_Rainbow = !m_Rainbow;
      m_Shader.setInt("u_Rainbow", m_Rainbow);
      break;
  }
}

void Game::keyRelease(int key, int mods) {

}

void Game::windowResize(int width, int height) {
  m_Window.width  = width;
  m_Window.height = height;
  m_Shader.use();
  m_Shader.setMat4("u_Projection", glm::ortho(0.0f, (float)m_Window.width, (float)m_Window.height, 0.0f, -1.0f, 1.0f));
};

void Game::resetBall(Entity& entity, bool left) {
  entity.setSpeed(BALL_SPEED);
  entity.setPosition(m_Window.width/2, m_Window.height/2 - RESET_MARGIN + (float)(rand() % (RESET_MARGIN*2)));
  if (left) {
    entity.setDirection((float)(rand() % 100) * -1, (float)(rand() % 100));
  } else {
    entity.setDirection((float)(rand() % 100), (float)(rand() % 100));
  }
}
