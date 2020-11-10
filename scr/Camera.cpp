#include "Camera.h"
#include <iostream>

void Camera::SetAspect(float aspect) { this->aspect = aspect; }
void Camera::SetAperture(float aperture) { this->aperture = aperture; }
void Camera::SetNear(float near) { this->near = near; }
void Camera::SetFar(float far) { this->far = far; }

glm::mat4 Camera::GetMatView()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), this->position);
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = this->GetRotatedAxis().right.x;
	rotation[0][1] = this->GetRotatedAxis().right.y;
	rotation[0][2] = this->GetRotatedAxis().right.z;

	rotation[1][0] = this->GetRotatedAxis().up.x;
	rotation[1][1] = this->GetRotatedAxis().up.y;
	rotation[1][2] = this->GetRotatedAxis().up.z;

	rotation[2][0] = this->GetRotatedAxis().forward.x;
	rotation[2][1] = this->GetRotatedAxis().forward.y;
	rotation[2][2] = this->GetRotatedAxis().forward.z;
	return glm::inverse(translation * rotation);
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