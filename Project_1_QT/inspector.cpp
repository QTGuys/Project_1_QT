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
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiMesh;
}

void Inspector::goSelected(GameObject* go)
{
    selected_go = go;
    printf(go->name.c_str());
    uiTransform->posX->setValue(go->transform->position.x());
    uiTransform->posY->setValue(go->transform->position.y());
    uiTransform->scaleX->setValue(go->transform->scale.x());
    uiTransform->scaleY->setValue(go->transform->scale.y());
}

void Inspector::onNewEntity(GameObject *go)
{
    //printf(go->name.c_str());
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
