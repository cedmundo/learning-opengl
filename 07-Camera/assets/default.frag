#version 330 core
out vec4 FragColor;

in vec2 oTex;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main() {
    vec4 t0 = texture2D(tex0, oTex);
    vec4 t1 = texture2D(tex1, oTex);
    FragColor = mix(t0, t1, t1.a);
}

