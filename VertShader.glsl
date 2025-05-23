#version 330 core
layout(location=0) in vec3 aPos; 
layout(location=1) in vec3 aNormal; 

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;


void main()
{
	gl_Position = model*proj*view*(vec4,1.0f);
}