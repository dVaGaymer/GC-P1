#include "Camera.h"
#include <iostream>

void Camera::SetAspect(float aspect){ this->aspect = aspect; }
void Camera::SetAperture(float aperture) { this->aperture = aperture; }
void Camera::SetNear(float near) { this->near = near; }
void Camera::SetFar(float far) { this->far = far; }

float Camera::GetNear() { return this->near; }
float Camera::GetFar() { return this->far; }
float Camera::GetAperture() { return this->aperture; }
float Camera::GetAspect() { return this->aspect; }

//TODO GetMatView using from & to
glm::mat4 Camera::GetMatView()
{
	return  glm::inverse(this->GetTransform());
}

glm::mat4 Camera::GetMatProj()
{
	float r = glm::tan(glm::radians(this->aperture) / 2), l = -glm::tan(glm::radians(this->aperture) / 2);
	float t = r / this->aspect, b = l / this->aspect;
	glm::mat4 proj = glm::mat4(0.0f);
	proj[0].x = (2 * this->near) / (r - l);
	proj[1].y = (2 * this->near) / (t - b);
	proj[2].x = (r + l) / (r - l);
	proj[2].y = (t + b) / (t - b);
	proj[2].z = -(this->far + this->near) / (this->far - this->near);
	proj[2].w = -1.0f;
	proj[3].z = -(2.0f * this->near * this->far) / (this->far - this->near);
	return proj;
}

void Camera::UploadMatProj()
{
	IGlib::setProjMat(this->GetMatProj());
}
void Camera::UploadMatView()
{
	IGlib::setViewMat(this->GetMatView());
}