#include "utils.h"

void drawLine(glm::vec2 start, glm::vec2 end) {
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
