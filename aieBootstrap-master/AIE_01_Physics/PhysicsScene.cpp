#include <list>
#include <iostream>

#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Sphere.h"



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

void PhysicsScene::AddVector(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);

}

void PhysicsScene::RemoveVector(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	if (it != m_actors.end()) 
	{
		m_actors.erase(it);
	}
}

void PhysicsScene::Update(float a_dt)
{
	//temp --------------------------

	static std::list<PhysicsObject*> dirtyList;

	//----------------------------------



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

		// Must Remove Later :)==============

		//check for collisions, we will want to update this to 
		//have some kind of scene management in place

		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors) 
			{
				if (pActor == pOther) 
				{
					continue;
				}

				if (std::find(dirtyList.begin(), dirtyList.end(), pActor) != dirtyList.end()
					&& std::find(dirtyList.begin(), dirtyList.end(), pOther) != dirtyList.end())
					continue;
				
				RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);
				if (pRigid->CheckCollosion(pOther)) 
				{
					pRigid->ApplyForceToActor(dynamic_cast<RigidBody*>(pOther),
						pRigid->GetVelocity() * pRigid->GetMass());

					dirtyList.push_back(pRigid);
					dirtyList.push_back(pOther);
				}
	
			}
				
		}

		dirtyList.clear();
		

	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->Draw();
	}
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject* a_sphere, PhysicsObject* a_otherSphere)
{
	//tries to cast the object to sphere to sphere (2D so its actually circle to circle)
	Sphere* sphere1 = dynamic_cast<Sphere*>(a_sphere);
	Sphere* sphere2 = dynamic_cast<Sphere*>(a_otherSphere);

	//if susscessful then test cor collision

	if (sphere1 != nullptr && sphere2 != nullptr) 
	{
		//TODO the maths requiered here :)

		//=================================
	}

	return false;
}
