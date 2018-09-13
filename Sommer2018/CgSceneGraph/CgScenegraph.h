#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include <stack>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include "CgScenegraphEntity.h"
#include "CgBase/CgBaseRenderer.h"
#include "ObjectMeshCreator.h"

class ObjectMeshCreator;
class ObjectMesh;

using namespace std;

class CgScenegraph
{
public:
    CgScenegraph();
    CgScenegraph(CgScenegraphEntity* root_node);
    ~CgScenegraph();

    void render(CgBaseRenderer* renderer);
    void init(CgBaseRenderer* renderer);

    stack<glm::mat4> getModelviewMatrixStack();
    void setModelviewMatrixStack(stack<glm::mat4> m_modelview_matrix_stack);

    CgScenegraphEntity* getRootNode();

    void renderChild(CgScenegraphEntity* node, CgBaseRenderer* renderer);
    void renderObj(std::vector<CgBaseRenderableObject*> obj, CgBaseRenderer* renderer);

    void initObj(std::vector<CgBaseRenderableObject*> obj, CgBaseRenderer* renderer);
    void initChild(CgScenegraphEntity* node, CgBaseRenderer* renderer);

    ObjectMesh* createMeshObjectCylinder(int id);
    ObjectMesh* createMeshObjectCube(int id);
    void deleteMeshObject(int index);

    std::vector<ObjectMesh*> getObjList();

    void setRootNode(CgScenegraphEntity* root_node);

    //Test

    int getStackSize();

private:
    CgScenegraphEntity* m_root_node;
    stack<glm::mat4> m_modelview_matrix_stack;
    std::vector<ObjectMesh*> objList;

    ObjectMeshCreator* creator;

    void pushMatrix();
    void popMatrix();
    void applyTransform(glm::mat4 arg);

};

inline void CgScenegraph::pushMatrix() {m_modelview_matrix_stack.push(m_modelview_matrix_stack.top());}
inline void CgScenegraph::popMatrix(){m_modelview_matrix_stack.pop();}
inline void CgScenegraph::applyTransform(glm::mat4 arg){m_modelview_matrix_stack.top()*=arg;}

#endif // CGSCENEGRAPH_H
