#ifndef CGCUBE_H
#define CGCUBE_H

#include <vector>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"
#include "ObjectMesh.h"

class CgCube : public ObjectMesh
{

public:
    CgCube(int id);
    ~CgCube();




private:
    void calculateFaceNormals();
    void calculateFaceFocus();



};



#endif // CGCUBE_H
