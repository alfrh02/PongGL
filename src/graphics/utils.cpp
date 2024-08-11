#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void drawLine(Shader& shader, glm::vec4 color, glm::vec2 start, glm::vec2 end) {
  shader.setMat4("u_Model", glm::mat4(1.0f));
  shader.setVec4("u_Color", color);

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

/*
 * Creates a quad & gives it appropriate tex coordinates for the letter it's supposed to display
 */
void drawBitmapString(Shader& shader, std::string string, glm::vec2 position, glm::vec4 color, glm::vec2 scale, float rotation, bool centred) {
  uint vbo, ebo, vao, texture;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  std::vector<float> vertices;
  std::vector<ushort> indices;

  #define GLYPH_ROW_LENGTH 13
  #define GLYPHMAP_SIZE    104.0f
  #define GLYPH_WIDTH      8
  #define GLYPH_HEIGHT     12
  #define GLYPH_RATIO      8.0f/12.0f

  for (int i = 0; i < string.length(); i++) {
    int ch = string[i];
    ch -= 33;

    glm::vec2 index = glm::vec2(0);
    index.x = ch % GLYPH_ROW_LENGTH + 1;
    index.y = ch / GLYPH_ROW_LENGTH + 1;

    vertices.insert(vertices.end(), {
    // positions    texture coords
      i+1, 1,  GLYPH_WIDTH/GLYPHMAP_SIZE * index.x,                               GLYPH_HEIGHT/GLYPHMAP_SIZE * index.y,                               // bottom left
      i+1, 0,  GLYPH_WIDTH/GLYPHMAP_SIZE * index.x,                              (GLYPH_HEIGHT/GLYPHMAP_SIZE * index.y) - GLYPH_HEIGHT/GLYPHMAP_SIZE, // top left
      i,   0, (GLYPH_WIDTH/GLYPHMAP_SIZE * index.x) - GLYPH_WIDTH/GLYPHMAP_SIZE, (GLYPH_HEIGHT/GLYPHMAP_SIZE * index.y) - GLYPH_HEIGHT/GLYPHMAP_SIZE, // top right
      i,   1, (GLYPH_WIDTH/GLYPHMAP_SIZE * index.x) - GLYPH_WIDTH/GLYPHMAP_SIZE,  GLYPH_HEIGHT/GLYPHMAP_SIZE * index.y                                // bottom right
    //i+0.5,  0.5,  8.0f/104.0f * index.x,                 12.0f/104.0f * index.y,                 // top right
    //i+0.5, -0.5,  8.0f/104.0f * index.x,                (12.0f/104.0f * index.y) - GLYPH_HEIGHT, // bottom right
    //i-0.5, -0.5, (8.0f/104.0f * index.x) - GLYPH_WIDTH, (12.0f/104.0f * index.y) - GLYPH_HEIGHT, // bottom left
    //i-0.5,  0.5, (8.0f/104.0f * index.x) - GLYPH_WIDTH,  12.0f/104.0f * index.y                  // top left
    });

    ushort v = i*4;
    indices.insert(indices.end(), {
      v,   v+1, v+3,
      v+1, v+2, v+3
    });
  }

  if (centred) {
    // grabs each vertex position from `vertices` & shifts it to be centred
    // 0, 1, 4, 5, 8, 9, 12, 13, 16, 17, 20, 21
    for (ushort i = 0; i < vertices.size(); i += 4) {
      vertices[i]   -= 0.5;
      vertices[i+1] -= 0.5;
    }

    // shifts each quad leftwards
    for (ushort i = 0; i < vertices.size(); i += 16) {
      //std::cout << i << std::endl;
      for (ushort j = i; j < i+16; j += 4) {
        //std::cout << j << std::endl;
        vertices[j] -= string.length()/2;
        if (!(string.length() % 2)) vertices[j] += 0.5;
      }
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(ushort), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);                   // vertex location
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // vertex tex coord
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glGenTextures(1, &texture);
  loadImageTexture(texture, "assets/textures/font.png");

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::scale(model, glm::vec3(scale.x * GLYPH_RATIO, scale.y, 1.0f));
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  shader.setMat4("u_Model", model);
  shader.setVec4("u_Color", color);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteVertexArrays(1, &vao);
}

void loadImageTexture(uint handle, std::string filepath) {
  glBindTexture(GL_TEXTURE_2D, handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height, channels;
  unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

  uint mode = GL_RED;
  switch (channels) {
    case 2:
      mode = GL_RG;
      break;
    case 3:
      mode = GL_RGB;
      break;
    case 4:
      mode = GL_RGBA;
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
