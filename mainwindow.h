#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwidget.h"
#include "params.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(char* filename);

public slots:
    void setEdgeWeightValue(int value);

private slots:
    void newFile();
    void open();
    void save();
    void print();
    void about();
    void aboutQt();

private:
    QLabel *infoLabel;
    GraphWidget* graph_widget;

    void createActions();
    void createMenus();

    QWidget* CreateControlsLayout();
    QWidget* CreateControlsEdges();
    QWidget* CreateControlsNodes();
    QWidget* CreateControlsWidget();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    Params params;
};

#endif
