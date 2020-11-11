#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <iomanip>

#include "Object.h"
#include "Entity.h"
#include "Camera.h"

//Idenficadores de los objetos de la escena
Object *sun;
Object *earth, *middleLayer, *innerLayer;
Object *moon;
Object *cubo0, *cubo1;
Camera *camera;

//Declaración de CB
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);

int main(int argc, char** argv)
{
	std::locale::global(std::locale("spanish"));// acentos ;)
	if (!IGlib::init("../shaders_P1/shader.v11b.vert", "../shaders_P1/shader.v11b.frag"))
		return -1;
   
	//Se ajusta la cámara
	camera = &Camera();
	camera->UploadMatView();
	
	//Se crean objetos
	cubo0 = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	cubo0->UploadTexture("../img/cleanUnicorn.png");
	cubo1 = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	cubo1->UploadTexture("../img/cleanUnicorn.png");

	sun = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	sun->UploadTexture("../img/sun.png");
	earth = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	earth->UploadTexture("../img/earth.png");
	middleLayer = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	middleLayer->UploadTexture("../img/middleLayer.png");
	innerLayer = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	innerLayer->UploadTexture("../img/innerLayer.png");
	moon = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	moon->UploadTexture("../img/moon.png");

	cubo1->SetParent(cubo0);

	earth->SetParent(sun);
	innerLayer->SetParent(earth);
	middleLayer->SetParent(earth);
	moon->SetParent(earth);

	//Test Position
	cubo0->SetPosition(glm::vec3(0.0f, 0.0f, -30.0f));
	cubo1->SetPosition(glm::vec3(-10.0f, 0.0f, 0.0f));

	sun->SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
	earth->SetPosition(glm::vec3(-6.0f, 0.0f, 0.0f));
	middleLayer->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	innerLayer->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	moon->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	//Test Rotation
	sun->Rotate(glm::vec3(0.0f, 0.0f, 0.0f));
	earth->Rotate(glm::vec3(0.0f, 0.0f, 0.0f));

	//Test Scale
	sun->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	earth->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	middleLayer->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
	innerLayer->SetScale(glm::vec3(0.4f, 0.4f, 0.4f));
	moon->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));

	//Upload Matrices to GPU
	cubo0->UploadMatModel();
	cubo1->UploadMatModel();

	sun->UploadMatModel();
	earth->UploadMatModel();
	middleLayer->UploadMatModel();
	innerLayer->UploadMatModel();
	moon->UploadMatModel();

	//CBs
	IGlib::setResizeCB(resizeFunc);
	IGlib::setIdleCB(idleFunc);
	IGlib::setKeyboardCB(keyboardFunc);
	IGlib::setMouseCB(mouseFunc);
	IGlib::setMouseMoveCB(mouseMotionFunc);
	
	//Mainloop
	IGlib::mainLoop();
	IGlib::destroy();
	return 0;
}

void resizeFunc(int width, int height)
{
	camera->SetAspect((float)width / (float)height);
	camera->UploadMatProj();
}

void idleFunc()
{
	float rotationSpeed = 1.0f;
	cubo0->RotateY(rotationSpeed);
	cubo1->RotateY(-5.0 * rotationSpeed);

	sun->RotateY(rotationSpeed);
	earth->Rotate(glm::vec3(0.0f, 0.0f, 1.0f) * rotationSpeed);
	middleLayer->Rotate(glm::vec3(0.0f, -1.0f, 1.0f) * rotationSpeed);
	innerLayer->Rotate(glm::vec3(1.0f, 1.0f, -1.0f) * rotationSpeed);
	moon->Rotate(glm::vec3(1.0f, 1.0f, 0.0f));

	sun->UploadMatModel();
	earth->UploadMatModel();
	middleLayer->UploadMatModel();
	innerLayer->UploadMatModel();
	moon->UploadMatModel();
	cubo0->UploadMatModel();
	cubo1->UploadMatModel();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	std::cout << "Se ha pulsado la tecla " << key << std::endl << std::endl;
	//Camera Movement
	float movementSpeed = 1.0f;
	if (key == 'w')
		camera->MoveLocal(glm::vec3(0.0f, 0.0f, -1.0f) * movementSpeed);
	if (key == 's')
		camera->MoveLocal(glm::vec3(0.0f, 0.0f, 1.0f) * movementSpeed);
	if (key == 'a')
		camera->MoveLocal(glm::vec3(-1.0f, 0.0f, 0.0f) * movementSpeed);
	if (key == 'd')
		camera->MoveLocal(glm::vec3(1.0f, 0.0f, 0.0f) * movementSpeed);
	if (key == 'q')
		camera->MoveLocal(glm::vec3(0.0f, 1.0f, 0.0f) * movementSpeed);
	if (key == 'e')
		camera->MoveLocal(glm::vec3(0.0f, -1.0f, 0.0f) * movementSpeed);

	//Camera Rotation
	float rotationSpeed = 2.0f;
	if (key == 'i')
		camera->RotateX(rotationSpeed);
	if (key == 'k')
		camera->RotateX(-rotationSpeed);
	if (key == 'j')
		camera->RotateY(rotationSpeed);
	if (key == 'l')
		camera->RotateY(-rotationSpeed);
	if (key == 'u')
		camera->RotateZ(rotationSpeed);
	if (key == 'o')
		camera->RotateZ(-rotationSpeed);

	//Camera Aperture
	if (key == 'z')
		camera->SetAperture(camera->GetAperture() + 1.0f);
	if (key == 'x')
		camera->SetAperture(camera->GetAperture() - 1.0f);

	//Fast change between "scenes"
	if (key == '0')
	{
		camera->SetRotationMat(glm::mat4(1.0f));
		camera->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
		camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (key == '1')
	{
		camera->SetRotationMat(glm::mat4(1.0f));
		camera->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
		camera->RotateY(180);
		camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	camera->UploadMatView();
	camera->UploadMatProj();
}

void mouseFunc(int button, int state, int x, int y)
{
	if (state==0)
		std::cout << "Se ha pulsado el botón ";
	else
		std::cout << "Se ha soltado el botón ";
	
	if (button == 0) std::cout << "de la izquierda del ratón " << std::endl;
	if (button == 1) std::cout << "central del ratón " << std::endl;
	if (button == 2) std::cout << "de la derecha del ratón " << std::endl;

	std::cout << "en la posición " << x << " " << y << std::endl << std::endl;
}

void mouseMotionFunc(int x, int y)
{
	std::cout << "x: " << x << " y: " << y << std::endl;
}
