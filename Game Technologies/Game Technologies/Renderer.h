/******************************************************************************
Class:Renderer		
Implements:OGLRenderer - Basic working Renderer.
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and Amit Ahire <amitahire@gmail.com>

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////


#pragma once

#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/SceneNode.h"
#include "../../nclgl/Camera.h"
#include "../../nclgl/Frustum.h"
#include "../../nclgl/TextMesh.h"
#include "../../nclgl/HeightMap.h"
#include "../../nclgl/SeaMap.h"
#include "../../nclgl/ParticleEmitter.h"
#include "Ball_Spring_Chain.h"
#include "PhysicsNode.h"
#include <algorithm>

extern	int		score;
extern	Vector3	pos;
extern	bool	AI;
extern	Vector3	RandPos;
extern	bool	fireFlag;
extern	int		AIlevel;
extern	Vector3	CamPos;
extern	int		lifes;
extern	int		m_speed;
extern	bool	jitter;
extern	bool	dead;

class Renderer : public OGLRenderer	{
public:
	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	float fps;
	//Draw Text - FPs counter.
	void DrawText(const std::string &text, const Vector3 &position, const float size, const bool perspective = false);


	void	SetCamera(Camera*c);

	void	AddNode(SceneNode* n);

	void	RemoveNode(SceneNode* n);

	void	DrawSparks();

	//Statics
	static bool Initialise() {
		instance = new Renderer(Window::GetWindow());
		return instance->HasInitialised();
	}

	bool	shaderReload;
	void	reloadShaders();
	ParticleEmitter*	emitter;

	static void Destroy() {
		delete instance;
	}
	
	static Renderer& GetRenderer() { return *instance;}

protected:	
	Renderer(Window &parent);
	virtual ~Renderer(void);

	void	init_Shader();
	void	init_Components();
	// Part.
	void	init_Root();
	void	init_HeightMap();
	void	init_WaterMap();
	void	init_Skybox();
	void	init_KPAXShip();
	void	init_Font();

	//Back.
	void	init_Light();
	void	init_Enable();
	void	init_Matrix();




	////////////////////////////////////////////////////////////////
	void	BuildNodeLists(SceneNode* from);
	void	SortNodeLists();
	void	ClearNodeLists();
	void	DrawNodes();
	void	DrawNode(SceneNode*n);

	void	DrawSkybox();
	void	DrawHeightMap();
	void	DrawWater();





	SceneNode*	root;
	Camera*		camera;
	
	Shader*		simpleShader;
	Shader*		textShader;
	Shader*		nodeShipShader;




	Font*		basicFont;

	Frustum		frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;

	static Renderer*	instance;

	////////New set.///////////
	
	Shader*		skyboxShader;
	GLuint		cubeMap;
	Mesh*		quad;

	Mesh*		heightMap;
	Shader*		lightShader;
	Light*		light;

	SeaMap*		water;
	Shader*		seaShader;



	float		waterRotate;
	float		timeWave;
	float		rotation;
	
	springdemo_c* sd;
	

};

