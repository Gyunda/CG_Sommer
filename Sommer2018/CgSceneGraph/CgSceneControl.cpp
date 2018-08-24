#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgEvents/CgDrawEvent.h"
#include "../CgEvents/CgColorChangedEvent.h"
#include "CgEvents/CgSmoothLineEvent.h"
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



CgSceneControl::CgSceneControl()
{
    creator = new ObjectMeshCreator();
    idGiver = CGIdGiver::getInstance();
    //objects.push_back(creator->createCube());
    //objects.push_back(creator->createCylinder());
    //simpleObject = creator->createCube();
    //for(int i = 0; i < simpleObject->getFaceFocus().size(); i++) {
     //   m_facenormals.push_back(new CgPolyline(simpleObject->getFaceFocus().at(i), simpleObject->getFaceFocus().at(i) + simpleObject->getFaceNormals().at(i), glm::vec3(1.0, 1.0, 1.0), 0.5));
    //}
    m_triangle = NULL;


    rotationObject = new RotationObject();
    line = rotationObject->getLine();

     m_current_transformation=glm::mat4(1.);
      m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
     m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
   m_trackball_rotation=glm::mat4(1.);

   // line = new CgPolyline(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2, 0.5, 0.4), glm::vec3(0.0, 1.0, 1.0), 0.5);
    //polylines.push_back(line);
}


CgSceneControl::~CgSceneControl()
{
    if(m_triangle!=NULL) {
        delete m_triangle;
    }
    //for(int i = 0; i < objects.size(); i++) {
     //       delete objects.at(i);
       // }
    //for(int i = 0; i < polylines.size(); i++) {
      //  delete polylines.at(i);
   // if(simpleObject != NULL) {
     //   delete simpleObject;
    //}
    if(line !=NULL) {
        delete line;
    }
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);
   // m_renderer->init(simpleObject);
    //for(int i = 0; i<m_facenormals.size(); i++) {
      //  m_renderer->init(m_facenormals.at(i));
    //}

    //m_renderer->init(objects.at(0));
    //m_renderer->init(objects.at(1));
    m_renderer->init(line);
    m_renderer->setUniformValue("mycolor",glm::vec4(1.0,1.0,1.0,1.0)); //eingefügt damit color change richtig läuft (so ein bullshit)

}


void CgSceneControl::renderObjects()
{

    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....

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

    if(m_triangle!=NULL)
    m_renderer->render(m_triangle);
    //for(int i = 0; i < objects.size(); i++) {
      //  if(objects.at(i) != NULL) {
        //    m_renderer->render(objects.at(i));
    //if(simpleObject != NULL) {
      //  m_renderer->render(simpleObject);
        //}
    //for(int i = 0; i<m_facenormals.size(); i++) {
      //  m_renderer->render(m_facenormals.at(i));
    //}
    m_renderer->render(line);
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



        objects.at(0)->init(pos,norm,indx);
        m_renderer->init(objects.at(0));
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

    if(e->getType() & Cg::CgDrawEvent) {
        CgDrawEvent* ev = (CgDrawEvent*)e;

        if(ev->getKoerper() == 1) {
            simpleObject = creator->createCube();
            std::cout << "zeichne würfel" << std::endl;
        } else if(ev->getKoerper() == 2) {
            simpleObject = creator->createCylinder();
            std::cout << "zeichne zylinder" << std::endl;
        } else if(ev->getKoerper() == 3) {
            for(int i = 0; i < simpleObject->getFaceFocus().size(); i++) {
                m_facenormals.push_back(new CgPolyline(simpleObject->getFaceFocus().at(i), simpleObject->getFaceFocus().at(i) + simpleObject->getFaceNormals().at(i), glm::vec3(1.0, 1.0, 1.0), 0.5));
            }
            for(int i = 0; i < m_facenormals.size(); i++) {
                m_renderer->init(m_facenormals.at(i));
                m_renderer->render(m_facenormals.at(i));
            }
            std::cout << "zeichne face normale" << std::endl;
        } else if(ev->getKoerper() == 4) {
            std::cout << "zeichne vertex normale" << std::endl;
        }

        m_renderer->init(simpleObject);
        m_renderer->render(simpleObject);
        m_renderer->setUniformValue("mycolor",glm::vec4(1.0,1.0,1.0,1.0));
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgSmoothLineEvent) {
        CgSmoothLineEvent* ev = (CgSmoothLineEvent*)e;
        rotationObject->smoothLine();
        line = rotationObject->getLine();
        setRenderer(m_renderer);
        m_renderer->init(line);
        m_renderer->render(line);
        m_renderer->redraw();
        //std::cout << "shizzle" << std::endl;
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
