#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 a_position, glm::vec2 a_velocity,
 float a_mass, float a_radius, glm::vec4 a_colour) : 
 RigidBody (CIRCLE, a_position, a_velocity, 0, a_mass)
{
	m_Radius = a_radius;
	m_colour = a_colour;
}

Sphere::~Sphere()
{
}

void Sphere::MakeGizmo()
{
	aie::Gizmos::add2DCircle(m_Position, m_Radius, 12, m_colour);
}

bool Sphere::CheckCollision(PhysicsObject* a_pOther)
{
	Sphere* pSphere = dynamic_cast<Sphere*>(a_pOther);
	if (pSphere != nullptr) 
	{
		float dist = glm::distance(m_Position, pSphere->m_Position);

		if (m_Radius + pSphere->m_Radius > dist) 		
			return true;		
	}
	return false;
}
