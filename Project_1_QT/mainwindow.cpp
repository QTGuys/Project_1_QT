#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "sceneview.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>

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
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete hierarchy;
    delete inspector;
}

