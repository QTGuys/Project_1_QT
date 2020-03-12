#include "sceneview.h"
#include "gameobject.h"
#include "componenttransform.h"
#include "componentshape.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

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

    if (currGO)
    {

        brush.setColor(currGO->shape->fillColor);
        pen.setWidth(4);
        pen.setColor(currGO->shape->borderColor);
        pen.setStyle(currGO->shape->style);
        painter.setBrush(brush);
        painter.setPen(pen);

        switch (currGO->shape->shape)
        {
        case NONE:
            break;

        case SPHERE:
        {
            int radius = currGO->shape->size;

            int rWidth = radius * 2 * currGO->transform->scale.x();
            int rHeight = radius * 2 * currGO->transform->scale.y();

            int x = currGO->transform->position.x();
            int y = currGO->transform->position.y();

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
