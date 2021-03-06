#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QLabel>

#include "params.h"

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget, std::string category, std::string value, TLayout layout, QLabel* infoLabel, Params* params);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QList<Edge *> edgeList;

private:
    QPointF newPos;
    GraphWidget *graph;

public:
    std::string category;
    std::string value;
    bool selected {false};
    bool deleted {false};
    bool is_clique {false};

private:
    TLayout layout;
    QLabel* infoLabel;
    Params* params;
};

#endif // NODE_H
