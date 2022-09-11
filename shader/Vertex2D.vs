#version 330 core
layout (location = 0) in vec2 aPos;

out vec3 mColor;

uniform mat4 uProjMatrix;

void main()
{
    gl_Position = uProjMatrix * vec4(aPos.xy, 1.0, 1.0);
    mColor = vec3(1, 1, 1);
}