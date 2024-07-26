#ifndef MESH2D_H
#define MESH2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, scale, rotate
#include "shader.h"

class Mesh2D {
  public:
    void draw(Shader& shader, int drawMode = GL_TRIANGLES);

    void setPosition(glm::vec2 position);
    void setRotation(float degrees);
    void setSize(float size);

    glm::vec2 getPosition();
    float     getRotation();
    float     getSize();

  protected:
    glm::vec2 m_Position;
    float m_Rotation; // degrees
    float m_Size;

    uint m_VAO, m_VBO, m_EBO;
    uint m_IndexAmount;
};

#endif /* MESH2D_H */
