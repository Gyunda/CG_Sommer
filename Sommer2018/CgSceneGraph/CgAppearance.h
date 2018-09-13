#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include <glm/glm.hpp>


class CgAppearance
{
public:
    CgAppearance(glm::vec4 object_color);

    void setObjectColor(glm::vec4 object_color);
    void setDifuseMaterial(glm::vec3 difuse_material);

    glm::vec4 getObjectColor();
    glm::vec3 getDifuseMaterial();

private:
    glm::vec4 object_color;
    glm::vec3 difuse_material;
};

#endif // CGAPPEARANCE_H
