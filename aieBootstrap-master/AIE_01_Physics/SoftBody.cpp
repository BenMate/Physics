#include "PhysicsScene.h"

#include "SoftBody.h"
#include "Sphere.h"
#include "Spring.h"

void SoftBody::Build(PhysicsScene* a_scene, glm::vec2 a_position, 
	float a_spacing, float a_springForce, float a_damping, 
	std::vector<std::string>& a_string)
{
	int numColumms = a_string.size();
	int numRows = a_string[0].length();

	//we want to traverse across the array and add spheres 
	//where the correct ascii art states should be

	//this is used to create p[aticles as our first pass, based on the ASCII art provided.
	Sphere** spheres = new Sphere * [numRows * numColumms];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumms; j++)
		{
			if (a_string[j][i] == '0')
			{
				spheres[i * numColumms + j] = new Sphere(a_position + glm::vec2(i, j) * a_spacing,
					glm::vec2(0), 1.0f, 2.0f, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				a_scene->AddActor(spheres[i * numColumms + j]);
			}
			else 
			{
				spheres[i * numColumms + j] = nullptr;
			}
		}
	}

	//this is the second pass, we will connected the particles with springs
	for (int i = 1; i < numRows; i++)
	{
		for (int j = 1; j < numColumms; j++)
		{
			Sphere* p11 = spheres[i * numColumms + j];
			Sphere* p01 = spheres[(i - 1) * numColumms + j];
			Sphere* p10 = spheres[i * numColumms + j - 1];
			Sphere* p00 = spheres[(i - 1) * numColumms + j - 1];

			//Make the springs connect to their cardinal neighbours if they exist
			if (p11 && p01)		
				a_scene->AddActor(new Spring(p11, p01, a_damping, a_springForce));
			
			if (p11 && p10) 			
				a_scene->AddActor(new Spring(p11, p10, a_damping, a_springForce));
			
			if (p10 && p00)		
				a_scene->AddActor(new Spring(p10, p00, a_damping, a_springForce));
			
			if (p01 && p00)		
				a_scene->AddActor(new Spring(p01, p00, a_damping, a_springForce));
			
			//make the diagonal springs connected if the correct partner exits
			
				if (p11 && p00)
					a_scene->AddActor(new Spring(p11, p00, a_damping, a_springForce));

				if (p01 && p10)
					a_scene->AddActor(new Spring(p01, p10, a_damping, a_springForce));
			
				bool endOfJ = j == numColumms - 1;
				bool endOfI = i == numRows - 1;

				Sphere* p22 = (!endOfI && !endOfJ) ? spheres[(i + 1) * numColumms + (j + 1)] : nullptr;
				Sphere* p02 = !endOfJ ? spheres[(i - 1) * numColumms + (j + 1)] : nullptr;
				Sphere* p20 = !endOfI ? spheres[(i + 1) * numColumms + j - 1] : nullptr;

				if (p22 && p02)
					a_scene->AddActor(new Spring(p22, p02, a_damping, a_springForce));

				if (p22 && p20)
					a_scene->AddActor(new Spring(p22, p20, a_damping, a_springForce));

				if (p20 && p00)
					a_scene->AddActor(new Spring(p20, p00, a_damping, a_springForce));

				if (p02 && p00)
					a_scene->AddActor(new Spring(p02, p00, a_damping, a_springForce));
		}
	}
}
