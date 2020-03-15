#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include <QColor>

namespace Ui{
        class Transform;
        class Mesh;
        class GeneralInspector;
}

class GameObject;

class Inspector : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color_1 NOTIFY colorChanged)
    Q_PROPERTY(QColor color READ color_2 NOTIFY colorChanged)

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();

    QColor color_1() const
    {
        return fColor;
    }

    QColor color_2() const
    {
        return bColor;
    }

signals:
    void transformChanged();
    void nameChanged();
    void colorChanged(QColor color);
    void goDeleted(GameObject* go);

public slots:
   void goSelected(GameObject* go);
    void onNewEntity(GameObject* go);
    void onPosXChanged(double v);
    void onPosYChanged(double v);
    void onScaleXChanged(double v);
    void onScaleYChanged(double v);
    void onRotationChanged(double v);
    void onSRChanged(int v);
    void onSGChanged(int v);
    void onSBChanged(int v);
    void onFRChanged(int v);
    void onFGChanged(int v);
    void onFBChanged(int v);
    void onThicknessChanged(double v);
    void onStyleChanged(int index);
    void onShapeChanged(int index);
    void onNameChanged();

    void onGoDelete();

    void onFColorChanged();
    void onBColorChanged();

private:
    Ui::Transform *uiTransform;
    Ui::Mesh* uiMesh;
    Ui::GeneralInspector* uiGeneralInspector;

    QWidget* transformWidget;
    QWidget* meshWidget;
    QWidget* generalInspectorWidget;

    GameObject* selected_go;
    QColor fColor;
    QColor bColor;
};

#endif // HIERARCHY_H
