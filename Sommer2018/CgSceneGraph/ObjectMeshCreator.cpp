#include "ObjectMeshCreator.h"

ObjectMeshCreator::ObjectMeshCreator()
{
}

ObjectMesh* ObjectMeshCreator::createCube() {
    return new CgCube();
}

//  ObjectMesh* ObjectMeshCreator::createCylinder() {
//
//  }

 // ObjectMesh* ObjectMeshCreator::createPolyLine() {
//
//  }
