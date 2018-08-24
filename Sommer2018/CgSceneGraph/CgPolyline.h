#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include "CgBase/CgBasePolyline.h"


class CgPolyline:public CgBasePolyline
{
public:
    CgPolyline(glm::vec3 start, glm::vec3 end, glm::vec3 color, unsigned int lineWidth);
    CgPolyline(std::vector<glm::vec3> verticies, unsigned int lineWidth);
    ~CgPolyline();

    const std::vector<glm::vec3>& getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;
    void setColor(glm::vec3 color);


    Cg::ObjectType getType() const;
    unsigned int getID() const;

private:

    std::vector<glm::vec3> m_verticies;
    glm::vec3 m_color;
    unsigned int m_lineWidth;


    const Cg::ObjectType m_type;
    const unsigned int m_id;
    static unsigned int total_ids;
};

inline Cg::ObjectType  CgPolyline::getType() const {return m_type;}
inline unsigned int CgPolyline::getID() const {return m_id;}

#endif // CGPOLYLINE_H
