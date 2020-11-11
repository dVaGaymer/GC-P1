#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>
#include <iostream >

/*
* position is relative to parent (parent is world if null)
* rotation is relative to itself
*/

typedef struct	s_axis
{
	union
	{
		glm::vec3 x;
		glm::vec3 right;
	};
	union
	{
		glm::vec3 y;
		glm::vec3 up;
	};
	union
	{
		glm::vec3 z;
		glm::vec3 forward;
	};
}				t_axis;

class Entity
{
protected:
	glm::vec3	position;
	glm::vec3	rotation;
	glm::vec3	scale;

	glm::mat4	rotationMat;
public:
	//TODO change axis compatibilit
	Entity()
		:position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f),
		scale(1),
		rotationMat(1.0f) {}
	Entity(glm::vec3 position)
		:position(position),
		rotation(0.0f, 0.0f, 0.0f),
		scale(1),
		rotationMat(1.0f) {}
	Entity(glm::vec3 position, glm::vec3 rotation, float scale)
		:position(position),
		rotation(rotation),
		scale(scale),
		rotationMat(1.0f) {}

	void MoveLocal(glm::vec3 offset);
	void MoveWorld(glm::vec3 offset);
	void Rotate(glm::vec3 offset, bool eulerRotation = true);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	//TODO SetPosition relative to Local
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetRotationMat(glm::mat4 rotationMat);
	void SetScale(glm::vec3 scale);

	glm::mat4 GetMatTranslation();
	glm::mat4 GetMatRotation();
	glm::mat4 GetMatScale();
	glm::mat4 GetTransform();
};