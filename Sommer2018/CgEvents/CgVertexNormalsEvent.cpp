#include "CgVertexNormalsEvent.h"
#include "CgBase/CgEnums.h"

CgVertexNormalsEvent::CgVertexNormalsEvent(bool checked): m_type(Cg::CgVertexNormalsEvent)
{
    draw = checked;
}

CgVertexNormalsEvent::~CgVertexNormalsEvent() {

}

Cg::EventType CgVertexNormalsEvent::getType() {
    return m_type;
}

CgBaseEvent* CgVertexNormalsEvent::clone() {
    return new CgVertexNormalsEvent(draw);
}

bool CgVertexNormalsEvent::getChecked() {
    return draw;
}
