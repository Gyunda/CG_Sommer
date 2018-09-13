#ifndef OBJECTMESHCREATOR_H
#define OBJECTMESHCREATOR_H

class ObjectMesh;

#include "CgCube.h"
#include "CgCylinder.h"
#include "RotationObject.h"

class ObjectMeshCreator
{
public:
    ObjectMeshCreator();
    ObjectMesh* createObject(int id);
    CgCube* createCube(int id);
    CgCylinder* createCylinder(int id);
    ObjectMesh* createRotationObject(int id);
};

#endif // OBJECTMESHCREATOR_H
