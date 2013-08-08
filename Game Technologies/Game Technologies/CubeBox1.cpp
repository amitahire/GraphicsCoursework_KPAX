#include "CubeBox1.h"


CubeBox1::CubeBox1(void){
	renderNode	= NULL;
	physicsNode = NULL;
}

CubeBox1::CubeBox1(SceneNode* s, PhysicsNode* p) {
	renderNode	= s;
	physicsNode = p;
}


CubeBox1::~CubeBox1(void)
{
}


void CubeBox1::Update(float msec){


	PhysicsSystem* psys = &PhysicsSystem::GetPhysicsSystem();

	psys->cAB1.pos		= physicsNode->GetPosition();

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_P))
	{
		physicsNode->AddForce(Vector3(2000, 0, 0));
	
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_O))
	{
		physicsNode->AddForce(Vector3(-2000, 0, 0));

	}


	physicsNode->IntergrateGravity(msec * 0.001f);
	
}
