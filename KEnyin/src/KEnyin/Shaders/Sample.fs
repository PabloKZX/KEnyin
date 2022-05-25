#version 440 core
out vec4 fragColor;

in vec3 v_Position;

void main()
{
    fragColor = vec4(v_Position * 0.5 + 0.5, 1.0);
}