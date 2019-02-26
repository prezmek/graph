
#include <iostream>
#include "math.h"
#include <QtWidgets>

#include "mainwindow.h"
#include "graphwidget.h"
#include "params.h"
#include "node.h"

QWidget* MainWindow::CreateControlsLayout()
{
    QGroupBox* controlsGroup = new QGroupBox("Layout");
    QLabel* layoutLabel = new QLabel(tr("Select layout"));

    QComboBox *combo = new QComboBox;
    for(int l = TLayout::CATEGORIES; l < TLayout::LAST; l++)
        combo->addItem(params.GetLayoutName((TLayout)l));

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(layoutComboChanged(int)));

    QGridLayout* controlsLayout = new QGridLayout;
    controlsLayout->addWidget(layoutLabel, 0, 0);
    controlsLayout->addWidget(combo, 0, 1);
    controlsGroup->setLayout(controlsLayout);

    return controlsGroup;
}

QWidget* MainWindow::CreateControlsEdges()
{
    QGroupBox* controlsGroup = new QGroupBox("Edges");

    // Items

    QLabel* weightLabel = new QLabel(tr("Weight:"));

    QSpinBox* weightSpinBox = new QSpinBox;
    weightSpinBox->setRange(-20, 20);
    weightSpinBox->setSingleStep(1);

    QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setRange(-20, 20);
    slider->setSingleStep(1);
    slider->setTickInterval(5);

    // Connect Items

    connect(slider, SIGNAL(valueChanged(int)), weightSpinBox, SLOT(setValue(int)));
    connect(weightSpinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setEdgeWeightValue(int)));

    // Layout

    QGridLayout* controlsLayout = new QGridLayout;
    controlsLayout->addWidget(weightLabel, 0, 0);
    controlsLayout->addWidget(weightSpinBox, 0, 1);
    controlsLayout->addWidget(slider, 0, 2);

    controlsGroup->setLayout(controlsLayout);

    return controlsGroup;
}

QWidget* MainWindow::CreateControlsNodes()
{
    QGroupBox* controlsGroup = new QGroupBox("Nodes");

    // Items

    QLabel* weightLabel = new QLabel(tr("No of edges:"));

    QSpinBox* edgesSpinBox = new QSpinBox;
    edgesSpinBox->setRange(0, 200);
    edgesSpinBox->setSingleStep(1);
    edgesSpinBox->setValue(0);

    QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setRange(0, 200);
    slider->setSingleStep(1);
    slider->setTickInterval(10);
    slider->setValue(0);

    QPushButton* but_select = new QPushButton("SelectAll");
    QPushButton* but_unselect = new QPushButton("UnSelectAll");
    button_onlyselected = new QPushButton("ShowSelected");
    QPushButton* but_deleteSelected = new QPushButton("DeleteSelected");

    // Connect Items

    connect(slider, SIGNAL(valueChanged(int)), edgesSpinBox, SLOT(setValue(int)));
    connect(edgesSpinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setNoOfEdgesValue(int)));

    connect(but_select, SIGNAL (released()), this, SLOT (selectNodesAll()));
    connect(but_unselect, SIGNAL (released()), this, SLOT (unselectNodesAll()));
    connect(button_onlyselected, SIGNAL (released()), this, SLOT (onlyselectedNodes()));
    connect(but_deleteSelected, SIGNAL (released()), this, SLOT (deleteSelected()));

    // Layout

    QGridLayout* controlsLayout = new QGridLayout;
    controlsLayout->addWidget(weightLabel, 0, 0);
    controlsLayout->addWidget(edgesSpinBox, 0, 1);
    controlsLayout->addWidget(slider, 0, 2);
    controlsLayout->addWidget(but_select, 1, 0);
    controlsLayout->addWidget(but_unselect, 1, 1);
    controlsLayout->addWidget(button_onlyselected, 1, 2);
    controlsLayout->addWidget(but_deleteSelected, 1, 3);

    controlsGroup->setLayout(controlsLayout);

    return controlsGroup;
}

QWidget* MainWindow::CreateControlsCliques()
{
    QGroupBox* controlsGroup = new QGroupBox("Cliques");

    // Items

    QSpinBox* SpinBox = new QSpinBox;
    SpinBox->setRange(0, soddata.GetCliques().size() - 1);
    SpinBox->setSingleStep(1);
    SpinBox->setValue(1);

    QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setRange(0, soddata.GetCliques().size() - 1);
    slider->setSingleStep(1);
    slider->setTickInterval(1);
    slider->setValue(1);

    QPushButton* but_show = new QPushButton("Show Cliques");

    // Connect Items

    connect(slider, SIGNAL(valueChanged(int)), SpinBox, SLOT(setValue(int)));
    connect(SpinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setCliqueNo(int)));

    // Layout

    QGridLayout* controlsLayout = new QGridLayout;
    controlsLayout->addWidget(SpinBox, 0, 0);
    controlsLayout->addWidget(slider, 0, 1);
    controlsLayout->addWidget(but_show, 1, 0);

    controlsGroup->setLayout(controlsLayout);

    return controlsGroup;
}

QWidget* MainWindow::CreateControlsWidget()
{
    QWidget* widget = new QWidget;

    QHBoxLayout* layout = new QHBoxLayout;
    widget->setLayout(layout);

    layout->addWidget(CreateControlsLayout());
    layout->addWidget(CreateControlsEdges());
    layout->addWidget(CreateControlsNodes());
    layout->addWidget(CreateControlsCliques());

    return widget;
}

MainWindow::MainWindow(char* filename)
{
    // Read data from file

    soddata.ReadFile(filename);

    // Create main widget

    QWidget* widget = new QWidget;
    setCentralWidget(widget);

    // Layout widgets vertically

    QVBoxLayout* layout = new QVBoxLayout;
    widget->setLayout(layout);

    // Create buttons widget

    layout->addWidget(CreateControlsWidget());

    // Create info label

    infoLabel = new QLabel(tr("<b>Click</b> on node to see its parameters <b>Double click</b> on node to select it"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(infoLabel);

    // Create graph widget

    graph_widget = new GraphWidget(filename, &params, infoLabel, &soddata);
    layout->addWidget(graph_widget);

    // Create actions

    createActions();

    // Create MENU

    createMenus();

    // Main window

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("SOD Graph"));
    setMinimumSize(160, 160);
    resize(WIN_SIZE_X, WIN_SIZE_Y);
}

void MainWindow::RefreshGraphWidget()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier);
    QApplication::sendEvent(graph_widget, &event);
}

void MainWindow::setEdgeWeightValue(int value)
{
    params.edge_weight = value;
    RefreshGraphWidget();
}

void MainWindow::setNoOfEdgesValue(int value)
{
    params.no_of_edges = value;
    RefreshGraphWidget();
}

void MainWindow::selectNodesAll()
{
    for(int i = 0; i < soddata.GetNodes().size(); i++) {
        Node* n = (Node*)(graph_widget->items()[i]);
        n->selected = true;
    }
    RefreshGraphWidget();
}

void MainWindow::unselectNodesAll()
{
    for(int i = 0; i < soddata.GetNodes().size(); i++) {
        Node* n = (Node*)(graph_widget->items()[i]);
        n->selected = false;
    }
    RefreshGraphWidget();
}

void MainWindow::onlyselectedNodes()
{
    params.only_selected_mode = !params.only_selected_mode;
    if(params.only_selected_mode)
        button_onlyselected->setText("ShowAll");
    else
        button_onlyselected->setText("ShowSelected");
    RefreshGraphWidget();
}

void MainWindow::layoutComboChanged(int i)
{
    switch(i) {
    case 0: {
        QKeyEvent event(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier);
        QApplication::sendEvent(graph_widget, &event);
        break;
    }
    case 1: {
        QKeyEvent event(QEvent::KeyPress, Qt::Key_2, Qt::NoModifier);
        QApplication::sendEvent(graph_widget, &event);
        break;
    }
    case 2: {
        QKeyEvent event(QEvent::KeyPress, Qt::Key_3, Qt::NoModifier);
        QApplication::sendEvent(graph_widget, &event);
        break;
    }
    case 3: {
        QKeyEvent event(QEvent::KeyPress, Qt::Key_4, Qt::NoModifier);
        QApplication::sendEvent(graph_widget, &event);
        break;
    }
    }
}

void MainWindow::deleteSelected()
{
    for(int i = 0; i < soddata.GetNodes().size(); i++) {
        Node* n = (Node*)(graph_widget->items()[i]);
        if(n->selected)
            n->deleted = true;
    }
    RefreshGraphWidget();
}

void MainWindow::setCliqueNo(int value)
{
    auto& cl = soddata.GetCliques()[value];
    for(int i = 0; i < soddata.GetNodes().size(); i++) {
        Node* n = (Node*)(graph_widget->items()[i]);
        if(i == cl.v1 || i == cl.v2 || i == cl.v3)
            n->is_clique = true;
        else
            n->is_clique = false;
    }
    RefreshGraphWidget();
}

void MainWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("GRAPH"), tr("<b>GRAPH</b> by Przemek Pazio"));
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::createActions()
{
    // MENU actions

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

    // Widgets actions
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
