#include "MatrixUtils.h"
#include <glm/glm.hpp>
#include <math.h>

//Klasse mit vorgefertigten Matrizen, zur Vereinfachung von Transformationen
MatrixUtils::MatrixUtils(){

}
//gibt Matrize aus, damit mupltipliziert eine Rotation über Z-Achse durchgeführt werden kann
glm::mat4 MatrixUtils::getZrotationMatrix(){

    float bogen = (2 * M_PI * 10)/((float) 360);
    glm::vec4 zeile1(cos(bogen), -sin(bogen), 0, 0);
    glm::vec4 zeile2(sin(bogen), cos(bogen), 0, 0);
    glm::vec4 zeile3(0, 0, 1, 0);
    glm::vec4 zeile4(0, 0, 0, 1);
    return glm::mat4(zeile1,zeile2,zeile3,zeile4);
}
//gibt Matrize aus, damit mupltipliziert eine Rotation über X-Achse durchgeführt werden kann
glm::mat4 MatrixUtils::getXrotationMatrix(){

    float bogen = (2 * M_PI * 10)/((float) 360);
    glm::vec4 zeile1(1, 0, 0, 0);
    glm::vec4 zeile2(0, cos(bogen),-sin(bogen), 0);
    glm::vec4 zeile3(0, sin(bogen), cos(bogen), 0);
    glm::vec4 zeile4(0, 0, 0, 1);
    return glm::mat4(zeile1,zeile2,zeile3,zeile4);

}
//gibt Matrize aus, damit mupltipliziert eine Rotation über Y-Achse durchgeführt werden kann
glm::mat4 MatrixUtils::getYrotationMatrix(){

    float bogen = (2 * M_PI * 10)/((float) 360);
    glm::vec4 zeile1(cos(bogen), 0, sin(bogen), 0);
    glm::vec4 zeile2(0, 1, 0, 0);
    glm::vec4 zeile3(-sin(bogen), 0, cos(bogen), 0);
    glm::vec4 zeile4(0, 0, 0, 1);
    return glm::mat4(zeile1,zeile2,zeile3,zeile4);

}

glm::mat4 MatrixUtils::translationMatrix(glm::vec3 t){

    glm::vec4 zeile1(1, 0, 0, t.x);
    glm::vec4 zeile2(0, 1, 0, t.y);
    glm::vec4 zeile3(0, 0, 1, t.z);
    glm::vec4 zeile4(0, 0, 0, 1);
    return glm::mat4(zeile1,zeile2,zeile3,zeile4);

}
