#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ModelComponent.h"
#include "ShaderComponent.h"
#include "CameraComponent.h"

int main() 
{
	GLFWwindow* _Window;

	if (!glfwInit()) 
	{
		return - 1;
	}

	_Window = glfwCreateWindow(800, 800, "VBOEngine", NULL, NULL);

	if (!_Window) 
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_Window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glClearColor(0, 0, 0, 0);
	Shader _Shader = Shader("./VertShader.glsl", "./FragShader.glsl");
	Model _Model = Model("");
	Camera _Camera = Camera(800, 800, vec3(0.0f, 0.0f, 0.0f));
	_Shader.UseShader();

	while (!glfwWindowShouldClose(_Window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);

		_Shader.UseShader();

		_Camera.CameraMatrix(45.0f, 0.1f, 100.0f, _Shader);
		_Camera.Input(_Window);
		
		_Model.Draw(_Shader);

		glfwSwapBuffers(_Window);


		glfwPollEvents();
	}
}