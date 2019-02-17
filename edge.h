#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode, int weight = 20);

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    int weight;
};

#endif // EDGE_H
