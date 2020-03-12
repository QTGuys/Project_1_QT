#ifndef COMPONENTTRANSFORM_H
#define COMPONENTTRANSFORM_H

#include "component.h"
#include <QVector2D>


class ComponentTransform : public Component
{
public:
    ComponentTransform();
    ComponentTransform(GameObject* go);

public:

    QVector2D position = {0.0f,0.0f};
    QVector2D scale = {0.0f,0.0f};
    //QVector2D rotation = {0.0f,0.0f};

};

#endif // COMPONENTTRANSFORM_H
