#ifndef OBJECTMESHCREATOR_H
#define OBJECTMESHCREATOR_H

class ObjectMesh;

#include "CgCube.h"
#include "CgCylinder.h"

class ObjectMeshCreator
{
public:
    ObjectMeshCreator();
    ObjectMesh* createCube();
    ObjectMesh* createCylinder();
   // virtual ObjectMesh* createPolyLine() = 0;
};

#endif // OBJECTMESHCREATOR_H
