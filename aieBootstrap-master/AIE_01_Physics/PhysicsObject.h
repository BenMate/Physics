#pragma once
#include <vector>
#include <glm/glm.hpp>

//this is pure abstract class, it will 
//be used as a base for the derived classes that wil use
//fixedUpdate

enum ShapeType
{
	PLANE = 0,
	CIRCLE,
	AABB,
};

class PhysicsObject
{

protected:

	PhysicsObject(ShapeType a_shapeID) : m_shapteID(a_shapeID) {}
	
public:

	virtual void FixedUpdate
	(glm::vec2 a_gravity, float a_TimeStep) = 0;

	virtual void Draw() = 0;
	virtual void ResetPosition() {};

	

	void Update();
	void Debug();
	void MakeGizmo();

protected:

	ShapeType m_shapteID;


};

