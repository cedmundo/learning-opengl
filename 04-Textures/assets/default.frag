#version 330 core
out vec4 FragColor;

in vec3 oCol;
in vec2 oTex;

uniform sampler2D tex0;

void main() {
    FragColor = texture(tex0, oTex) * vec4(oCol, 1.0);
}

