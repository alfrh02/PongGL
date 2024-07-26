#version 460 core

uniform sampler2D a_Texture;

out vec4 fragColor;

in vec2 texCoords;

void main() {
  fragColor = vec4(texCoords.x, texCoords.y, 1.0f, 1.0f);
  //fragColor = texture(a_Texture, texCoords);
}
