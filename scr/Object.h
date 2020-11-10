#pragma once
#include <IGL/IGlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity.h"

class Object : public Entity
{
private:
	int objId;
	Object* parent;

public:
	Object(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent)
		:objId(IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent)),
		parent(nullptr),
		Entity() {}
	Object(int objId)
		:objId(objId),
		parent(nullptr),
		Entity() {}
	Object(glm::vec3 position)
		:objId(-1),
		parent(nullptr),
		Entity(position) {}
	Object(glm::vec3 position, glm::vec3 rotation, float scale)
		:objId(-1),
		parent(nullptr),
		Entity(position, rotation, scale) {}

	void SetParent(Object* parent);

	int GetObjId();
	glm::mat4 GetMatModel();
};