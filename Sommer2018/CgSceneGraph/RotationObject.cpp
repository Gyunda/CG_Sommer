#include "RotationObject.h"
#include <iostream>

RotationObject::RotationObject()
{

    glm::vec3 a = glm::vec3(0.2,0.0, 0.0);
    glm::vec3 b = glm::vec3(0.2, 0.1, 0.0);
    glm::vec3 c = glm::vec3(0.3, 0.4, 0.0);
    glm::vec3 d = glm::vec3(0.1, 0.45, 0.0);
    glm::vec3 e = glm::vec3(0.0, 0.6, 0.0);
    list.push_back(a);
    list.push_back(b);
    list.push_back(c);
    list.push_back(d);
    list.push_back(e);
    line = new CgPolyline(list, 1);
}

CgPolyline* RotationObject::getLine() {
    return line;
}

void RotationObject::smoothLine() {
   float w = 0.0625;
   float x;
   float y;
   float z;
   glm::vec3 hilfsvektor = glm::vec3(0.0,0.0,0.0);
    int size = list.size();
    //std::cout << size << std::endl;
    for(int i = 0; i < size-1; i++) {
        list.push_back(glm::vec3(0.0,0.0,0.0));
    }
    //std::cout << list.size() << std::endl;
    //ursprüngliche Elemente an den neuen Platz tun
    for(int i = size-1; i > 0 ; i--) {
       // std::cout << i << std::endl;
        list.at(2*i) = list.at(i);
    }
    //zweiter Punkt
    for(int i = 0; i < list.size(); i++) {
        std::cout << "liste " << list.at(i).x << " " << list.at(i).y << " " << list.at(i).z << std::endl;
    }

    hilfsvektor.x = list.at(0).x + (list.at(0).x - list.at(2).x);
    hilfsvektor.y = list.at(0).y + (list.at(0).y - list.at(2).y);
    hilfsvektor.z = list.at(0).z + (list.at(0).z - list.at(2).z);
    //std::cout << hilfsvektor.x << hilfsvektor.y << hilfsvektor.z << std::endl;
    x = ((-w) * list.at(0).x) + (((0.5) + w) * hilfsvektor.x) + (((0.5) + w) * list.at(2).x) - (w * list.at(4).x);
    y = ((-w) * list.at(0).y) + (((0.5) + w) * hilfsvektor.y) + (((0.5) + w) * list.at(2).y) - (w * list.at(4).y);
    z = ((-w) * list.at(0).z) + (((0.5) + w) * hilfsvektor.z) + (((0.5) + w) * list.at(2).z) - (w * list.at(4).z);
    list.at(1) = glm::vec3(x,y,z);
    std::cout << "neuer zweiter punkt: " << list.at(1).x << " " << list.at(1).x << " " << list.at(1).z << std::endl;
    //mittlere Punkte
    for(int i = 1; i < size -2; i++) {
        x = -w * list.at(2*i).x + ((0.5) + w) * list.at(2*1 - 2).x + ((0.5) + w) * list.at(2*i+2).x - w * list.at(2 * i + 4).x;
        y = -w * list.at(2*i).y + ((0.5) + w) * list.at(2*1 - 2).y + ((0.5) + w) * list.at(2*i+2).y - w * list.at(2 * i + 4).y;
        z = -w * list.at(2*i).z + ((0.5) + w) * list.at(2*1 - 2).z + ((0.5) + w) * list.at(2*i+2).z - w * list.at(2 * i + 4).z;
        list.at(2*i+1) = glm::vec3(x,y,z);
    }
    //vorletzter Punkt
    hilfsvektor.x = list.at(list.size()-1).x + (list.at(list.size()-1).x - list.at(list.size()-3).x);
    hilfsvektor.y = list.at(list.size()-1).y + (list.at(list.size()-1).y - list.at(list.size()-3).y);
    hilfsvektor.z = list.at(list.size()-1).z + (list.at(list.size()-1).z - list.at(list.size()-3).z);

    x = ((-w) * list.at(list.size()-5).x) + (((0.5) + w) * list.at(list.size()-3).x) + (((0.5) + w) * list.at(list.size()-1).x) - (w * hilfsvektor.x);
    y = ((-w) * list.at(list.size()-5).y) + (((0.5) + w) * list.at(list.size()-3).y) + (((0.5) + w) * list.at(list.size()-1).y) - (w * hilfsvektor.y);
    z = ((-w) * list.at(list.size()-5).z) + (((0.5) + w) * list.at(list.size()-3).z) + (((0.5) + w) * list.at(list.size()-1).z) - (w * hilfsvektor.z);
    list.at(list.size()-2) = glm::vec3(x,y,z);

    //letzter Punkt

    line = new CgPolyline(list, 1);
}

