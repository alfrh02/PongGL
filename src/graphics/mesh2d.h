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
    Mesh2D(MeshType type, ushort resolution = 32, float size = 100); // resolution is only for when type is CIRCLE

    void draw(Shader& shader, int drawMode = GL_TRIANGLES);

    void setTexture(std::string filepath);

    void  setSize(float size);
    float getSize();

  protected:
    float m_Size;       // pixels
    uint m_IndexAmount; // needed for glDrawElements

    uint m_VAO, m_VBO, m_EBO, m_Texture; // opengl handles
};

#endif /* MESH2D_H */
