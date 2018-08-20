#include "CgCylinder.h"
#include "CgBase/CgEnums.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <glm/gtx/rotate_vector.hpp>

#define r 0.25;

CgCylinder::CgCylinder()
{

}

CgCylinder::CgCylinder(int anzahl_kreispunkte, int anzahl_hoehe, double hoehe)
{
 this->anzahl_kreispunkte= anzahl_kreispunkte;
 this->hoehe= hoehe;
    this->anzahl_hoehe= anzahl_hoehe;
 radius= r;


    punkte();
    kreisflaechen();
    mantelflaeche();
    berechneVertexNormalen();

}


CgCylinder::~CgCylinder()
{
m_vertices.clear();
m_vertex_normals.clear();
m_vertex_colors.clear();
m_tex_coords.clear();
m_triangle_indices.clear();
m_face_normals.clear();
m_face_colors.clear();
}




void CgCylinder::punkte() {
    float winkel = 2*M_PI/anzahl_kreispunkte;
    float phi = 0;
    float x, y, z;
    glm::vec3 mittelpunkt = glm::vec3(0,0,0);
    glm::vec3 kreispunkt;
    //anzahl_hoehe+1 für Anzahl Ebenen in denen die Punkte liegen
    for(int j =0; j<anzahl_hoehe+1; j++) {
        m_vertices.push_back(mittelpunkt);
        z = mittelpunkt.z;
        //Zeichne Punkte in einem Kreis, beginnend mit Mittelpunkt
        for(int i=0; i<anzahl_kreispunkte; i++) {
            x = radius* glm::cos(phi);
            y = radius* glm::sin(phi);
            kreispunkt = glm::vec3(x,y,z);
            m_vertices.push_back(kreispunkt);


            phi+=winkel;
        }
        mittelpunkt.z += hoehe/anzahl_hoehe;

    }
    //printf(" Anzahl Elemente in Vektor: %d\n", m_vertices.size());
    //for(int i = 0; i < m_vertices.size(); i++) {
    //    printf("punkt %d: %.3f %.3f %.3f\n", i, m_vertices.at(i).x, m_vertices.at(i).y, m_vertices.at(i).z);
    //}
}

//zeichne die kreisflächen oben und unten
void CgCylinder::kreisflaechen() {
       for(int j=1; j < anzahl_kreispunkte; j++) {
           m_triangle_indices.push_back(0);
           m_triangle_indices.push_back(0+j);
           m_triangle_indices.push_back(0+j+1);
    }
       m_triangle_indices.push_back(0);
       m_triangle_indices.push_back(anzahl_kreispunkte);
       m_triangle_indices.push_back(1);

        int m = (anzahl_kreispunkte+1)*anzahl_hoehe;

       for(int i = 1; i < anzahl_kreispunkte; i++) {
           m_triangle_indices.push_back(m);
           m_triangle_indices.push_back(m+i);
           m_triangle_indices.push_back(m+i+1);
       }
       m_triangle_indices.push_back(m);
       m_triangle_indices.push_back(m+anzahl_kreispunkte);
       m_triangle_indices.push_back(m+1);
}


//zeichnet die dreiecke in der mantelfläche
void CgCylinder::mantelflaeche() {

    int anzahl_punkte = m_vertices.size();
    int i;
    for(int j=0; j< anzahl_punkte-(anzahl_kreispunkte+1);j+=(anzahl_kreispunkte+1)) {

        for(i=1; i<anzahl_kreispunkte; i++) {
    //rechts untere dreiecke
            m_triangle_indices.push_back(i+j);
            m_triangle_indices.push_back(i+j+1);
            m_triangle_indices.push_back(i+j+1+(anzahl_kreispunkte+1));
            //links obere dreiecke
            m_triangle_indices.push_back(i+j);
            m_triangle_indices.push_back(i+j+1+(anzahl_kreispunkte+1));
            m_triangle_indices.push_back(i+j+(anzahl_kreispunkte+1));
        }
        //rechts unten abschließende dreiecke
        m_triangle_indices.push_back(i+j);
        m_triangle_indices.push_back(j+1);
        m_triangle_indices.push_back(j+1 + (anzahl_kreispunkte+1));

        //links oben abschließende dreiecke
        m_triangle_indices.push_back(i+j);
        m_triangle_indices.push_back(i+j+2);
        m_triangle_indices.push_back(i+j+(anzahl_kreispunkte+1));

    }


}
//die facefocus-elemente stimmen in der position mit den facenormale-elementen überein
void CgCylinder::berechneFaceFocus() {
    //facefocus boden
    for(int i = 0; i < anzahl_kreispunkte - 1; i++) {
        glm::vec3 zwischen = m_vertices.at(m_triangle_indices.at(0)) + m_vertices.at(m_triangle_indices.at(i+1)) + m_vertices.at(m_triangle_indices.at(i+2));
        zwischen[0] = zwischen[0]/3;
        zwischen[1] = zwischen[1]/3;
        zwischen[2] = zwischen[2]/3;
        m_face_focus.push_back(zwischen);
    }

    //facefocus mantel

    //facefocus deckel

}


void CgCylinder::berechneFaceNormalen() {
    //facenormale boden
    for(int i = 1; i < anzahl_kreispunkte; i++) {
        glm::vec3 a = m_vertices.at(0) - m_vertices.at(i);
        glm::vec3 b = m_vertices.at(i+1) - m_vertices.at(i);
        glm::vec3 normale = glm::cross(a,b);
        m_face_normals.push_back(normale);
    }
    //facenormalen mantel
    for(int i = 0; i < anzahl_kreispunkte * anzahl_hoehe; i++) {

    }
    //facenormale deckel


}

void CgCylinder::berechneVertexNormalen() {
    //für kanten und bereits glatte flächennicht nützlich, also keine vertexnormalen am boden und deckel, nur für den mantel
    //da die vertexnormalen für eine vertikale reihe gleich sind werden sie nur pro reihe gespeichert.
    glm::vec3 vec_radius = m_vertices.at(1) - m_vertices.at(0);
    float winkel = 2*M_PI/anzahl_kreispunkte;
    m_vertex_normals.push_back(vec_radius);
    for(int i = 0; i < anzahl_kreispunkte; i++) {
        vec_radius = glm::rotateZ(vec_radius, winkel);
        m_vertex_normals.push_back(vec_radius);
    }
}




