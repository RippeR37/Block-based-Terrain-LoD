#version 330 core

out vec4 color;

uniform vec3 COL;

void main() {
    color = vec4(COL, 1.0);
}
