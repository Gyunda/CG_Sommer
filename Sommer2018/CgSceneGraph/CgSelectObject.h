#ifndef CGSELECTOBJECT_H
#define CGSELECTOBJECT_H

#include "CgScenegraphEntity.h"
#include <vector>
#include <stack>

class CgSelectObject
{
private:
    CgScenegraphEntity* currentNode;
    CgScenegraphEntity* startNode;
    std::stack<unsigned int> posStack;
    CgAppearance* selectAppearance;
    CgAppearance* previousAppearance;
    CgScenegraphEntity* prevNode;

public:
    CgSelectObject();
    CgSelectObject(CgScenegraphEntity* rootNode);
    ~CgSelectObject();
    void nextNode();
    CgScenegraphEntity* getCurrentNode();
};

#endif // CGSELECTOBJECT_H
