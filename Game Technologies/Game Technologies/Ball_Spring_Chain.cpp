
#include "../../nclgl/Vector3.h"
#include "Renderer.h"
#include "Ball_Spring_Chain.h"



//gravity acceleration
const static float g			=	-9.8f;

//mass
const static float mass			=	10.0f;

//spring parameter in hook's law.
const static float ks			=	0.6f;

//velocity damping paramrter.
const static float kd			=	0.7f;

//time slice
const static float dt			=	0.5f;

//const static int maxnumballs	=	7;


//spring demo class - whole demo is encapsulated within this class.
	springdemo_c::springdemo_c()
	{
		
		//Vector3 m_ballposition[maxnumballs];
		//Vector3 m_ballvelocity[maxnumballs];
		//Vector3 m_ballforce[maxnumballs];

		//creating balls.
		for (int i = 0; i < maxnumballs; i++){

			m_ballposition[i]	= Vector3(0, 0, 0);
			m_ballforce[i]		= Vector3(0, 0, 0);
			m_ballvelocity[i]	= Vector3(0, 0, 0);
		}

		//fix first ball - 
		m_ballposition[0].x		= 100;
		m_ballposition[0].y		= 100;

		//fix last ball.
		m_ballposition[maxnumballs - 1].x	= 400.0f;
		m_ballposition[maxnumballs - 1].y	= 400.0f;
		/////////////////////////////////////////////////////
		//Fixing 4th and 5th ball.
		//m_ballposition[4].x		= 100;
		//m_ballposition[4].y		= 500;
		//
		//m_ballposition[5].x		= 500;
		//m_ballposition[5].y		= 500;

		/////////////////////////////////////////////////////
		/*m_ballposition[m_ballposition.size()-1].x = 500;		
		m_ballposition[m_ballposition.size()-1].y = 100;*/

		//initialize moving balls.
		for(int i = 1; i < 5; i++)
		{
				m_ballposition[i].x = m_ballposition[i-1].x + 100;
				m_ballposition[i].y = 100;

		}

		m_ballposition[5].x = 500;
		m_ballposition[5].y = 200;

		for(int i = 6; i < 10; i++)
		{
				m_ballposition[i].x = m_ballposition[i-1].x - 100;
				m_ballposition[i].y = 200;

		}

		m_ballposition[10].x = 100;
		m_ballposition[10].y = 300;

		for(int i = 11; i < 15; i++)
		{
				m_ballposition[i].x = m_ballposition[i-1].x + 100;
				m_ballposition[i].y = 300;

		}

		m_ballposition[15].x = 500;
		m_ballposition[15].y = 400;

		for(int i = 16; i < 20; i++)
		{
				m_ballposition[i].x = m_ballposition[i-1].x - 100;
				m_ballposition[i].y = 400;

		}

		//m_ballposition[15].x = 500;
		//m_ballposition[15].y = 400;

		//for(int i = 16; i < 20; i++)
		//{
		//		m_ballposition[i].x = m_ballposition[i-1].x - 100;
		//		m_ballposition[i].y = 400;

		//}

			/*m_ballposition[i].x = -(rand() % 450) + 100;
			m_ballposition[i].y = -(rand() % 90) + 100;*/
			/*m_ballposition[i].x	= randomfloat(0, 450);
			m_ballposition[i].y = randomfloat(0, 90);*/
	}

	void springdemo_c::drawballs() {

		for (int i = 0; i < maxnumballs; i++)
		{
			
			Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, m_ballposition[i], 10.0f, Vector3(0,1,0));
		}

		//draw springs.
		for(int i = 0; i < maxnumballs - 1; i++)
		{
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[i], m_ballposition[i+1], Vector3(1,0,0), Vector3(1,0,0));
		}

	
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[3], m_ballposition[6], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[2], m_ballposition[7], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[1], m_ballposition[8], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[0], m_ballposition[9], Vector3(1,0,0), Vector3(1,0,0));

			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[5], m_ballposition[14], Vector3(1,0,0), Vector3(1,0,0));

			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[6], m_ballposition[13], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[7], m_ballposition[12], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[8], m_ballposition[11], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[9], m_ballposition[10], Vector3(1,0,0), Vector3(1,0,0));

			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[13], m_ballposition[16], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[12], m_ballposition[17], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[11], m_ballposition[18], Vector3(1,0,0), Vector3(1,0,0));
			Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, m_ballposition[10], m_ballposition[19], Vector3(1,0,0), Vector3(1,0,0));
		

	}

		//calculate forces on each node.
	void springdemo_c::recalculateballposition() {

			//calculate the spring force
			for(int i = 1; i < maxnumballs; i++)
			{

				//force from the left ball and right ball.
				Vector3	f0 = (m_ballposition[i] - m_ballposition[i-1]) * ks;
				Vector3	f1 = (m_ballposition[i] - m_ballposition[i+1]) * ks;

				Vector3	f = -(f0 + f1);
				m_ballforce[i] = f - m_ballvelocity[i] * kd;
				m_ballforce[i].y	-=	mass * g;
			}

			//Self-Check
			////////////
			//calculate the new position of each nodes.
			for(int i = 1; i < maxnumballs; i++){


				//acceleration.
				Vector3	a = m_ballforce[i] * (1.0f/mass);

				//velocities.
				m_ballvelocity[i] += a * dt * 0.2;

				//position.
				m_ballposition[i] += m_ballvelocity[i] * dt * 0.3;
			}
		}

		//game state is kept here in the draw update
		//for simplicity, we assume a fixed
		//timestep update call( so the function is always called at the same interval).
	void springdemo_c::draw(){

	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_Q)){

		m_ballforce[7] = Vector3(10, 10, 100000);
		//m_ballposition[7] = m_ballposition[7] + Vector3(10, 10, 100);
		//ProjList.push_back();
	}
			recalculateballposition();

			drawballs();
	}
