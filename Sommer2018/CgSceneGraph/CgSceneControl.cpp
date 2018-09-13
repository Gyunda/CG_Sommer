#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgColorChangedEvent.h"
#include "CgEvents/CgRotateEvent.h"
#include "CgEvents/CgResetEvent.h"
#include "CgEvents/CgUnterteilungsEvent.h"
#include "CgEvents/CgVertexNormalsEvent.h"
#include "CgEvents/CgTranslationEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include "ObjectMesh.h"
#include "ObjectMeshCreator.h"
#include "CGIdGiver.h"
#include "CgCube.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgUtils/ObjLoader.h"
#include <string>
#include "CgPolyline.h"
#include "RotationObject.h"
#include "CgSelectObject.h"
#include "CgScenegraph.h"
#include "CgScenegraphEntity.h"
#include "CgUtils/MatrixUtils.h"


CgSceneControl* CgSceneControl::instance = 0;

CgSceneControl* CgSceneControl::getInstance() {
    if(instance == 0) {
        instance = new CgSceneControl();
    }
    return instance;
}

unsigned int CgSceneControl::getId() {
    id++;
    return id;
}


CgSceneControl::CgSceneControl()
{
    id = 0;
    creator = new ObjectMeshCreator();
    cube = NULL;
    cylinder = NULL;
    line = NULL;
    m_object = NULL;
    //m_vierPunkt = NULL;
std::vector<glm::vec3> list;
   /* glm::vec3 a = glm::vec3(0.5,0.0, 0.0);
    glm::vec3 b = glm::vec3(2.0, 2.0, 0.0);
    glm::vec3 c = glm::vec3(3.0, 4.0, 0.0);
    glm::vec3 d = glm::vec3(1.0, 6.0, 0.0);

    list.push_back(a);
    list.push_back(b);
    list.push_back(c);
    list.push_back(d);*/
    list.push_back(glm::vec3(0.0,0.37,0.0));
     list.push_back(glm::vec3(0.1,0.35,0.0));
     list.push_back(glm::vec3(0.13,0.30,0.0));
     list.push_back(glm::vec3(0.1,0.25,0.0));
     list.push_back(glm::vec3(0.06,0.22,0.0));
     list.push_back(glm::vec3(0.08,0.20,0.0));
     list.push_back(glm::vec3(0.03,0.08,0.0));

     //Körper
     list.push_back(glm::vec3(0.08,-0.03,0.0));
     list.push_back(glm::vec3(0.13,-0.08,0.0));
     list.push_back(glm::vec3(0.13,-0.17,0.0));
     list.push_back(glm::vec3(0.1,-0.20,0.0));
     list.push_back(glm::vec3(0.0,-0.20,0.0));
    m_vierPunkt = new CgPolyline(getId(),list, 0.1);

    //Szenegraphen shit
  /*   m_matrixUtils = new MatrixUtils();
         CgAppearance* app= new CgAppearance(glm::vec4(1.0, 0.0, 0.0, 1.0));

         graph= new CgScenegraph();
         // index:0
         graph->createMeshObjectCylinder(getId());
         // index:1
         graph->createMeshObjectCube(getId());
         //index:2
         graph->createMeshObjectCube(getId());
         //index:3
         graph->createMeshObjectCube(getId());
         //index:4
         graph->createMeshObjectCube(getId());

         entity = new CgScenegraphEntity(graph->getObjList().at(0), glm::mat4(0.5), app);
         entity2 = new CgScenegraphEntity(graph->getObjList().at(1), glm::mat4(0.5), app);
         entity3 = new CgScenegraphEntity(graph->getObjList().at(2),glm::mat4(2),app);
         entity4 = new CgScenegraphEntity(graph->getObjList().at(3),glm::mat4(0.5),app);
         entity5 = new CgScenegraphEntity(graph->getObjList().at(4),glm::mat4(0.5),app);



         graph->setRootNode(entity);
         entity->addChild(entity2);
         entity2->addChild(entity3);
         entity3->addChild(entity4);
         entity4->addChild(entity5);

         std::cout << "ObjList: " << graph->getObjList().size() << std::endl;

         m_select = new CgSelectObject(graph->getRootNode());
*/

    rotationObject = NULL;

     m_current_transformation=glm::mat4(1.);
      m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
     m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
   m_trackball_rotation=glm::mat4(1.);

}

CgSceneControl::CgSceneControl(const CgSceneControl &) {

}


CgSceneControl::~CgSceneControl()
{
    if(line !=NULL) {
        delete line;
    }
    if(cube !=NULL) {
        delete cube;
    }
    if(cylinder != NULL) {
        delete cylinder;
    }
    if(m_vierPunkt != NULL) {
        delete m_vierPunkt;
    }
    if(rotationObject != NULL) {
        delete rotationObject;
    }
    if(m_facenormals.size() > 0) {
        for(int i = 0; i < m_facenormals.size(); i++) {
            m_facenormals.pop_back();
        }
    }
    if(m_vertexnormals.size() > 0) {
        for(int i = 0; i < m_vertexnormals.size(); i++) {
            m_vertexnormals.pop_back();
        }
    }
    if(objects.size() > 0) {
        objects.clear();
    }
    if(m_object != NULL) {
        delete m_object;
    }
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);
    if(cube != NULL) {
        m_renderer->init(cube);
    }
    if(cylinder != NULL) {
        m_renderer->init(cylinder);
    }
    if(line != NULL) {
        m_renderer->init(line);
    }
    if(m_vierPunkt != NULL) {
        m_renderer->init(m_vierPunkt);
    }
    if(rotationObject != NULL) {
        m_renderer->init(rotationObject);
    }
    if(m_facenormals.size() > 0) {
        for(int i = 0; i < m_facenormals.size(); i++) {
            m_renderer->init(m_facenormals.at(i));
        }
    }
    if(m_vertexnormals.size() > 0) {
        for(int i = 0; i < m_vertexnormals.size(); i++) {
            m_renderer->init(m_vertexnormals.at(i));
        }
    }
    if(objects.size() > 0) {
        for(int i = 0; i < objects.size(); i++) {
            m_renderer->init(objects.at(i));
        }
    }
    if(m_object != NULL) {
        m_renderer->init(m_object);
    }

   // graph->init(m_renderer);

    m_renderer->setUniformValue("mycolor",glm::vec4(1.0,1.0,1.0,1.0)); //eingefügt damit color change richtig läuft

}


void CgSceneControl::renderObjects()
{

    //m_renderer->setUniformValue("mycolor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matDiffuseColor",glm::vec4(0.35,0.31,0.09,1.0));
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matAmbientColor",glm::vec4(0.25,0.22,0.06,1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matSpecularColor",glm::vec4(0.8,0.72,0.21,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));


    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);

    if(cube != NULL) {
        m_renderer->render(cube);
    }
    if(cylinder != NULL) {
        m_renderer->render(cylinder);
    }
    if(line != NULL) {
        m_renderer->render(line);
    }
    if(m_vierPunkt != NULL) {
        m_renderer->render(m_vierPunkt);
    }
    if(rotationObject != NULL) {
        m_renderer->render(rotationObject);
    }
    if(m_facenormals.size() > 0) {
        for(int i = 0; i < m_facenormals.size(); i++) {
            m_renderer->render(m_facenormals.at(i));
        }
    }
    if(m_vertexnormals.size() > 0) {
        for(int i = 0; i < m_vertexnormals.size(); i++) {
            m_renderer->render(m_vertexnormals.at(i));
        }
    }
    if(objects.size() > 0) {
        for(int i = 0; i < objects.size(); i++) {
            m_renderer->render(objects.at(i));
        }
    }
    if(m_object != NULL) {
        m_renderer->render(m_object);
    }

   // graph->render(m_renderer);

}





void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h


    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        //std::cout << *ev << std::endl;

         // hier kommt jetzt die Abarbeitung des Events hin...
    }

    //Rotieren im Fenster
    if(e->getType() & Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;


        m_trackball_rotation=ev->getRotationMatrix();
        m_renderer->redraw();

    }


    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        if(ev->text()=="+")
        {
            glm::mat4 scalemat;
            scalemat= glm::scale(scalemat,glm::vec3(1.2,1.2,1.2));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            glm::mat4 scalemat;
            scalemat= glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()== "v") {
            std::cout << "habe v gedrückt" << std::endl;
            if(cube != NULL) {

            }
        }
        //Element im Szenegraphen
                if(ev->text()=="q"){
                    //aufruf nächstes Element im Szenegraphen
                    m_select->nextNode();
                }
                //rotation um x Achse
                if(ev->text()=="x"){
                    m_select->getCurrentNode()->setCurrentTransformation(m_select->getCurrentNode()->getCurrentTransformation() * m_matrixUtils->getXrotationMatrix());

                }
                //rotation um y Achse
                if(ev->text()=="y"){
                     m_select->getCurrentNode()->setCurrentTransformation(m_select->getCurrentNode()->getCurrentTransformation() * m_matrixUtils->getYrotationMatrix());

                }
                //rotation um z Achse
                if(ev->text()=="z"){
                     m_select->getCurrentNode()->setCurrentTransformation(m_select->getCurrentNode()->getCurrentTransformation() * m_matrixUtils->getZrotationMatrix());

                }
                m_renderer->redraw();
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
         CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
         std::cout << *ev <<std::endl;
         m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() & Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;



        ObjLoader* loader= new ObjLoader();
        loader->load(ev->FileName());

        std::cout << ev->FileName() << std::endl;

        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);

         std::vector<glm::vec3> norm;
         loader->getNormalData(norm);

          std::vector<unsigned int> indx;
          loader->getFaceIndexData(indx);


        m_object = new ObjectMesh(getId());




        m_object->init(pos,norm,indx);
        setRenderer(m_renderer);
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgColorChangedEvent)
    {
        CgColorChangedEvent* ev = (CgColorChangedEvent*)e;
        std::cout << *ev <<std::endl;
       // objects.at(0);
        m_renderer->setUniformValue("mycolor", glm::vec4(ev->getColor().x, ev->getColor().y, ev->getColor().z, 1.0));
        m_renderer->redraw();
    }




    if(e->getType() & Cg::CgRotateEvent) {
        CgRotateEvent* ev = (CgRotateEvent*)e;
        if(rotationObject != NULL) {
            std::cout << "Ist bereits rotiert." << std::endl;
            delete rotationObject;
            rotationObject = NULL;
            m_facenormals.clear();
            m_vertexnormals.clear();

        } else if(m_vierPunkt == NULL) {
            std::cout << "Keine Linie zum Rotieren" << std::endl;
        } else {
            rotationObject = new RotationObject(getId(), m_vierPunkt, ev->getAufloesung());
            std::cout << "Rotiere." << std::endl;
        }
        setRenderer(m_renderer);
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgUnterteilungsEvent)
        {
            CgUnterteilungsEvent* ev = (CgUnterteilungsEvent*)e;
            if(rotationObject != NULL) {
                m_vierPunkt->vierPunkt();
                delete rotationObject;
                rotationObject = new RotationObject(getId(), m_vierPunkt, ev->getAufloesung());

                m_vertexnormals.clear();
                m_facenormals.clear();
                if(m_vertexnormals.size() > 0) {
                    for(int i = 0; i < rotationObject->getVertexNormals().size(); i++) {

                        glm::vec3 start = rotationObject->getVertices().at(i);
                        glm::vec3 ende = rotationObject->getVertices().at(i) + rotationObject->getVertexNormals().at(i);
                        m_vertexnormals.push_back(new CgPolyline(getId(), start, ende, glm::vec3(1.0,1.0,1.0), 0.1));
                    }
                }
            } else {
                m_vierPunkt->vierPunkt();
            }
            setRenderer(m_renderer);
            m_renderer->redraw();
            std::cout << *ev <<std::endl;
        }

     if(e->getType() & Cg::CgResetEvent){
         CgResetEvent* ev = (CgResetEvent*)e;
         m_vierPunkt->reset();
         setRenderer(m_renderer);
         m_renderer->redraw();
         std::cout << *ev <<std::endl;
     }

     if(e->getType() & Cg::CgVertexNormalsEvent) {
         CgVertexNormalsEvent* ev = (CgVertexNormalsEvent*)e;
         if(ev->getChecked() == true) {
            /* for(int i = 0; i < rotationObject->getFaceNormals().size(); i++) {
                 glm::vec3 start = rotationObject->getFaceFocus().at(i);
                 glm::vec3 ende = rotationObject->getFaceFocus().at(i) + rotationObject->getFaceNormals().at(i);
                 m_facenormals.push_back(new CgPolyline(getId(), start, ende, glm::vec3(1.0,1.0,1.0), 0.1));
             }*/
            if(rotationObject != NULL) {
                 for(int i = 0; i < rotationObject->getVertexNormals().size(); i++) {

                     glm::vec3 start = rotationObject->getVertices().at(i);
                     glm::vec3 ende = rotationObject->getVertices().at(i) + rotationObject->getVertexNormals().at(i);
                     m_vertexnormals.push_back(new CgPolyline(getId(), start, ende, glm::vec3(1.0,1.0,1.0), 0.1));
                 }
            } else if(cube != NULL) {
                for(int i = 0; i < cube->getVertexNormals().size(); i++) {

                    glm::vec3 start = cube->getVertices().at(i);
                    glm::vec3 ende = cube->getVertices().at(i) + cube->getVertexNormals().at(i);
                    m_vertexnormals.push_back(new CgPolyline(getId(), start, ende, glm::vec3(1.0,1.0,1.0), 0.1));
                }
            } else if(cylinder != NULL) {
                for(int i = 0; i < cylinder->getVertexNormals().size(); i++) {

                    glm::vec3 start = cylinder->getVertices().at(i);
                    glm::vec3 ende = cylinder->getVertices().at(i) + cylinder->getVertexNormals().at(i);
                    m_vertexnormals.push_back(new CgPolyline(getId(), start, ende, glm::vec3(1.0,1.0,1.0), 0.1));
                }
            } else {
                std::cout << "keine Vertexnormalen gezeichnet." << std::endl;
            }
         } else {
             m_vertexnormals.clear();
         }
         setRenderer(m_renderer);
         m_renderer->redraw();
     }

     if(e->getType() & Cg::CgTranslationEvent)
         {
             CgTranslationEvent* ev = (CgTranslationEvent*)e;
             m_select->getCurrentNode()->setCurrentTransformation(m_select->getCurrentNode()->getCurrentTransformation() * m_matrixUtils->translationMatrix(ev->getVektorTranslation()));
             m_renderer->redraw();
             std::cout << *ev <<std::endl;
         }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
