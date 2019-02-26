#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
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
    void setNoOfEdgesValue(int value);
    void selectNodesAll();
    void unselectNodesAll();
    void onlyselectedNodes();
    void layoutComboChanged(int i);
    void deleteSelected();
    void setNoOfCliques(int value);

private slots:
    void open();
    void about();
    void aboutQt();

private:
    QLabel *infoLabel;
    GraphWidget* graph_widget;
    QPushButton* button_onlyselected;

    void createActions();
    void createMenus();

    void RefreshGraphWidget();

    QWidget* CreateControlsLayout();
    QWidget* CreateControlsEdges();
    QWidget* CreateControlsNodes();
    QWidget* CreateControlsCliques();
    QWidget* CreateControlsWidget();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *openAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    Params params;
    SodData soddata;
};

#endif
