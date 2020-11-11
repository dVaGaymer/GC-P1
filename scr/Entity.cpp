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
	this->position = glm::vec3(this->GetMatTranslation() * this->GetMatRotation() * this->GetMatScale() * glm::vec4(offset, 1.0f));
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
/*
* Change Rotation relative to current rotation
*/
void	Entity::Rotate(glm::vec3 offset, bool eulerRotation)
{
	this->rotation.x += this->rotation.x >= 360 ? offset.x - 360 : offset.x;
	this->rotation.y += this->rotation.y >= 360 ? offset.y - 360 : offset.y;
	this->rotation.z += this->rotation.z >= 360 ? offset.z - 360 : offset.z;

	if (!eulerRotation)
		this->rotationMat = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.z), glm::vec3(0, 0, 1));
	else
		this->rotationMat = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.z), glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.y), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.x), glm::vec3(0, 0, 1));
}
void Entity::RotateX(float angle)
{
	this->rotationMat = this->rotationMat * glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
}
void Entity::RotateY(float angle)
{
	this->rotationMat = this->rotationMat * glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
}
void Entity::RotateZ(float angle)
{
	this->rotationMat = this->rotationMat * glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}
void	Entity::SetPosition(glm::vec3 position)
{
	this->position = position;
}
void Entity::SetRotationMat(glm::mat4 rotationMat) { this->rotationMat = rotationMat; }
void	Entity::SetRotation(glm::vec3 rotation) { this->rotation = rotation; }
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