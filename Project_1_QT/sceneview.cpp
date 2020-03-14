#include "sceneview.h"
#include "gameobject.h"
#include "componenttransform.h"
#include "componentshape.h"

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
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

void SceneView::onNewEntity(GameObject *go)
{
    gameobjects.push_back(go);
    this->update();
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
        pen.setWidth(gameobjects[i]->shape->penWidth);
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

void SceneView::CleanScene()
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

    this->update();
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
        ComponentTransform* trans = gameobjects[i]->transform;
        ComponentShape* shape = gameobjects[i]->shape;


        xml.writeStartElement("GameObject");
        xml.writeAttribute("name",gameobjects[i]->name.c_str());

        //Saving Transform
        {
            xml.writeStartElement("Transform");

            //size
            xml.writeAttribute("size",std::to_string(trans->size).c_str());

            //Position
            xml.writeAttribute("posX",std::to_string(trans->position.x()).c_str());
            xml.writeAttribute("posY",std::to_string(trans->position.y()).c_str());

            //Scale
            xml.writeAttribute("scaleX",std::to_string(trans->scale.x()).c_str());
            xml.writeAttribute("scaleY",std::to_string(trans->scale.y()).c_str());

            xml.writeEndElement();
        }

        //Saving Shape
        {
            xml.writeStartElement("Shape");

            //main shape
            xml.writeAttribute("shape",std::to_string(shape->shape).c_str());

            //Fill color
            xml.writeAttribute("fillColor_R",std::to_string(shape->fillColor.red()).c_str());
            xml.writeAttribute("fillColor_G",std::to_string(shape->fillColor.green()).c_str());
            xml.writeAttribute("fillColor_B",std::to_string(shape->fillColor.blue()).c_str());

            //Line Color
            xml.writeAttribute("borderColor_R",std::to_string(shape->borderColor.red()).c_str());
            xml.writeAttribute("borderColor_G",std::to_string(shape->borderColor.green()).c_str());
            xml.writeAttribute("borderColor_B",std::to_string(shape->borderColor.blue()).c_str());

            //Pen width
            xml.writeAttribute("penWidth",std::to_string(shape->penWidth).c_str());

            //Pen Style
            xml.writeAttribute("penStyle",std::to_string(shape->style).c_str());

            xml.writeEndElement();
        }

        xml.writeEndElement();
    }

    xml.writeEndElement();

    file.close();
}

void SceneView::LoadScene()
{
    CleanScene();

    QFile file("Scenes/scene.xml");
    file.open(QIODevice::ReadOnly);

    QXmlStreamReader xmlReader(&file);

    //Scene
    if(xmlReader.readNextStartElement())
    {
        //Game Object
        while(xmlReader.readNextStartElement())
        {
            GameObject* current = new GameObject();
            ComponentTransform* trans = current->transform;
            ComponentShape* shape = current->shape;

            QXmlStreamAttributes goAttributes = xmlReader.attributes();

            //Name
            current->name=goAttributes.value("name").toLocal8Bit().constData();

            //Components
            while(xmlReader.readNextStartElement())
            {
                if(xmlReader.name()=="Transform")
                {
                    QXmlStreamAttributes trAttributes = xmlReader.attributes();

                    //Size
                    trans->size = trAttributes.value("size").toFloat();

                    //Position
                    trans->position.setX(trAttributes.value("posX").toFloat());
                    trans->position.setY(trAttributes.value("posY").toFloat());

                    //Scale
                    trans->scale.setX(trAttributes.value("scaleX").toFloat());
                    trans->scale.setY(trAttributes.value("scaleY").toFloat());
                }

                if(xmlReader.name()=="Shape")
                {
                    QXmlStreamAttributes shAttributes = xmlReader.attributes();

                    //Shape
                    shape->shape=(shapeType)shAttributes.value("shape").toInt();

                    //Fill Color
                    shape->fillColor.setRgb(shAttributes.value("fillColor_R").toInt(),
                                            shAttributes.value("fillColor_G").toInt(),
                                            shAttributes.value("fillColor_B").toInt());
                    //Fill Color
                    shape->borderColor.setRgb(shAttributes.value("borderColor_R").toInt(),
                                              shAttributes.value("borderColor_G").toInt(),
                                              shAttributes.value("borderColor_B").toInt());
                    //Pen Width
                    shape->penWidth=shAttributes.value("penWidth").toInt();

                    //Pen Style
                    shape->style=(Qt::PenStyle)shAttributes.value("penStyle").toInt();

                    std::cout<<shape->fillColor.red()<<std::endl;
                    std::cout<<shape->borderColor.green()<<std::endl;

                }
                //gameobjects.push_back(current);
                xmlReader.skipCurrentElement();
            }
        }
    }

    file.close();
}










