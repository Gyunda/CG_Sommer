#include "CgScenegraph.h"

CgScenegraph::CgScenegraph(){}

CgScenegraph::CgScenegraph(CgScenegraphEntity* root_node)
{
    this->m_root_node= root_node;
    //m_modelview_matrix_stack.push(root_node->getCurrentTransformation());
}

CgScenegraph::~CgScenegraph(){
    delete m_root_node;

    for(unsigned int i=0; i<objList.size(); i++){
            objList.at(i);
        }
}

stack<glm::mat4> CgScenegraph::getModelviewMatrixStack(){
    return m_modelview_matrix_stack;
}

void CgScenegraph::setModelviewMatrixStack(stack<glm::mat4> m_modelview_matrix_stack){
    this->m_modelview_matrix_stack=m_modelview_matrix_stack;
}

CgScenegraphEntity* CgScenegraph::getRootNode(){
    return m_root_node;
}

void CgScenegraph::init(CgBaseRenderer* renderer){
    vector<CgBaseRenderableObject*> objList;
    objList= m_root_node->getlistOfObjects();
    initObj(objList, renderer);

    for(unsigned int i=0; i<m_root_node->getChildVecSize(); i++){
        initChild(m_root_node->getChildren().at(i), renderer);
    }

}

void CgScenegraph::initObj(std::vector<CgBaseRenderableObject *> obj, CgBaseRenderer *renderer){
    for(unsigned int i=0; i<obj.size(); i++){
        renderer->init(obj.at(i));
    }
}

void CgScenegraph::initChild(CgScenegraphEntity *node, CgBaseRenderer *renderer){
    vector<CgBaseRenderableObject*> objList;
    objList= node->getlistOfObjects();
    initObj(objList, renderer);

    for(unsigned int i=0; i<node->getChildren().size(); i++){
        initChild(node->getChildren().at(i), renderer);
    }
}


void CgScenegraph::render(CgBaseRenderer* renderer){
    unsigned int childAnzahl;
    CgScenegraphEntity* temp;
    vector<CgBaseRenderableObject*> objList;

    m_modelview_matrix_stack.push(m_root_node->getCurrentTransformation());

    renderer->setUniformValue("mycolor", m_root_node->getAppearance()->getObjectColor());
    renderer->setUniformValue("normalMatrix", m_modelview_matrix_stack.top());

    childAnzahl = m_root_node->getChildVecSize();
    objList= m_root_node->getlistOfObjects();
    renderObj(objList, renderer);

    for(unsigned int i=0; i<childAnzahl; i++){
        temp= m_root_node->getChildren().at(i);
        renderChild(temp, renderer);
       }

    popMatrix();
}

void CgScenegraph::renderChild(CgScenegraphEntity* node, CgBaseRenderer* renderer){
     CgScenegraphEntity* temp;
     unsigned int childAnzahl;
     vector<CgBaseRenderableObject*> objList;

     childAnzahl= node->getChildVecSize();
     objList= node->getlistOfObjects();

    //fehlerstelle

     pushMatrix();
     applyTransform(node->getCurrentTransformation());

     renderer->setUniformValue("mycolor", node->getAppearance()->getObjectColor());
     renderer->setUniformValue("projMatrix", m_modelview_matrix_stack.top());

     renderObj(objList, renderer);

     for(unsigned int i=0; i<childAnzahl; i++){
         temp= node->getChildren().at(i);
         renderChild(temp, renderer);
     }

     popMatrix();
}

void CgScenegraph::renderObj(std::vector<CgBaseRenderableObject*> obj, CgBaseRenderer* renderer){
    for(unsigned int i=0; i<obj.size(); i++){
        renderer->render(obj.at(i));
    }
}

ObjectMesh* CgScenegraph::createMeshObjectCylinder(int id){
    ObjectMesh* mesh= creator->createCylinder(id);
    objList.push_back(mesh);
}

ObjectMesh* CgScenegraph::createMeshObjectCube(int id){
    ObjectMesh* mesh= creator->createCube(id);
    objList.push_back(mesh);
}

void CgScenegraph::deleteMeshObject(int index){
    objList.erase(objList.begin()+index);
}

std::vector<ObjectMesh*> CgScenegraph::getObjList(){
    return objList;
}

void CgScenegraph::setRootNode(CgScenegraphEntity* root_node){
    m_root_node=root_node;
}

int CgScenegraph::getStackSize(){
    return m_modelview_matrix_stack.size();
}
