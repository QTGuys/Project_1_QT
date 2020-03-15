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
   connect(inspector, SIGNAL(nameChanged()),sceneView,SLOT(onNameChanged()));
   connect(sceneView, SIGNAL(nameChanged(std::vector<GameObject*>)),hierarchy,SLOT(onNameChanged(std::vector<GameObject*>)));

   connect(inspector,SIGNAL(goDeleted(GameObject*)),hierarchy,SLOT(onGoDeleted(GameObject*)));
   connect(inspector,SIGNAL(goDeleted(GameObject*)),sceneView,SLOT(onGoDeleted(GameObject*)));


   connect(sceneView, SIGNAL(onDeleteAllEntities()),hierarchy,SLOT(RemoveAllEntities()));
   connect(sceneView, SIGNAL(onGoSelectedList(int)),hierarchy,SLOT(onSelectFromView(int)));
   connect(sceneView, SIGNAL(LoadItem(std::string)),hierarchy,SLOT(onAddLoadItem(std::string)));


   connect(uiMainWindow->actionSave_Scene,SIGNAL(triggered()),sceneView,SLOT(SaveScene()));
   connect(uiMainWindow->actionC,SIGNAL(triggered()),sceneView,SLOT(LoadScene()));
   connect(uiMainWindow->actionClose_Scene,SIGNAL(triggered()),sceneView,SLOT(CallToClean()));
   connect(uiMainWindow->actionClose_App,SIGNAL(triggered()),this,SLOT(onAppClose()));

   connect(this,SIGNAL(appClose()),sceneView,SLOT(onAppClose()));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete hierarchy;
    delete inspector;
    delete sceneView;
}

void MainWindow::onAppClose()
{
    emit appClose();
}

