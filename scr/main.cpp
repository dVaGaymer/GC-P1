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
Object *cubo0, *cubo1, *center;
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
	camera = &Camera(glm::vec3(0.0f, 0.0f, 0.0f));
	camera->UploadMatView();
	
	//Se crean objetos
	cubo0 = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	cubo0->UploadTexture("../img/cleanUnicorn.png");
	cubo1 = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	cubo1->UploadTexture("../img/unicorn.png");

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
	cubo0->SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	cubo1->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	cubo0->RotateZ(0);

	sun->SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
	earth->SetPosition(glm::vec3(-6.0f, 0.0f, 0.0f));
	middleLayer->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	innerLayer->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	moon->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

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
	cubo0->RotateX(rotationSpeed);
	cubo1->RotateY(-5.0 * rotationSpeed);

	sun->RotateY(rotationSpeed);
	earth->RotateZ(1.0f * rotationSpeed);
	middleLayer->RotateY(-1.0f * rotationSpeed);
	innerLayer->RotateX(1.0f * rotationSpeed);
	moon->RotateX(1.0f * rotationSpeed);

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
	float movementSpeed = 0.5f;
	if (key == 'w')
		camera->Move(glm::vec3(-1.0f, 0.0f, 0.0f), movementSpeed);
	if (key == 's')
		camera->Move(glm::vec3(1.0f, 0.0f, 0.0f), movementSpeed);
	if (key == 'a')
		camera->Move(glm::vec3(0.0f, 1.0f, 0.0f), movementSpeed);
	if (key == 'd')
		camera->Move(glm::vec3(0.0f, -1.0f, 0.0f), movementSpeed);
	if (key == 'i')
		camera->Rotate(0.0f, 1.0f);
	if (key == 'k')
		camera->Rotate(0.0f, -1.0f);
	if (key == 'j')
		camera->Rotate(1.0f, .0f);
	if (key == 'l')
		camera->Rotate(-1.0f, 0.0f);
	std::cout << "a: " << camera->axis.right.x		<< " " << camera->axis.right.y		<< " " << camera->axis.right.z		<< std::endl;
	std::cout << "a: " << camera->axis.up.x			<< " " << camera->axis.up.y			<< " " << camera->axis.up.z			<< std::endl;
	std::cout << "a: " << camera->axis.forward.x	<< " " << camera->axis.forward.y	<< " " << camera->axis.forward.z	<< std::endl;

	//Camera Aperture
	if (key == 'z')
		camera->SetAperture(camera->GetAperture() + 1.0f);
	if (key == 'x')
		camera->SetAperture(camera->GetAperture() - 1.0f);

	camera->UploadMatView();
}

glm::vec2 prev;
bool pressed = false;
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
	if (state == 0 && button == 2)
	{
		prev.x = x;
		prev.y = y;
	}
}

void mouseMotionFunc(int x, int y)
{
	std::cout << x - prev.x << " " << prev.y - y << std::endl;
	camera->Rotate(x - prev.x, prev.y - y);
	camera->UploadMatView();

	prev.x = x;
	prev.y = y;
}
