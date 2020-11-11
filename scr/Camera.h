#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>

#include "Entity.h"

class Camera : public Entity
{
private:
	float near;
	float far;
	float aperture;
	float aspect;

public:
	Camera()
		:near(1), far(50), aperture(60), aspect(1), Entity() {}
	Camera(glm::vec3 position)
		:near(1), far(50), aperture(60), aspect(1), Entity(position) {}
	Camera(glm::vec3 position, float far, float near, float aperture, float aspect)
		:near(near), far(far), aperture(aperture), aspect(aspect), Entity(position) {}

	void SetNear(float near);
	void SetFar(float far);
	void SetAperture(float aperture);
	void SetAspect(float aspect);

	float GetNear();
	float GetFar();
	float GetAperture();
	float GetAspect();

	glm::mat4 GetMatView();
	glm::mat4 GetMatProj();

	void UploadMatProj();
	void UploadMatView();
};