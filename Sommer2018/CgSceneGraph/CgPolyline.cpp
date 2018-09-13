#include "CgPolyline.h"

#include "CgBase/CgEnums.h"

//unsigned int CgPolyline::total_ids = 1000;

CgPolyline::CgPolyline(unsigned int id, glm::vec3 start, glm::vec3 end, glm::vec3 color, unsigned int lineWidth):
    m_type(Cg::Polyline),
    m_id(id)
{
    m_verticies.push_back(start);
    m_verticies.push_back(end);
    m_color = color;
    m_lineWidth = lineWidth;
}

CgPolyline::CgPolyline(unsigned int id, std::vector<glm::vec3> verticies, unsigned int lineWidth): //unendliche Linie Konstruktor
    m_type(Cg::Polyline),
    m_id(id)
{

    m_verticies = verticies;
    m_lineWidth = lineWidth;
    m_color = glm::vec3(0,0,1);
}

CgPolyline::~CgPolyline(){
    m_verticies.clear();
}

const std::vector<glm::vec3>& CgPolyline::getVertices() const{
    return m_verticies;
}

glm::vec3 CgPolyline::getColor() const{
    return m_color;
}

unsigned int CgPolyline::getLineWidth() const{
    return m_lineWidth;
}

void CgPolyline::setColor(glm::vec3 color){
    m_color = color;
}

void CgPolyline::doppeln(){
    int length = m_verticies.size();
    int i;

    //Dummy Elemente anhängen um Liste 2n-1 zu verdoppeln
    for(i = 0; i < length -1; i++){
        m_verticies.push_back(glm::vec3(0,0,0));
    }


    //Liste korrekt neu orientieren A/?/B/?/C/?/D
    for(i = length-1; i >= 0; i--){
        m_verticies[i*2] = m_verticies[i];
        m_verticies[i*2+1] = glm::vec3(0,0,0); //? gleich null gesetzt
    }

}

void CgPolyline::mitteln(){
    float w = (1.0/16);
    int length = m_verticies.size();
    int i = 3;
    float mitteX=0,mitteY=0;

    //gespigelter Punkt Anfang
    float gespiegelterPunktX = m_verticies[0].x + (m_verticies[0].x - m_verticies[2].x);
    float gespiegelterPunktY = m_verticies[0].y + (m_verticies[0].y - m_verticies[2].y);

    //Anfang Rand
    float anfangX = ((-w)*gespiegelterPunktX) + ((0.5f + w)*m_verticies[0].x) + ((0.5f + w)*m_verticies[2].x) -(w*m_verticies[4].x);
    float anfangY = ((-w)*gespiegelterPunktY) + ((0.5f + w)*m_verticies[0].y) + ((0.5f + w)*m_verticies[2].y) -(w*m_verticies[4].y);
    m_verticies[1] = glm::vec3(anfangX, anfangY,0);

    //mittel Punkte
    while(i < length-3){
        mitteX = ((-w)*m_verticies[i-3].x) + ((0.5f + w)*m_verticies[i-1].x) + ((0.5f + w)*m_verticies[i+1].x) - (w*m_verticies[i+3].x);
        mitteY = ((-w)*m_verticies[i-3].y) + ((0.5f + w)*m_verticies[i-1].y) + ((0.5f + w)*m_verticies[i+1].y) - (w*m_verticies[i+3].y);
        m_verticies[i] = glm::vec3(mitteX, mitteY,0);
        i+=2;
    }

    //gespigelter Punkt Ende
    float gespiegelterPunktX2 = m_verticies[length-1].x + (m_verticies[length-1].x - m_verticies[length-3].x);
    float gespiegelterPunktY2 = m_verticies[length-1].y + (m_verticies[length-1].y - m_verticies[length-3].y);

    //Ende Rand
    float endeX = ((-w)*m_verticies[length-5].x) + ((0.5f + w)*m_verticies[length-3].x) + ((0.5f + w)*m_verticies[length-1].x) -(w*gespiegelterPunktX2);
    float endeY = ((-w)*m_verticies[length-5].y) + ((0.5f + w)*m_verticies[length-3].y) + ((0.5f + w)*m_verticies[length-1].y) -(w*gespiegelterPunktY2);
    m_verticies[length-2] = glm::vec3(endeX, endeY,0);

}

void CgPolyline::vierPunkt(){
    //Kopie erstellen
    if(m_kopie.empty()){
        m_kopie = m_verticies;
    }
    //vier Punkt Schema
    doppeln();
    mitteln();
}

void CgPolyline::reset(){
    if(!m_kopie.empty()){
        m_verticies.clear();
        m_verticies = m_kopie;
    }
}
