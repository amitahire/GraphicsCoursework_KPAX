#include "MoveSphere.h"
#include "../../nclgl/Camera.h"


MoveSphere::MoveSphere(void) {
	renderNode = NULL;
	physicsNode = NULL;
}


MoveSphere::MoveSphere(SceneNode* s, MoveSpherePhy* p){
	renderNode	=	s;
	physicsNode	=	p;
	SpherePhy	=	p;

}


MoveSphere::~MoveSphere(void){
}

void MoveSphere::Update(float msec) {

	//psys = &PhysicsSystem::GetPhysicsSystem();

	//psys->cs1.m_pos		= physicsNode->GetPosition();

	
	

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_I))
	{
	
		SpherePhy->SetPosition(SpherePhy->GetPosition() + Matrix4::Rotation( SpherePhy->GetYaw(), Vector3 (0.0f ,1.0f ,0.0f)) * Vector3 ( -1.0f ,0.0f ,0.0f) * msec) ;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_K))
	{
		SpherePhy->AddForce(Vector3(0, -2000, 0));
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_J))
	{
		cout << SpherePhy->GetPosition() << endl;
		SpherePhy->SetPosition(SpherePhy->GetPosition() + Matrix4::Rotation( SpherePhy->GetYaw(), Vector3 (0.0f ,1.0f ,0.0f)) * Vector3 ( -1.0f ,0.0f ,0.0f) * msec * 100) ;
		cout << SpherePhy->GetPosition() << endl;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_L))
	{
		SpherePhy->SetPosition(SpherePhy->GetPosition() - Matrix4::Rotation(SpherePhy->GetYaw() , Vector3 (0.0f ,1.0f ,0.0f)) *	Vector3 ( -1.0f ,0.0f ,0.0f) * msec ) ;
	}
	
	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_2))
	{
		SpherePhy->AddForce(Vector3(0, 0, -2000));

	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_1))
	{
		SpherePhy->AddForce(Vector3(0, 0, +2000));

	}
	

	SpherePhy->IntergrateGravity(msec * 0.001f);
}
