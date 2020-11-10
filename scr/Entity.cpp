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
void Entity::MoveLocal(glm::vec3 offset)
{
	this->position.x += GetRotatedAxis().x[0] * offset.x;
	this->position.y += GetRotatedAxis().x[1] * offset.x;
	this->position.z += GetRotatedAxis().x[2] * offset.x;

	this->position.x += GetRotatedAxis().y[0] * offset.y;
	this->position.y += GetRotatedAxis().y[1] * offset.y;
	this->position.z += GetRotatedAxis().y[2] * offset.y;

	this->position.x += GetRotatedAxis().z[0] * offset.z;
	this->position.y += GetRotatedAxis().z[1] * offset.z;
	this->position.z += GetRotatedAxis().z[2] * offset.z;
}
/*
* Change Position relative to current position
* Offset is calculated relative to world
* offset -> (x Local offset, y Local offset, z Local offset)
*/
void Entity::MoveWorld(glm::vec3 offset)
{
	this->position.x += offset.x;
	this->position.y += offset.y;
	this->position.z += offset.z;
}
/*
* Change Rotation relative to current rotation
*/
void Entity::Rotate(glm::vec3 offset)
{
	this->rotation.x += this->rotation.x >= 360 ? offset.x - 360 : offset.x;
	this->rotation.y += this->rotation.y >= 360 ? offset.y - 360 : offset.y;
	this->rotation.z += this->rotation.z >= 360 ? offset.z - 360 : offset.z;
}
void Entity::SetPosition(glm::vec3 position) { this->position = position; }
void Entity::SetRotation(glm::vec3 rotation) { this->rotation = rotation; }
void Entity::SetScale(glm::vec3 scale) { this->scale = scale; }

glm::mat4 Entity::GetMatTranslation()
{
	return glm::translate(glm::mat4(1.0f), this->position);
}
glm::mat4 Entity::GetMatRotation()
{
	return	glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.y), glm::vec3(0, 1, 0)) *
			glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.z), glm::vec3(0, 0, 1));
}
glm::mat4 Entity::GetMatScale()
{
	glm::mat4 scale(1.0f);
	scale[0][0] = this->scale.x;
	scale[1][1] = this->scale.y;
	scale[2][2] = this->scale.z;
	return scale;
}

t_axis Entity::GetRotatedAxis()
{
	t_axis axis;
	/*this->right = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->up) * glm::vec4(this->right, 0);
	this->forward = glm::cross(this->right, this->up);

	this->forward = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->right) * glm::vec4(this->forward, 0);
	this->up = glm::cross(this->forward, this->right);

	this->up = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->forward) * glm::vec4(this->up, 0);
	this->right = glm::cross(this->up, this->forward);*/

	axis.right = glm::normalize(GetMatRotation() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	axis.up = glm::normalize(GetMatRotation() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	axis.forward = glm::normalize(GetMatRotation() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	return axis;
}