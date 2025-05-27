#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ModelComponent.h"
#include "ShaderComponent.h"
#include "CameraComponent.h"

//VBOEngine - This game engine with open source code. You can create or write a new function for engine
//Engine made by Russian developer: Operator.
//Have a good and luck development!

//#MakeRussiaGamesGreat

int main() 
{
	GLFWwindow* _Window;


	if (!glfwInit()) 
	{
		return - 1;
	}

	cout << "Welcome to VBOEngine" << endl;
	_Window = glfwCreateWindow(800, 800, "VBOEngine", NULL, NULL);

	if (!_Window) 
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_Window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glClearColor(0, 0, 0, 1);
	Shader _Shader = Shader("VertShader.glsl", "FragShader.glsl");
	Model _Model = Model("Model/Cube.fbx");

	glEnable(GL_DEPTH_TEST);
	Camera _Camera = Camera(800, 800, vec3(0.0f, 0.0f, 0.0f));
	_Shader.UseShader();

	while (!glfwWindowShouldClose(_Window)) 
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		_Shader.UseShader();

		_Camera.Input(_Window);

		if (glfwGetKey(_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
		{
			return -1;
		}


		_Camera.CameraMatrix(45.0f, 0.1f, 100.0f, _Shader);
		
		
		_Model.Draw(_Shader);

		glfwSwapBuffers(_Window);


		glfwPollEvents();
	}
}