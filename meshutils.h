#ifndef MESHUTILS_H
#define MESHUTILS_H

#include "mesh.h"

class MeshUtils
{
public:
	static Mesh* CreatePlane();

	static Mesh* CreateSphere(int rings, int sectors);
};

#endif // MESHUTILS_H
