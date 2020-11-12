#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>
#include <iostream >

/*
* position is relative to parent (parent is world if null)
* rotation is relative to itself
*/

class Entity
{
protected:
	glm::vec3	position;
	glm::vec3	scale;

	glm::mat4	rotationMat;
public:
	//TODO change axis compatibilit
	Entity()
		:position(0.0f, 0.0f, 0.0f),
		scale(1),
		rotationMat(1.0f) {}
	Entity(glm::vec3 position)
		:position(position),
		scale(1),
		rotationMat(1.0f) {}
	Entity(glm::vec3 position, glm::vec3 rotation, float scale)
		:position(position),
		scale(scale),
		rotationMat(1.0f) {}

	void MoveLocal(glm::vec3 offset);
	void MoveWorld(glm::vec3 offset);

	virtual void RotateX(float angle);
	virtual void RotateY(float angle);
	virtual void RotateZ(float angle);
	void Rotate(glm::vec3 offset, bool eulerRotation = true);

	void SetPosition(glm::vec3 position);
	virtual glm::vec3 Entity::GetPosition() = 0;

	void SetRotationMat(glm::mat4 rotationMat);

	void SetScale(glm::vec3 scale);

	glm::mat4 GetMatTranslation();
	glm::mat4 GetMatRotation();
	glm::mat4 GetMatScale();

	glm::mat4 Entity::GetTransform();
	virtual void ResetTransform() = 0;
};