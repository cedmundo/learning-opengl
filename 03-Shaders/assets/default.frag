#version 330 core

in vec3 oCol;
out vec4 FragColor;

uniform float colsat;

vec3 saturation(vec3 rgb, float adjustment)
{
    // Algorithm from Chapter 16 of OpenGL Shading Language
    const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    vec3 intensity = vec3(dot(rgb, W));
    return mix(intensity, rgb, adjustment);
}

void main() {
    FragColor = vec4(saturation(oCol, colsat), 1.0);
}

