#include "MoveSpherePhy.h"


MoveSpherePhy::MoveSpherePhy(void)
{

}

MoveSpherePhy::MoveSpherePhy(Quaternion orientation, Vector3 position) {

	m_orientation	= orientation;
	m_position		= position;
	isPlane			= false;
}



MoveSpherePhy::~MoveSpherePhy(void)
{
}

void MoveSpherePhy::Update(float msec){

	//////////////// COMMON SECTION. ///////////////////////////////
	msec *= 0.001f;

	//////////////// LINEAR CALCULATION. ///////////////////////////
	if( isLinear) {

		//m_invMass = 1.0;
		//m_force = Vector3(0, 10, 10);
		m_acce = (m_force * m_invMass);

		m_linearVelocity = m_linearVelocity + m_acce * msec;
		m_position = m_position + m_linearVelocity * msec;
		m_force.ToZero();

		//Damping Factor.
		m_linearVelocity = m_linearVelocity * 0.99995; //* DAMP_FACTOR;


		if(m_position.y < 0)
		{
			m_position.y = 0;
			//this->m_linearVelocity = -this->m_linearVelocity * (0.4);

		}
	}
	///////////////////ANGULAR CALCULATION.////////////////////////////
		m_torque = Vector3(1, 1, 1);
		

		//Solid Sphere.
		float Iner = (2 * PI * (radius) * (radius)) / 5;
		float width		= this->GetDimension().x;
		float height	= this->GetDimension().y;
		float lenght	= this->GetDimension().z;


		float Inxx = 1.0/12 * m_invMass * (height*height + width*width);
		float Inyy = 1.0/12 * m_invMass * (lenght*lenght + width*width);
		float Inzz = 1.0/12 * m_invMass * (height*height + lenght*lenght);
		
		//Trying with some basic test values.
		//float Inxx = 3333;
		//float Inyy = 3333;
		//float Inzz = 3333;

		m_invInertia = Matrix4();
		m_invInertia.values[0] = Inxx;
		m_invInertia.values[5] = Inyy;
		m_invInertia.values[10] = Inzz;
		m_invInertia.Inverse();

		m_angularAcce = m_invInertia * m_torque; /* invIner * torque */
		m_orientation = m_orientation * m_orientation.EulerAnglesToQuaternion(m_angularVelocity.x*msec, m_angularVelocity.y*msec, m_angularVelocity.z*msec);

		m_angularVelocity = m_angularVelocity * 0.99f;


		//IntergrateGravity(msec);
		lessG(msec);

	/////////////////////////////////////////////////////////////////////
		if(target) {
			target->SetTransform(BuildTransform());
		}

}

void MoveSpherePhy::lessG(float dt){

		//Gravity & Friction.
	m_linearVelocity = m_linearVelocity + (Vector3(0, -4.0, 0)) * dt;
	m_position = m_position + m_linearVelocity *dt; //* msec;

	//m_linearVelocity = m_linearVelocity * DAMP_FACTOR;

	if(m_position.y < 0)
	{
		m_position.y = 0;
		//m_linearVelocity = m_linearVelocity - (Vector3(10,10,10) * dt);
		//m_linearVelocity.x = m_linearVelocity.x * 0.6;
		//m_linearVelocity.z = m_linearVelocity.z * 0.6;
	}
}