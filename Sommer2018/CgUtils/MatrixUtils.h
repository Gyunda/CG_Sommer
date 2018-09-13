#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H
#include <glm/glm.hpp>


class MatrixUtils
{
public:
    MatrixUtils();
    glm::mat4 getZrotationMatrix();
    glm::mat4 getXrotationMatrix();
    glm::mat4 getYrotationMatrix();
    glm::mat4 translationMatrix(glm::vec3);
};

#endif // MATRIXUTILS_H
