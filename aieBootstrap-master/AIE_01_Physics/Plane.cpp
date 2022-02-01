#include "Plane.h"

#include <Gizmos.h>

Plane::Plane(glm::vec2 a_normal, float a_distanceToOrigin) : PhysicsObject(PLANE)
{
	m_normal = a_normal;
	m_distanceToOrigin = a_distanceToOrigin;
	m_colour = glm::vec4(0, 1, 0, 1);

}

Plane::Plane() : PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0, 1);
	m_distanceToOrigin = 0;
	m_colour = glm::vec4(1,1,1,1);
}

Plane::~Plane()
{
}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
}

void Plane::MakeGizmo()
{
	float lineSegmentLength = 300;

	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colourFade = m_colour;

	colourFade.a = 0;
	colourFade.r = 0;

	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	//aie::Gizmos::add2DLine(start, end, m_colour);

	aie::Gizmos::add2DLine(start, end, glm::vec4(1, 0, 0, 1));

	aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, 
		m_colour, colourFade);

	aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, 
		m_colour, colourFade, colourFade);
}

void Plane::SetColour()
{

}
