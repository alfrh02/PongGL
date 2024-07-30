#include "mesh2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Mesh2D::draw(Shader& shader, int drawMode) {
  glBindVertexArray(m_VAO);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(m_Position, 0.0f));
  model = glm::scale(model, glm::vec3(m_Size));
  model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  shader.setMat4("u_Model", model);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_Texture.handle);
  glDrawElements(drawMode, m_IndexAmount, GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);
}

void Mesh2D::loadTexture(std::string filepath) {
  glGenTextures(1, &m_Texture.handle);
  glBindTexture(GL_TEXTURE_2D, m_Texture.handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, channels;
  unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

  uint mode = GL_RED;
  switch (channels) {
    case 3:
      mode = GL_RGB;
      break;
    case 4:
      mode = GL_RGB;
      break;
  }

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "ERROR: Failed to load texture " << filepath << std::endl;
  }

  stbi_image_free(data);
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
