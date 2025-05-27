#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"ShaderComponent.h"
using namespace glm;

//You can write or create new construction here, but! Don't destroy base construction function here. 

class Camera 
{

public:
	vec3 _Position;
	vec3 _Orient = vec3(0.0f, 0.0f, -1.0f);
	vec3 _Up = vec3(0.0f, 1.0f, 0.0f);

	bool _Click = true;

	int _Width;
	int _Hegth;

	float _Speed = 10.1f;
	float _Sent = 50.0f;

	Camera(int _Width, int _Hegth, vec3 _Position);

	void CameraMatrix(float _FOV, float _NearPlane, float _FarPlane, Shader& _Shader);
	void Input(GLFWwindow* _Window);

private:
	void UpdateVector();

};
