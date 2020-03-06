#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

signals:
    void entitySelected(int entity_id);

public slots:
    void onAddEntity(int entity_type);
    void onRemoveEntity();
    void onEntitySelected(int row);
private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
