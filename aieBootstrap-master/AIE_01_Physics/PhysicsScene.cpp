#include <list>
#include <iostream>
#include <algorithm>
#include <glm/ext.hpp>

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
	Plane* plane = dynamic_cast <Plane*>(a_plane);
	Box* box = dynamic_cast<Box*>(a_box);

	//when the argument return true start the collision test
	if (box != nullptr && plane != nullptr) 
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactVel = 0;

		glm::vec2 planeOrigin = plane->GetNormal() * plane->GetDistance();

		//check all four corners of the box for any have touced the
		//plane

		for (float x = -box->GetExtents().x; x < box->GetWidth(); x+= box->GetWidth())
		{
			for (float y = -box->GetExtents().y; y < box->GetHieght(); y += box->GetHieght())
			{
				//next, grab the poition of the corner in world space
				glm::vec2 p = box->GetPosition() + x * box->GetLocalX() + y * box->GetLocalY();
				float distanceFromPlane = glm::dot(p - planeOrigin, plane->GetNormal());

				//this is the total velcoity of the box's points in the world space
				glm::vec2 displacement = x * box->GetLocalX() + y * box->GetLocalY();
				glm::vec2 pointVelocity = box->GetVelocity() + box->GetAngularVelocity()
					* glm::vec2(-displacement.y, displacement.x);

				//this s the component of th point velocity into the plane
				float velocityIntoPlane = glm::dot(pointVelocity, plane->GetNormal());

				//while our box is penatrating the plane .....
				if (distanceFromPlane < 0 && velocityIntoPlane <= 0) 
				{
					numContacts++;
					contact += p;
					contactVel += velocityIntoPlane;
				}
			}
		}

		//we have a hit if greater then 0, typically only 1 to 2 corners will colide
		if (numContacts > 0) 
		{
			//TODO: account for 1 or 2 corners overlapping
			plane->ResolvePlaneCollision(box, contact / (float) numContacts);


			return true;
		}
	}
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
			//we can set object to respond to a plane collision

			glm::vec2 contact = sphere->GetPosition() + (collisionNormal * -sphere->GetRadius());
			plane->ResolvePlaneCollision(sphere, contact);
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
	return Box2Sphere(a_box, a_sphere);
}

bool PhysicsScene::Box2Plane(PhysicsObject* a_box, PhysicsObject* a_plane)
{
	return Plane2Box(a_plane, a_box);
}

bool PhysicsScene::Box2Sphere(PhysicsObject* a_box, PhysicsObject* a_sphere)
{
	Sphere* sphere = dynamic_cast<Sphere*>(a_sphere);
	Box* box = dynamic_cast<Box*>(a_box);

	if (box != nullptr && sphere != nullptr) 
	{
		//transform the sphere into the box's coordinate space
		glm::vec2 sphereWorldPos = sphere->GetPosition() - box->GetPosition();
		glm::vec2 sphereBoxPos = glm::vec2(glm::dot(sphereWorldPos, box->GetLocalX()),
			glm::dot(sphereWorldPos, box->GetLocalY()));

		//then find the closest point to the circle center on the box,
		//do this by clamping the coordinates in box space to the 
		//box's extents

		glm::vec2 closestPointOnTheBox = sphereBoxPos;
		glm::vec2 extents = box->GetExtents();

		if (closestPointOnTheBox.x < -extents.x)
			closestPointOnTheBox.x = -extents.x;

		if (closestPointOnTheBox.x > extents.x)
			closestPointOnTheBox.x = extents.x;

		if (closestPointOnTheBox.y < -extents.y)
			closestPointOnTheBox.y = -extents.y;

		if (closestPointOnTheBox.y > extents.y)
			closestPointOnTheBox.y = extents.y;
		
		//Finally, convert back to world coordinates
		//fun thing to test swap the x and y around

		glm::vec2 closestPointInBoxWorld = box->GetPosition() + closestPointOnTheBox.x * 
			box->GetLocalX() + closestPointOnTheBox.y * box->GetLocalY();

		glm::vec2 sphereToBox = sphere->GetPosition() - closestPointInBoxWorld;

		float penertration = sphere->GetRadius() - glm::length(sphereToBox);

		if (penertration > 0)
		{
			glm::vec2 direction = glm::normalize(sphereToBox);
			glm::vec2 contact = closestPointInBoxWorld;
			box->ResolveCollision(sphere, contact, &direction);
			return true;
		}

	}

	return false;
}

bool PhysicsScene::Box2Box(PhysicsObject* a_box, PhysicsObject* a_otherBox)
{
	Box* box1 = dynamic_cast<Box*>(a_box);
	Box* box2 = dynamic_cast<Box*>(a_otherBox);

	if (box1 != nullptr && box2 != nullptr) 
	{
		glm::vec2 boxPos = box2->GetPosition() - box1->GetPosition();
		glm::vec2 norm(0, 0);
		glm::vec2 contact(0, 0);
		float pen = 0;
		int numContract = 0;
		box1->CheckBoxCorners(*box2, contact, numContract, pen, norm);
		if (box2->CheckBoxCorners(*box1, contact, numContract, pen, norm)) 
		{
			norm = -norm;
		}
		if (pen > 0) 
		{
			box1->ResolveCollision(box2, contact / float(numContract), &norm);
		}
		return true;
	}
	return false;
}
