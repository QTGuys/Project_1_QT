#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"
#include <QColor>
#include <QPen>

enum shapeType{
    NONE,
    SPHERE,
    RECTANGLE,
    TRIANGLE
};

class ComponentShape : public Component
{
public:
    ComponentShape();
    ComponentShape(GameObject*);

    float size=1.0f;

    shapeType shape = NONE;

    QColor fillColor=QColor::fromRgb(0.0f,0.0f,0.0f);
    QColor borderColor = QColor::fromRgb(0.0f,0.0f,0.0f);

    int penWidth =0;
    Qt::PenStyle style = Qt::PenStyle::DashLine;

};

#endif // COMPONENTSHAPE_H
