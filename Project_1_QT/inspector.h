#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui{
        class Transform;
        class Mesh;
        class GeneralInspector;
}

class GameObject;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();
signals:
    void transformChanged();
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

    void onStyleChanged(int index);

private:
    Ui::Transform *uiTransform;
    Ui::Mesh* uiMesh;
    Ui::GeneralInspector* uiGeneralInspector;

    QWidget* transformWidget;
    QWidget* meshWidget;
    QWidget* generalInspectorWidget;

    GameObject* selected_go;
};

#endif // HIERARCHY_H
