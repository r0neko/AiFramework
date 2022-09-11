#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uProjMatrix;

out vec4 mColor;
out vec2 TexCoord;

void main()
{
    gl_Position = uProjMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);
    mColor = vec4(aColor.x / 255, aColor.y / 255, aColor.z / 255, aColor.w / 255);
    TexCoord = aTexCoord;
}