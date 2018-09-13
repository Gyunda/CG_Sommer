

#include "CgQtGLRenderWidget.h"
#include "QLineEdit"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgColorChangedEvent.h"
#include "../CgEvents/CgRotateEvent.h"
#include "../CgEvents/CgResetEvent.h"
#include "../CgEvents/CgUnterteilungsEvent.h"
#include "../CgEvents/CgVertexNormalsEvent.h"
#include "../CgEvents/CgTranslationEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <iostream>
#include <QSignalMapper>
#include<stdio.h>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;


    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;


    QWidget *cubeColor = new QWidget;
    createOptionPanelCubeColor(cubeColor);

    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    QWidget *rotation = new QWidget;
    createOptionPanelRotation(rotation);

    QWidget *transformation = new QWidget;
    createOptionPanelTransformation(transformation);



    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(cubeColor, "&Farbe");
    m_tabs->addTab(rotation, "&Rotation");
    m_tabs->addTab(opt,"&My Tab1");
    m_tabs->addTab(otheropt,"&My Tab2");
    m_tabs->addTab(transformation, "&Transformation");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2018"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);



}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 255);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    connect(slider, SIGNAL( sliderMoved(int)) , this, SLOT(slotMySliderChanged()));
    return slider;
}

//Panels in der GUI


void CgQtGui::createOptionPanelCubeColor(QWidget* parent)
{
    QVBoxLayout *tab3_control = new QVBoxLayout();  //Layout erstellen

    QLabel *options_label = new QLabel("Slider");   //Name erstellen
    tab3_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignTop);

    mySlider1 = createSlider();   //slider
    mySlider2 = createSlider();
    mySlider3 = createSlider();
    tab3_control->addWidget(mySlider1);
    tab3_control->addWidget(mySlider2);
    tab3_control->addWidget(mySlider3);


    parent->setLayout(tab3_control);

}

void CgQtGui::createOptionPanelRotation(QWidget* parent)
{
    QVBoxLayout *tabRotation_control = new QVBoxLayout();

    QLabel *options_label = new QLabel("Rotationskörper und Glättung");
    tabRotation_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignTop);

    QPushButton* myButtonReset = new QPushButton("&Reset Curve");
    tabRotation_control->addWidget(myButtonReset);

    QPushButton* myButtonUnterteilung = new QPushButton("&Unterteilung");
    tabRotation_control->addWidget(myButtonUnterteilung);

    QPushButton* rotate = new QPushButton("Rotieren");
    connect(rotate, SIGNAL(clicked()), this, SLOT(slotRotateLine()));
    tabRotation_control->addWidget(rotate);

    aufloesung = new QLineEdit("8");
    tabRotation_control->addWidget(aufloesung);
    QLocale loc(QLocale::C);
    QIntValidator* validate = new QIntValidator(parent);
   // loc.setNumberOptions(QLocale::RejectGroupSeparator);
    validate->setRange(3, 100);
    //validate->setLocale(loc);
    aufloesung->setValidator(validate);
    QCheckBox* closedRotation = new QCheckBox("geschlossen");
    closedRotation->setCheckable(true);
    closedRotation->setChecked(false);
    tabRotation_control->addWidget(closedRotation);

    QCheckBox* renderVertexNormals = new QCheckBox("Vertexnormalen");
    renderVertexNormals->setCheckable(true);
    renderVertexNormals->setChecked(false);
    tabRotation_control->addWidget(renderVertexNormals);

    connect(myButtonUnterteilung, SIGNAL( clicked() ), this, SLOT(slotUnterteilung()) );

    connect(myButtonReset,SIGNAL(clicked()),this, SLOT(slotResetCurve()) );

    connect(renderVertexNormals, SIGNAL(toggled(bool)), this, SLOT(slotDrawVertexNormals(bool)));

    parent->setLayout(tabRotation_control);
}


void CgQtGui::createOptionPanelTransformation(QWidget* parent) {
    QVBoxLayout *tabTransformation_control = new QVBoxLayout();

        QLabel *options_label = new QLabel("Rotationskörper und Glättung");
        tabTransformation_control->addWidget(options_label);
        options_label->setAlignment(Qt::AlignTop);

        vektorX = new QLineEdit("0");
        vektorY = new QLineEdit("0");
        vektorZ = new QLineEdit("0");
        tabTransformation_control->addWidget(vektorX);
        tabTransformation_control->addWidget(vektorY);
        tabTransformation_control->addWidget(vektorZ);

        QLocale loc(QLocale::C);
        QDoubleValidator* validate = new QDoubleValidator(parent);
        loc.setNumberOptions(QLocale::RejectGroupSeparator);
        validate->setDecimals(3);
        validate->setNotation(QDoubleValidator::StandardNotation);
        validate->setLocale(loc);

        vektorX->setValidator(validate);
        vektorY->setValidator(validate);
        vektorZ->setValidator(validate);

        QPushButton* myButtonSet = new QPushButton("&Set Vector");
        tabTransformation_control->addWidget(myButtonSet);
        connect(myButtonSet,SIGNAL(clicked() ),this, SLOT(slotTranslation()) );

        parent->setLayout(tabTransformation_control);
}




void CgQtGui::createOptionPanelExample1(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();


    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);


    /*Example for using a spinbox */

    mySpinBox1 = new QSpinBox();
    tab1_control->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
   // mySpinBox1->setSuffix("   suffix");
   // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab1_control->addWidget(mySpinBox1);


    /*Example for using a checkbox */

    myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    tab1_control->addWidget(myCheckBox1);


    /*Example for using a button */

    QPushButton* myButton1 = new QPushButton("&drueck mich");
    tab1_control->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );



    parent->setLayout(tab1_control);

}


void CgQtGui::createOptionPanelExample2(QWidget* parent)
{


    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();



    /*Example for using a button group */

    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);
    myButtonGroup->addButton(radiobutton5,4);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab2_control->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );
    parent->setLayout(tab2_control);

}



//Slots für Events


void CgQtGui::slotMySliderChanged()
{
    CgBaseEvent* e = new CgColorChangedEvent((mySlider1->value())/255.0,(mySlider2->value())/255.0,(mySlider3->value())/255.0);

    notifyObserver(e);

}



void CgQtGui::slotRotateLine() {
    if(aufloesung->text().isEmpty() || aufloesung->text().toInt() < 3) {

        std::cout << "Bitte eine passende Zahl zwischen 3 und 100 eingeben." << std::endl;
    } else {
        CgBaseEvent* e = new CgRotateEvent(aufloesung->text().toInt());

     notifyObserver(e);
    }
}


void CgQtGui::slotUnterteilung()
{
      CgBaseEvent* e = new CgUnterteilungsEvent(aufloesung->text().toInt());
      notifyObserver(e);
}

void CgQtGui::slotResetCurve(){

    CgBaseEvent* e= new CgResetEvent();
    notifyObserver(e);
}

void CgQtGui::slotDrawVertexNormals(bool checked) {

    CgBaseEvent* e = new CgVertexNormalsEvent(checked);
    notifyObserver(e);
}

void CgQtGui::slotTranslation(){

    CgBaseEvent* e= new CgTranslationEvent((vektorX->text().toFloat()),(vektorY->text().toFloat()),(vektorZ->text().toFloat()));
    notifyObserver(e);
}


void CgQtGui::slotButtonGroupSelectionChanged()
{

}

void CgQtGui::slotMySpinBox1Changed()
{

}

void CgQtGui::slotMyCheckBox1Changed()
{

}


void CgQtGui::slotLoadMeshFile()
{



   QString file=  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));


    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());

    notifyObserver(e);
}


void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotMyButton1Pressed()
{
   std::cout << "button 1 pressed " << std::endl;

}


void CgQtGui::mouseEvent(QMouseEvent* event)
{

   // std::cout << QApplication::keyboardModifiers() << std::endl;

  //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


   if(event->type()==QEvent::MouseButtonPress)
   {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
   }

   if(event->type()==QEvent::MouseMove)
   {
       CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                        glm::vec2(event->localPos().x() ,event->localPos().y()),
                                        (Cg::MouseButtons)event->button());
       notifyObserver(e);
   }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
   CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
   notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
     CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
     notifyObserver(e);
}




CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}





