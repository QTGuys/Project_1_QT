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
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiMesh;
}

void Inspector::goSelected(GameObject* go)
{
    selected_go = go;
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
    printf("%i \n",v);

    selected_go->shape->fillColor.setGreen(v);
    // selected_go->shape->fillColor.
    printf("%i \n",selected_go->shape->fillColor.green());
    emit transformChanged();
}

void Inspector::onFBChanged(int v)
{
    selected_go->shape->fillColor.setBlue(v);
    emit transformChanged();
}
