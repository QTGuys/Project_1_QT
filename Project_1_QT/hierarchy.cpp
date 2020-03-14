#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "gameobject.h"

#include "componentshape.h"
#include "componenttransform.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

//    connect(ui->add_entity, SIGNAL(clicked()),this,SLOT(onAddEntity()));
//    connect(ui->remove_entity, SIGNAL(clicked()),this,SLOT(onRemoveEntity()));
      connect(ui->list_widget, SIGNAL(currentRowChanged(int)),this,SLOT(onEntitySelected(int)));
      connect(ui->create,SIGNAL(clicked()),this,SLOT(onAddEntity()));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity()
{
    GameObject* new_go = new GameObject();

    switch (ui->add_object->currentIndex()) {
    case 0:
        new_go->name = "Circle";
        new_go->shape->shape = shapeType::SPHERE;
        break;
   case 1:
        new_go->name = "Polygon";
        new_go->shape->shape = shapeType::RECTANGLE;
        break;
   case 2:
        new_go->name = "Triangle";
        new_go->shape->shape = shapeType::TRIANGLE;
        break;
    }
    emit newEntity(new_go);
    ui->list_widget->addItem(new_go->name.c_str());
}

void Hierarchy::onRemoveEntity()
{
    ui->list_widget->takeItem( ui->list_widget->currentRow());
}

void Hierarchy::onEntitySelected(int row)
{
    emit entitySelected(row);
}

