#include "FirstProjectile.h"

//Mesh* CubeRobot::cube = NULL;

FirstProjectile::FirstProjectile(void) {

	//Optional - Uncomment if you want a local origin marker - What does it mean? :P
	//SetMesh(cube);

	SceneNode* globe = new SceneNode(cube, Vector4(1, 0, 0, 1));		//Red
	globe->SetModelScale(Vector3(50, 50, 50));
	//globe->SetTransform(Matrix4::Translation(Vector3(0, 35, 0)));
	AddChild(globe);

}

void FirstProjectile::Update(float msec) {
	transform = transform * Matrix4::Rotation(msec / 10.0f, Vector3(0, 1, 0));
	

	SceneNode::Update(msec);

}

FirstProjectile::~FirstProjectile() {

	delete cube;
	delete head;

}

//void CubeRobot::MySphere() {
//
//	SceneNode* globe = new SceneNode(sphere2, Vector4(1, 1, 1, 1));		//Black.
//	globe->SetModelScale(Vector3(5, 5, 5));
//	globe->SetTransform(Matrix4::Translation(Vector3(0, 35, 0)));
//	//globe->AddChild(globe);
//	AddChild(globe); // -- a nonstatic member reference must be relative to a specific object -- WHY??
//}



