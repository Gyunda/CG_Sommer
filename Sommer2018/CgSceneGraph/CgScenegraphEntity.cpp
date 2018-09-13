#include "CgScenegraphEntity.h"

CgScenegraphEntity::CgScenegraphEntity(CgBaseRenderableObject* obj, glm::mat4 trans, CgAppearance* app)
{
   listOfObjects.push_back(obj);
   setCurrentTransformation(trans);
   setAppearance(app);
}

CgScenegraphEntity::~CgScenegraphEntity(){
    for(unsigned int i=0; i<m_children.size(); i++){
        delete m_children.at(i);
    }

    for(unsigned int i=0; i<listOfObjects.size(); i++){
        delete listOfObjects.at(i);
    }
}

glm::mat4 CgScenegraphEntity::getCurrentTransformation(){
    return m_current_transformation;
}

CgScenegraphEntity* CgScenegraphEntity::getParent(){
    return m_parent;
}

int CgScenegraphEntity::getChildVecSize(){
    return m_children.size();
}

int CgScenegraphEntity::getlistOfObjSize(){
    return listOfObjects.size();
}

std::vector<CgBaseRenderableObject*> CgScenegraphEntity::getlistOfObjects(){
    return listOfObjects;
}

std::vector <CgScenegraphEntity*> CgScenegraphEntity::getChildren(){
    return m_children;
}

CgAppearance* CgScenegraphEntity::getAppearance(){
    return m_appearance;
}

void CgScenegraphEntity::setCurrentTransformation(glm::mat4 m_current_transformation){
    this->m_current_transformation= m_current_transformation;
}

void CgScenegraphEntity::setParent(CgScenegraphEntity *m_parent){
    this->m_parent=m_parent;
}

void CgScenegraphEntity::setAppearance(CgAppearance *app){
    m_appearance=app;
}


void CgScenegraphEntity::addChild(CgScenegraphEntity* newChild){
    newChild->setParent(this);
    m_children.push_back(newChild);
}

void CgScenegraphEntity::addObj(CgBaseRenderableObject *obj){
    listOfObjects.push_back(obj);
}

void CgScenegraphEntity::deleteChild(int childPos){
    m_children.erase(m_children.begin()+childPos);
}
