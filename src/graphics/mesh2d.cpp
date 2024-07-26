#include "mesh2d.h"

void Mesh2D::draw(Shader& shader, int drawMode) {
  glBindVertexArray(m_VAO);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(m_Position, 0.0f));
  model = glm::scale(model, glm::vec3(m_Size));
  model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  shader.setMat4("u_Model", model);
  glDrawElements(drawMode, m_IndexAmount, GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);
}

void Mesh2D::setPosition(glm::vec2 position) {
  m_Position = position;
}

void Mesh2D::setRotation(float degrees) {
  m_Rotation = degrees;
}

void Mesh2D::setSize(float size) {
  m_Size = size;
}

glm::vec2 Mesh2D::getPosition() {
  return m_Position;
}

float Mesh2D::getRotation() {
  return m_Rotation;
}

float Mesh2D::getSize() {
  return m_Size;
}
