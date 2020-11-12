#pragma once
#include <IGL/IGlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity.h"

class Object : public Entity
{
private:
	int objId;
	const char* texPath;
	Object* parent;

public:
	Object(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent)
		:objId(IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent)),
		texPath(nullptr),
		parent(nullptr),
		Entity() {}
	Object(int objId)
		:objId(objId),
		texPath(nullptr),
		parent(nullptr),
		Entity() {}
	Object(int objId, const char* texPath)
		:objId(objId),
		texPath(texPath),
		parent(nullptr),
		Entity() {}
	Object(glm::vec3 position)
		:objId(-1),
		texPath(nullptr),
		parent(nullptr),
		Entity(position) {}
	Object(glm::vec3 position, glm::vec3 rotation, float scale)
		:objId(-1),
		texPath(nullptr),
		parent(nullptr),
		Entity(position, rotation, scale) {}

	void SetObjId(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent);
	void SetTexPath(const char* texPath);
	void SetParent(Object* parent);

	int GetObjId();
	glm::mat4 GetMatModel();

	void UploadMatModel();
	void UploadTexture();
	void UploadTexture(const char* texPath);

	void Object::ResetTransform();
	glm::vec3 Object::GetPosition();
};