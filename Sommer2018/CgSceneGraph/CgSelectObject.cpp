#include "CgSelectObject.h"

CgSelectObject::CgSelectObject(CgScenegraphEntity* rootNode) : currentNode(rootNode)
{
    posStack.push(0);
    startNode = currentNode;
    selectAppearance = new CgAppearance(glm::vec4(1.0,1.0,1.0,1.0));
    previousAppearance = startNode->getAppearance();
    currentNode->setAppearance(selectAppearance);
}

CgSelectObject::~CgSelectObject(){

}

void CgSelectObject::nextNode(){
    prevNode = currentNode;
    if(!currentNode->getChildren().empty()){
        posStack.push(0);
        currentNode = currentNode->getChildren().at(0);
    }
    else if(currentNode->getChildren().empty()){
        posStack.top()++;
        if(posStack.top() < currentNode->getParent()->getChildren().size()){
            currentNode->setAppearance(previousAppearance);
            currentNode = currentNode->getParent()->getChildren().at(posStack.top());
        }
        else{
            posStack.pop();
            posStack.top()++;
            currentNode->setAppearance(previousAppearance);
            if(currentNode->getParent() != startNode && posStack.top() < currentNode->getParent()->getParent()->getChildren().size()){
                currentNode = currentNode->getParent()->getParent()->getChildren().at(posStack.top());
            }
            else{
                currentNode = startNode;
                posStack.pop();
                posStack.push(0);
            }
        }
    }
    prevNode->setAppearance(previousAppearance);
    previousAppearance = currentNode->getAppearance();
    currentNode->setAppearance(selectAppearance);
}

CgScenegraphEntity* CgSelectObject::getCurrentNode(){
    return this->currentNode;
}
