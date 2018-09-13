#include "CgCube.h"
#include "CgBase/CgEnums.h"

#define SIZE 0.25

CgCube::CgCube(int id) : ObjectMesh(id)
{
    //8 Eckpunkte für Würfel
    m_vertices.push_back(glm::vec3(-SIZE,-SIZE,SIZE)); //0 //Würfel
    m_vertices.push_back(glm::vec3(SIZE,-SIZE,SIZE)); //1
    m_vertices.push_back(glm::vec3(-SIZE,SIZE,SIZE)); //2
    m_vertices.push_back(glm::vec3(SIZE,SIZE,SIZE)); //3

    m_vertices.push_back(glm::vec3(-SIZE,-SIZE,-SIZE)); //4
    m_vertices.push_back(glm::vec3(SIZE,-SIZE,-SIZE)); //5
    m_vertices.push_back(glm::vec3(-SIZE,SIZE,-SIZE)); //6
    m_vertices.push_back(glm::vec3(SIZE,SIZE,-SIZE)); //7


    //Den Dreiecken jeweils die Ecken zuweisen
    m_triangle_indices.push_back(2);        //0 i
    m_triangle_indices.push_back(0);        //1 i+1
    m_triangle_indices.push_back(1);        //2 i+2

    m_triangle_indices.push_back(1);        //3 i+3
    m_triangle_indices.push_back(3);        //4 i+4
    m_triangle_indices.push_back(2);        //5 i+5

    m_triangle_indices.push_back(1);        //6
    m_triangle_indices.push_back(5);        //7
    m_triangle_indices.push_back(3);        //8

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(3);

    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);

    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(5);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(7);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(4);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(1);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);


    //Berechnung der Face_Normals (senkrechte auf Dreiecksfläche)
    calculateFaceNormals();

    //Berechnung der Schwerpunkte der Dreiecke
    calculateFaceFocus();
}
void CgCube::calculateFaceNormals() {
    for(int i=0; i < 12; i++) {
        glm::vec3 a = m_vertices.at(m_triangle_indices.at(i*3+1)) - m_vertices.at(m_triangle_indices.at(i*3+2));
        glm::vec3 b =m_vertices.at(m_triangle_indices.at(i*3+1)) - m_vertices.at(m_triangle_indices.at(i*3));
        m_face_normals.push_back(glm::cross(a,b));
    }
}

void CgCube::calculateFaceFocus() {
    for(int i = 0; i < 12; i++) {
        glm::vec3 zwischen = m_vertices.at(m_triangle_indices.at(i*3)) + m_vertices.at(m_triangle_indices.at(i*3+1)) + m_vertices.at(m_triangle_indices.at(i*3+2));
        zwischen[0] = zwischen[0]/3;
        zwischen[1] = zwischen[1]/3;
        zwischen[2] = zwischen[2]/3;
        m_face_focus.push_back(zwischen);
    }
}


CgCube::~CgCube()
{
m_vertices.clear();
m_vertex_normals.clear();
m_vertex_colors.clear();
m_tex_coords.clear();
m_triangle_indices.clear();
m_face_normals.clear();
m_face_colors.clear();
m_face_focus.clear();
}



