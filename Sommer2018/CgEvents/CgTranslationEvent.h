#ifndef CGTRANSLATIONEVENT_H
#define CGTRANSLATIONEVENT_H


#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>

class CgTranslationEvent: public CgBaseEvent
{
private:
    glm::vec3 m_vektor;
    Cg::EventType m_type;
public:
    CgTranslationEvent(float x, float y, float z);

    ~CgTranslationEvent();
    Cg::EventType getType();
    CgBaseEvent* clone();
    glm::vec3 getVektorTranslation();

    friend std::ostream& operator <<(std::ostream& os, const CgTranslationEvent& e);
};

#endif // CGTRANSLATIONEVENT_H
