#include "sceneview.h"
#include "gameobject.h"
#include "componenttransform.h"
#include "componentshape.h"

#include <QApplication>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>

SceneView::SceneView(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    offset=new QVector2D();
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

void SceneView::onTransformChanged()
{
    this->update();
}

void SceneView::onEntitySelected(int row)
{
    if(row >= 0)
    {
        GameObject* go = gameobjects[row];
        if(go)
            emit onGoSelected(gameobjects[row]);
    }
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
        //Position Stuff
        int radius = gameobjects[i]->transform->size;

        int rWidth = radius * 2 * gameobjects[i]->transform->scale.x();
        int rHeight = radius * 2 * gameobjects[i]->transform->scale.y();

        QVector2D objCenter={(radius*gameobjects[i]->transform->scale.x()),
                             (radius*gameobjects[i]->transform->scale.y())};

        gameobjects[i]->transform->realPosition.setX(gameobjects[i]->transform->position.x()+screenCenter.x()-objCenter.x());
        gameobjects[i]->transform->realPosition.setY(gameobjects[i]->transform->position.y()+screenCenter.y()-objCenter.y());

        QRect objectRect(gameobjects[i]->transform->realPosition.x(),gameobjects[i]->transform->realPosition.y(),rWidth,rHeight);

        //Draw Selected Rect

        if(gameobjects[i]==selectedGO)
        {
            QRect sObjectRect(objectRect.x()-5,objectRect.y()-5,objectRect.width()+10,objectRect.height()+10);

            brush.setColor(QColor::fromRgb(0,0,0,0));
            pen.setWidth(2);
            pen.setColor(QColor::fromRgb(0,0,0,255));
            pen.setStyle(Qt::PenStyle::DotLine);
            painter.setBrush(brush);
            painter.setPen(pen);

            painter.drawRect(sObjectRect);
        }

        //Color Stuff
        brush.setColor(gameobjects[i]->shape->fillColor);
        pen.setWidth(gameobjects[i]->shape->penWidth);
        pen.setColor(gameobjects[i]->shape->borderColor.rgb());
        pen.setStyle(gameobjects[i]->shape->style);
        painter.setBrush(brush);
        painter.setPen(pen);

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
    selectedGO=nullptr;
}

void SceneView::CallToClean()
{
    if(gameobjects.size()>0)
    {
        QMessageBox msgBox;
        msgBox.setText("You are going to open a new Scene");
        msgBox.setInformativeText("Do you want to save your current scene?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
        {
            SaveScene();
            CleanScene();
            break;
        }
        case QMessageBox::Discard:
        {
            CleanScene();
            break;
        }
        }
    }
}

void SceneView::onGoDeleted(GameObject *go)
{
    for(int i = 0;i<gameobjects.size();i++)
    {
        if(gameobjects[i] == go)
        {
            gameobjects.erase(gameobjects.begin()+i);
            break;
        }

    }
}

void SceneView::onAppClose()
{
    if(gameobjects.size()>0)
    {
        QMessageBox msgBox;
        msgBox.setText("Closing App");
        msgBox.setInformativeText("Do you want to save your current scene before closing?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
        {
            SaveScene();
            CleanScene();
            break;
        }
        case QMessageBox::Discard:
        {
            CleanScene();
            break;
        }
        }
    }

    QApplication::quit();
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
    selectedGO=nullptr;

    this->update();

    emit onDeleteAllEntities();
}

//https://gist.github.com/lamprosg/2133804
void SceneView::SaveScene()
{
    QString path = QFileDialog::getSaveFileName(this,"Save Scene",".",tr("Xml files(*.xml)"));

    if(path.isEmpty())
    {
        return;
    }

    QFile file(path);
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
    //QString path = QFileDialog::getOpenFileName(this,"Open Scene",".",tr("Xml files(*.xml)"));
    QString path = QFileDialog::getOpenFileName(this,"Open Scene");


    if(path.isEmpty())
    {
        return;
    }

    CleanScene();

    QFile file(path);
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
                }
                xmlReader.skipCurrentElement();
            }
            gameobjects.push_back(current);
            std::cout<<"Adding %s"+current->name<<std::endl;
            emit LoadItem(current->name);
        }
    }

    file.close();
}

void SceneView::mousePressEvent(QMouseEvent *event)
{
    mouseClicked=true;

    QVector2D screenCenter ={rect().width()/2.0f,rect().height()/2.0f};

    offset->setX(event->x()-screenCenter.x());
    offset->setY(event->y()-screenCenter.y());

    selectedGO=nullptr;
    int idx=-1;

    for(int i=0; i<gameobjects.size();++i)
    {
        int posX=gameobjects[i]->transform->realPosition.x();
        int posY=gameobjects[i]->transform->realPosition.y();

        int size=gameobjects[i]->transform->size;

        if(event->x() > posX && event->x() < posX+size*2*gameobjects[i]->transform->scale.x())
        {
            if(event->y() > posY && event->y() < posY+size*2*gameobjects[i]->transform->scale.y())
            {
                selectedGO = gameobjects[i];
                idx=i;
            }
        }
    }

    if(selectedGO && idx!=-1)
    {
        emit onGoSelectedList(idx);
        this->update();
    }
}

void SceneView::mouseReleaseEvent(QMouseEvent *event)
{
    mouseClicked=false;
}

void SceneView::mouseMoveEvent(QMouseEvent *event)
{
    if(selectedGO && mouseClicked)
    {
        QVector2D screenCenter ={rect().width()/2.0f,rect().height()/2.0f};

        QVector2D mousePos={(event->x()-screenCenter.x()),
                             (event->y()-screenCenter.y())};

        QVector2D newPos={selectedGO->transform->position.x()-(offset->x()-mousePos.x()),
                          selectedGO->transform->position.y()-(offset->y()-mousePos.y())};

        selectedGO->transform->position.setX(newPos.x());
        selectedGO->transform->position.setY(newPos.y());
        this->update();

        offset->setX(mousePos.x());
        offset->setY(mousePos.y());
        emit onGoSelected(selectedGO);
    }
}

void SceneView::onNameChanged()
{
    emit nameChanged(gameobjects);
}










