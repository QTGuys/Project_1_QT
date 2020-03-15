#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }
class Hierarchy;
class Inspector;
class SceneView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void appClose();
public slots:
    void onAppClose();
private:
    Ui::MainWindow *uiMainWindow;

    Hierarchy* hierarchy;
    Inspector* inspector;
    SceneView* sceneView;
};
#endif // MAINWINDOW_H
