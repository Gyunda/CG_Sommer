#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <vector>
#include "CgPolyline.h"

class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;
class ObjectMesh;
class CgCube;
class CgCylinder;
class ObjectMeshCreator;
class CGIdGiver;
class RotationObject;
class CgSelectObject;
class CgScenegraph;
class CgScenegraphEntity;
class MatrixUtils;


class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    static CgSceneControl* getInstance();
    unsigned int getId();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();

private:
    CgSceneControl();
    CgSceneControl(const CgSceneControl&);
    static CgSceneControl* instance;
    unsigned int id;
    CgPolyline *line;
    CgCube* cube;
    CgCylinder* cylinder;
    CgPolyline* m_vierPunkt;
    ObjectMesh* m_object;
    RotationObject* rotationObject;

    CgSelectObject* m_select;   //Select Object
    MatrixUtils* m_matrixUtils;
        //Szenegraph shit
        CgScenegraph* graph;
        CgScenegraphEntity* entity;
        CgScenegraphEntity* entity2;
        CgScenegraphEntity* entity3;
        CgScenegraphEntity* entity4;
        CgScenegraphEntity* entity5;

    CgBaseRenderer* m_renderer;
    std::vector<CgPolyline*> m_facenormals;
    std::vector<CgPolyline*> m_vertexnormals;
    ObjectMeshCreator* creator;
    std::vector<ObjectMesh*> objects;

    CgExampleTriangle* m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H
