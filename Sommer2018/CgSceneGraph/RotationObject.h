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
    RotationObject(int id, CgPolyline* newLine, int aufloesung);
    void smoothLine();
    void rotate(int newanzahl);
    CgPolyline* getLine();
private:
    CgPolyline* line;
    float winkel;
    int anzahl;
    glm::mat3x3 rotationmatrix;
    std::vector<glm::vec3> list;
    void calculateVertexNormals();
    void closeRotationObject();
};

#endif // ROTATIONOBJECT_H
