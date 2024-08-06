#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, scale, rotate
#include <glad/include/glad/glad.h>
#include "shader.h"

#define PI       3.14159265359
#define TWO_PI  (3.14159265359*2)
#define HALF_PI (3.14159265359/2)

void drawLine(Shader& shader, glm::vec4 color, glm::vec2 start, glm::vec2 end);
void renderBitmapString(Shader& shader, std::string string, glm::vec2 position, glm::vec4 color = glm::vec4(1.0f), glm::vec2 scale = glm::vec2(16.0f), float rotation = 0.0f, bool centred = true);
void loadImageTexture(uint handle, std::string filepath);

#endif /* UTILS_H */
