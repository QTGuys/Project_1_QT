#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"
#include <QColor>
#include <QPen>

enum shapeType{
    SPHERE,
    RECTANGLE,
    TRIANGLE,
    NONE
};

class ComponentShape : public Component
{
public:
    ComponentShape();
    ComponentShape(GameObject*);

    shapeType shape = NONE;

    QColor fillColor=QColor::fromRgb(255,255,255);
    QColor borderColor = QColor::fromRgb(0,0,0);

    int penWidth =4;
    Qt::PenStyle style = Qt::PenStyle::DashLine;

};

#endif // COMPONENTSHAPE_H
