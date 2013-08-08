#include "KPAXNode.h"
#include "../../nclgl/SceneNode.h"
#include "../../nclgl/Light.h"
//#include "Renderer.h"

Mesh* KPAXNode::MotherShip = NULL;
//Mesh* KPAXNode::fume = NULL;
Vector3 KPAXNode::pos = Vector3(0,0,0);

KPAXNode::KPAXNode(void) {

	//Optional - Uncomment if you want a local origin marker - What does it mean? :P
	//SetMesh(cube);
	
	// So you need not to present the return type -- Check all other and leftarm. Both work.!!

	//// Let me add the code for the other objects.
	//SceneNode* ico1 = new SceneNode(ico, Vector4(1, 0, 0, 1));
	//ico1->SetModelScale(Vector3(3, 10, 3));
	//ico1->SetTransform(Matrix4::Translation(Vector3(15, 0, 0)));
	//body->AddChild(ico1);
	

	helperShip1 = new SceneNode(MotherShip, Vector4(1, 1, 0, 1));
	helperShip1->SetModelScale(Vector3(30, 30, 30));
	helperShip1->SetTransform(Matrix4::Translation(Vector3(1 , 1, 1)) * Matrix4::Rotation( 270.0f, Vector3(1, 0, 0)));
	//helperShip1-> -- SETTING in DrawNode.
	AddChild(helperShip1);

	//helperShip2 = new SceneNode(MotherShip, Vector4(1, 1, 0, 1));
	//helperShip2->SetModelScale(Vector3(30, 30, 30));
	//helperShip2->SetTransform(Matrix4::Translation(Vector3(1, 200, 1)));
	//helperShip1->AddChild(helperShip2);

	//helperShip3 = new SceneNode(MotherShip, Vector4(1, 1, 0, 1));
	//helperShip3->SetModelScale(Vector3(30, 30, 30));
	//helperShip3->SetTransform(Matrix4::Translation(Vector3(2000, -4000, 1)));
	//helperShip1->AddChild(helperShip3);

	//helperShip4 = new SceneNode(MotherShip, Vector4(1, 1, 0, 1));
	//helperShip4->SetModelScale(Vector3(30, 30, 30));
	//helperShip4->SetTransform(Matrix4::Translation(Vector3(1, -400, -300)));
	//helperShip1->AddChild(helperShip4);

	//HelperShip2 goes off into the space. 
/*
	lg1 = new SceneNode(MotherShip, Vector4(1, 0, 0, 1));
	lg1->SetTransform(Matrix4::Translation(Vector3(2000 , 1000, 1)) * Matrix4::Rotation( 270.0f, Vector3(1, 0, 0)));
	Light* l1 = new Light(Vector3(2000,1000,1), Vector4(0, 0, 1, 1), 10000.0f);
	
	helperShip1->AddChild(lg1);
*/
	//lg1 = new SceneNode(fume, Vector4(0, 1, 0, 0.2));
	//lg1->SetTransform(Matrix4::Translation(Vector3(40, 50, 1)) * Matrix4::Rotation(90.0f, Vector3(1, 0, 0)));
	//lg1->SetModelScale(Vector3(100, 30, 30));
	//helperShip1->AddChild(lg1);





}

void KPAXNode::Update(float msec) {

	static float shipRotation = 0;


	shipRotation += msec * 0.1f;
	//Vector3 pos =  Renderer::postition;
	//helperShip1->SetTransform(Matrix4::Translation(Vector3(2000 , 1000, 1) + pos) * Matrix4::Rotation( 270.0f, Vector3(1, 0, 0)));
	//helperShip1->SetTransform(Matrix4::Rotation(shipRotation, Vector3(0, 0, 1)) * Matrix4::Translation(Vector3(100, 0, 0)));
		//helperShip1->SetTransform(Matrix4::Rotation(shipRotation, Vector3(0, 0, 0)) * Matrix4::Translation(Vector3(100, 0, 0))); // Orbiting
	//helperShip1->SetTransform(Matrix4::Rotation(shipRotation/ 50, Vector3(0, 1, 0)) * Matrix4::Translation(Vector3(1, 1,1)));




//	cout << helperShip1->GetTransform().GetPositionVector() << endl;
//	cout << helperShip1->GetWorldTransform().GetPositionVector()<< endl;
	// Use this for ROTATING.
	/*helperShip2->*/
	//transform = transform * Matrix4::Rotation(msec / 10.0f, Vector3(0, 1, 0));
	//helperShip2->SetTransform(helperShip2->GetTransform() * Matrix4::Translation(Vector3(msec /100, 1, 1)) * Matrix4::Rotation(-msec /10.0f, Vector3(0, 1, 0)) * Matrix4::Translation(Vector3(-(msec /100), 1, 1)));
	
	//helperShip3->SetTransform(helperShip3->GetTransform() * Matrix4::Translation(Vector3(msec /10, msec/ 50, 1)) * Matrix4::Rotation(-msec /10.0f, Vector3(0, 0, 1)) * Matrix4::Translation(Vector3(-(msec /100), 1, 1)));
	//helperShip3->SetTransform(helperShip3->GetTransform() * Matrix4::Translation(Vector3(msec /10, msec/ 50, 1)) * Matrix4::Rotation(-msec /10.0f, Vector3(0, 0, 1)) * Matrix4::Translation(Vector3(100, 1, 1)));

	//helperShip4->SetTransform(helperShip3->GetTransform() * Matrix4::Translation(Vector3(msec /10, msec/ 50, 1)) * Matrix4::Rotation(-msec /10.0f, Vector3(0, 0, 1)) * Matrix4::Translation(Vector3(-(msec /10), -50, 1)));
	/*f_track += msec;
	if (f_track > 3000.0) { f_track = -3; helperShip2->SetTransform(helperShip1->GetWorldTransform()); }*/

	//if (helperShip2->GetTransform().GetPositionVector().z > 8)
	//{
	//	helperShip2->SetTransform(helperShip3->GetWorldTransform());
	//}

	//if (helperShip3->GetTransform().GetPositionVector().z > 8)
	//{
	//	helperShip3->SetTransform(helperShip1->GetWorldTransform());
	//}

	//UpdateShaderMatricces();
	
	//transform = transform * Matrix4::Rotation(msec / 90.0f, Vector3(0, 0, 1));
	//transform = transform * Matrix4::Rotation(msec/ 90.0f, Vector3(0, 1, 0));
//	head->SetTransform(head->GetTransform() * Matrix4::Rotation(-msec / 10.0f, Vector3(0, 1, 0)));
	//leftArm->SetTransform(leftArm->GetTransform() * Matrix4::Rotation(-msec / 10.0f, Vector3(1, 0, 0)));
	//rightArm->SetTransform(rightArm->GetTransform() * Matrix4::Rotation(-msec / 10.0f, Vector3(1, 0, 0))); // some


	SceneNode::Update(msec);

}

