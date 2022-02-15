#include "Spring.h"

Spring::Spring(RigidBody* a_actor1, RigidBody* a_actor2,
	float a_damping, float a_springCoefficient, float a_restingLength,
	glm::vec2 a_contact1, glm::vec2 a_contact2) : PhysicsObject(JOINT),
	m_actor1(a_actor1), m_actor2(a_actor2), m_damping(a_damping), m_springCoeffincient(a_springCoefficient),
	m_restLength(a_restingLength), m_contact1(a_contact1), m_contact2(a_contact2)
{
	if (a_restingLength == 0) 
	{
		m_restLength = glm::distance(GetContact1(), GetContact2());
	}
}

Spring::~Spring()
{

}

void Spring::FixedUpdate(glm::vec2 a_gravity, float a_timestep)
{
	//grab the world coordinate of the ends of our spring

	glm::vec2 p1 = GetContact1();
	glm::vec2 p2 = GetContact2();

	float length = glm::distance(p1, p2);
	glm::vec2 dir = glm::normalize(p2 - p1);

	//Time to apply damping
	glm::vec2 reltiveVelocity = m_actor2->GetVelocity() - m_actor1->GetVelocity();
	//if F = -kX -bv
	glm::vec2 force = dir * m_springCoeffincient * (m_restLength - length) 
		- m_damping * reltiveVelocity;
	
	m_actor1->ApplyForce(-force * a_timestep, p1 - m_actor1->GetPosition());
	m_actor2->ApplyForce( force * a_timestep, p2 - m_actor2->GetPosition());
}

void Spring::MakeGizmo()
{
	aie::Gizmos::add2DLine(GetContact1(), GetContact2(),
		glm::vec4(1, 1, 1, 1));
}
