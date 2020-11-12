#pragma once
#include <IGL/IGlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object
{
private:
	int objId;
	const char* texPath;
	Object* parent;

	glm::vec3	position;
	glm::mat4	rotationMat;
	glm::vec3	scale;

public:
	Object(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent)
		:objId(IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent)),
		texPath(nullptr),
		parent(nullptr),
		position(0.0f, 0.0f, 0.0f),
		rotationMat(1.0f),
		scale(1) {}
	Object(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent, const char* texPath)
		:objId(IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent)),
		texPath(texPath),
		parent(nullptr),
		position(0.0f, 0.0f, 0.0f),
		rotationMat(1.0f),
		scale(1) { UploadTexture(); }
	Object()
		:objId(-1),
		texPath(nullptr),
		parent(nullptr),
		position(0.0f, 0.0f, 0.0f),
		rotationMat(1.0f),
		scale(1) {}
	void SetObjId(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent);
	void SetObjId(int objId);
	void SetTexPath(const char* texPath);
	void SetParent(Object* parent);
	int GetObjId();

	void SetPosition(glm::vec3 position);
	void SetRotationMat(glm::mat4 rotationMat);
	void SetScale(glm::vec3 scale);

	/*
	* Object Movement
	*/
	void MoveLocal(glm::vec3 offset);
	void MoveWorld(glm::vec3 offset);

	/*
	* Object Rotation
	*/
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Rotate(glm::vec3 offset, bool eulerRotation = true);

	/*
	* Object Transforms
	*/
	glm::mat4 GetMatTranslation();
	glm::mat4 GetMatRotation();
	glm::mat4 GetMatScale();
	glm::mat4 GetTransform();
	glm::vec3 GetPositionRelativeToWorld();

	/*
	* Upload to GPU Object Matrices
	*/
	glm::mat4 GetMatModel();
	void UploadMatModel();
	void UploadTexture();
	void UploadTexture(const char* texPath);
};