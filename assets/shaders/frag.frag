#version 460 core

uniform sampler2D u_Texture;
uniform vec4 u_Color;

in vec2 texCoords;

out vec4 fragColor;

void main() {
  fragColor = texture(u_Texture, texCoords) * u_Color;
}
