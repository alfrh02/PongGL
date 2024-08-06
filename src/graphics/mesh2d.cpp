#include "mesh2d.h"

#define PI      3.14159265359
#define TWO_PI  (3.14159265359*2)
#define HALF_PI (3.14159265359/2)

Mesh2D::Mesh2D(MeshType type, ushort resolution, float width, float height)
: Mesh2D(type, resolution, glm::vec2(width, height)) {
}

Mesh2D::~Mesh2D() {
//  this causes a segfault and i dont know why
//  glDeleteBuffers(1, &m_VBO);
//  glDeleteBuffers(1, &m_EBO);
//  glDeleteVertexArrays(1, &m_VAO);
}

Mesh2D::Mesh2D(MeshType type, ushort resolution, glm::vec2 size) {
  m_Size = size;

  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  std::vector<float> vertices;
  std::vector<ushort> indices;

  switch (type) {
    case SQUARE:
      vertices.insert(vertices.end(), {
      // positions  texture coords
         0.5f,  0.5f, 1.0f, 1.0f, // top right
         0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f  // top left 
      });

      indices.insert(indices.end(), {
        0, 1, 3,
        1, 2, 3
      });
      break;
    case CIRCLE:
      vertices.insert(vertices.end(), {
    //  position,   texcoords
        0.0f, 0.0f, 0.5f, 0.5f // middle vertex for all other vertices to connect to
      });

      float t = 0;
      for (ushort i = 1; i < resolution + 1; i++) {
        glm::vec2 coords = glm::vec2(sin(t) * 0.5f, cos(t) * 0.5f);
        vertices.insert(vertices.end(), {
      //  position,           texcoords
          coords.x, coords.y, coords.x, coords.y
        });
        t += (1.0f/resolution) * TWO_PI;
      }

   /* for this kind of circle, indices are intuitive - view each triangle as a series of columns:
      ushort indices[4*3] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1
      }; */

      for (ushort i = 0; i < resolution; i++) {
        indices.insert(indices.end(), {
          0, i+1, i+2
        });
      }
      indices.back() = 1;
  }

  m_IndexAmount = indices.size();

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(ushort), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);                   // vertex location
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // vertex tex coord
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glGenTextures(1, &m_Texture);
  setTexture("assets/textures/missingtex.png");
}

void Mesh2D::draw(Shader& shader, int drawMode) {
  glBindVertexArray(m_VAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  glDrawElements(drawMode, m_IndexAmount, GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);
}

void Mesh2D::setSize(glm::vec2 size) {
  m_Size = size;
}

void Mesh2D::setTexture(std::string filepath) {
  loadImageTexture(m_Texture, filepath);
}

glm::vec2 Mesh2D::getSize() {
  return m_Size;
}
