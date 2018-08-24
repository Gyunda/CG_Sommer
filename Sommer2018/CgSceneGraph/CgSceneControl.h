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


class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();

private:
    CgPolyline *line;
    ObjectMesh* simpleObject;
    RotationObject* rotationObject;

    CgBaseRenderer* m_renderer;
    std::vector<CgPolyline*> m_facenormals;
    std::vector<CgPolyline*> m_vertexnormals;
    ObjectMeshCreator* creator;
    CGIdGiver* idGiver;
    std::vector<ObjectMesh*> objects;

    CgExampleTriangle* m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H
