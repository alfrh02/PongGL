#ifndef ENTITY_H
#define ENTITY_H

#include "../graphics/mesh2d.h"
#include <glm/gtc/matrix_transform.hpp> // translate, scale, rotate

class Entity {
  public:
    Entity(glm::vec2 position, Mesh2D mesh, glm::vec4 color = glm::vec4(1.0f));
    ~Entity();

    void update(double deltaTime);
    void draw(Shader& shader, int drawMode = GL_TRIANGLES);
    void drawDebug(Shader& shader);

    void checkCollision(Entity& entity);

    void setPosition(glm::vec2 position);
    void setDirection(glm::vec2 direction);
    void setDirection(float x, float y);
    void setRotation(float degrees);
    void setColor(glm::vec4 color);

    glm::vec2 getPosition();
    glm::vec2 getDirection();
    glm::vec2 getSize();
    float     getRotation();
    glm::vec4 getColor();

  private:
    static void drawLine(glm::vec2 start, glm::vec2 end);
    //static void drawAABB(glm::vec2 pos, glm::vec2 scale);

    glm::vec2 m_Position;
    glm::vec2 m_Direction;
    float m_Rotation; // degrees
    glm::vec2 m_Scale;    // pixels
    float m_Speed;    // pixels per second

    Mesh2D* m_Mesh;
    glm::vec4 m_Color;

    //BoundingBox m_BoundingBox;
};

#endif /* ENTITY_H */
