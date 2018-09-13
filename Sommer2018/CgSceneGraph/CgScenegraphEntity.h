#ifndef CGSCENCEGRAPHENTITY_H
#define CGSCENCEGRAPHENTITY_H

#include <vector>
#include <glm/glm.hpp>

#include <CgBase/CgBaseRenderableObject.h>
#include "CgAppearance.h"

//class CgAppearance;

class CgScenegraphEntity
{
public:
    CgScenegraphEntity(CgBaseRenderableObject* obj, glm::mat4 trans, CgAppearance* app);
                       //, glm::mat4 trans);

    ~CgScenegraphEntity();

    glm::mat4 getCurrentTransformation();
    void setCurrentTransformation(glm::mat4 m_current_transformation);

    CgScenegraphEntity* getParent();
    void setParent( CgScenegraphEntity* m_parent);

    std::vector<CgBaseRenderableObject*> getlistOfObjects();

    //??????
    void setChildren(std::vector <CgScenegraphEntity*> child);
    void setAppearance(CgAppearance* app);

    void addChild(CgScenegraphEntity* newChild);
    void addObj(CgBaseRenderableObject* obj);
    void deleteChild(int childPos);

    int getChildVecSize();
    int getlistOfObjSize();

    std::vector <CgScenegraphEntity*> getChildren();
    CgAppearance* getAppearance();


private:
    std::vector<CgBaseRenderableObject*> listOfObjects;
    glm::mat4 m_current_transformation;

    CgAppearance* m_appearance;

    CgScenegraphEntity* m_parent;
    std::vector <CgScenegraphEntity*> m_children;
};

#endif // CGSCENCEGRAPHENTITY_H
