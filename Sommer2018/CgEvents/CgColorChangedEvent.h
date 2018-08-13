#ifndef CGCOLORCHANGEDEVENT_H
#define CGCOLORCHANGEDEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>


class CgColorChangedEvent: public CgBaseEvent
{

public:
    CgColorChangedEvent(float red, float green, float blue);


    ~CgColorChangedEvent();

    Cg::EventType getType();
    CgBaseEvent* clone();
    glm::vec3 getColor();

    friend std::ostream& operator <<(std::ostream& os, const CgColorChangedEvent& e);

private:
    Cg::EventType m_type;
    glm::vec3 m_color;

};

#endif // CGCOLORCHANGEDEVENT_H
