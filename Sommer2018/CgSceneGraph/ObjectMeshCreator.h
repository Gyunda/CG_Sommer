#ifndef OBJECTMESHCREATOR_H
#define OBJECTMESHCREATOR_H

class ObjectMesh;

#include "CgCube.h"

class ObjectMeshCreator
{
public:
    ObjectMeshCreator();
    ObjectMesh* createCube();
   // virtual ObjectMesh* createCylinder() = 0;
   // virtual ObjectMesh* createPolyLine() = 0;
};

#endif // OBJECTMESHCREATOR_H
