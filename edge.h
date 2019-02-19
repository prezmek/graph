#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QLabel>
#include "params.h"

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode, Params* params, QLabel* infoLabel, int weight = 20);

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Node *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    Params* params;
    QLabel* infoLabel;

public:
    int weight;
};

#endif // EDGE_H
