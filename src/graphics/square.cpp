#include "square.h"

Square::Square(glm::vec2 position, float size) {
  m_Position = position;
  m_Size = size;

  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  float vertices[8*4] = {
       // positions            // colors             // texture coords
       0.5f,  0.5f, /* 0.0f,   1.0f, 0.0f, 0.0f, */  1.0f, 1.0f, // top right
       0.5f, -0.5f, /* 0.0f,   0.0f, 1.0f, 0.0f, */  1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, /* 0.0f,   0.0f, 0.0f, 1.0f, */  0.0f, 0.0f, // bottom left
      -0.5f,  0.5f, /* 0.0f,   1.0f, 1.0f, 0.0f, */  0.0f, 1.0f  // top left 
  };

  ushort indices[6] = {
    0, 1, 3,
    1, 2, 3
  };

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
