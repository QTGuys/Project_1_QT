#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

    hierarchy = new Hierarchy();
   uiMainWindow->dock_hierarchy->setWidget(hierarchy);

   inspector = new Inspector();
   uiMainWindow->dock_inspector->setWidget(inspector);
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete hierarchy;
    delete inspector;
}

