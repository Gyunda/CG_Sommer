#include "ObjectMeshCreator.h"

ObjectMeshCreator::ObjectMeshCreator()
{
}

ObjectMesh* ObjectMeshCreator::createCube() {
    return new CgCube();
}

ObjectMesh* ObjectMeshCreator::createCylinder() {
    return new CgCylinder(6, 3, 1);
  }

