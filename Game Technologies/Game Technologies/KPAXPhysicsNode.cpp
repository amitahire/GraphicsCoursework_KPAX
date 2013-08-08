#include "KPAXPhysicsNode.h"


KPAXPhysicsNode::KPAXPhysicsNode(void)
{
}

KPAXPhysicsNode::KPAXPhysicsNode(Quaternion orientation, Vector3 position) {

	m_orientation	= orientation;
	m_position		= position;
	isPlane			= false;
	isHit			= false;
	isShip			= true;
}


KPAXPhysicsNode::~KPAXPhysicsNode(void)
{
}


void KPAXPhysicsNode::Update(float msec){

	//////////////// COMMON SECTION. ///////////////////////////////
	msec *= 0.001f;

	//////////////// LINEAR CALCULATION. ///////////////////////////
	if( isLinear) {


		////////////// Changing the Position - to Rotate./////////////
		if(m_position.x >= 1000.0f){

			m_force = Vector3(0, 0.2, 0.4);
		}
		else
		{

			m_force = Vector3(0.2, 0, 0.2);
		}
		if(m_position.y >= 2500){
			this->m_linearVelocity =  -this->m_linearVelocity;
		}

		m_acce = (m_force * m_invMass);
 
		m_linearVelocity = m_linearVelocity + m_acce * msec;
		m_position = m_position + m_linearVelocity * msec;
		m_force.ToZero();
		//cout << m_position << endl;

		//Damping Factor.
		m_linearVelocity = m_linearVelocity * 0.99995; //* DAMP_FACTOR;


		if(m_position.y < 0)
		{
			m_position.y = 0;
			this->m_linearVelocity = -this->m_linearVelocity * (0.4);

		}
	}
	///////////////////ANGULAR CALCULATION.////////////////////////////
		m_torque = Vector3(1, 1, 0);
		
	//////////////////////////////////////////////////////////////
	
	if(this->isHit == true){

		m_torque = Vector3(2, 3, 4);
		IntergrateGravity(msec * 2);
		m_linearVelocity.ToZero();
		m_linearVelocity.y = -100;
		m_position = m_position - m_linearVelocity * msec;
	}

	//////////////////////////////////////////////////////////////
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

		//m_angularVelocity = m_angularVelocity * 0.59f;
		if(m_position.y < 0 )
		{
			//Die - Kill - Delete.
			m_force.ToZero();
			
			m_position.y = 0;
			m_position.z = 0;
			m_position.x = 0;

		}
	/////////////////////////////////////////////////////////////////////
		if(target) {
			target->SetTransform(BuildTransform());
		}

}