#pragma once

#include "../../nclgl/Vector3.h"
#include "../../nclgl/Matrix4.h"

const static int maxnumballs	=	20;

class springdemo_c{

public:

	Vector3 m_ballposition[maxnumballs];
	Vector3 m_ballvelocity[maxnumballs];
	Vector3 m_ballforce[maxnumballs];

	springdemo_c();
	~springdemo_c(){};

	void drawballs();
	void recalculateballposition();


	void draw();

};

