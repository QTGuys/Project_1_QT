#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"
#include <QColor>
#include <QPen>

enum Shape{
    NONE,
    SPHERE,
    RECTANGLE,
    TRIANGLE
};

class ComponentShape : public Component
{
public:
    ComponentShape();

    float size=0.0f;

    Shape shape = NONE;

    QColor fillColor=QColor::fromRgb(0.0f,0.0f,0.0f);
    QColor borderColor = QColor::fromRgb(0.0f,0.0f,0.0f);

    int penWidth =0;
    Qt::PenStyle style = Qt::PenStyle::DashLine;

};

#endif // COMPONENTSHAPE_H
