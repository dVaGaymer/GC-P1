#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Object.h"
#include "Entity.h"
#include "Camera.h"

//Idenficadores de los objetos de la escena
Object* hijo;
Object* padre;
Camera* camera;

//Declaración de CB
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);

int main(int argc, char** argv)
{
	std::locale::global(std::locale("spanish"));// acentos ;)
	if (!IGlib::init("../shaders_P1/shader.v10.vert", "../shaders_P1/shader.v10.frag"))
		return -1;
   
	//Se ajusta la cámara
	camera = &Camera();
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
	IGlib::setViewMat(camera->GetMatView());
	
	//Se crean objetos
	hijo = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
	padre = &Object(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);

	hijo->SetParent(padre);

	//Test Position
	hijo->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	padre->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	//Test Rotation
	padre->Rotate(glm::vec3(0.0f, 0.0f, 0.0f));
	hijo->Rotate(glm::vec3(45.0f, 0.0f, 0.0f));

	//Test Scale
	hijo->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	padre->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	IGlib::setModelMat(hijo->GetObjId(), hijo->GetMatModel());
	IGlib::setModelMat(padre->GetObjId(), padre->GetMatModel());

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
	IGlib::setProjMat(camera->GetMatProj());
}

void idleFunc()
{
	hijo->Rotate(glm::vec3(1.0f, 0.0f, 0.0f));
	IGlib::setModelMat(hijo->GetObjId(), hijo->GetMatModel());
}

void keyboardFunc(unsigned char key, int x, int y)
{
	std::cout << "Se ha pulsado la tecla " << key << std::endl << std::endl;
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
