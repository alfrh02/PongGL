#include "shader.h"

Shader::Shader() {
}

Shader::Shader(std::string vertShaderPath, std::string fragShaderPath) {
  createShader(vertShaderPath, fragShaderPath);
}

void Shader::createShader(std::string vertShaderPath, std::string fragShaderPath) {
//Shader::Shader(std::string vertShaderPath, std::string fragShaderPath) {
  auto genShader = [](std::string shaderFilepath, GLenum shaderType) {
    std::ifstream shaderFile(shaderFilepath);
    std::string shaderCodeStr;

    while(shaderFile.good()) {
        std::string line;
        std::getline(shaderFile, line);
        shaderCodeStr += line + "\n";
    }

    const char* shaderCode = shaderCodeStr.c_str();

    uint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "<ERR> : Shader compilation failed - \"" << shaderFilepath << "\"\n" << infoLog << std::endl;
      glDeleteShader(shader);
    }

    return shader;
  };

  uint vert, frag;
  vert = genShader(vertShaderPath, GL_VERTEX_SHADER);
  frag = genShader(fragShaderPath, GL_FRAGMENT_SHADER);

  m_ShaderProgram = glCreateProgram();
  glAttachShader(m_ShaderProgram, vert);
  glAttachShader(m_ShaderProgram, frag);

  glLinkProgram(m_ShaderProgram);

  glDeleteShader(vert);
  glDeleteShader(frag);
}

void Shader::use() {
  glUseProgram(m_ShaderProgram);
}

void Shader::setInt(std::string u_Name, int value) {
  glUniform1i(glGetUniformLocation(m_ShaderProgram, u_Name.c_str()), value);
}

void Shader::setMat4(std::string u_Name, glm::mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, u_Name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4(std::string u_Name, glm::vec4 value) {
  glUniform4fv(glGetUniformLocation(m_ShaderProgram, u_Name.c_str()), 1, glm::value_ptr(value));
}
