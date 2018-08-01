#include "ObjectMesh.h"

unsigned int ObjectMesh::total_ids = 0;

ObjectMesh::ObjectMesh() : m_id(total_ids++)
{

}
void ObjectMesh::print_ids() {
    printf("aktuelle ID: %d\n", m_id);
    printf("Gesamtzahl IDs: %d\n", total_ids);
}

