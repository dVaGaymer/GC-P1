#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <IGL/IGlib.h>

typedef struct	s_axis
{
	union
	{
		glm::vec3 x;
		glm::vec3 right;
	};
	union
	{
		glm::vec3 y;
		glm::vec3 up;
	};
	union
	{
		glm::vec3 z;
		glm::vec3 forward;
	};
}				t_axis;

class Camera
{
private:
	//Camera local axis
	t_axis		axis;
	//Camera projection
	float near;
	float far;
	float aperture;
	float aspect;
	//Camera Position
	glm::vec3 position;
	//Camera Rotation
	glm::vec2 eulerAngles;
public:
	Camera()
		:axis({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 1.0f) }),
		near(1), far(60), aperture(100), aspect(1), position(0.0f, 0.0f, 0.0f), eulerAngles(90, 0) {}
	Camera(glm::vec3 position)
		:axis({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 1.0f) }),
		near(1), far(60), aperture(100), aspect(1), position(position), eulerAngles(90, 0) {}
	Camera(glm::vec3 position, float far, float near, float aperture, float aspect)
		:axis({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 1.0f) }),
		near(near), far(far), aperture(aperture), aspect(aspect), position(position), eulerAngles(90, 0) {}

	void SetNear(float near);
	void SetFar(float far);
	void SetAperture(float aperture);
	void SetAspect(float aspect);
	void SetPosition(glm::vec3 position);

	float GetNear();
	float GetFar();
	float GetAperture();
	float GetAspect();
	glm::vec3 GetPosition();

	void LookAt(glm::vec3 to, glm::vec3 up);
	void Move(glm::vec3 offset, float speed = 1.0f);
	void Rotate(float yaw, float pitch, float speed = 0.1f);
	void UpdateAxis();

	glm::mat4 GetMatProj();
	glm::mat4 GetMatView();
	void UploadMatProj();
	void UploadMatView();
};