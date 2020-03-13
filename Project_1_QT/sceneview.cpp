#include "sceneview.h"
#include "gameobject.h"
#include "componenttransform.h"
#include "componentshape.h"

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFile>
#include <QXmlStreamWriter>

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

void SceneView::onNewEntity(GameObject *go)
{
    gameobjects.push_back(go);
    this->update();
    SaveScene();
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

    for(int i = 0; i < gameobjects.size() && gameobjects[i]; ++i)
    {
        //Color Stuff
        brush.setColor(gameobjects[i]->shape->fillColor);
        pen.setWidth(4);
        pen.setColor(gameobjects[i]->shape->borderColor);
        pen.setStyle(gameobjects[i]->shape->style);
        painter.setBrush(brush);
        painter.setPen(pen);

        //Position Stuff
        int radius = gameobjects[i]->transform->size;

        int rWidth = radius * 2 * gameobjects[i]->transform->scale.x();
        int rHeight = radius * 2 * gameobjects[i]->transform->scale.y();

        QVector2D objCenter={(radius*gameobjects[i]->transform->scale.x()),
                             (radius*gameobjects[i]->transform->scale.y())};

        int x = gameobjects[i]->transform->position.x()+screenCenter.x()-objCenter.x();
        int y = gameobjects[i]->transform->position.y()+screenCenter.y()-objCenter.y();

        QRect objectRect(x,y,rWidth,rHeight);

        switch (gameobjects[i]->shape->shape)
        {
        case NONE:
            break;

        case SPHERE:
        {
            painter.drawEllipse(objectRect);

            break;
        }
        case RECTANGLE:
        {
            painter.drawRect(objectRect);
            break;
        }
        case TRIANGLE:
            break;

        }
    }
}

SceneView::~SceneView()
{
    for(int i = 0; i < gameobjects.size(); ++i)
    {
        if(gameobjects[i])
        {
            delete gameobjects[i];
            gameobjects[i]=nullptr;
        }
    }

    gameobjects.clear();
}

//https://gist.github.com/lamprosg/2133804
void SceneView::SaveScene()
{
    QFile file("Scenes/scene.xml");
    file.open(QIODevice::WriteOnly);


    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("Scene");

    for(int i=0; i < gameobjects.size();++i)
    {
        xml.writeStartElement("GameObject");
        xml.writeTextElement("name",gameobjects[i]->name.c_str());
        xml.writeEndElement();
    }

    xml.writeEndElement();

    file.close();
}











