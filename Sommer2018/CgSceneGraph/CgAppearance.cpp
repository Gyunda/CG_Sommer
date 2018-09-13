#include "CgAppearance.h"

CgAppearance::CgAppearance(glm::vec4 object_color)
{
    this->object_color=object_color;
}

// setter u. getter

void CgAppearance::setObjectColor(glm::vec4 object_color){
    this->object_color= object_color;
}

void CgAppearance::setDifuseMaterial(glm::vec3 difuse_material){
    this->difuse_material=difuse_material;
}

glm::vec4 CgAppearance::getObjectColor(){
    return object_color;
}

glm::vec3 CgAppearance::getDifuseMaterial(){
    return difuse_material;
}
