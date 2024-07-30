#ifndef MESH2D_H
#define MESH2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, scale, rotate
#include "shader.h"

struct Texture {
  uint        handle;
  std::string filepath;
};

class Mesh2D {
  public:
    void draw(Shader& shader, int drawMode = GL_TRIANGLES);

    void loadTexture(std::string filepath);

    void setPosition(glm::vec2 position);
    void setRotation(float degrees);
    void setSize(float size);

    glm::vec2 getPosition();
    float     getRotation();
    float     getSize();

  protected:
    glm::vec2 m_Position;
    float m_Rotation; // degrees
    float m_Size; // pixels
    uint m_IndexAmount; // needed for glDrawElements
    Texture m_Texture;

    uint m_VAO, m_VBO, m_EBO;
};

#endif /* MESH2D_H */
