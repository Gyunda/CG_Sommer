#include "RotationObject.h"
#include <iostream>
#include <math.h>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>


//Rotationskörper
//Speichert eine Polyline list als Ausgangsgröße
//Rotiert diese Linie um y-Achse





RotationObject::RotationObject(int id, CgPolyline* newLine, int aufloesung) : ObjectMesh(id)
{
    anzahl = aufloesung;
/*
    list.push_back(glm::vec3(0.0,0.37,0.0));
     list.push_back(glm::vec3(0.1,0.35,0.0));
     list.push_back(glm::vec3(0.13,0.30,0.0));
     list.push_back(glm::vec3(0.1,0.25,0.0));
     list.push_back(glm::vec3(0.06,0.22,0.0));
     list.push_back(glm::vec3(0.08,0.20,0.0));
     list.push_back(glm::vec3(0.03,0.08,0.0));

     //Körper
     list.push_back(glm::vec3(0.08,-0.03,0.0));
     list.push_back(glm::vec3(0.13,-0.08,0.0));
     list.push_back(glm::vec3(0.13,-0.17,0.0));
     list.push_back(glm::vec3(0.1,-0.20,0.0));
     list.push_back(glm::vec3(0.0,-0.20,0.0));
*/
    for(int i = 0; i < newLine->getVertices().size(); i++) {
        list.push_back(newLine->getVertices().at(i));
    line = new CgPolyline(123456, list, 0.1);
    }
    rotate(anzahl);
}

CgPolyline* RotationObject::getLine() {
    return line;
}

void RotationObject::smoothLine() {

}

void RotationObject::rotate(int newanzahl) {
    anzahl = newanzahl;
    winkel = ((float)360)/((float)anzahl);
    int anzahlPunkte = list.size() * anzahl;
    int size = list.size();
    float bogen = (2 * M_PI * winkel)/((float) 360);
    glm::vec3 schwerpunkt = glm::vec3(0.0,0.0,0.0);
    glm::vec3 u = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 v = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 n = glm::vec3(0.0, 0.0, 0.0);
    float a = cos(bogen);
    float b = sin(bogen);
    //Rotationsmatrix für Drehung um die y-Achse
    rotationmatrix =glm::mat3x3(glm::vec3(a,0.0,b), glm::vec3(0.0,1.0,0.0), glm::vec3(-b,0.0,a));


    //liste mit 0 auffüllen und punkte an richtigen ort kopieren
    for(int i =0; i < anzahlPunkte; i++) {
        m_vertices.push_back(glm::vec3(0.0,0.0,0.0));
    }

    for(int i = 0; i <size; i++) {
        m_vertices.at(i*anzahl) = list.at(i);
    }
    //punkte rotieren und in liste tun

    for(int i = 0; i < m_vertices.size(); i = i+anzahl) {
        for(int j = 0; j <anzahl-1; j++) {
           m_vertices.at(i+j+1) = rotationmatrix*m_vertices.at(i+j);
        }
    }

    //punkte in triangle liste tun:
    //rechts unten:
    for(int i= 0; i < list.size()-1; i++) {
        for(int j = 0; j < anzahl-1; j++) {
            m_triangle_indices.push_back(i*anzahl + j);
            m_triangle_indices.push_back((i+1)*anzahl + j);
            m_triangle_indices.push_back(i*anzahl + j + 1);
            u = m_vertices.at((i+1)*anzahl + j) - m_vertices.at(i*anzahl + j);
            v = m_vertices.at(i*anzahl + j + 1) - m_vertices.at(i*anzahl + j);
            n = glm::cross(u,v);
            n = glm::normalize(n);
            m_face_normals.push_back(n);
            schwerpunkt = (m_vertices.at(i*anzahl + j) + m_vertices.at((i+1)*anzahl + j) + m_vertices.at(i*anzahl + j + 1)) /  (float)3;
            m_face_focus.push_back(schwerpunkt);
        }
        //Randstück:
        m_triangle_indices.push_back(i*anzahl+anzahl-1);
        m_triangle_indices.push_back((i+1)*anzahl+anzahl-1);
        m_triangle_indices.push_back(i*anzahl);
        u = m_vertices.at((i+1)*anzahl+anzahl-1) - m_vertices.at(i*anzahl+anzahl-1);
        v = m_vertices.at(i*anzahl) - m_vertices.at(i*anzahl+anzahl-1);
        n = glm::cross(u,v);
        n = glm::normalize(n);
        m_face_normals.push_back(n);
        schwerpunkt = (m_vertices.at(i*anzahl+anzahl-1) + m_vertices.at((i+1)*anzahl+anzahl-1) + m_vertices.at(i*anzahl)) /  (float)3;
        m_face_focus.push_back(schwerpunkt);
    }
    //links oben:
    for(int i= list.size(); i > 1; i--) {
        for(int j = 1; j < anzahl; j++) {
            m_triangle_indices.push_back(i*anzahl-j);
            m_triangle_indices.push_back(i*anzahl - j - anzahl);
            m_triangle_indices.push_back(i*anzahl-j-1);
            u = m_vertices.at(i*anzahl - j - anzahl) - m_vertices.at(i*anzahl-j);
            v = m_vertices.at(i*anzahl-j-1) - m_vertices.at(i*anzahl-j);
            n = glm::cross(u,v);
            n = glm::normalize(n);
            m_face_normals.push_back(n);
            schwerpunkt = (m_vertices.at(i*anzahl-j) + m_vertices.at(i*anzahl - j - anzahl) + m_vertices.at(i*anzahl-j-1)) /  (float)3;
            m_face_focus.push_back(schwerpunkt);
        }
        //Randstück:
        m_triangle_indices.push_back((i-1)*anzahl);
        m_triangle_indices.push_back((i-2)*anzahl);
        m_triangle_indices.push_back(i*anzahl-1);
        u = m_vertices.at((i-2)*anzahl) - m_vertices.at((i-1)*anzahl);
        v = m_vertices.at(i*anzahl-1) - m_vertices.at((i-1)*anzahl);
        n = glm::cross(u,v);
        n = glm::normalize(n);
        m_face_normals.push_back(n);
        schwerpunkt = (m_vertices.at((i-1)*anzahl) + m_vertices.at((i-2)*anzahl) + m_vertices.at(i*anzahl-1)) /  (float)3;
        m_face_focus.push_back(schwerpunkt);
    }

    calculateVertexNormals();
}

void RotationObject::calculateVertexNormals() {
    //suche alle Punkte in der Triangle_Indices Liste um Nachbarschaft festzustellen.
    for(int i = 0; i < m_vertices.size(); i++) {
        glm::vec3 vertexnormal = glm::vec3(0.0,0.0,0.0);
        for(int j = 0; j < m_triangle_indices.size(); j++) {
            if(m_triangle_indices.at(j) == i) {
                vertexnormal += m_face_normals.at(j/3);
            }
        }
        vertexnormal = glm::normalize(vertexnormal);
        m_vertex_normals.push_back(vertexnormal);
    }
}

void RotationObject::closeRotationObject() {

    glm::vec3 u = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 v = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 n = glm::vec3(0.0, 0.0, 0.0);

    //Wenn Polyline nicht auf Achse liegt, lege neuen Punkt auf Achse und mache neue Dreiecke
    //Oben:
   if(list.at(list.size()-1).x != 0 || list.at(list.size()-1).z != 0) {
       glm::vec3 l = glm::vec3(0.0,list.at(list.size()-1).y, 0.0);
        m_vertices.push_back(l);
        for(int i = 0; i < anzahl-1; i++) {
            m_triangle_indices.push_back(m_vertices.size()-1);
            m_triangle_indices.push_back(anzahl*(list.size()-1)+1 + i);
            m_triangle_indices.push_back(anzahl*(list.size()-1)+ i);
        }
        m_triangle_indices.push_back(m_vertices.size()-1);
        m_triangle_indices.push_back(anzahl*(list.size()-1));
        m_triangle_indices.push_back(anzahl*list.size()-1);
    }

    //Unten:
    if(list.at(0).x != 0 || list.at(0).z != 0) {
        glm::vec3 m = glm::vec3(0.0, list.at(0).y, 0.0);
        //m_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
        //m_vertices.at(m_vertices.size()-1).y = list.at(0).y;
        m_vertices.push_back(m);
        for(int i = 0; i <anzahl-1; i++) {
            m_triangle_indices.push_back(m_vertices.size()-1);
            m_triangle_indices.push_back(i+1);
            u = m_vertices.at(m_triangle_indices.back());
            m_triangle_indices.push_back(i);
        }
        m_triangle_indices.push_back(m_vertices.size()-1);
        m_triangle_indices.push_back(0);
        m_triangle_indices.push_back(anzahl-1);
    }

    //Wenn Punkt auf y-Achse, dann einen topologischen Punkt draus machen
}


