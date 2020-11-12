#include "Object.h"

void Object::SetParent(Object* parent) { this->parent = parent; }
int Object::GetObjId() { return this->objId; }

void Object::SetObjId(unsigned int nTriangles, unsigned int nVertex,
	const unsigned int* triangleIdx, const float* vertexPos,
	const float* vertexColor, const float* vertexNormal,
	const float* vertexTexCoord, const float* vertexTangent)
{ this->objId = IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent); }
void Object::SetTexPath(const char* texPath) { this->texPath = texPath; }

glm::mat4 Object::GetMatModel()
{
	if (this->parent)
		return	this->parent->GetMatModel() * this->GetTransform();
	else
		return	this->GetTransform();
}

void Object::UploadTexture()
{
	IGlib::addColorTex(this->objId, this->texPath);
}

void Object::UploadTexture(const char* texPath)
{
	this->SetTexPath(texPath);
	this->UploadTexture();
}

void Object::UploadMatModel()
{
	IGlib::setModelMat(this->objId, this->GetMatModel());
}

void Object::ResetTransform()
{
	parent = nullptr;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	rotationMat = glm::mat4(1.0f);
}

glm::vec3 Object::GetPosition()
{
	return this->GetMatModel() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}