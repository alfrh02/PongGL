#ifndef CIRCLE_H
#define CIRCLE_H

#include "mesh2d.h"

class Circle: public Mesh2D {
  public:
    Circle(glm::vec2 position, ushort resolution = 32, float size = 100);
};

#endif /* CIRCLE_H */
