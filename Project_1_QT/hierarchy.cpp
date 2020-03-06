#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

//    connect(ui->add_entity, SIGNAL(clicked()),this,SLOT(onAddEntity()));
//    connect(ui->remove_entity, SIGNAL(clicked()),this,SLOT(onRemoveEntity()));
//    connect(ui->listWidget, SIGNAL(currentRowChanged(int)),this,SLOT(onEntitySelected(int)));
        connect(ui->add_object,SIGNAL(activated(int)),this,SLOT(onAddEntity(int)));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity(int entity_type)
{
    std::string name;
    switch (entity_type) {
    case 0:
        return;
    case 1:
        name = "Circle";
        break;
   case 2:
        name = "Polygon";
        break;
   case 3:
        name = "Background";
        break;
    }
    ui->list_widget->addItem(name.c_str());
}

void Hierarchy::onRemoveEntity()
{
    ui->list_widget->takeItem( ui->list_widget->currentRow());
}

void Hierarchy::onEntitySelected(int row)
{

    emit entitySelected(row);
}

