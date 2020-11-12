#include "Camera.h"
#include <iostream>

void Camera::SetAspect(float aspect){ this->aspect = aspect; }
void Camera::SetAperture(float aperture) { this->aperture = aperture; }
void Camera::SetNear(float near) { this->near = near; }
void Camera::SetFar(float far) { this->far = far; }
void Camera::SetPosition(glm::vec3 position) { this->position = position; }

float Camera::GetNear() { return this->near; }
float Camera::GetFar() { return this->far; }
float Camera::GetAperture() { return this->aperture; }
float Camera::GetAspect() { return this->aspect; }
glm::vec3 Camera::GetPosition() { return this->position; }

void Camera::UploadMatProj() { IGlib::setProjMat(this->GetMatProj()); }
void Camera::UploadMatView() { IGlib::setViewMat(GetMatView()); }

void Camera::LookAt(glm::vec3 to, glm::vec3 up)
{
	this->axis.forward = glm::normalize(this->position - to);
	this->axis.right = glm::normalize(glm::cross(up, this->axis.forward));
	this->axis.up = glm::cross(this->axis.forward, this->axis.right);
}
glm::mat4 Camera::GetMatProj()
{
	float r, t, b, l;
	t = glm::tan(glm::radians(this->aperture / 2));
	b = -t;
	r = t * this->aspect;
	l = b * this->aspect;
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
glm::mat4 Camera::GetMatView()
{
	glm::mat4 lookAt(1.0f);
	lookAt[0][0] = this->axis.right.x;
	lookAt[1][0] = this->axis.right.y;
	lookAt[2][0] = this->axis.right.z;
	lookAt[0][1] = this->axis.up.x;
	lookAt[1][1] = this->axis.up.y;
	lookAt[2][1] = this->axis.up.z;
	lookAt[0][2] = this->axis.forward.x;
	lookAt[1][2] = this->axis.forward.y;
	lookAt[2][2] = this->axis.forward.z;

	lookAt[3][0] = -glm::dot(this->axis.right, this->position);
	lookAt[3][1] = -glm::dot(this->axis.up, this->position);
	lookAt[3][2] = -glm::dot(this->axis.forward, this->position);

	return lookAt;
}

void Camera::Move(glm::vec3 offset, float speed)
{
	this->position += (offset.z * speed) * this->axis.forward;
	this->position += (offset.x * speed) * this->axis.right;
	this->position += (offset.y * speed) * this->axis.up;
}

void Camera::Rotate(float pitchOffset, float yawOffset, float speed)
{ 
	this->eulerAngles.x -= yawOffset * speed;
	this->eulerAngles.y -= pitchOffset * speed;
	if (this->eulerAngles.y > 89.0f)
		this->eulerAngles.y = 89.0f;
	if (this->eulerAngles.y < -89.0f)
		this->eulerAngles.y = -89.0f;
	UpdateAxis();
}

void Camera::UpdateAxis()
{
	this->axis.forward.x = glm::cos(glm::radians(this->eulerAngles.x)) * glm::cos(glm::radians(this->eulerAngles.y));
	this->axis.forward.y = glm::sin(glm::radians(this->eulerAngles.y));
	this->axis.forward.z = glm::sin(glm::radians(this->eulerAngles.x)) * glm::cos(glm::radians(this->eulerAngles.y));
	this->axis.forward = glm::normalize(this->axis.forward);

	this->axis.right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->axis.forward));
	this->axis.up = glm::normalize(glm::cross(this->axis.forward, this->axis.right));
}