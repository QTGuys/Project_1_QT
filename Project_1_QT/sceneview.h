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

    void CleanScene();

signals:
    void onGoSelected(GameObject* go);
    void onGoSelectedList(int idx);
    void onDeleteAllEntities();
    void nameChanged(std::vector<GameObject*> gameobjects);
    void LoadItem(std::string name);


public slots:
    void onEntitySelected(int row);
    void onNewEntity(GameObject* go);
    void onTransformChanged();
    void onNameChanged();
    void SaveScene();
    void LoadScene();
    void CallToClean();
    void onGoDeleted(GameObject* go);



private:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // SCENEVIEW_H
