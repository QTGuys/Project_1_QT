#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <iostream>

namespace Ui {
class Hierarchy;
}

class GameObject;

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

signals:
    void entitySelected(int row);
    void newEntity(GameObject* go);

public slots:
    void onAddEntity();
    void onRemoveEntity();
    void onEntitySelected(int row);
    void RemoveAllEntities();
    void onSelectFromView(int idx);
    void onNameChanged(std::vector<GameObject*> gameobjects);
    void onAddLoadItem(std::string name);
    void onGoDeleted(GameObject* go);

private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
