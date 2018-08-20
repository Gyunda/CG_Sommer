#include "ObjectMesh.h"
#include "CgUtils/ObjLoader.h"

unsigned int ObjectMesh::total_ids = 0;

ObjectMesh::ObjectMesh() : m_id(total_ids++), m_type(Cg::TriangleMesh)
{

}
void ObjectMesh::print_ids() {
    printf("aktuelle ID: %d\n", m_id);
    printf("Gesamtzahl IDs: %d\n", total_ids);
}



void ObjectMesh::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void ObjectMesh::init( std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
}




const std::vector<glm::vec3>& ObjectMesh::getVertices() const
{

return m_vertices;
}

const std::vector<glm::vec3>& ObjectMesh::getVertexNormals() const
{
return m_vertex_normals;
}

const std::vector<glm::vec3>& ObjectMesh::getVertexColors() const
{
return m_vertex_colors;
}

const std::vector<glm::vec2>& ObjectMesh:: getVertexTexCoords() const
{
return m_tex_coords;
}

const std::vector<unsigned int>& ObjectMesh::getTriangleIndices() const
{
return m_triangle_indices;
}

const std::vector<glm::vec3>& ObjectMesh::getFaceNormals() const
{
return m_face_normals;
}

const std::vector<glm::vec3>& ObjectMesh::getFaceColors() const
{
return m_face_colors;
}

const std::vector<glm::vec3>& ObjectMesh::getFaceFocus() const {
    return m_face_focus;
}


