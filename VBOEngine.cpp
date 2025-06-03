#include <glad/glad.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include<ModelComponent.h>
#include<ShaderComponent.h>
#include<CameraComponent.h>
#include<SkyBoxComponent.h>
#include<ConfigComponent.h>
#include<iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;

//VBOEngine - This game engine with open source code and current under active work. You can create or write a new function for engine and, you can create new components for VBOEngine
//Engine made by Russian developer: Operator.
//Have a luck development!

//Thanks you for download and choice russian game engine VBOEngine.
//#MakeRussiaGamesGreat
//#MakeRussiaITGreat

//---------------------------------------------------------------//

//VBOEngine - Это игровой движок с открытым исходным кодом, который в настоящее время находится в активной разработке. Вы можете создать или написать новую функцию для движка, а также вы можете создать новые компоненты для VBOEngine
//Движок создан российским разработчиком: Operator.
//Удачной разработки!

//Спасибо за скачивание и выбор российского игрового движка VBOEngine.
//#MakeRussiaGamesGreat
//#MakeRussiaITGreat


int main() 
{
	string _RenderSystem;
	cout << "Input you render system: vk|gl:" << endl;
	cin >> _RenderSystem;
	if (_RenderSystem=="gl")
	{
		GLFWwindow* _Window;


		if (!glfwInit())
		{
			return -1;
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
		Model _Model = Model("Model/Torus.fbx");


		glEnable(GL_DEPTH_TEST);
		Camera _Camera = Camera(800, 800, vec3(0.0f, 0.0f, 0.0f));


		vector<const char*> _SkyTexture = { "Texture/SkyBox/Sky.jpg","Texture/SkyBox/Sky.jpg","Texture/SkyBox/Sky.jpg","Texture/SkyBox/Sky.jpg",
			"Texture/SkyBox/Sky.jpg","Texture/SkyBox/Sky.jpg" };
		SkyBox _SkyBox = SkyBox(_SkyTexture);

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
	else if (_RenderSystem=="vk")
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* _Window;

		if (!glfwInit())
		{
			return -1;
		}

		cout << "Welcome to VBOEngine" << endl;
		_Window = glfwCreateWindow(800, 800, "VBOEngine", NULL, NULL);
		
		//Get required instance extension be must for vulkan
		//THIS VARY IMPORTANT!!!
		uint32_t _ExCount = 0; //create extension variable count
		const char** _ExName = glfwGetRequiredInstanceExtensions(&_ExCount); //Get REQUIRED extensions for vulkan
		vector<const char*> _Ex(_ExName, _ExCount + _ExName); //Set vector for extensions



		//Set application vk info:
		VkApplicationInfo _App = {};
		_App.pEngineName = nullptr; //Set use engine
		_App.engineVersion = VK_MAKE_VERSION(1, 0, 0); //Set engine version
		_App.pApplicationName = "VBOEngine"; //Set app name
		_App.applicationVersion = VK_MAKE_VERSION(0, 0, 1); //Set app version
		_App.apiVersion = VK_VERSION_1_4; //Set API Version

		//Set info for vk
		VkInstanceCreateInfo _Info = {};
		_Info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; //Set type info vk
		_Info.pApplicationInfo = &_App; //Set application info for vk
		_Info.enabledExtensionCount = static_cast<uint32_t>(_Ex.size()); //Count global extension be must setup
		_Info.ppEnabledExtensionNames = _Ex.data(); //Names extension must setup
		
		//Set output instance variable
		VkInstance _Instance = {};

		//Set winddow surface
		VkSurfaceKHR _Surface = {};

		//Create vulkan
		vkCreateInstance(&_Info, nullptr, &_Instance);

		//Create window surface
		glfwCreateWindowSurface(_Instance, _Window, nullptr, &_Surface);

		//Add variable for count physical devices
		uint32_t _PCount;
		vkEnumeratePhysicalDevices(_Instance, &_PCount, nullptr); //Set _PCount value GPU
		vector<VkPhysicalDevice> _PDevice(_PCount); //Set vector for count GPU
		vkEnumeratePhysicalDevices(_Instance, &_PCount, _PDevice.data()); //Set _PDevice count of GPU

		VkPhysicalDevice _PDeviceProp = _PDevice.data()[0];
		

		

		uint32_t _QueueFamilyCount = 0; //Count streams
		vkGetPhysicalDeviceQueueFamilyProperties(_PDeviceProp, &_QueueFamilyCount, nullptr); //Get stream GPU

		vector<VkQueueFamilyProperties> _QFamilyProperties(_QueueFamilyCount); //type stream in GPU 
		
		//Get GPU streams and their properties
		vkGetPhysicalDeviceQueueFamilyProperties(_PDeviceProp, &_QueueFamilyCount, _QFamilyProperties.data()); 

		//streams
		uint32_t _GraphicsQueueFamIndex = 0; //graphics stream 
		uint32_t _PresentQueueFamIndex = 0; //output graphic stream on window

		//Check properties all streams
		for (size_t i = 0; i < _QFamilyProperties.size(); i++) 
		{
			auto _QueueFamily = _QFamilyProperties[i];

			VkBool32 _ValidSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(_PDeviceProp, i, _Surface, &_ValidSupport); //Check support surface
			if (_ValidSupport==true)
			{
				_PresentQueueFamIndex = i; //if support, set _PresentQueueFamIndex own index.
			}

			if (_QueueFamily.queueFlags&VK_QUEUE_GRAPHICS_BIT) //Check: this stream graphics?
			{
				_GraphicsQueueFamIndex = i; //if yes, set _GraphicsQueueFamIndex own index.
				break;
			}
			
		}

		VkPhysicalDeviceFeatures _DeviceFeatures = {};
		vector<VkDeviceQueueCreateInfo> _QueueInfos; //Queue list
		set<uint32_t> _Family = {_GraphicsQueueFamIndex, _PresentQueueFamIndex}; //Set streams

		for (const uint32_t _AllQueue : _Family) 
		{
			//Bind graphics queue family info
			float _QueuePriority = 1.0f;
			VkDeviceQueueCreateInfo _QueueInfo = {};
			_QueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			_QueueInfo.queueCount = 1; //Graphics count queue
			_QueueInfo.queueFamilyIndex = _GraphicsQueueFamIndex; //Graphics queue index
			_QueueInfo.pQueuePriorities = &_QueuePriority; //Priorities
			_QueueInfos.push_back(_QueueInfo);
		}

		

		//Set device info
		VkDeviceCreateInfo _DeviceInfo = {};
		_DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		_DeviceInfo.enabledExtensionCount = 0;
		_DeviceInfo.pEnabledFeatures = &_DeviceFeatures;
		_DeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(_QueueInfos.size()); //Create count queue info
		_DeviceInfo.pQueueCreateInfos = _QueueInfos.data(); //Data queue infos

		VkDevice _Device = {};
		vkCreateDevice(_PDeviceProp, &_DeviceInfo, nullptr, &_Device);


		VkSwapchainKHR _Swap;
		VkSwapchainCreateInfoKHR _SwapInfo = {};
		_SwapInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		_SwapInfo.surface = _Surface; //Set surface
		_SwapInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Alpha layer
		_SwapInfo.clipped = VK_TRUE; //paint object or not paint if not see
		_SwapInfo.oldSwapchain = VK_NULL_HANDLE;
		_SwapInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //Set usage image mode
		_SwapInfo.imageArrayLayers = 1; //Set layer image for render aka 2D
		
		//Set sharing mode and stream queue for _SwapInfo
		uint32_t  _QueueFamilyIndex[] = { _GraphicsQueueFamIndex, _PresentQueueFamIndex }; //List all streams
		if (_GraphicsQueueFamIndex != _PresentQueueFamIndex)
		{
			_SwapInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT; //Image can sharing data
			_SwapInfo.queueFamilyIndexCount = 2; //Count stream in queue
			_SwapInfo.pQueueFamilyIndices = _QueueFamilyIndex;
		}
		else 
		{
			_SwapInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; //Image not can sharing data
		}

		vkCreateSwapchainKHR(_Device, &_SwapInfo, nullptr, &_Swap);

		while (!glfwWindowShouldClose(_Window)) {
			glfwPollEvents();
		}

		glfwDestroyWindow(_Window);

		glfwTerminate();

	}
	
}
