#include "entity.h"

#define PI      3.14159265359
#define TWO_PI  (3.14159265359*2)
#define HALF_PI (3.14159265359/2)

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
  shader.setMat4("u_Model", glm::mat4(1.0f));
  shader.setVec4("u_Color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  drawLine(m_Position, m_Position + glm::vec2(m_Direction.x * 20, m_Direction.y * 20));
}

void Entity::checkCollision(Entity& entity) {
  glm::vec2 epos  = entity.getPosition();
  glm::vec2 edir  = entity.getDirection();
  glm::vec2 esize = entity.getSize();
  glm::vec2 ehalfsize = esize / glm::vec2(2);

  glm::vec2 halfsize = getSize() / glm::vec2(2);
  // check if our y is within the height of entity
  if (m_Position.y + halfsize.y > epos.y - ehalfsize.y && m_Position.y - halfsize.y < epos.y + ehalfsize.y) {
    // check if our x is within the width of the entity
    if (m_Position.x + halfsize.x > epos.x - ehalfsize.x && m_Position.x - halfsize.x < epos.x + ehalfsize.x) {
      glm::vec2 dir = glm::normalize((m_Position - epos) / esize);
      float angle = std::atan2(dir.x, dir.y) - (HALF_PI / 2);
      if (angle > 0 && angle < HALF_PI) { // colliding on the right side
        m_Direction.x = -m_Direction.x;
      } else if (angle < 0 && angle > -HALF_PI) { // bottom side
        m_Direction.y = -m_Direction.y;
      } else if (angle < -HALF_PI && angle > -PI) { // left side
        m_Direction.x = -m_Direction.x;
      } else { // top side
        m_Direction.y = -m_Direction.y;
      }
    }
  }
}

void Entity::setPosition(glm::vec2 position) {
  m_Position = position;
}

void Entity::setDirection(glm::vec2 direction) {
  m_Direction = glm::normalize(direction);
}

void Entity::setDirection(float x, float y) {
  m_Direction = glm::normalize(glm::vec2(x, y));
}

void Entity::setRotation(float degrees) {
  m_Rotation = degrees;
}

void Entity::setColor(glm::vec4 color) {
  m_Color = color;
}

glm::vec2 Entity::getPosition() {
  return m_Position;
}

glm::vec2 Entity::getDirection() {
  return m_Direction;
}

glm::vec2 Entity::getSize() {
  return m_Mesh->getSize() * m_Scale;
}

float Entity::getRotation() {
  return m_Rotation;
}

glm::vec4 Entity::getColor() {
  return m_Color;
}

void Entity::drawLine(glm::vec2 start, glm::vec2 end) {
  float vertices[4] = {
    start.x, start.y,
    end.x,   end.y
  };

  uint vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glDrawArrays(GL_LINES, 0, 4);

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}
