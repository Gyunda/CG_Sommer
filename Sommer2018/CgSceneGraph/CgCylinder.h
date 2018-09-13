#ifndef CGCYLINDER_H
#define CGCYLINDER_H

#include <vector>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"
#include "ObjectMesh.h"

class CgCylinder : public ObjectMesh
{
public:
        CgCylinder();
        CgCylinder(int id, int anzahl_kreispunkte, int anzahl_hoehe, double hoehe);
        ~CgCylinder();
        void punkte();
        void kreisflaechen();
        void mantelflaeche();
        void berechneFaceNormalen();
        void berechneVertexNormalen();
        void berechneFaceFocus();





    private:
        //mathematische Definition des Zylinders -> zum finden der Punkte und Schnittberechnungen wichtig. Die gefundenen Punkte dann als Vertexliste benutzen, dreiecke etc...
        double radius;
        double hoehe;
        int anzahl_kreispunkte;
        int anzahl_hoehe;



};


#endif // CGCYLINDER_H
