#include "MyGame.h"
#include "../../nclgl/HeightMap.h"

Mesh* CubeRobot::cube = NULL;
Mesh* FirstProjectile::cube = NULL;
Mesh* Cube::cube = NULL;
//Mesh* KPAXNode::MotherShip = NULL;



MyGame::MyGame()	{

	gameCamera = new Camera(-30.0f,0.0f,Vector3(0,450,850));
	gameCamera -> SetYaw(180);
	gameCamera -> SetPitch(-40);
	gameCamera -> SetPosition(Vector3(2000.0,1300.0f,-400.0f));

	Renderer::GetRenderer().SetCamera(gameCamera);

	CubeRobot::CreateCube();
	KPAXNode::KPAXNode();

	FirstProjectile::CreateCube();
	Cube::CreateCube();
	//////////////////////////For the SpaceShips///////////////////////////////////////////////////

	KPAXNode::DeployShips();

	///////////////////////////////////////////////////////////////////////////////////////////////
	SceneNode* s = new Cube();
	s->SetModelScale(Vector3(500.0f,500.0f,500.0f));
	s->SetBoundingRadius(100); 
	cubeObj = new MoveCube(s, new PhysicsNode());


	////////////////////////////////////////////////////////////////////////////////////////////////

	SceneNode* s2 = new Cube();
	sphereObj = new MoveSphere(s2, new MoveSpherePhy(Quaternion::AxisAngleToQuaterion(Vector3(1, 0, 0), 90.0f),Vector3(100,0,0)));
	
	////////////////////////////////////////////////////////////////////////////////////////////////


	cube			= new OBJMesh("../../Meshes/cube.obj");
	quad			= Mesh::GenerateQuad();
	sphere			= new OBJMesh("../../Meshes/ico.obj");
	sphere2			= new OBJMesh("../../Meshes/sphere.obj");
	
	heightMap2		= new HeightMap("../../Textures/KPAX-Fin2.raw");


	// Connect to the system.
	allEntities.push_back(BuildCubeEntity(10));
	allEntities.push_back(BuildCube2(10));

	allEntities.push_back(BuildSpaceShip(Vector3(0, 300, 0)));
	allEntities.push_back(BuildSpaceShip(Vector3(2000, 1000, 300)));
	allEntities.push_back(BuildSpaceShip(Vector3(1000, 300, 800)));
	allEntities.push_back(BuildSpaceShip(Vector3(500, 700, 3000)));





}

MyGame::~MyGame(void)	{

	delete cube;
	delete quad;
	delete sphere;
	delete sphere2;


	delete sphereObj;
	delete cubeObj;
	
	CubeRobot::DeleteCube();
	FirstProjectile::DeleteCube();
	Cube::DeleteCube();

}


void MyGame::UpdateGame(float msec) {
	if(gameCamera) {
		gameCamera->UpdateCamera(msec);
		CamPos = gameCamera->GetPosition();
	}

	for(vector<GameEntity*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i) {
		(*i)->Update(msec);
	}

	
	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_G)){

		allEntities.push_back(ShotProjectile(msec));

	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_R)){
		Renderer::GetRenderer().reloadShaders();
		//Renderer::GetRenderer().shaderReload = false;
	}

	//Spawn new Enemy.
	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_N)){

		float x = rand()%2000 + 350;
		float y = rand()%1100 + 200;
		float z = rand()%2000 + 850;
		allEntities.push_back(BuildSpaceShip(Vector3(x, y , z)));
	}


	//AI
	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_Q)){
		AI = (AI == false) ? true : false;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_P)){	

		allEntities.push_back(BackFire(RandPos));
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_9)){	

		AIlevel = 0;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_0)){	

		AIlevel = 1;
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_K)){	

		m_speed = m_speed - 1;
		if(m_speed <= 1) { m_speed = 1;}
	}

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_L)){	

		m_speed = m_speed + 1;
		if(m_speed >= 10) { m_speed = 10;}
	}

	if(jitter){
		
		gameCamera->SetPosition(gameCamera->GetPosition() + Vector3(10,0,30));
		jitter = false;
	}

	if(dead) {
		gameCamera->SetPosition(gameCamera->GetPosition() + Vector3(0,-100,0));
	}


	cubeObj->Update(msec);
	sphereObj->Update(msec);

	// Updating the CubeBox's

	cB0->Update(msec);
	cB1->Update(msec);
	/////////////////////////////////////////////////////////////////////////////////////

	//Deleting the ship after being hit.
	for(vector<GameEntity*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i) {

		if(abs(((*i))->GetRenderNode().GetWorldTransform().GetPositionVector().x) > 1000 ||
			abs(((*i))->GetRenderNode().GetWorldTransform().GetPositionVector().y) > 1000 ||
			abs(((*i))->GetRenderNode().GetWorldTransform().GetPositionVector().z) > 1000 ) {

				std::remove(allEntities.begin(), allEntities.end(), ((*i))), allEntities.end();
				((*i))->DisconnectFromSystems();
				delete *i;

			
		}

		if(((*i))->GetPhysicsNode().isHit == true && ((*i))->GetRenderNode().GetWorldTransform().GetPositionVector().y <= 0) {

				std::remove(allEntities.begin(), allEntities.end(), ((*i))), allEntities.end();
				((*i))->DisconnectFromSystems();
				delete *i;

		}

	}
	
	this->ClearNodeList();
}


GameEntity* MyGame::BuildRobotEntity() {
	GameEntity*g = new GameEntity(new CubeRobot(), new PhysicsNode());

	g->ConnectToSystems();
	return g;
}

GameEntity* MyGame::BuildSpaceShip(Vector3 pos) {
	GameEntity*g = new GameEntity(new KPAXNode(), new KPAXPhysicsNode(Quaternion::AxisAngleToQuaterion(Vector3(1,0,0), 90.0f), pos));

	PhysicsNode* p = &g->GetPhysicsNode();
	SceneNode*	s= &g->GetRenderNode();
	
	s->isTextured	= true;
	s->type			=	1;
	s->SetBoundingRadius(100);
	
	p->SetDimension(s->GetModelScale());
	p->AddTorque(Vector3(1, 1, 1));
	p->SetInverseMass(500);
	p->isShip = true;
	g->ConnectToSystems();
	return g;
}


GameEntity* MyGame::BuildCubeEntity(float size) {
	cB0 = new CubeBox0(new SceneNode(cube), new PhysicsNode());
	//cB0->ConnectToSystems();

	SceneNode &test = cB0->GetRenderNode();
	PhysicsNode & cp = cB0->GetPhysicsNode();
	
	test.SetModelScale(Vector3(10, 10, 10));
	cp.SetDimension(test.GetModelScale());

	test.SetColour(Vector4(0,1,0,1));
	cp.SetPosition(Vector3(40,0,0));

	return cB0;
}


GameEntity* MyGame::BuildCube2(float size) {
	cB1 = new CubeBox1(new SceneNode(cube), new PhysicsNode());
	
	SceneNode &test = cB1->GetRenderNode();
	PhysicsNode & cp = cB1->GetPhysicsNode();

	
	test.SetModelScale(Vector3(10, 20, 20));
	cp.SetDimension(test.GetModelScale());
	test.SetColour(Vector4(0,1,0,1));
	cp.SetPosition(Vector3(-10,0,0));

	return cB1;
}

/*
Makes a sphere.
*/
GameEntity* MyGame::BuildSphereEntity(float radius) {
	SceneNode* s = new SceneNode(sphere2);

	s->SetModelScale(Vector3(radius,radius,radius));
	s->SetBoundingRadius(radius);
	
	PhysicsNode*p = new PhysicsNode(Quaternion::AxisAngleToQuaterion(Vector3(1,0,0), 90.0f), Vector3(0, 100, 0));
	GameEntity*g = new GameEntity(s, p);
	g->ConnectToSystems();
	return g;
}

/*
Makes a flat quad
*/
GameEntity* MyGame::BuildQuadEntity(float size) {
	SceneNode* s = new SceneNode(quad);

	s->SetModelScale(Vector3(size,size,size));
	s->SetBoundingRadius(size);
	PhysicsNode*p = new PhysicsNode(Quaternion::AxisAngleToQuaterion(Vector3(1,0,0), 90.0f), Vector3());
	GameEntity*g = new GameEntity(s, p);

	p->isPlane = true;
	g->ConnectToSystems();
	return g;
}

/*ANOTHER Quad -  In Z - Axis.*/
GameEntity* MyGame::BuildQuadEntity2(float size) {
	SceneNode* s = new SceneNode(quad);

	s->SetModelScale(Vector3(size,size,size));
	s->SetColour(Vector4(0, 1, 0, 1));
	s->SetBoundingRadius(size);

	PhysicsNode* p = new PhysicsNode(Quaternion::AxisAngleToQuaterion(Vector3(1,0,0), 180.0f), Vector3(1,1,-500));
	GameEntity* g = new GameEntity(s, p);

	p->isPlane = true;

	g->ConnectToSystems();
	return g;
}


GameEntity* MyGame::DrawMyAnything() {

	SceneNode*	s =  new FirstProjectile();

	s->SetModelScale(Vector3(50.0f, 50.0f, 50.0f));
	s->SetBoundingRadius(50.0f);

	PhysicsNode *p = new PhysicsNode(Quaternion::AxisAngleToQuaterion(Vector3(1, 0, 0), 90.0f), Vector3(1,1,1));

	GameEntity* g =  new GameEntity(s, p);
	g->ConnectToSystems();

	return g;

}

GameEntity* MyGame::ShotProjectile(float msec){

	GameEntity* g = new MoveSphere(new Cube(), new MoveSpherePhy(Quaternion::AxisAngleToQuaterion(Vector3(0, 1, 0), 0.0f),Vector3(100,0,0)));

	SceneNode*		s = &g->GetRenderNode();
	PhysicsNode*	p = &g->GetPhysicsNode();

	Vector3 CamDir = gameCamera->GetCamDir();
	

	s->SetColour(Vector4(0, 0, 1, 1));
	s->type = 1; 
	s->SetBoundingRadius(50);
	s->SetTransform(Matrix4::Translation(Vector3(1, 1, 1)) * Matrix4::Rotation( 270.0f, Vector3(1, 0, 0)));
	s->SetModelScale(Vector3(10,10,20));
	p->SetDimension(s->GetModelScale());

	m_speed = m_speed * 1000;

	p->SetInverseMass(9.0f);
	p->SetSphereRadius(50);
	p->AddForce(CamDir * 7000);
	p->SetPosition(gameCamera->GetPosition());
	p->SetOrientation(Quaternion::EulerAnglesToQuaternion(gameCamera->GetPitch(), gameCamera->GetYaw(), 0.0));
	p->isMissile = true;

	g->ConnectToSystems();

	return g;
}

GameEntity* MyGame::BackFire(Vector3 pos) {

	GameEntity* g = new MoveSphere(new Cube(), new MoveSpherePhy(Quaternion::AxisAngleToQuaterion(Vector3(0, 1, 0), 90.0f), pos + Vector3(0, 0, 150)));

	SceneNode*		s = &g->GetRenderNode();
	PhysicsNode*	p = &g->GetPhysicsNode();

	Vector3 CamDir = gameCamera->GetCamDir();

	s->SetTransform(Matrix4::Translation(Vector3(1, 1, 1)) * Matrix4::Rotation( 90.0f, Vector3(1, 0, 0)));
	s->SetColour(Vector4(0, 0, 1, 1));
	s->type = 1; // For debug boxes. If 1 = debug boxes ON.
	s->SetBoundingRadius(50);
	
	s->SetModelScale(Vector3(10,10,20));
	p->SetDimension(s->GetModelScale());



	p->SetInverseMass(12.0f);
	p->SetSphereRadius(50);
	p->AddForce(-CamDir * 9000);


	p->SetOrientation(Quaternion::EulerAnglesToQuaternion(gameCamera->GetPitch(), gameCamera->GetYaw(), 0.0));
	p->isMissile = true;
	p->isBackFire = true;


	g->ConnectToSystems();

	return g;
}

