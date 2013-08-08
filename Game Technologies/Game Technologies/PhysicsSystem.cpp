#include "PhysicsSystem.h"
#include "Renderer.h"

PhysicsSystem* PhysicsSystem::instance = 0;


PhysicsSystem::PhysicsSystem(void)	{

	pla = new Plane(Vector3(0,-1,0), 10, true); // Normal , Distance from origin and Normalise.

}

PhysicsSystem::~PhysicsSystem(void)	{

	delete pla;

}


void	PhysicsSystem::Update(float msec) {	


	BroadPhaseCollisions();
	NarrowPhaseCollisions();
	//DeleteCollided();
	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		(*i)->Update(msec);
	}
}

void	PhysicsSystem::BroadPhaseCollisions() {

		for(vector<PhysicsNode*>::iterator i = allNodes.begin()  ; i != allNodes.end(); ++i) {

		if((*i)->isPlane)
		{
			for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) 
			{
				if(*i != *j)
				{
					c_Sphere		c2 =  c_Sphere((*j)->GetPosition(), 50);
					CollisionData	cd =  CollisionData();
					if(SphereInPlane((*j)->GetPosition(), c2.m_radius, c2, &cd))
					{
						AddCollImpulse2(*j, cd);
						//(*j)->SetLinearVelocity((*j)->GetLinearVelocity());
						//Vector3 temp = (*j)->GetLinearVelocity();
						//temp.y = -temp.y;
						//(*j)->SetLinearVelocity(temp);

					}

				}
			}

		}

		//Getting the position from and making the spaceship backfire.
		if(((*i))->isShip && (*i)->isHit == false) 
		{
			RandPos = (*i)->GetPosition();// + Vector3(100, 100, 100);
			//hitCount++;
		}

		//Check if hit the player/camera.
		if((*i)->isBackFire)
		{
			cubeAABB a = cubeAABB((*i)->GetPosition(), Vector3(100,100,100));
			cubeAABB b = cubeAABB(CamPos, Vector3(300, 300, 300));

			if(AABBCollision(a, b)){
				lifes -= 1;
				jitter = true;

			}
		}


		for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) {
			if(*i != *j)
			{
					c_Sphere		c1 =  c_Sphere((*i)->GetPosition(), 50);
					c_Sphere		c2 =  c_Sphere((*j)->GetPosition(), 50);

					CollisionData	cd =  CollisionData();
					if(SphereSphereCollision(c1, c2, &cd) == true){
						AddCollisionImpulse(*i, *j, cd);
						(*i)->m_HasHit = true;
						if((*i)->isShip == true)
						{
								((*i))->isHit = true;
								score += 100; 
								pos = ((*i))->GetPosition();
						}

					}

			
					// AI
					if (AI){

						if((*i)->isShip && (*j)->isMissile)
						{
							if(*i != *j)
							{

								Vector3 a = (*i)->GetPosition();
								Vector3 b = (*j)->GetPosition();
								float diffX = abs(a.x-b.x);
								float diffY = abs(a.y-b.y);
								float diffZ = abs(a.z-b.z);
								Vector3 diff = Vector3(diffX, diffY, diffZ);
								float sep;
								sep = (AIlevel == 0) ? 100.0 : 150.0f; 
								if(diff.x <= 100)
								{
									if(diff.y <= 100)
									{
										if(diff.z <= 100)
										{
										
											(*i)->SetPosition((*i)->GetPosition() + Vector3(100, 100, 100));
											RandPos = (*i)->GetPosition() + Vector3(100, 100, 100);

											}

											// add force or velo or acce
										}
									}
								}
							}
						}

					}
				}

			 }
	}
	




void	PhysicsSystem::DeleteCollided(){

	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		if((*i)->m_HasHit = true) {
			allNodes.erase(i);



			return;
		}
	}

}

void	PhysicsSystem::NarrowPhaseCollisions() {

}

void	PhysicsSystem::AddNode(PhysicsNode* n) {
	allNodes.push_back(n);
}

void	PhysicsSystem::RemoveNode(PhysicsNode* n) {
	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		if((*i) == n) {
			allNodes.erase(i);
			return;
		}
	}
}


bool PhysicsSystem::SphereSphereCollision(const c_Sphere &s0, const c_Sphere &s1, CollisionData *collisionData) const {
	
	const float distSq = LengthSq(s0.m_pos - s1.m_pos);
	//DBG_ASSERT (distSq > 0.00001f);
	
	const float sumRadius	= (s0.m_radius + s1.m_radius);

	if( distSq < sumRadius*sumRadius && distSq > 0.001f){
		if(collisionData){
			collisionData->m_penetration	= sumRadius - sqrtf(distSq);
			Vector3 NormVec = (s0.m_pos - s1.m_pos);
			NormVec.Normalise();
			collisionData->m_normal			= NormVec; 
			collisionData->m_point			= s0.m_pos - collisionData->m_normal * (s0.m_radius - collisionData->m_penetration * 0.5f );
		}
		//cout << "TRUE" << endl;
		return true; // A Hit!
	}
	//system("cls");
	//cout << "FAL" << endl;
	return false;
}

bool PhysicsSystem::AABBCollision(const cubeAABB &cube0, const cubeAABB &cube1) const{

	//Testing along the x-axis.
	float dist	= abs(cube0.pos.x - cube1.pos.x);
	float sum	= (cube0.halfdims.x + cube1.halfdims.x);

	//If the distance is less than the sum, we have a overlap.
	if( dist <= sum) {
		dist	= abs(cube0.pos.y - cube1.pos.y);
		sum		= (cube0.halfdims.y + cube1.halfdims.y);
		if(dist <= sum){
			float dist	= abs(cube0.pos.z - cube1.pos.z);
			float sum	= (cube0.halfdims.z + cube1.halfdims.z);
			if( dist <= sum) {
				//Overlap in all three axes so there is an intersection.
				return true;
			}
		}
	}
	return false;
}

bool PhysicsSystem::PointInConvexPolygon(const Vector3 testPosition, Vector3 * convexShapePoints, int numPointsL) const {

	//Check if our test point is inside our convex shape.
	for(int i =0; i<numPointsL; ++i){
		const int i0 = i;
		const int i1 = (i+1) % numPointsL;

		const Vector3& p0 = convexShapePoints[i0];
		const Vector3& p1 = convexShapePoints[i1];


		//Required things - a point on the edge and the normal.
		Vector3 normal = p0 - p1;
		normal.Normalise();
		const Vector3 n = Vector3::Cross(Vector3(0,0,1), normal);

		//Using the point equation to calculate d and determine if our point 
		//is on the positive or negative side of the plane (edge).
		const float d = Vector3::Dot( n, p0);

		//Calculate whihc side out test points is..
		//+ve = inside ; -ve = outside; 0 = on plane.
		const float s = d - Vector3::Dot(n, testPosition);

		if(s < 0.0f) {
			//Failed - so skip rest of the test.
			return false;
		}

	}
	return true;
}


bool PhysicsSystem::LineLineIntersection(const Line_c& l0, const Line_c& l1, float* t0, float* t1, float* t2){

	const Vector3& p0 = l0.m_p0;
	const Vector3& p1 = l0.m_p1;
	const Vector3& p2 = l1.m_p0;
	const Vector3& p3 = l1.m_p1;

	const float div = (p3.y-p2.y) * (p1.x-p0.x) - (p3.x-p2.x) * (p1.y - p0.y);

	//Nearly parallel lines.
	if(abs(div) < 0.000001f)	{ return false;}

	const float ta = ((p3.x-p2.x) * (p0.y-p2.y) - (p3.y - p2.y) * (p0.x-p2.x)) /div;
	if( ta < 0 || ta > 1.0f) {
		return false;
	}

	const float tb = ((p1.x-p0.x)*(p0.y-p2.y) - (p1.y-p0.y)*(p0.x-p2.x)) / div;
	if(tb < 0 || tb > 1.0f){
		return false;
	}

	if (t0)		(*t0) = ta;
	if (t1)		(*t1) = tb;

	return true;

}

bool PhysicsSystem::InsideConcaveShape(const Vector3* shapePoints, const int numPoints, const Vector3& testPoint){

	int intersectionCount = 0;
	//Counting hom many times we cross the line.
	for( int i = 0; i < numPoints; ++i){
		const int i0 = i;
		const int i1 = (i+1)%numPoints;

		const Vector3& p0 = shapePoints[i0];
		const Vector3& p1 = shapePoints[i1];

		bool intersect = LineLineIntersection(Line_c(p0,p1), Line_c(testPoint, testPoint + Vector3(1000,1000,0)));

		if (intersect){
			intersectionCount++;
		}
	}

	//Even = false;
	if(intersectionCount % 2 == 0){
		return false;
	}
	else {return true;}
}


///////////////SphereInPlane///////////////////////////////////

bool PhysicsSystem::SphereInPlane(const Vector3 &position, float radius, c_Sphere &s0, CollisionData* collData) const {


	//Debug boxes
	//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, Vector3(0,0,-400), Vector3(100,100,100), Vector3(1,0,0));
	//float seperation = Vector3::Dot(position,normal) + distance;
	Vector3 normal = pla->GetNormal();
	float seperation = Vector3::Dot(position, normal) + pla->GetDistance();
	if ( seperation <= -radius) {
		return false;
	}else
	{
		if(collData) {
			collData->m_penetration = radius + seperation;
			collData->m_normal = -pla->GetNormal();
			collData->m_point = s0.m_pos - normal * collData->m_penetration;
		}
	}

	return true;

}


///////////////////////////////////////////////////////////////

//Impulse Method.
void PhysicsSystem::AddCollisionImpulse( PhysicsNode* c0, PhysicsNode* c1, const CollisionData& cd){

	//Some simple check code.
	float invMass0 = (c0->GetInverseMass() > 1000.0f) ? 0.0f : (1.0f/c0->GetInverseMass());
	float invMass1 = (c1->GetInverseMass() > 1000.0f) ? 0.0f : (1.0f/c1->GetInverseMass());

	/*invMass0 = (!c0.m_awake) ? 0.0f : invMass0;
	invMass1 = (!c1.m_awake) ? 0.0f : invMass1;*/

	const Matrix4 worldInvInertia0	= c0->GetInvInertia();
	const Matrix4 worldInvInertia1	= c1->GetInvInertia();

	//Both objects are non movable.
	if((invMass0 + invMass1) == 0.0) return;

	//Assuming m_c is the center.
	Vector3 r0 = cd.m_point - c0->GetPosition();
	//Vector3 r1 = cd.m_point - c1.m_c;
	Vector3 r1 = cd.m_point - c1->GetPosition();

	Vector3 v0 = c0->GetLinearVelocity() + Vector3::Cross(c0->GetAngularVelocity(), r0);
	Vector3 v1 = c1->GetLinearVelocity() + Vector3::Cross(c1->GetAngularVelocity(), r1);

	//Relative Velocity.
	Vector3 dv = v0 - v1;

	//If the objects are moving away from each other
	//we dont need to apply an impulse.
	float relativeMovement	=	-(Vector3::Dot(dv, cd.m_normal));
	if(relativeMovement < -0.01f)		{ return; }


	//NORMAL Impulse.///////////////////////////////////////////////////////////////
	{
		//Coefficient Of Restitution.
		float e = 0.5f;

		float normDiv	= Vector3::Dot(cd.m_normal, cd.m_normal) * ((invMass0 + invMass1) + Vector3::Dot(cd.m_normal, Vector3::Cross(PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal), worldInvInertia0), r0)
						  + Vector3::Cross(PhysicsSystem::Transform(Vector3::Cross(r1, cd.m_normal), worldInvInertia1), r1)));

		float jn		= -1 * (1+e) * Vector3::Dot(dv, cd.m_normal) / normDiv;

		//Hack fix to stop sinking.
		//Bias impulse proportional to penetration distance.
		jn				= jn + (cd.m_penetration * 1.5f);

		//OLD - //c0->m_linearVelocity += cd.m_normal * invMass0 * jn;
		c0->SetLinearVelocity(c0->GetLinearVelocity() + cd.m_normal * invMass0 * jn);
		c0->SetAngularVelocity(c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal * jn), worldInvInertia0));

		c1->SetLinearVelocity(c1->GetLinearVelocity() - cd.m_normal * invMass1 * jn);
		c1->SetAngularVelocity(c1->GetAngularVelocity() - PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal * jn), worldInvInertia1));

	}

	//TANGENT Impusle Code///////////////////////////////////////////////////////////
	{
		//Work out the tangent vector, Which is perpendicular to the collision normal.
		Vector3 tangent = Vector3(0, 0, 0);
		tangent			= dv - (cd.m_normal * Vector3::Dot(dv, cd.m_normal) ); //TODO - Make sure - We are talking the SAME normals here - CHECK 
		tangent.Normalise();

		//tangent			= Vector3::Normalise(tangent);

		float tangDiv	= invMass0 + invMass1 + Vector3::Dot(tangent, Vector3::Cross((c0->GetInvInertia() * Vector3::Cross(r0, tangent) ), r0)
			+ Vector3::Cross((c1->GetInvInertia() * Vector3::Cross(r1, tangent)), r1));

		float jt		= -1 * Vector3::Dot(dv, tangent) / tangDiv;

		//Clamp main/max tangental component
		//Apply contact impulse.
		c0->SetLinearVelocity(c0->GetLinearVelocity() + tangent * invMass0 * jt);
		c0->SetAngularVelocity((c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, tangent * jt), worldInvInertia0)) * 2);
		//c0.m_linVelocity += tangent * invMass0  * jt;
		//c0.m_angVelocity += PhysicsSystem::Transform(Vector3::Cross(r0, tangent * jt), worldInvInertia0);
		
		c1->SetLinearVelocity(c1->GetLinearVelocity() - tangent * invMass1  * jt);
		c1->SetAngularVelocity(c1->GetAngularVelocity() - PhysicsSystem::Transform(Vector3::Cross(r1, tangent * jt), worldInvInertia1));
		//c1.m_linVelocity -= tangent * invMass1  * jt;
		//c1.m_angVelocity -= PhysicsSystem::Transform(Vector3::Cross(r1, tangent * jt), worldInvInertia1);

	}
	////////////////////////////////////////////////////////////////////////////////
}

//////////////////////////////Collision Responce for SphereInPlane./////////////////
void PhysicsSystem::AddCollImpulse2( PhysicsNode* c0, const CollisionData& cd){

	//Some simple check code.
	float invMass0 = (c0->GetInverseMass() > 1000.0f) ? 0.0f : (1.0f/c0->GetInverseMass());

	/*invMass0 = (!c0.m_awake) ? 0.0f : invMass0;
	invMass1 = (!c1.m_awake) ? 0.0f : invMass1;*/

	const Matrix4 worldInvInertia0	= c0->GetInvInertia();

	//Both objects are non movable.
	if((invMass0) == 0.0) return;

	//Assuming m_c is the center.
	Vector3 r0 = cd.m_point - c0->GetPosition();

	Vector3 v0 = c0->GetLinearVelocity() + Vector3::Cross(c0->GetAngularVelocity(), r0);

	//Relative Velocity.
	Vector3 dv = v0;

	//If the objects are moving away from each other
	//we dont need to apply an impulse.
	float relativeMovement	=	-(Vector3::Dot(dv, cd.m_normal));
	if(relativeMovement < -0.01f)		{ return; }


	//NORMAL Impulse.///////////////////////////////////////////////////////////////
	{
		//Coefficient Of Restitution.
		float e = 0.5f;

		float normDiv	= Vector3::Dot(cd.m_normal, cd.m_normal) * ((invMass0) + Vector3::Dot(cd.m_normal, Vector3::Cross(PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal), worldInvInertia0), r0)));

		float jn		= -1 * (1+e) * Vector3::Dot(dv, cd.m_normal) / normDiv;

		//Hack fix to stop sinking.
		//Bias impulse proportional to penetration distance.
		jn				= jn + (cd.m_penetration * 1.5f);

		//OLD - //c0->m_linearVelocity += cd.m_normal * invMass0 * jn;
		c0->SetLinearVelocity(c0->GetLinearVelocity() + cd.m_normal * invMass0 * jn);
		c0->SetAngularVelocity(c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal * jn), worldInvInertia0));


	}

	//TANGENT Impusle Code///////////////////////////////////////////////////////////
	{
		//Work out the tangent vector, Which is perpendicular to the collision normal.
		Vector3 tangent = Vector3(0, 0, 0);
		tangent			= dv - (cd.m_normal * Vector3::Dot(dv, cd.m_normal) ); //TODO - Make sure - We are talking the SAME normals here - CHECK 
		tangent.Normalise();

		float tangDiv	= invMass0 + Vector3::Dot(tangent, Vector3::Cross((c0->GetInvInertia() * Vector3::Cross(r0, tangent) ), r0));

		float jt		= -1 * Vector3::Dot(dv, tangent) / tangDiv;

		//Clamp main/max tangental component
		//Apply contact impulse.
		c0->SetLinearVelocity(c0->GetLinearVelocity() + tangent * invMass0 * jt);
		c0->SetAngularVelocity(c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, tangent * jt), worldInvInertia0));

	}
}

////////////////////////////////////////////////////////////////////////////////////////////