#ifndef MESH2D_H
#define MESH2D_H

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"

enum MeshType {
  SQUARE = 0,
  CIRCLE
};

class Mesh2D {
  public:
    Mesh2D(MeshType type, ushort resolution, glm::vec2 size); // resolution is only for when type is CIRCLE
    Mesh2D(MeshType type, ushort resolution = 32, float width = 100, float height = 100);

    void draw(Shader& shader, int drawMode = GL_TRIANGLES);

    void setTexture(std::string filepath);

    void setSize(glm::vec2 size);
    glm::vec2 getSize();

  protected:
    glm::vec2 m_Size;   // pixels width & height
    uint m_IndexAmount; // needed for glDrawElements

    uint m_VAO, m_VBO, m_EBO, m_Texture; // opengl handles
};

#endif /* MESH2D_H */
