#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>

class GameObject;

class SceneView : public QWidget
{
    Q_OBJECT

public:

    explicit SceneView(QWidget *parent = nullptr);
    ~SceneView();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public:

    GameObject* currGO = nullptr;
    std::vector<GameObject*> gameobjects;

signals:
    void goSelected(GameObject* go);

public slots:
    void entitySelected(int row);
    void onNewEntity(GameObject* go);

private:

    void paintEvent(QPaintEvent *event) override;

};

#endif // SCENEVIEW_H
