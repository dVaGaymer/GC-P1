#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <iomanip>

#include "Object.h"
#include "Camera.h"

//Idenficadores de los objetos de la escena
Object *cubo0;
Object *cubo1, *traslacion1;
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
	if (!IGlib::init("../shaders_P1/shader.v11a.vert", "../shaders_P1/shader.v11a.frag"))
		return -1;

	//Se ajusta la cámara
	camera = &Camera(glm::vec3(0.0f, 0.0f, -15.0f));
	camera->UploadMatView();

	//Se crean objetos
	cubo0 = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent, "../img/color.png");
	cubo1 = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent, "../img/moon.png");
	traslacion1 = &Object();

	//Set Position
	cubo0->SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	cubo0->UploadMatModel();
	//Traslacion cubo1 sobre cubo0
	traslacion1->SetPosition(cubo0->GetPositionRelativeToWorld());
	cubo1->SetParent(traslacion1);
	cubo1->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	cubo1->UploadMatModel();

	//Upload Matrices to GPU
	cubo0->UploadMatModel();
	cubo1->UploadMatModel();

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
	traslacion1->RotateY(1 * rotationSpeed);
	cubo1->RotateY(2 * rotationSpeed);
	cubo1->UploadMatModel();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	std::cout << "Se ha pulsado la tecla " << key << std::endl << std::endl;
	//Camera Movement
	float movementSpeed = 0.5f;
	if (key == 'w')
		camera->Move(glm::vec3(0.0f, 0.0f, -1.0f), movementSpeed);
	if (key == 's')
		camera->Move(glm::vec3(0.0f, 0.0f, 1.0f), movementSpeed);
	if (key == 'a')
		camera->Move(glm::vec3(-1.0f, 0.0f, 0.0f), movementSpeed);
	if (key == 'd')
		camera->Move(glm::vec3(1.0f, 0.0f, 0.0f), movementSpeed);
	if (key == 'q')
		camera->Move(glm::vec3(0.0f, 1.0f, 0.0f), movementSpeed);
	if (key == 'e')
		camera->Move(glm::vec3(0.0f, -1.0f, 0.0f), movementSpeed);

	//Camera Rotation
	if (key == 'i')
		camera->Rotate(1.0f, 0.0f, 1.5f);
	if (key == 'k')
		camera->Rotate(-1.0f, 0.0f, 1.5f);
	if (key == 'j')
		camera->Rotate(0.0f, 1.0f, 1.5f);
	if (key == 'l')
		camera->Rotate(0.0f, -1.0f);

	//Camera Aperture
	if (key == 'z')
		camera->SetAperture(camera->GetAperture() + 1.0f);
	if (key == 'x')
		camera->SetAperture(camera->GetAperture() - 1.0f);

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
}