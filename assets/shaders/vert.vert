#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform vec2 u_WindowDimensions;

out vec2 texCoords;

mat4 aspectRatio = mat4(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);

void main() {
  gl_Position = (aspectRatio * u_Projection) * u_Model * vec4(vec3(a_Position, 0.0f), 1.0f);
  texCoords = a_TexCoords;
}
