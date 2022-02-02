#include <list>
#include <iostream>

#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Box.h"
#include "Plane.h"

PhysicsScene::PhysicsScene() : 
	m_TimeStep(0.1f),m_gravity(glm::vec2(0,0))
{
	
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors) 
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	if (it != m_actors.end()) 
	{
		m_actors.erase(it);
	}
}

void PhysicsScene::Update(float a_dt)
{
	//Update Physics at a fixed time step.
	static float accumulatedTime = 0.0f;
	accumulatedTime += a_dt;

	while (accumulatedTime >= m_TimeStep) 
	{
		for (auto pActor : m_actors) 
		{
			pActor->FixedUpdate(m_gravity, m_TimeStep);
		}

		accumulatedTime -= m_TimeStep;

		CheckForCollisions();

	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->MakeGizmo();
	}
}

//==============================================================================
//function pointer array for handling our collisions
typedef bool (*fn)(PhysicsObject*, PhysicsObject*);
static fn collisionsFunctionArray[] =
{
	PhysicsScene::Plane2Plane,  PhysicsScene::Plane2Sphere,  PhysicsScene::Plane2Box,
	PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere, PhysicsScene::Sphere2Box,
	PhysicsScene::Box2Plane,	PhysicsScene::Box2Sphere,	 PhysicsScene::Box2Box
};

void PhysicsScene::CheckForCollisions()
{
	int actorCount = m_actors.size();

	//we need to check our collisions against all other objects except this one...

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->GetShapeID();
			int shapeID2 = object2->GetShapeID();

			//using the function pointer....
			int functionIdx = (shapeID1 * SHAPECOUNT) + shapeID2;
			fn collisionsFunctionPtr = collisionsFunctionArray[functionIdx];

			if (collisionsFunctionPtr != nullptr) 
			{
				//check if the collisions occurs;
				collisionsFunctionPtr(object1, object2);
			}
		}
	}

}

bool PhysicsScene::Plane2Plane(PhysicsObject* a_plane, PhysicsObject* a_otherPlane)
{
	return false;
}

bool PhysicsScene::Plane2Sphere(PhysicsObject* a_plane, PhysicsObject* a_sphere)
{

	return Sphere2Plane(a_sphere, a_plane);
}

bool PhysicsScene::Plane2Box(PhysicsObject* a_plane, PhysicsObject* a_box)
{
	return false;
}

bool PhysicsScene::Sphere2Plane(PhysicsObject* a_sphere, PhysicsObject* a_plane)
{

	Sphere* sphere = dynamic_cast<Sphere*>(a_sphere);
	Plane* plane = dynamic_cast<Plane*>(a_plane);

	//if this is successful then test for a collision;

	if (sphere != nullptr && plane != nullptr) 
	{
		glm::vec2 collisionNormal = plane->GetNormal();

		float sphereToPlane = glm::dot(sphere->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		float intersection = sphere->GetRadius() - sphereToPlane;
		float velocityOutofThePlane = glm::dot(sphere->GetVelocity(), plane->GetNormal());

		if (intersection > 0 && velocityOutofThePlane < 0)
		{
			//we can set the spheres responce
			sphere->ApplyForce(-sphere->GetVelocity() * sphere->GetMass(), sphere->GetPosition());
			return true;
		}
	}

	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject* a_sphere, PhysicsObject* a_otherSphere)
{
	//tries to cast the object to sphere to sphere (2D so its actually circle to circle)
	Sphere* sphere1 = dynamic_cast<Sphere*>(a_sphere);
	Sphere* sphere2 = dynamic_cast<Sphere*>(a_otherSphere);

	//if susscessful then test cor collision
	if (sphere1 != nullptr && sphere2 != nullptr) 
	{
		//do the maths to check for the overlap
		float dist = glm::distance(sphere1->GetPosition(),sphere2->GetPosition());
		//...if the circles touch, resolve the collision.
		float penertration = sphere1->GetRadius() + sphere2->GetRadius() - dist;

		if (penertration > 0) 
		{
			sphere1->ResolveCollision(sphere2,0.5f * 
				(sphere1->GetPosition() + sphere2->GetPosition()));
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Sphere2Box(PhysicsObject* a_sphere, PhysicsObject* a_box)
{
	return false;
}

bool PhysicsScene::Box2Plane(PhysicsObject* a_box, PhysicsObject* a_plane)
{
	return false;
}

bool PhysicsScene::Box2Sphere(PhysicsObject* a_box, PhysicsObject* a_sphere)
{
	return false;
}

bool PhysicsScene::Box2Box(PhysicsObject* a_box, PhysicsObject* a_otherBox)
{
	return false;
}
