#version 460 core

uniform sampler2D u_Texture;
uniform float u_Time;
uniform vec4 u_Color;
uniform bool u_Rainbow;
uniform bool u_Wireframe;

in vec2 texCoords;

out vec4 fragColor;

// https://stackoverflow.com/questions/15095909/from-rgb-to-hsv-in-opengl-glsl
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
  vec4 color = u_Color;
  if (u_Rainbow) {
    color = vec4(hsv2rgb(vec3(u_Time, 1.0f, 1.0f)), 1.0f);
  }
  fragColor = texture(u_Texture, texCoords) * color;
  if (u_Wireframe) {
    fragColor = u_Color;
  }
}
