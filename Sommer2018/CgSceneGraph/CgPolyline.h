#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include "CgBase/CgBasePolyline.h"


class CgPolyline:public CgBasePolyline
{
public:
    CgPolyline(unsigned int id, glm::vec3 start, glm::vec3 end, glm::vec3 color, unsigned int lineWidth);
    CgPolyline(unsigned int id,std::vector<glm::vec3> verticies, unsigned int lineWidth);
    ~CgPolyline();

    const std::vector<glm::vec3>& getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;
    void setColor(glm::vec3 color);
    void doppeln();
        void mitteln();
        void vierPunkt();
        void reset();


    Cg::ObjectType getType() const;
    unsigned int getID() const;

private:

    std::vector<glm::vec3> m_verticies;
    std::vector<glm::vec3> m_kopie;
    glm::vec3 m_color;
    unsigned int m_lineWidth;


    const Cg::ObjectType m_type;
    const unsigned int m_id;
    //static unsigned int total_ids;
};

inline Cg::ObjectType  CgPolyline::getType() const {return m_type;}
inline unsigned int CgPolyline::getID() const {return m_id;}

#endif // CGPOLYLINE_H
