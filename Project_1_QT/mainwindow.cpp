#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "sceneview.h"
#include "gameobject.h"
#include "componentshape.h"
#include "componenttransform.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

   hierarchy = new Hierarchy();
   uiMainWindow->dock_hierarchy->setWidget(hierarchy);

   inspector = new Inspector();
   uiMainWindow->dock_inspector->setWidget(inspector);

    sceneView = new SceneView();

   QVBoxLayout* layout = new QVBoxLayout();
   layout->addWidget(sceneView);
   uiMainWindow->centralWidget->setLayout(layout);

   connect(hierarchy,SIGNAL(newEntity(GameObject*)),inspector,SLOT(onNewEntity(GameObject*)));
   connect(hierarchy,SIGNAL(newEntity(GameObject*)),sceneView,SLOT(onNewEntity(GameObject*)));

   sceneView->currGO=new GameObject();
   sceneView->currGO->shape->shape=SPHERE;
   sceneView->currGO->shape->size=64.0f;
   sceneView->currGO->shape->fillColor=QColor::fromRgb(255,255,255);
   sceneView->currGO->transform->position=QVector2D(0,0);
   sceneView->currGO->transform->scale=QVector2D(1,2);
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete hierarchy;
    delete inspector;
    delete sceneView;
}

