#include "Object.h"

/*
* Object properties
*/
void Object::SetTexPath(const char* texPath) { this->texPath = texPath; }
void Object::SetParent(Object* parent) { this->parent = parent; }
void Object::SetObjId(int objId) { this->objId = objId;  };
void Object::SetObjId(unsigned int nTriangles, unsigned int nVertex,
	const unsigned int* triangleIdx, const float* vertexPos,
	const float* vertexColor, const float* vertexNormal,
	const float* vertexTexCoord, const float* vertexTangent)
{ this->objId = IGlib::createObj(nTriangles, nVertex, triangleIdx, vertexPos, vertexColor, vertexNormal, vertexTexCoord, vertexTangent); }
int Object::GetObjId() { return this->objId; }

glm::vec3	Object::GetPositionRelativeToWorld() { return this->GetMatModel() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); }
void		Object::SetPosition(glm::vec3 position) { this->position = position; }
void		Object::SetRotationMat(glm::mat4 rotationMat) { this->rotationMat = rotationMat; }
void		Object::SetScale(glm::vec3 scale) { this->scale = scale; }

/*
* Movement
*/
void	Object::MoveLocal(glm::vec3 offset) { this->position = glm::vec3(this->GetTransform() * glm::vec4(offset, 1.0f)); }
void	Object::MoveWorld(glm::vec3 offset) { this->position += offset; }

/*
* Rotation
*/
void Object::RotateX(float angle)
{
	glm::mat4 xRot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	this->rotationMat = this->rotationMat * xRot;
}
void Object::RotateY(float angle)
{
	glm::mat4 yRot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	this->rotationMat = this->rotationMat * yRot;
}
void Object::RotateZ(float angle)
{
	glm::mat4 zRot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	this->rotationMat = this->rotationMat * zRot;
}
void	Object::Rotate(glm::vec3 offset, bool eulerRotation)
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
	rotationMat *= offsetMat;
}

/*
* Object Transforms
*/
glm::mat4	Object::GetMatTranslation() { return glm::translate(glm::mat4(1.0f), this->position); }
glm::mat4	Object::GetMatRotation() { return this->rotationMat; }
glm::mat4	Object::GetMatScale()
{
	glm::mat4 scale(1.0f);
	scale[0][0] = this->scale.x;
	scale[1][1] = this->scale.y;
	scale[2][2] = this->scale.z;
	return scale;
}
glm::mat4 Object::GetTransform()
{
	return	GetMatTranslation() *
			GetMatRotation() *
			GetMatScale();
}
glm::mat4 Object::GetMatModel()
{
	if (this->parent)
		return	this->parent->GetMatModel() * this->GetTransform();
	else
		return	this->GetTransform();
}

/*
* Upload transforms and texture to GPU
*/
void Object::UploadTexture(const char* texPath)
{
	this->SetTexPath(texPath);
	this->UploadTexture();
}
void Object::UploadTexture() { IGlib::addColorTex(this->objId, this->texPath); }
void Object::UploadMatModel() { IGlib::setModelMat(this->objId, this->GetMatModel()); }