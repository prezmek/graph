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
    void selectNodesAll();
    void unselectNodesAll();

private slots:
    void open();
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
    QAction *openAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    Params params;
};

#endif
