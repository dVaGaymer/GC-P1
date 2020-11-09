#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>

class Object
{
private:
	int objId;
public:
	Object(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent);
	Object(int objId);
	inline int getObjId() { return objId; }

	virtual glm::mat4 GetRot(bool using_euler_angles = false) = 0;
	virtual glm::mat4 GetTrans() = 0;
	virtual glm::mat4 GetScale() = 0;
};

/*
* position is relative to parent (parent is world if null)
* rotation is relative to itself
*/
class Entity : public Object
{
private:
	Object* parent;
	const char* texture_path;

	glm::vec3 position;
	glm::vec3 rotation;
	float	scale;
public:
	Entity(unsigned int nTriangles, unsigned int nVertex,
		const unsigned int* triangleIdx, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent);
	Entity(int objId);

	void SetParent(Object* parent);

	void AddRotation(glm::vec3 angles);
	void SetRotation(glm::vec3 rotation);
	void AddPosition(glm::vec3 offset);
	void SetPosition(glm::vec3 position);

	void SetScale(float scale);

	glm::mat4 GetRot(bool using_euler_angles = false);
	glm::mat4 GetTrans();
	glm::mat4 GetScale();

	glm::mat4 GetModelMat(bool using_euler_angles = false);
};