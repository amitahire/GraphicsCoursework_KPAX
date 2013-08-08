#include "Renderer.h"
#include <math.h>
#include <sstream>

//Setting the Globals here - Can also do it in common.h - Shift later. 
int			score = 0;
Vector3		pos = Vector3(0, 0, 0);
bool		AI = false;
Vector3		RandPos = Vector3(0, 0, 0); // For the spaceship backfire.
bool		fireFlag = false;
bool		jitter	=	false;
int			AIlevel;
Vector3		CamPos = Vector3(0, 0, 0);
int			lifes = 100;
int			m_speed = 7;
bool		dead = false;


Renderer* Renderer::instance = NULL;


Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{	

	instance		= this;
	shaderReload	= false;
	///////////////////////////////////////////////
	////1. Construction and Destructor.
	///////////////////////////////////////////////
	init_Shader();
	init_Components();
	init_Light();
	init_Enable();
	init_Matrix();
		
	////////////////////////////////////////////////
	////////////////////////////////////////////////

	camera			= NULL;
	
	//sd = new springdemo_c();
	
	waterRotate		= 0.0f;
	timeWave		= 1.0f; // For waves in Water.

	init			= true;

	fps				=	0; 
	
}

Renderer::~Renderer(void)	{
	delete root;
	delete simpleShader;
	delete textShader;
	delete basicFont;
	delete skyboxShader;

	currentShader = NULL;
}


//////////////////////////////////////////////////////////////////////////
/////////2. Init														//
//////////////////////////////////////////////////////////////////////////

void Renderer::init_Shader() {

	//Shader for text and skybox.
	simpleShader	= new Shader(SHADERDIR"TechVertex.glsl", SHADERDIR"TechFragment.glsl");
	textShader		= new Shader(SHADERDIR"TexturedVertex.glsl", SHADERDIR"TexturedFragment.glsl");
	skyboxShader	= new Shader(SHADERDIR"skyboxVertex.glsl",SHADERDIR"skyboxFragment.glsl");

	if(!simpleShader->LinkProgram() || !textShader->LinkProgram() || !skyboxShader->LinkProgram()){
		return;
	}

	// Light, Sea and Spaceship
	lightShader		= new Shader(SHADERDIR"PerPixelVertex.glsl",SHADERDIR"PerPixelFragment.glsl");
	seaShader		= new Shader(SHADERDIR"SeaVertex.glsl", SHADERDIR"SeaFrag.glsl");
	nodeShipShader	= new Shader(SHADERDIR"SceneVertex.glsl", SHADERDIR"SceneFragment.glsl");
	

	if(!lightShader->LinkProgram() || !seaShader->LinkProgram() || !nodeShipShader->LinkProgram() ){
		return;
	}

}

void Renderer::reloadShaders(){

	//Simple Shader - Check for what?
	Shader*		pTempShader1;
	pTempShader1 = new Shader(SHADERDIR"TechVertex.glsl", SHADERDIR"TechFragment.glsl");
	if(pTempShader1->LinkProgram()) {
		delete simpleShader;
		simpleShader = pTempShader1;
	}

	//For Text shader.
	Shader*		pTempShader2;
	pTempShader2 = new Shader(SHADERDIR"TexturedVertex.glsl", SHADERDIR"TexturedFragment.glsl");
	if(pTempShader2->LinkProgram()) {
		delete textShader;
		textShader = pTempShader2;
	}

	//For skybox.
	Shader*		pTempShader3;
	pTempShader3 = new Shader(SHADERDIR"skyboxVertex.glsl",SHADERDIR"skyboxFragment.glsl");
	if(pTempShader3->LinkProgram()) {
		delete skyboxShader;
		skyboxShader = pTempShader3;
	}


	//For Light.
	Shader*		pTempShader4;
	pTempShader4 = new Shader(SHADERDIR"PerPixelVertex.glsl",SHADERDIR"PerPixelFragment.glsl");
	if(pTempShader4->LinkProgram()) {
		delete lightShader;
		lightShader = pTempShader4;
	}

	//For Seamap.
	Shader*		pTempShader5;
	pTempShader5 = new Shader(SHADERDIR"SeaVertex.glsl", SHADERDIR"SeaFrag.glsl");
	if(pTempShader5->LinkProgram()) {
		delete seaShader;
		seaShader = pTempShader5;
	}

	//For MotherShip.
	Shader*		pTempShader6;
	pTempShader6 = new Shader(SHADERDIR"SeaVertex.glsl", SHADERDIR"SeaFrag.glsl");
	if(pTempShader6->LinkProgram()) {
		delete nodeShipShader;
		nodeShipShader = pTempShader6;
	}

}

void Renderer::init_Components() {

	// Init Root.
	init_Root();

	// Init World Components.
	init_HeightMap();
	init_WaterMap();
	init_Skybox();
	//TODO : Particle Emitter

	// Init KPAX Ships.
	//TODO: init_KPAXShip();
	init_Font();

	//DEFFERED RENDERING LATER.

	//Scene Buffers.
	//init_SceneBuffer();

}

void Renderer::init_Root() {
	root		= new SceneNode();
}

void Renderer::init_HeightMap() {

	//HeightMap.
	heightMap		= new HeightMap(TEXTUREDIR"KPAX-Fin2.raw");
	heightMap->SetBumpMap ( SOIL_load_OGL_texture (TEXTUREDIR"Barren RedsDOT3.jpg", SOIL_LOAD_AUTO ,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS));
	heightMap->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"Barren Reds.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS));
	SetTextureRepeating(heightMap->GetTexture(), true);
	if(!heightMap->GetTexture()) { return;}
}

void Renderer::init_WaterMap() {

	//Water - SeaMap.
	water			= new SeaMap(TEXTUREDIR"terrain.raw");
	water->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	SetTextureRepeating(water->GetTexture(), true);
	if(!water->GetTexture()) { return; }
}

void Renderer::init_Skybox() {

	quad			= Mesh::GenerateQuad();
	cubeMap			= SOIL_load_OGL_cubemap(
											TEXTUREDIR"Thuliac_Night_West.bmp",TEXTUREDIR"Thuliac_Night_East.bmp", 
											TEXTUREDIR"Thuliac_Night_Top.bmp", TEXTUREDIR"Thuliac_Night_Bottom.bmp",
											TEXTUREDIR"Thuliac_Night_North.bmp", TEXTUREDIR"Thuliac_Night_South.bmp", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
	
	quad->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	SetTextureRepeating(quad->GetTexture(), true);
	if(!cubeMap || !quad->GetTexture()) {
		return;
	}

}

void Renderer::init_KPAXShip() {


}

void Renderer::init_Font() {
	//Font!
	basicFont		= new Font(SOIL_load_OGL_texture(TEXTUREDIR"tahoma.tga",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_COMPRESS_TO_DXT),16,16);
}

void Renderer::init_Light() {
	//Light.
	//light			= new Light(Vector3((RAW_HEIGHT * HEIGHT_X / 2.0f), 500.0f, (RAW_HEIGHT * HEIGHT_Z / 2.0f)), Vector4(1,1,1,1),(RAW_WIDTH * HEIGHT_X)* 2.0f);
	light			= new Light(Vector3( 500.0f, (RAW_HEIGHT * HEIGHT_Z / 2.0f), (RAW_HEIGHT * HEIGHT_X / 2.0f)), Vector4(1,1,1,1),(RAW_WIDTH * HEIGHT_X)* 2.0f);
}

void Renderer::init_Enable() {
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void Renderer::init_Matrix() {
	projMatrix		= Matrix4::Perspective(1.0f, 15000.0f, (float)width/ (float)height, 60.0f);
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void	Renderer::UpdateScene(float msec)	{
	if(camera) {
		camera->UpdateCamera(msec); 
	}
	root->Update(msec);
	viewMatrix	= camera->BuildViewMatrix();

	//FPS Counter.
	fps			=	1000 / msec;
	timeWave	+= msec / 1000.0f;
	waterRotate += msec/ 1000.0f;
	rotation	= msec * 0.01f;

	//sd->draw();



}

void	Renderer::RenderScene()	{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Skybox
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	projMatrix		= Matrix4::Perspective(1.0f,10000.0f,(float)width / (float) height, 60.0f);
	DrawSkybox();
	
	
	projMatrix		= Matrix4::Perspective(1.0f,10000.0f,(float)width / (float) height, 60.0f);
	DrawHeightMap();
	DrawWater();
	
	if(camera) {
		SetCurrentShader(simpleShader);
		glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

		textureMatrix.ToIdentity();
		modelMatrix.ToIdentity();
		viewMatrix		= camera->BuildViewMatrix();
		projMatrix		= Matrix4::Perspective(1.0f,10000.0f,(float)width / (float) height, 60.0f);
		frameFrustum.FromMatrix(projMatrix * viewMatrix);
		UpdateShaderMatrices();

		//Return to default 'usable' state every frame!
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		BuildNodeLists(root); 
		SortNodeLists();
		DrawNodes();
		ClearNodeLists();
	}



	//For FPS counter.
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	textureMatrix.ToIdentity();
	
	std::ostringstream ss;
	ss << fps;
	std::string FpsD(ss.str());
	SetCurrentShader(textShader);
	DrawText("FPS: " + FpsD , Vector3(0, 0, 0), 16.0f);
	//SCore
	std::ostringstream ss1;
	ss1 << score;
	std::string points(ss1.str());
	SetCurrentShader(textShader);
	DrawText("SCORE: " + points , Vector3(0, 20,0) , 16.0f);
	pos += Vector3(0, 1, 0);
	DrawText( points , pos , 26.0f, true);
	//Lives & hit situatio 
	std::ostringstream ss2;
	ss2 << lifes;
	std::string lifescount(ss2.str());
	DrawText("HEALTH:" + lifescount , Vector3(0.0f, 36.0f, 0.0f), 16.0f);
	if(lifes <= 0)
	{ 
		lifes = 0;
		DrawText("YOU ARE GOING DOWN." , Vector3(600.0f, 15.0f, 0.0f), 30.0f);
		dead = true;
	}
	//Menu
	DrawText("--MENU--", Vector3(1000, 735,0) , 16.0f);
	DrawText("Press \"B\" for Bounding Boxes.", Vector3(1000, 767,0) , 16.0f);
	DrawText("Press \"R\" for Spawning Ships.", Vector3(1000, 781,0) , 16.0f);
	DrawText("Press \"G\" to Fire missiles", Vector3(1000, 796,0) , 16.0f);
	DrawText("Press \"Q\" to Enable AI", Vector3(1000, 752,0) , 16.0f);
	DrawText("Press \"P\" for Enemy Backfire.", Vector3(1000, 812,0) , 16.0f);
	string a;
	if(AI == true) { a = "ON";} else { a = "OFF";}
	DrawText("AI :" + a, Vector3(1370, 30,0) , 16.0f);
	glUseProgram(0);


	

	//For debug boxes and lines. 
	projMatrix		= Matrix4::Perspective(1.0f,10000.0f,(float)width / (float) height, 60.0f);
	modelMatrix.ToIdentity();
	viewMatrix= camera->BuildViewMatrix();
	UpdateShaderMatrices();

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_6)){	

		//sd->drawballs();
		//sd->m_ballforce[4] = Vector3(0, 10.0f, 0);
	}

	projMatrix		= Matrix4::Perspective(1.0f,10000.0f,(float)width / (float) height, 60.0f);
	modelMatrix.ToIdentity();
	viewMatrix= camera->BuildViewMatrix();
	UpdateShaderMatrices();

	SwapBuffers();
}

void	Renderer::DrawNode(SceneNode*n)	{
	if(n->GetMesh()) {
		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"),	1,false, (float*)&(n->GetWorldTransform()*Matrix4::Scale(n->GetModelScale())));
		glUniform4fv(glGetUniformLocation(currentShader->GetProgram(), "nodeColour"),1,(float*)&n->GetColour());
		glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "useTexture"), (int)n->GetMesh()->GetTexture());
		n->Draw(*this);
	}
}

void	Renderer::BuildNodeLists(SceneNode* from)	{
	Vector3 direction = from->GetWorldTransform().GetPositionVector() - camera->GetPosition();
	from->SetCameraDistance(Vector3::Dot(direction,direction));

	if(frameFrustum.InsideFrustum(*from)) {
		if(from->GetColour().w < 1.0f) {
			transparentNodeList.push_back(from);
		}
		else{
			nodeList.push_back(from);
		}
	}

	for(vector<SceneNode*>::const_iterator i = from->GetChildIteratorStart(); i != from->GetChildIteratorEnd(); ++i) {
		BuildNodeLists((*i));
	}
}

void	Renderer::DrawNodes()	 {
	for(vector<SceneNode*>::const_iterator i = nodeList.begin(); i != nodeList.end(); ++i ) {
		//Debug Boxes.
		int Dbox = 1;
		if(Window::GetKeyboard()->KeyHeld(KEYBOARD_B)) { Dbox = 0;} //else { Dbox = false; }
		if((*i)->type == 1 && Dbox == 0)
		{
			Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, (*i)->GetWorldTransform().GetPositionVector() ,(*i)->GetBoundingRadius(), Vector3(0,1,0));
			Vector3 radius = Vector3((*i)->GetBoundingRadius(), (*i)->GetBoundingRadius(), (*i)->GetBoundingRadius());
			Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, (*i)->GetWorldTransform().GetPositionVector(), radius*2, Vector3(1,0,0));
			//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, (*i)->GetWorldTransform().GetPositionVector() + Vector3(0, 0, +100), radius*2, Vector3(1,0,0));
		}
		//For textures.
		if((*i)->isTextured == true)
		{
			SetCurrentShader(nodeShipShader);
			//glUniform1i( glGetUniformLocation(currentShader->GetProgram(),"diffuseTex"), 0);
			UpdateShaderMatrices();
			DrawNode((*i));
			glUseProgram(0);

		}else
		{

			SetCurrentShader(simpleShader);
			DrawNode((*i));
		
		}
	}

	for(vector<SceneNode*>::const_reverse_iterator i = transparentNodeList.rbegin(); i != transparentNodeList.rend(); ++i ) {
		DrawNode((*i));
	}
}

void	Renderer::SortNodeLists()	{
	std::sort(transparentNodeList.begin(),	transparentNodeList.end(),	SceneNode::CompareByCameraDistance);
	std::sort(nodeList.begin(),				nodeList.end(),				SceneNode::CompareByCameraDistance);
}

void	Renderer::ClearNodeLists()	{
	transparentNodeList.clear();
	nodeList.clear();
	//Clearing.
}

void	Renderer::SetCamera(Camera*c) {
	camera = c;
	camera->SetPosition(Vector3(1940.0f, 2160.0f, 5440.0f));
	camera->SetPitch(-30.0f);
	camera->SetYaw(360.0f);

}

void	Renderer::AddNode(SceneNode* n) {
	root->AddChild(n);
}

void	Renderer::RemoveNode(SceneNode* n) {
	root->RemoveChild(n);
}

void	Renderer::DrawText(const std::string &text, const Vector3 &position, const float size, const bool perspective)	{

	glDisable(GL_DEPTH_TEST);

	//Create a new temporary TextMesh, using our line of text and our font
	TextMesh* mesh = new TextMesh(text,*basicFont);

	//This just does simple matrix setup to render in either perspective or
	//orthographic mode, there's nothing here that's particularly tricky.
	if(perspective) {
		modelMatrix = Matrix4::Translation(position) * Matrix4::Scale(Vector3(size,size,1));
		viewMatrix = camera->BuildViewMatrix();
		projMatrix = Matrix4::Perspective(1.0f,10000.0f,(float)width / (float)height, 60.0f);
	}
	else{	
		//In ortho mode, we subtract the y from the height, so that a height of 0
		//is at the top left of the screen, which is more intuitive
		modelMatrix = Matrix4::Translation(Vector3(position.x,height-position.y, position.z)) * Matrix4::Scale(Vector3(size,size,1));
		viewMatrix.ToIdentity();
		projMatrix = Matrix4::Orthographic(-1.0f,1.0f,(float)width, 0.0f,(float)height, 0.0f);
	}
	//Either way, we update the matrices, and draw the mesh
	UpdateShaderMatrices();
	mesh->Draw();
	

	delete mesh; //Once it's drawn, we don't need it anymore!
}

void	Renderer::DrawSkybox()	{

	glDepthMask(GL_FALSE);
	SetCurrentShader(skyboxShader);

	
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	UpdateShaderMatrices();
	quad->Draw();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);


	glUseProgram(0);
	glDepthMask(GL_TRUE);

}

void	Renderer::DrawHeightMap(){

	SetCurrentShader(lightShader);
	SetShaderLight(*light);

	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "bumpTex"), 1);

	modelMatrix.ToIdentity();
	textureMatrix.ToIdentity();

	UpdateShaderMatrices();

	heightMap->Draw();

	glUseProgram(0);

}

void	Renderer::DrawWater() {

	SetCurrentShader(seaShader);
	SetShaderLight(*light);

	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos") , 1,(float*)&camera->GetPosition());

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "cubeTex"), 2);

	glUniform1f(glGetUniformLocation(currentShader->GetProgram(), "timeWave"), timeWave );

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	modelMatrix = Matrix4::Translation(Vector3(0, HEIGHT_Y - 200.0f , 0));

	textureMatrix = Matrix4::Scale(Vector3(10.0f, 10.0f, 10.0f)) * Matrix4::Rotation(waterRotate * 0.4, Vector3(0.0f, 0.0f, 1.0f));

	UpdateShaderMatrices();

	water->Draw();

	glUseProgram(0);

}
