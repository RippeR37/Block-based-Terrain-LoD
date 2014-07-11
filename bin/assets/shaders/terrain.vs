#version 330 core

layout(location = 0) in vec4 Pos;

uniform mat4 MVP;

void main(){

    gl_Position = MVP * vec4(Pos.x, Pos.y * 40, Pos.z, 1.0);
}
