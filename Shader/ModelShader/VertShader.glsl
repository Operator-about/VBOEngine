#version 330 core
layout(location=0) in vec3 aPos; 
layout(location=1) in vec3 aNormal; 
layout(location=2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;


void main()
{
	TexCoord = aTexCoord;
	gl_Position = model*proj*view*vec4(aPos,1.0f);
}