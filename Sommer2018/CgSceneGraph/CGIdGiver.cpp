#include "CGIdGiver.h"

CGIdGiver* CGIdGiver::instance = 0;

CGIdGiver* CGIdGiver::getInstance() {
    if(instance == 0) {
        instance = new CGIdGiver();
    }
    return instance;
}

CGIdGiver::CGIdGiver() {
    id = 0;
}

CGIdGiver::CGIdGiver(const CGIdGiver &) {

}

unsigned int CGIdGiver::getId() {
    id++;
    return id;
}

