#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QLabel>
#include "soddata.h"
#include "params.h"

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(char* filename, Params* params, QLabel *infoLabel, SodData* soddata, QWidget *parent = 0);

    void itemMoved();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    Params* params;
    QLabel *infoLabel;
    SodData* soddata;

    void SetItemsLayout(TLayout dm);
};

#endif // GRAPHWIDGET_H
