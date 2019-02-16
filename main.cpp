
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QTime>

#include "mainwindow.h"
#include "graphwidget.h"
#include "soddata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(argc != 2) {
        QMessageBox::information(nullptr, "ERROR", "Incorrect number of input parameters\nUsage: graph file_with_data");
        exit(1);
    }

#if 0
    GraphWidget *widget = new GraphWidget(argv[1]);
    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);
    mainWindow.show();
#else
    MainWindow mainWindow(argv[1]);
    mainWindow.show();
#endif

    return a.exec();
}
