#include "Camera.h"
#include <iostream>

Camera::Camera()
	:forward(0.0f, 0.0f, 1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f), position(0.0f, 0.0f, 0.0f),
	near(1), far(50), aperture(60), aspect(1)
{
}

void Camera::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Camera::SetAspect(float aspect) { this->aspect = aspect; }
void Camera::SetApreture(float aperture) { this->aperture = aperture; }
void Camera::SetNear(float near) { this->near = near; }
void Camera::SetFar(float far) { this->far = far; }

/*
* Revcieve Camera coordinates
*/
void Camera::MoveForward(float offset)
{
	this->position.x += this->forward.x * offset;
	this->position.y += this->forward.y * offset;
	this->position.z += this->forward.z * offset;
}
void Camera::MoveUpDown(float offset)
{
	this->position.x += this->up.x * offset;
	this->position.y += this->up.y * offset;
	this->position.z += this->up.z * offset;
}
void Camera::MoveSide(float offset)
{
	this->position.x += this->right.x * offset;
	this->position.y += this->right.y * offset;
	this->position.z += this->right.z * offset;
}
void Camera::RotateUp(float angle)
{
	this->right = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->up) * glm::vec4(this->right, 0);
	this->forward = glm::cross(this->right, this->up);
}
void Camera::RotateRight(float angle)
{
	this->forward = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->right) * glm::vec4(this->forward, 0);
	this->up = glm::cross(this->forward, this->right);
}
void Camera::RotateForward(float angle)
{
	this->up = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->forward) * glm::vec4(this->up, 0);
	this->right = glm::cross(this->up, this->forward);
}

glm::mat4 Camera::GetViewMat()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), this->position);
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = this->right.x;
	rotation[0][1] = this->right.y;
	rotation[0][2] = this->right.z;

	rotation[1][0] = this->up.x;
	rotation[1][1] = this->up.y;
	rotation[1][2] = this->up.z;

	rotation[2][0] = this->forward.x;
	rotation[2][1] = this->forward.y;
	rotation[2][2] = this->forward.z;
	return glm::inverse(translation * rotation);
}

glm::mat4 Camera::GetProjMat()
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