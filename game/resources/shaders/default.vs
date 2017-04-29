#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec2 vertex_uv;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

uniform float time;

out vec3 ourColor;
out vec2 tex_coord0;

void main() {
  gl_Position = projection * camera * model * vec4(vertex_position, 1.0f);
  ourColor = vertex_color;
  tex_coord0 = vertex_uv;
}
