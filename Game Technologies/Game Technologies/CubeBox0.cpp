#include "CubeBox0.h"


CubeBox0::CubeBox0(void){
	renderNode	= NULL;
	physicsNode = NULL;
}

CubeBox0::CubeBox0(SceneNode* s, PhysicsNode* p) {
	renderNode	= s;
	physicsNode = p;
}


CubeBox0::~CubeBox0(void){}


void CubeBox0::Update(float msec){


	PhysicsSystem* psys = &PhysicsSystem::GetPhysicsSystem();

	psys->cAB0.pos		= physicsNode->GetPosition();

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_M))
	{
		physicsNode->AddForce(Vector3(2000, 0, 0));
	
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_N))
	{
		physicsNode->AddForce(Vector3(-2000, 0, 0));

	}


	physicsNode->IntergrateGravity(msec * 0.001f);
	
}
