QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgViewer

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgEvents/CgLoadObjFileEvent.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgTrackballEvent.cpp \
    CgSceneGraph/ObjectMesh.cpp \
    CgSceneGraph/ObjectMeshCreator.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgSceneGraph/CgCylinder.cpp \
    CgEvents/CgColorChangedEvent.cpp \
    CgSceneGraph/CGIdGiver.cpp \
    CgSceneGraph/RotationObject.cpp \
    CgEvents/CgResetEvent.cpp \
    CgEvents/CgUnterteilungsEvent.cpp \
    CgEvents/CgRotateEvent.cpp \
    CgEvents/CgVertexNormalsEvent.cpp \
    CgSceneGraph/CgAppearance.cpp \
    CgSceneGraph/CgScenegraphEntity.cpp \
    CgUtils/MatrixUtils.cpp \
    CgSceneGraph/CgSelectObject.cpp \
    CgSceneGraph/CgScenegraph.cpp \
    CgEvents/CgTranslationEvent.cpp

HEADERS += \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgEvents/CgLoadObjFileEvent.h \
    CgUtils/ObjLoader.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h \
    CgSceneGraph/ObjectMesh.h \
    CgSceneGraph/ObjectMeshCreator.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgPolyline.h \
    CgSceneGraph/CgCylinder.h \
    CgEvents/CgColorChangedEvent.h \
    CgSceneGraph/CGIdGiver.h \
    CgSceneGraph/RotationObject.h \
    CgEvents/CgResetEvent.h \
    CgEvents/CgUnterteilungsEvent.h \
    CgEvents/CgRotateEvent.h \
    CgEvents/CgVertexNormalsEvent.h \
    CgSceneGraph/CgAppearance.h \
    CgSceneGraph/CgScenegraphEntity.h \
    CgUtils/MatrixUtils.h \
    CgSceneGraph/CgSelectObject.h \
    CgSceneGraph/CgScenegraph.h \
    CgEvents/CgTranslationEvent.h

