#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 Color;
uniform sampler2D Texture;
uniform bool TextureValid;

void main()
{
	if(TextureValid==true)
	{
		FragColor = texture(Texture, TexCoord);
	}
	else
	{
		FragColor = vec4(Color,1.0f);
	}
	
}