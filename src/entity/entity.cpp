#include "entity.h"

Entity::Entity(glm::vec2 position, Mesh2D mesh, glm::vec4 color) {
  m_Position = position;
  m_Direction = glm::vec2(0.0f);
  m_Mesh = new Mesh2D(mesh);
  m_Color = color;

  glm::vec2 m_Direction = glm::vec2(0);
  m_Rotation = 0.0f; // degrees
  m_Scale = glm::vec2(1.0f);
  m_Speed = 100.0f; // pixels per second
}

Entity::~Entity() {
  delete m_Mesh;
}

void Entity::update(double deltaTime) {
  m_Position += m_Direction * glm::vec2(m_Speed * deltaTime);
}

void Entity::draw(Shader& shader, int drawMode) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(m_Position, 0.0f));
  model = glm::scale(model, glm::vec3(m_Mesh->getSize(), 1.0f));
  model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  shader.setMat4("u_Model", model);
  shader.setVec4("u_Color", m_Color);
  m_Mesh->draw(shader, drawMode);
}

void Entity::drawDebug(Shader& shader) {
  drawLine(shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), m_Position, m_Position + glm::vec2(m_Direction.x * 20, m_Direction.y * 20));
  draw(shader);
}

void Entity::checkCollision(Entity& entity) {
  glm::vec2 epos  = entity.getPosition();
  glm::vec2 edir  = entity.getDirection();
  glm::vec2 esize = entity.getSize();
  glm::vec2 ehalfsize = esize / glm::vec2(2);

  glm::vec2 halfsize = getSize() / glm::vec2(2);

  if (m_Position.y + halfsize.y > epos.y - ehalfsize.y && m_Position.y - halfsize.y < epos.y + ehalfsize.y) {
    if (m_Position.x + halfsize.x > epos.x - ehalfsize.x && m_Position.x - halfsize.x < epos.x + ehalfsize.x) {
      glm::vec2 dir = glm::normalize((m_Position - epos) / esize);
      float angle = std::atan2(dir.x, dir.y) - (HALF_PI / 2);

      /*
      if (angle > 0 && angle <= HALF_PI) {
        std::cout << angle << " right" << std::endl;
      } else if (angle > -HALF_PI && angle <= 0) {
        std::cout << angle << " bottom" << std::endl;
      } else if (angle > -PI && angle <= -HALF_PI) {
        std::cout << angle << " left" << std::endl;
      } else {
        std::cout << angle << " top" << std::endl;
      }
      */

      if ((angle > 0 && angle <= HALF_PI) || (angle > -PI && angle <= -HALF_PI)) {
        m_Direction.x = -m_Direction.x; // left & right
      } else if ((angle > -HALF_PI && angle <= 0)) {
        m_Direction.y = -m_Direction.y; // top & bottom
      }
      setDirection(m_Direction + dir);
    }
  }
}

void Entity::setPosition(glm::vec2 position) {
  m_Position = position;
}

void Entity::setPosition(float x, float y) {
  m_Position = glm::vec2(x, y);
}

void Entity::setDirection(glm::vec2 direction) {
  setDirection(direction.x, direction.y);
}

void Entity::setDirection(float x, float y) {
  m_Direction = glm::normalize(glm::vec2(x, y));
  if (x == 0 && y == 0) {
    m_Direction = glm::vec2(x, y);
  }
}

void Entity::setRotation(float degrees) {
  m_Rotation = degrees;
}

void Entity::setScale(glm::vec2 scale) {
  m_Scale = scale;
}

void Entity::setSpeed(float speed) {
  if (speed < 0) {
    speed = abs(speed);
  }
  m_Speed = speed;
}

void Entity::setColor(glm::vec4 color) {
  m_Color = color;
}

void Entity::setTexture(std::string filepath) {
  m_Mesh->setTexture(filepath);
}

glm::vec2 Entity::getPosition() {
  return m_Position;
}

float Entity::getRotation() {
  return m_Rotation;
}

glm::vec2 Entity::getDirection() {
  return m_Direction;
}

glm::vec2 Entity::getSize() {
  return m_Mesh->getSize() * m_Scale;
}

float Entity::getSpeed() {
  return m_Speed;
}

glm::vec4 Entity::getColor() {
  return m_Color;
}
