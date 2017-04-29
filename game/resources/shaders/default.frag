#version 330 core

in vec3 ourColor;
in vec2 tex_coord0;

uniform float time;
uniform sampler2D sampler;

out vec4 color;

float rand(vec2 co) {
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
  vec4 diffuse = texture (sampler, tex_coord0);
  if (diffuse.a == 0) discard;

  color = diffuse * (cos(time)*cos(time)+sin(time)*sin(time));
}
