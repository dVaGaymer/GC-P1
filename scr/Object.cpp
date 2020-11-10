#include "Object.h"

void Object::SetParent(Object* parent) { this->parent = parent; }
int Object::GetObjId() { return this->objId; }

glm::mat4 Object::GetMatModel()
{
	if (this->parent)
		return	this->parent->GetMatTranslation() *
				this->parent->GetMatRotation() *
				GetMatTranslation() *
				GetMatRotation() *
				GetMatScale();
	else
		return	GetMatTranslation() *
				GetMatRotation() *
				GetMatScale();
}