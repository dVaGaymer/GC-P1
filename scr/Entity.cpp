#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>
#include <iostream>

#include "Entity.h"

/*
* Change Position relative to current position
* Offset is calculated relative to local rotation
* offset -> (x Local offset, y Local offset, z Local offset)
*/
void	Entity::MoveLocal(glm::vec3 offset)
{
	this->position = glm::vec3(this->GetTransform() *glm::vec4(offset, 1.0f));
}
/*
* Change Position relative to current position
* Offset is calculated relative to world
* offset -> (x Local offset, y Local offset, z Local offset)
*/
void	Entity::MoveWorld(glm::vec3 offset)
{
	this->position += offset;
}
void Entity::RotateX(float angle)
{
	glm::mat4 xRot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	this->rotationMat = this->rotationMat * xRot;
}
void Entity::RotateY(float angle)
{
	glm::mat4 yRot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	this->rotationMat = this->rotationMat * yRot;
}
void Entity::RotateZ(float angle)
{
	glm::mat4 zRot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	this->rotationMat = this->rotationMat * zRot;
}
void	Entity::SetPosition(glm::vec3 position)
{
	this->position = position;
}
void Entity::SetRotationMat(glm::mat4 rotationMat) { this->rotationMat = rotationMat; }
void	Entity::SetScale(glm::vec3 scale) { this->scale = scale; }

glm::mat4	Entity::GetMatTranslation()
{
	return glm::translate(glm::mat4(1.0f), this->position);
}
glm::mat4	Entity::GetMatRotation()
{
	return this->rotationMat;
}
glm::mat4	Entity::GetMatScale()
{
	glm::mat4 scale(1.0f);
	scale[0][0] = this->scale.x;
	scale[1][1] = this->scale.y;
	scale[2][2] = this->scale.z;
	return scale;
}

glm::mat4 Entity::GetTransform()
{
	return	GetMatTranslation() *
		GetMatRotation() *
		GetMatScale();
}

/*
* Change Rotation relative to current rotation
*/
void	Entity::Rotate(glm::vec3 offset, bool eulerRotation)
{
	glm::mat4 offsetMat(1.0f);
	if (!eulerRotation)
		offsetMat = glm::rotate(glm::mat4(1.0), glm::radians(offset.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(offset.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(offset.z), glm::vec3(0, 0, 1));
	else
		offsetMat = glm::rotate(glm::mat4(1.0), glm::radians(offset.z), glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0), glm::radians(offset.y), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(offset.x), glm::vec3(0, 0, 1));
	rotationMat += offsetMat;
}