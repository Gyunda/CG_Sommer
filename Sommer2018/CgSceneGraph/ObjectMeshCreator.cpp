#include "ObjectMeshCreator.h"

ObjectMeshCreator::ObjectMeshCreator()
{
}

ObjectMesh* ObjectMeshCreator::createObject(int id) {

}

CgCube* ObjectMeshCreator::createCube(int id) {
    return new CgCube(id);
}

CgCylinder* ObjectMeshCreator::createCylinder(int id) {
    return new CgCylinder(id, 6, 3, 1);
  }

ObjectMesh* ObjectMeshCreator::createRotationObject(int id) {
   // return new RotationObject();
}

