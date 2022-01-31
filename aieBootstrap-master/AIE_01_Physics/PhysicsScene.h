#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;
class Sphere;

class PhysicsScene
{
public:

	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	/* this functions will update the physics simulation
	it calls the update each actor and updates	
	internally. this will handle collision and resolution */
	void Update(float a_dt);

	/* This is called once per frame,
	it handles the rendering of objects.
	you can draw objects from the gixmo class */
	void Draw();

	void SetGravity(const glm::vec2 a_gravity)
	{ m_gravity = a_gravity; }

	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float a_timeStep) 
	{ m_TimeStep = a_timeStep; }

	float GetTimeStep() const { return m_TimeStep; }

	static bool Sphere2Sphere(PhysicsObject* a_sphere, 
		PhysicsObject* a_otherSphere);

protected:

	glm::vec2 m_gravity;
	float m_TimeStep;

	/* stores all the physics objects in the
	scene we create as well as the functions
	that will add or remove objects */
	std::vector<PhysicsObject*> m_actors;



};

