#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 uProjMatrix;

out vec3 mColor;

void main()
{
    gl_Position = uProjMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);
    mColor = vec3(aColor.x / 255, aColor.y / 255, aColor.z / 255);
}