#ifndef MESH_H
#define MESH_H

#include <vector>
#include <qopengl.h>

class Mesh
{
public:
	Mesh();

	~Mesh();

	std::vector<GLfloat> vertices;
	std::vector<GLuint> elements;

	void render();

};

#endif // MESH_H
