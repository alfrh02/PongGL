#ifndef SQUARE_H
#define SQUARE_H

#include "mesh2d.h"

class Square: public Mesh2D {
  public:
    Square(glm::vec2 position, float size = 100);
};

#endif /* SQUARE_H */
