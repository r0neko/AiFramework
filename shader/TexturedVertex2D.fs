#version 330 core
out vec4 FragColor;
  
in vec4 mColor;
in vec2 TexCoord;

uniform sampler2D mTexture;

void main()
{
    FragColor = texture(mTexture, TexCoord) * mColor;
}