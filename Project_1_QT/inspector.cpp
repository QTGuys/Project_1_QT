#include "inspector.h"
#include "ui_transform.h"
#include "ui_mesh.h"
#include "ui_general_inspector.h"
#include <QVBoxLayout>
#include "gameobject.h"
#include "componenttransform.h"
#include "componentshape.h"

Inspector::Inspector(QWidget* parent):QWidget (parent),uiTransform(new Ui::Transform),uiMesh(new Ui::Mesh), uiGeneralInspector(new Ui::GeneralInspector)
{

    QVBoxLayout* layout = new QVBoxLayout();
    transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);
    meshWidget = new QWidget;
    uiMesh->setupUi(meshWidget);
    generalInspectorWidget = new QWidget;
    uiGeneralInspector->setupUi(generalInspectorWidget);

    layout->addWidget(generalInspectorWidget);
    layout->addWidget(transformWidget);
    layout->addWidget(meshWidget);
    setLayout(layout);


    connect(uiTransform->posX,SIGNAL(valueChanged(double)),this, SLOT(onPosXChanged(double)));
    connect(uiTransform->posY,SIGNAL(valueChanged(double)),this, SLOT(onPosYChanged(double)));
    connect(uiTransform->scaleX,SIGNAL(valueChanged(double)),this, SLOT(onScaleXChanged(double)));
    connect(uiTransform->scaleY,SIGNAL(valueChanged(double)),this, SLOT(onScaleYChanged(double)));

    connect(uiMesh->sr,SIGNAL(valueChanged(int)),this,SLOT(onSRChanged(int)));
    connect(uiMesh->sg, SIGNAL(valueChanged(int)),this,SLOT(onSGChanged(int)));
    connect(uiMesh->sb,SIGNAL(valueChanged(int)),this,SLOT(onSBChanged(int)));

    connect(uiMesh->fr,SIGNAL(valueChanged(int)),this,SLOT(onFRChanged(int)));
    connect(uiMesh->fg,SIGNAL(valueChanged(int)),this,SLOT(onFGChanged(int)));
    connect(uiMesh->fb, SIGNAL(valueChanged(int)),this,SLOT(onFBChanged(int)));

    connect(uiMesh->style, SIGNAL(currentIndexChanged(int)),this,SLOT(onStyleChanged(int)));
    connect(uiGeneralInspector->name_display, SIGNAL(editingFinished()),this,SLOT(onNameChanged()));

    connect(uiGeneralInspector->delete_button, SIGNAL(clicked()),this,SLOT(onGoDelete()));

    connect(uiMesh->shape_type, SIGNAL(currentIndexChanged(int)),this, SLOT(onShapeChanged(int)));
    generalInspectorWidget->setVisible(false);
    transformWidget->setVisible(false);
    meshWidget->setVisible(false);
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiMesh;
}

void Inspector::goSelected(GameObject* go)
{
    if(go)
    {
    generalInspectorWidget->setVisible(true);
    transformWidget->setVisible(true);
    meshWidget->setVisible(true);
    selected_go = go;

    uiGeneralInspector->name_display->setText(go->name.c_str());

    uiTransform->posX->setValue(go->transform->position.x());
    uiTransform->posY->setValue(go->transform->position.y());
    uiTransform->scaleX->setValue(go->transform->scale.x());
    uiTransform->scaleY->setValue(go->transform->scale.y());


    uiMesh->shape_type->setCurrentIndex(go->shape->shape);
    uiMesh->sr->setValue(go->shape->borderColor.red());
    uiMesh->sg->setValue(go->shape->borderColor.green());
    uiMesh->sb->setValue(go->shape->borderColor.blue());

    uiMesh->fr->setValue(go->shape->fillColor.red());
    uiMesh->fg->setValue(go->shape->fillColor.green());
    uiMesh->fb->setValue(go->shape->fillColor.blue());
    uiMesh->thickness->setValue(go->shape->penWidth);
    uiMesh->style->setCurrentIndex(go->shape->style);
    }
}

void Inspector::onNewEntity(GameObject *go)
{
    goSelected(go);
}

void Inspector::onPosXChanged(double v)
{
    selected_go->transform->position.setX(v);
    emit transformChanged();
}

void Inspector::onPosYChanged(double v)
{
        selected_go->transform->position.setY(v);
            emit transformChanged();
}

void Inspector::onScaleXChanged(double v)
{
        selected_go->transform->scale.setX(v);
            emit transformChanged();
}

void Inspector::onScaleYChanged(double v)
{
    selected_go->transform->scale.setY(v);
        emit transformChanged();
}

void Inspector::onRotationChanged(double v)
{
    emit transformChanged();
}

void Inspector::onSRChanged(int v)
{
    selected_go->shape->borderColor.setRed(v);
    emit transformChanged();
}

void Inspector::onSGChanged(int v)
{
    selected_go->shape->borderColor.setGreen(v);
    emit transformChanged();
}

void Inspector::onSBChanged(int v)
{
    selected_go->shape->borderColor.setBlue(v);
    emit transformChanged();
}

void Inspector::onFRChanged(int v)
{
    selected_go->shape->fillColor.setRed(v);
    emit transformChanged();
}

void Inspector::onFGChanged(int v)
{
    selected_go->shape->fillColor.setGreen(v);
    // selected_go->shape->fillColor.
    emit transformChanged();
}

void Inspector::onFBChanged(int v)
{
    selected_go->shape->fillColor.setBlue(v);
    emit transformChanged();
}

void Inspector::onStyleChanged(int index)
{
    selected_go->shape->style = Qt::PenStyle(index);
    emit transformChanged();
}

void Inspector::onShapeChanged(int index)
{
    selected_go->shape->shape = shapeType(index);
    emit transformChanged();
}

void Inspector::onNameChanged()
{
    if(selected_go)
    {
    selected_go->name = uiGeneralInspector->name_display->text().toStdString();
    emit nameChanged();
    }
}

void Inspector::onGoDelete()
{
    emit goDeleted(selected_go);
  //  delete selected_go;
//     emit transformChanged();
//     emit nameChanged();
    generalInspectorWidget->setVisible(false);
    transformWidget->setVisible(false);
    meshWidget->setVisible(false);
    selected_go = nullptr;
}
