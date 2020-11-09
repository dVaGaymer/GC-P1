#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>
#include <iostream>

#include "Entity.h"

Object::Object(	unsigned int nTriangles,				unsigned int nVertex,
				const unsigned int* triangleIdx,	const float* vertexPos,
				const float* vertexColor = NULL,	const float* vertexNormal = NULL,
				const float* vertexTexCoord = NULL, const float* vertexTangent = NULL)
	:objId(IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent)) {}

Object::Object(int objId)
	:objId(objId) {}

Entity::Entity(unsigned int nTriangles, unsigned int nVertex,
	const unsigned int* triangleIdx, const float* vertexPos,
	const float* vertexColor = NULL, const float* vertexNormal = NULL,
	const float* vertexTexCoord = NULL, const float* vertexTangent = NULL)
	:Object(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent),
	parent(nullptr),
	texture_path(nullptr),
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f),
	scale(1.0f) {}

Entity::Entity(int objId)
	: Object(objId),
	parent(nullptr),
	texture_path(nullptr),
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f),
	scale(1.0f) {}

void Entity::SetParent(Object* parent)
{
	this->parent = parent;
}

/*
* Degrees
* Recieve World coordinates
*/
void Entity::AddRotation(glm::vec3 angles)
{
	this->rotation.x += this->rotation.x >= 360 ? angles.x - 360 : angles.x;
	this->rotation.y += this->rotation.y >= 360 ? angles.y - 360 : angles.y;
	this->rotation.z += this->rotation.z >= 360 ? angles.z - 360 : angles.z;
}
void Entity::SetRotation(glm::vec3 rotation) { this->rotation = rotation; }

void Entity::AddPosition(glm::vec3 offset)
{
	this->position.x += offset.x;
	this->position.y += offset.y;
	this->position.z += offset.z;
}
void Entity::SetPosition(glm::vec3 position) { this->position = position; }

void Entity::SetScale(float scale) { this->scale = scale; }

glm::mat4 Entity::GetRot(bool using_euler_angles)
{
	if (using_euler_angles)
		return	glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.z), glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.y), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.x), glm::vec3(0, 0, 1));
	else if (!using_euler_angles)
		return	glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.z), glm::vec3(0, 0, 1));
}
glm::mat4 Entity::GetTrans()
{
	return glm::translate(glm::mat4(1.0f), this->position);
}
glm::mat4 Entity::GetScale()
{
	return glm::mat4(this->scale);
}

glm::mat4 Entity::GetModelMat(bool using_euler_angles)
{
	if (this->parent)
		return	this->parent->GetTrans() *
			this->parent->GetRot() *
			GetTrans() *
			GetRot() *
			GetScale();
	else
		return	GetTrans() *
				GetRot() *
				GetScale();
}