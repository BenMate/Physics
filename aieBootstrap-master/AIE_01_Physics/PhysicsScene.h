#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;
class RigidBody;

class PhysicsScene
{
public:

	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	void AddBall(PhysicsObject* a_ball);
	void RemoveBall(PhysicsObject* a_ball);

	bool IsBallCountZero() { return m_balls.empty(); }

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

	void CheckForCollisions();

	static void ApplyContactForces(RigidBody* a_rigidbody1, RigidBody* a_rigidbody2, 
		glm::vec2 a_collisionNorm, float a_pen);;

	static bool Plane2Plane(PhysicsObject* a_plane, PhysicsObject* a_otherPlane);
	static bool Plane2Sphere(PhysicsObject* a_plane, PhysicsObject* a_sphere);
	static bool Plane2Box(PhysicsObject* a_plane, PhysicsObject* a_box);

	static bool Sphere2Plane(PhysicsObject* a_sphere, PhysicsObject* a_plane);
	static bool Sphere2Sphere(PhysicsObject* a_sphere, PhysicsObject* a_otherSphere);
	static bool Sphere2Box(PhysicsObject* a_sphere, PhysicsObject* a_box);

	static bool Box2Plane(PhysicsObject* a_box, PhysicsObject* a_plane);
	static bool Box2Sphere(PhysicsObject* a_box, PhysicsObject* a_sphere);
	static bool Box2Box(PhysicsObject* a_box, PhysicsObject* a_otherBox);


protected:

	glm::vec2 m_gravity;
	float m_TimeStep;

	/* stores all the physics objects in the
	scene we create as well as the functions
	that will add or remove objects */

	std::vector<PhysicsObject*> m_actors;
	std::vector<PhysicsObject*> m_balls;
};

