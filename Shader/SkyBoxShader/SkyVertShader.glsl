#version 330 core
layout(location=0) in vec3 aPos;

out vec3 TexCoord;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	TexCoord = vec3(aPos.x, aPos.y, -aPos.z);
	vec4 Pos = view*proj*vec4(aPos,1.0f)
	gl_Position = vec4(pos.xyww);

}