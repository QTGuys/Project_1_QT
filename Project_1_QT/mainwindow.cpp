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
   connect(hierarchy,SIGNAL(entitySelected(int)),sceneView,SLOT(onEntitySelected(int)));
   connect(sceneView, SIGNAL(onGoSelected(GameObject*)),inspector,SLOT(goSelected(GameObject*)));
   connect(inspector, SIGNAL(transformChanged()),sceneView,SLOT(onTransformChanged()));

   connect(uiMainWindow->actionSave_Scene,SIGNAL(triggered()),sceneView,SLOT(SaveScene()));
   connect(uiMainWindow->actionC,SIGNAL(triggered()),sceneView,SLOT(LoadScene()));
   connect(uiMainWindow->actionClose_Scene,SIGNAL(triggered()),sceneView,SLOT(CallToClean()));

}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete hierarchy;
    delete inspector;
    delete sceneView;
}

