#ifndef ENTITY_H
#define ENTITY_H

#include "../graphics/mesh2d.h"
#include <glm/gtc/matrix_transform.hpp> // translate, scale, rotate
#include "../graphics/utils.h" // drawLine()

class Entity {
  public:
    Entity(glm::vec2 position, Mesh2D mesh, glm::vec4 color = glm::vec4(1.0f));
    ~Entity();

    void update(double deltaTime);
    void draw(Shader& shader, int drawMode = GL_TRIANGLES);
    void drawDebug(Shader& shader);

    void checkCollision(Entity& entity);

    void setPosition(glm::vec2 position);
    void setPosition(float x, float y);
    void setDirection(glm::vec2 direction);
    void setDirection(float x, float y);
    void setRotation(float degrees);
    void setScale(glm::vec2 scale);
    void setSpeed(float speed);
    void setColor(glm::vec4 color);
    void setTexture(std::string filepath);

    glm::vec2 getPosition();
    glm::vec2 getDirection();
    float     getRotation();
    glm::vec2 getSize(); // m_Mesh.size multiplied by m_Scale
    float     getSpeed();
    glm::vec4 getColor();

  private:
    glm::vec2 m_Position;
    glm::vec2 m_Direction;
    float m_Rotation;  // degrees
    glm::vec2 m_Scale; // pixels
    float m_Speed;     // pixels per second

    Mesh2D* m_Mesh;
    glm::vec4 m_Color;
};

#endif /* ENTITY_H */
