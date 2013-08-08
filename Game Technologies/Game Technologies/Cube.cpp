#include "Cube.h"


Cube::Cube(void)
{
	
	SceneNode* globe = new SceneNode(cube, Vector4(1, 0, 0, 1));	
	globe->SetModelScale(Vector3(50,50,50));
	//globe->SetTransform(Matrix4::Translation(Vector3(0, 1, 0)) * Matrix4::Rotation( 180.0f, Vector3(1, 0, 0)));
	AddChild(globe);

}

void Cube::Update(float msec){

	transform = transform * Matrix4::Rotation(msec / 10.0f, Vector3(0, 1, 0));
	SceneNode::Update(msec);
}


Cube::~Cube(void)
{
}
