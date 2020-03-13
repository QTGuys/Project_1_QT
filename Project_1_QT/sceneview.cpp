#include "sceneview.h"
#include "gameobject.h"
#include "componenttransform.h"
#include "componentshape.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <iostream>

SceneView::SceneView(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

QSize SceneView::sizeHint() const
{
    return QSize(256,256);
}

QSize SceneView::minimumSizeHint() const
{
    return QSize(64,64);
}

void SceneView::entitySelected(int row)
{
    emit goSelected(gameobjects[row]);
}

void SceneView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    //Background
    brush.setColor(QColor::fromRgb(127,190,220));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(rect());

    QVector2D screenCenter ={rect().width()/2.0f,rect().height()/2.0f};

    std::cout<<"LA X de la pantalla"<<std::endl;
    std::cout<<screenCenter.x()<<std::endl;
    std::cout<<"LA Y de la pantalla"<<std::endl;
    std::cout<<screenCenter.y()<<std::endl;

    if (currGO)
    {
        //Color Stuff
        brush.setColor(currGO->shape->fillColor);
        pen.setWidth(4);
        pen.setColor(currGO->shape->borderColor);
        pen.setStyle(currGO->shape->style);
        painter.setBrush(brush);
        painter.setPen(pen);

        //Position Stuff
        int radius = currGO->shape->size;

        int rWidth = radius * 2 * currGO->transform->scale.x();
        int rHeight = radius * 2 * currGO->transform->scale.y();

        QVector2D objCenter={(radius*currGO->transform->scale.x()),
                             (radius*currGO->transform->scale.y())};

        int x = currGO->transform->position.x()+screenCenter.x()-objCenter.x();
        int y = currGO->transform->position.y()+screenCenter.y()-objCenter.y();

        std::cout<<"LA X"<<std::endl;
        std::cout<<x<<std::endl;
        std::cout<<"LA Y"<<std::endl;
        std::cout<<y<<std::endl;

        switch (currGO->shape->shape)
        {
        case NONE:
            break;

        case SPHERE:
        {
            QRect circleRect(x,y,rWidth,rHeight);
            painter.drawEllipse(circleRect);

            break;
        }
        case RECTANGLE:
            break;

        case TRIANGLE:
            break;

        }
    }
}
