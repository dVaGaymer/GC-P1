#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Entity.h"
#include "Camera.h"


//Idenficadores de los objetos de la escena
Entity* hijo;
Entity* padre;
Camera* camera;

//Declaración de CB
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);

int main(int argc, char** argv)
{
	char l[10];

	//std::cin.get(l, 10);
	std::cin >> std::ws >> l;

	std::cout << l;
	std::locale::global(std::locale("spanish"));// acentos ;)
	if (!IGlib::init("../shaders_P1/shader.v10.vert", "../shaders_P1/shader.v10.frag"))
		return -1;
   
	//Se ajusta la cámara
	//Si no se da valor se cojen valores por defecto
	camera = &Camera();
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	IGlib::setViewMat(camera->GetViewMat());

	hijo = &Entity(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	padre = &Entity(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	hijo->SetParent(padre);

	hijo->SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
	padre->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	IGlib::setModelMat(hijo->getObjId(), hijo->GetModelMat());
	IGlib::setModelMat(padre->getObjId(), padre->GetModelMat());

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
	IGlib::setProjMat(camera->GetProjMat());
}

void idleFunc()
{
	float speed0 = 1.0f;
	float speed1 = 1.0f;

	hijo->AddRotation(glm::vec3(speed0, speed0, 0.0f));
	IGlib::setModelMat(hijo->getObjId(), hijo->GetModelMat());

	padre->AddRotation(glm::vec3(speed0, speed0, 0.0f));
	IGlib::setModelMat(padre->getObjId(), padre->GetModelMat());
	IGlib::setModelMat(hijo->getObjId(), hijo->GetModelMat());
}

void keyboardFunc(unsigned char key, int x, int y)
{
	std::cout << "Se ha pulsado la tecla " << key << std::endl << std::endl;
	if (key == 'x')
		camera->SetApreture(camera->GetAperture() + 1);
		
	else if (key == 'z')
		camera->SetApreture(camera->GetAperture() - 1);
	IGlib::setProjMat(camera->GetProjMat());

	if (key == 'w')
		camera->MoveForward(-0.2f);
	if (key == 's')
		camera->MoveForward(0.2f);
	if (key == 'a')
		camera->MoveSide(-0.2f);
	if (key == 'd')
		camera->MoveSide(0.2f);
	if (key == ' ')
		camera->MoveUpDown(0.2f);
	if (key == 'c')
		camera->MoveUpDown(-0.2f);

	if (key == 'i')
		camera->RotateRight(5.0f);
	if (key == 'k')
		camera->RotateRight(-5.0f);

	if (key == 'l')
		camera->RotateUp(-5.0f);
	if (key == 'j')
		camera->RotateUp(5.0f);

	if (key == 'o')
		camera->RotateForward(5.0f);
	if (key == 'u')
		camera->RotateForward(-5.0f);
	IGlib::setViewMat(camera->GetViewMat());
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
