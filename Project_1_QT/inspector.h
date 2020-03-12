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
public slots:
    void onEntitySelected(int row);
    void onNewEntity(GameObject* go);
private:
    Ui::Transform *uiTransform;
    Ui::Mesh* uiMesh;
    Ui::GeneralInspector* uiGeneralInspector;

    QWidget* transformWidget;
    QWidget* meshWidget;
    QWidget* generalInspectorWidget;
};

#endif // HIERARCHY_H
