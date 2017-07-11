#version 330 core
layout (location = 0) in vec3 aPos; // Attribute 0: Position
layout (location = 1) in vec3 aCol; // Attribute 1: Color
out vec3 oCol;

void main() {
    gl_Position = vec4(aPos, 1.0);
    oCol = aCol;
}
