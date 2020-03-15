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
      connect(ui->list_widget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onEntityClicked()));
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
    ui->list_widget->takeItem(ui->list_widget->currentRow());
}

void Hierarchy::onEntitySelected(int row)
{
    if(ui->list_widget->selectedItems().count() != 0)
        emit entitySelected(row);

}

void Hierarchy::onEntityClicked()
{
       if(ui->list_widget->selectedItems().count() != 0)
           emit entitySelected(ui->list_widget->currentRow());
}

void Hierarchy::onSelectFromView(int idx)
{
    ui->list_widget->setCurrentRow(idx);
}

void Hierarchy::onNameChanged(std::vector<GameObject *> gameobjects)
{
    ui->list_widget->clear();
    for(auto item = gameobjects.begin();item != gameobjects.end();item++)
    {
        ui->list_widget->addItem((*item)->name.c_str());
    }
}

void Hierarchy::RemoveAllEntities()
{
    ui->list_widget->reset();
    ui->list_widget->clear();
}

void Hierarchy::onAddLoadItem(std::string name)
{
    ui->list_widget->addItem(name.c_str());
}

void Hierarchy::onGoDeleted(GameObject *go)
{
    for(int i = 0; i<ui->list_widget->count();i++)
    {
        if(ui->list_widget->item(i)->text() == go->name.c_str())
        {
            ui->list_widget->takeItem(i);
            ui->list_widget->setCurrentItem(nullptr);
            break;
        }
    }
}

