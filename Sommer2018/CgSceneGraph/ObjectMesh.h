#ifndef OBJECTMESH_H
#define OBJECTMESH_H

#include <vector>
#include <glm/glm.hpp>
#include <stdio.h>

#include "CgBase/CgBaseTriangleMesh.h"

class ObjectMesh : public CgBaseTriangleMesh
{
public:
    ObjectMesh();
    void print_ids();
protected:
    const unsigned int m_id;
    static unsigned int total_ids;
};

#endif // OBJECTMESH_H
