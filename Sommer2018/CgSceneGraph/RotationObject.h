#ifndef ROTATIONOBJECT_H
#define ROTATIONOBJECT_H


#include "RotationObject.h"

#include <string>
#include "CgPolyline.h"
#include "CgBase/CgEnums.h"
#include "ObjectMesh.h"

class RotationObject: public ObjectMesh
{
public:
    RotationObject();
    void smoothLine();
    CgPolyline* getLine();
private:
    CgPolyline* line;
    std::vector<glm::vec3> list;
};

#endif // ROTATIONOBJECT_H
