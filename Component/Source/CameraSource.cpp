#include <CameraComponent.h>

//CameraSource.cpp - Engine component for add camera
//If you need create own function for camera, please write this here or in CameraComponent.h for add construction 

//-----------------------------------------------------//

//CameraSource.cpp - Компонент движка для добавления камеры
//Если вам нужно создать собственную функцию для камеры, пожалуйста, напишите это здесь или в CameraComponent.h для добавления конструкций


Camera::Camera(int _Width, int _Hegth, vec3 _Position)
{
	this->_Width = _Width;
	this->_Hegth = _Hegth;
	this->_Position = _Position;
}

void Camera::CameraMatrix(float _LFOV, float _LNearPlane, float _LFarPlane, Shader& _Shader)
{
	this->_FOV = _LFOV;
	this->_NearPlane = _LNearPlane;
	this->_FarPlane = _LFarPlane;

	mat4 _View = mat4(1.0f);
	mat4 _Proj = mat4(1.0f);

	_View = lookAt(_Position, _Position + _Orient, _Up);
	_Proj = perspective(radians(_FOV), (float)(_Width / _Hegth), _NearPlane, _FarPlane);

	_Shader.UseShader();
	_Shader.SetMatrix4("view", _View);
	_Shader.SetMatrix4("proj", _Proj);
}

mat4 Camera::GetView() 
{
	mat4 _View = mat4(1.0f);
	_View = lookAt(_Position, _Position + _Orient, _Up);
	return _View;
}

mat4 Camera::GetProjection() 
{
	mat4 _Proj = mat4(1.0f);
	_Proj = perspective(radians(_FOV), (float)(_Width / _Hegth), _NearPlane, _FarPlane);
	return _Proj;
}

void Camera::Input(GLFWwindow* _Window) 
{
	if (glfwGetKey(_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_Position += _Speed * _Orient;
		
	}
	if (glfwGetKey(_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_Position += _Speed * -_Orient;
		
	}
	if (glfwGetKey(_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_Position += _Speed * -normalize(cross(_Orient, _Up));
		
	}
	if (glfwGetKey(_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_Position += _Speed * normalize(cross(_Orient, _Up));
		
	}
	if (glfwGetKey(_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_Position += _Speed * _Up;
		
	}
	if (glfwGetKey(_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		_Position += _Speed * -_Up;
		
	}
	if (glfwGetKey(_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		_Speed = 20.0f;
		
	}
	else if (glfwGetKey(_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		_Speed = 10.0f;
		
	}

	if (glfwGetMouseButton(_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (_Click)
		{
			glfwSetCursorPos(_Window, (_Width / 2), (_Hegth / 2));
			_Click = false;
		}


		double _MouseX;
		double _MouseY;
		glfwGetCursorPos(_Window, &_MouseX, &_MouseY);

		float _RotationX = _Sent * (float)(_MouseY - (_Hegth / 2)) / _Hegth;
		float _RotationY = _Sent * (float)(_MouseX - (_Hegth / 2)) / _Hegth;

		vec3 _OrintNew = rotate(_Orient, radians(-_RotationX), normalize(cross(_Orient, _Up)));
		if (!(angle(_OrintNew, _Up) <= radians(5.0f) or angle(_OrintNew, -_Up) <= radians(5.0f)))
		{
			_Orient = _OrintNew;
		}

		_Orient = rotate(_Orient, radians(-_RotationY), _Up);

		glfwSetCursorPos(_Window, (_Width / 2), (_Hegth / 2));

	}
	if (glfwGetMouseButton(_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_Click = true;
	}
}
