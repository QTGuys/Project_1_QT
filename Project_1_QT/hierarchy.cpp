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
      connect(ui->add_object,SIGNAL(activated(int)),this,SLOT(onAddEntity(int)));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity(int entity_type)
{
    GameObject* new_go = new GameObject();

    switch (entity_type) {
    case 1:
        new_go->name = "Circle";
        new_go->shape->shape = shapeType::SPHERE;
        break;
   case 2:
        new_go->name = "Polygon";
        new_go->shape->shape = shapeType::RECTANGLE;
        break;
   case 3:
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

