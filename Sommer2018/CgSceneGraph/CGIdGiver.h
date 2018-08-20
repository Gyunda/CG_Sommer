#ifndef CGIDGIVER_H
#define CGIDGIVER_H

#include <iostream>
//Singletonklasse, erzeugt IDs für Objekte im SceneGraphen.
//Singleton ist problematisch bei Multithreading....

class CGIdGiver
{
public:
    static CGIdGiver* getInstance();
    unsigned int getId();
protected:

private:
    unsigned int id;
    static CGIdGiver* instance;
    CGIdGiver();
    CGIdGiver(const CGIdGiver&);
};

#endif // CGIDGIVER_H
