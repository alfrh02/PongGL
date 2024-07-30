#include "circle.h"

#define PI     3.14159265359
#define TWO_PI (3.14159265359*2)

Circle::Circle(glm::vec2 position, ushort resolution, float size) {
  m_Position = position;
  m_Size = size;

  glGenTextures(1, &m_Texture.handle);

  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  float vertices[(resolution+1)*4] = {
      // position  // texture coords
      0.0f,  0.0f, 0.5f, 0.5f  // 0 middle
  };

  float t = 0;
  for (ushort i = 1; i < resolution + 1; i++) {
    ushort v = i*4;
    glm::vec2 coords = glm::vec2(sin(t) * 0.5f, cos(t) * 0.5f);
    vertices[v]   = coords.x;
    vertices[v+1] = coords.y;
    vertices[v+2] = coords.x * 2;
    vertices[v+3] = coords.y * 2;
    t += (1.0f/resolution) * TWO_PI;
  }

  /*
  for this kind of circle, indices are intuitive - view each triangle as a series of columns:
  ushort indices[4*3] = {
    0, 1, 2,
    0, 2, 3,
    0, 3, 4,
    0, 4, 1
  };
  */

  ushort indices[resolution*3] = {};
  for (ushort i = 0; i < resolution; i++) {
    ushort v = i*3;
    indices[v]   = 0;
    indices[v+1] = i+1;
    indices[v+2] = i+2;
  }
  indices[resolution*3-1] = 1;

  m_IndexAmount = sizeof(indices) / sizeof(ushort);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);                   // vertex location
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // vertex tex coord
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}
