#include "mesh.h"
#include <cassert>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::render()
{
	glVertexPointer( 3,   //3 components per vertex (x,y,z)
					 GL_FLOAT,
					 11 * sizeof(GLfloat),
					 &vertices.front());
	glNormalPointer( GL_FLOAT,
					 11 * sizeof(GLfloat),
					 &vertices.front() + 3);

	glColorPointer(  3,   //3 components per vertex (r,g,b)
					 GL_FLOAT,
					 11 * sizeof(GLfloat),
					 &vertices.front() + 6);  //Pointer to the first color

	glTexCoordPointer( 2,   //2 components per vertex (u, v)
					 GL_FLOAT,
					 11 * sizeof(GLfloat),
					 &vertices.front() + 9);

	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, &elements.front());
}
