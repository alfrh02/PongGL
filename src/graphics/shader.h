#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <glad/include/glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
  public:
    Shader();
    Shader(std::string vertShader, std::string fragShader);

    void createShader(std::string vertShaderPath, std::string fragShaderPath);

    void use();

    void setInt(std::string u_Name, int value);
    void setMat4(std::string u_Name, glm::mat4 value);
    void setVec4(std::string u_Name, glm::vec4 value);
    void setVec2(std::string u_Name, glm::vec2 value);

  private:
    int m_ShaderProgram;
};

#endif /* SHADER_H */
