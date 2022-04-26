#include "Sphere.h"
#include <Gizmos.h>
#include <glm/ext.hpp>

Sphere::Sphere(glm::vec2 a_position, glm::vec2 a_velocity,
 float a_mass, float a_radius, glm::vec4 a_colour) : 
 RigidBody (SPHERE, a_position, a_velocity, 0, a_mass)
{
	m_Radius = a_radius;
	m_colour = a_colour;
	m_isKinematic = false;
	m_moment = 0.5f * a_mass * m_Radius * m_Radius;
}

Sphere::~Sphere()
{
	
}

void Sphere::MakeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation),
		std::sin(m_rotation)) * m_Radius;

	aie::Gizmos::add2DCircle(m_position, m_Radius, 15, m_colour);

	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(0, 0, 0, 0));
}

bool Sphere::CheckCollision(PhysicsObject* a_pOther)
{
	/*Sphere* pSphere = dynamic_cast<Sphere*>(a_pOther);
	if (pSphere != nullptr) 
	{
		float dist = glm::distance(m_Position, pSphere->m_Position);

		if (m_Radius + pSphere->m_Radius > dist) 		
			return true;		
	}*/
	return false;
}
