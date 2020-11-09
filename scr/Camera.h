#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IGL/IGlib.h>

class Camera
{
private:
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 position;

	float near, far, aperture, aspect;

public:
	Camera();

	void SetPosition(glm::vec3 position);
	void SetAspect(float aspect);
	void SetApreture(float aperture);
	void SetNear(float near);
	void SetFar(float far);

	void MoveForward(float offset);
	void MoveUpDown(float offset);
	void MoveSide(float offset);

	void RotateUp(float angle);
	void RotateRight(float angle);
	void RotateForward(float angle);

	glm::vec3 GetlookAt() { return this->forward; }
	glm::vec3 GetUp() { return this->up; }
	glm::vec3 GetRight() { return this->right; }
	glm::vec3 GetPosition() { return this->position; }
	float GetNear() { return this->near; }
	float GetFar() { return this->far; }
	float GetAperture() { return this->aperture; }
	float GetAspect() { return this->aspect; }

	glm::mat4 GetViewMat();
	glm::mat4 GetProjMat();
};