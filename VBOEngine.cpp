#include <GLFW/glfw3.h>

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

	while (!glfwWindowShouldClose(_Window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(_Window);


		glfwPollEvents();
	}
}