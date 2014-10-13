#include "meshutils.h"

#include <math.h>


Mesh* MeshUtils::CreatePlane()
{
	std::vector<GLfloat> v {
		-0.5, -0.5, 0.0, 0, 0, 1, 1, 1, 1, 0, 0,
		-0.5,  0.5, 0.0, 0, 0, 1, 1, 1, 1, 0, 1,
		 0.5, -0.5, 0.0, 0, 0, 1, 1, 1, 1, 1, 0,
		 0.5,  0.5, 0.0, 0, 0, 1, 1, 1, 1, 1, 1
	};
	std::vector<GLuint> e {
		0,3,1,
		0,2,3
	};


	Mesh* m = new Mesh();
	m->vertices = v;
	m->elements = e;

	return m;
}

Mesh* MeshUtils::CreateSphere(int rings, int sectors)
{
	std::vector<GLfloat> vertices;
	std::vector<GLuint> elements;

	float R = 1.f/(float)(rings-1);
	float S = 1.f/(float)(sectors-1);

	{
		vertices.resize(rings * sectors * 12);
		std::vector<GLfloat>::iterator itr = vertices.begin();
		for (int r = 0; r < rings; r++)
		{
			for (int s = 0; s < sectors; s++)
			{
				float u = (float)s*S;
				float v = (float)r*R;
				float theta = u * 2.0f * M_PI;
				float rho = v * M_PI;
				float x = cos(theta) * sin(rho);
				float y = sin((float)-M_PI_2 + rho);
				float z = sin(theta) * sin(rho);
				*itr++ = x;
				*itr++ = y;
				*itr++ = z;
				*itr++ = x;
				*itr++ = y;
				*itr++ = z;
				*itr++ = 1.0f;
				*itr++ = 1.0f;
				*itr++ = 1.0f;
				*itr++ = u;
				*itr++ = v;
			}
		}
	}

	{
		elements.resize(rings * sectors * 6);
		std::vector<GLuint>::iterator itr = elements.begin();
		for(int r = 0; r < rings-1; r++)
		{
			for(int s = 0; s < sectors-1; s++)
			{
				*itr++ = (r+1) * sectors + (s+1);
				*itr++ = r * sectors + (s+1);
				*itr++ = r * sectors + s;
				*itr++ = r * sectors + s;
				*itr++ = (r+1) * sectors + s;
				*itr++ = (r+1) * sectors + (s+1);
			}
		}
	}

	Mesh* m = new Mesh();
	m->vertices = vertices;
	m->elements = elements;

	return m;
}
