#pragma once
#include <vector>
#include <glm/glm.hpp>

//this is pure abstract class, it will 
//be used as a base for the derived classes that wil use
//fixedUpdate

enum ShapeType
{
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPECOUNT
};

class PhysicsObject
{

protected:

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
	
public:

	virtual void FixedUpdate
	(glm::vec2 a_gravity, float a_TimeStep) = 0;

	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};

	ShapeType GetShapeID() { return m_shapeID; }

	float GetElasticity() { return m_elasticity; }
	void SetElasticity(float a_elasticity) 
	{ m_elasticity = a_elasticity; }

protected:

	ShapeType m_shapeID;
	float m_elasticity;
	bool m_isKinematic;

};

