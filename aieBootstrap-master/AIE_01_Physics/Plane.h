#pragma once
#include "PhysicsObject.h"
//this is a one sided object and it is 
// considered to extend infiniatly along both sides of its edge
// and backwards from its normal direction



class Plane : public PhysicsObject
{

public:
	Plane(glm::vec2 a_normal, float a_distanceToOrigin);
	Plane();
	~Plane();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void MakeGizmo();
	virtual void Debug() {};
	virtual void ResetPosition() {};

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }

	void SetColour();
	glm::vec4 GetColour() { return m_colour; }


protected:

	glm::vec2 m_normal;
	glm::vec4 m_colour;
	float m_distanceToOrigin;

};

