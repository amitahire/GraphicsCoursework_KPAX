#include "MoveCube.h"
#include "PhysicsSystem.h"


MoveCube::MoveCube(void)	{
	renderNode	= NULL;
	physicsNode = NULL;
	isCuboid	= true;
}

MoveCube::MoveCube(SceneNode* s, PhysicsNode* p) {
	renderNode	= s;
	physicsNode = p;
}


MoveCube::~MoveCube()
{
	delete pla;
}


void MoveCube::Update(float msec){

	psys = &PhysicsSystem::GetPhysicsSystem();
	//psys->cs0.m_radius	= renderNode->GetModelScale().x; //TODO - Fix it
	//cout << renderNode->GetBoundingRadius() << endl; -- couts 1.

	psys->cs0.m_pos		= physicsNode->GetPosition();

	pla = new Plane(); //TODO - Might wanna delete it. Check for memory leak.
	pla->sp.m_pos		= physicsNode->GetPosition();
	//cout << pla->sp.m_pos << endl;

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_UP))
	{
		physicsNode->AddForce(Vector3(0, 2000, 0));
		cout << pla->sp.m_pos << endl;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_DOWN))
	{
		physicsNode->AddForce(Vector3(0, -2000, 0));
		//cout << pla->sp.m_pos / 2 << endl;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_RIGHT))
	{
		physicsNode->AddForce(Vector3(2000, 0, 0));
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_LEFT))
	{
		physicsNode->AddForce(Vector3(-2000, 0, 0));
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_0))
	{
		physicsNode->AddForce(Vector3(0, 0, -2000));
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_9))
	{
		physicsNode->AddForce(Vector3(0, 0, +2000));
	}
	
	//if(physicsNode->m_position.x == 0)
	//{

	//	m_linearVelocity = m_linearVelocity + acce * msec;
	//	m_position = m_position + m_linearVelocity *msec; 

	//}

	

	physicsNode->IntergrateGravity(msec * 0.001f);
	
}
