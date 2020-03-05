#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>

class GameObject;

class SceneView : public QWidget
{
    Q_OBJECT

public:

    explicit SceneView(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public:

    GameObject* currGO = nullptr;

signals:

public slots:
private:

    void paintEvent(QPaintEvent *event) override;

};

#endif // SCENEVIEW_H
