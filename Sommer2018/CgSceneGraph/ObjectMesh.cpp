#include "ObjectMesh.h"
#include "CgUtils/ObjLoader.h"



ObjectMesh::ObjectMesh(int id) : m_id(id), m_type(Cg::TriangleMesh)
{
}
void ObjectMesh::print_ids() {
    printf("aktuelle ID: %d\n", m_id);
}

ObjectMesh::~ObjectMesh() {

}


void ObjectMesh::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    //m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
    berechneVertexNormals();
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


void ObjectMesh::berechneFaceNormals(){
    for(unsigned int i=0; i < m_triangle_indices.size()/3; i++) {
        glm::vec3 a = m_vertices.at(m_triangle_indices.at(i*3+1)) - m_vertices.at(m_triangle_indices.at(i*3+2));
        glm::vec3 b =m_vertices.at(m_triangle_indices.at(i*3+1)) - m_vertices.at(m_triangle_indices.at(i*3));
        m_face_normals.push_back(glm::cross(a,b));
    }
}

void ObjectMesh::berechneVertexNormals(){
    unsigned int eckNr=0;

    berechneFaceNormals();


    //füllen des VertexArray auf entsprechende Laenge
    for(unsigned int i=0; i<m_vertices.size(); i++){
        m_vertex_normals.push_back(glm::vec3(0.0, 0.0, 0.0));
    }

    //Addition der Normalen an entsprechende Stelle im VertexArray
    for(unsigned int i=0; i<m_triangle_indices.size()/3; i++){
        m_face_normals.at(i)= glm::normalize(m_face_normals.at(i));

        eckNr = m_triangle_indices.at(i*3);

        m_vertex_normals.at(eckNr)+= m_face_normals.at(i);

        eckNr = m_triangle_indices.at(i*3+1);
        m_vertex_normals.at(eckNr)+= m_face_normals.at(i);

        eckNr = m_triangle_indices.at(i*3+2);
        m_vertex_normals.at(eckNr)+= m_face_normals.at(i);

    }


    //Normalisieren der Vertex-Normalen
    for(unsigned int i=0; i<m_vertex_normals.size(); i++){
        m_vertex_normals.at(i)= glm::normalize(m_vertex_normals.at(i));
    }
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


