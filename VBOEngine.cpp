#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<ModelComponent.h>
#include<ShaderComponent.h>
#include<CameraComponent.h>
#include<SkyBoxComponent.h>

//VBOEngine - This game engine with open source code and current under active work. You can create or write a new function for engine and, you can create new components for VBOEngine
//Engine made by Russian developer: Operator.
//Have a good and luck development!

//Thanks you for download and choice russian game engine VBOEngine.
//#MakeRussiaGamesGreat

//---------------------------------------------------------------//

//VBOEngine - Это игровой движок с открытым исходным кодом, который в настоящее время находится в активной разработке. Вы можете создать или написать новую функцию для движка, а также вы можете создать новые компоненты для VBOEngine
//Движок создан российским разработчиком: Operator.
//Удачной разработки!

//Спасибо за скачивание и выбор российского игрового движка VBOEngine.
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

	//Shader load
	//--------------//
	//Загрузка шейдеров
	Shader _Shader = Shader("Shader/ModelShader/VertShader.glsl", "Shader/ModelShader/FragShader.glsl");
	Shader _SkyShader = Shader("Shader/SkyBoxShader/SkyVertShader.glsl", "Shader/SkyBoxShader/SkyFragShader.glsl");

	//Model load
	//-------------//
	//Загрузка модели
	Model _Model = Model("Model/Cube.fbx");

	vector<const char*> _SkyTexture = {"","","","","",""};
	SkyBox _SkyBox = SkyBox(_SkyTexture);

	glEnable(GL_DEPTH_TEST);
	Camera _Camera = Camera(800, 800, vec3(0.0f, 0.0f, 0.0f));
	_Shader.UseShader();

	while (!glfwWindowShouldClose(_Window)) 
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		_Shader.UseShader();
		_SkyShader.UseShader();

		_Camera.Input(_Window);

		if (glfwGetKey(_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
		{
			return -1;
		}


		_Camera.CameraMatrix(45.0f, 0.1f, 100.0f, _Shader);
		
		
		_Model.Draw(_Shader);
		_SkyBox.Draw(_SkyShader, _Camera);

		glfwSwapBuffers(_Window);


		glfwPollEvents();
	}
}