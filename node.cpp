
#include <iostream>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include "params.h"

Node::Node(GraphWidget *graphWidget, std::string category, std::string value, TLayout layout, QLabel* infoLabel, Params* params)
    : graph(graphWidget)
    , category(category)
    , value(value)
    , layout(layout)
    , infoLabel(infoLabel)
    , params(params)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 43 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 40, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    //painter->setPen(Qt::NoPen);
    //painter->setBrush(Qt::darkGray);
    //painter->drawEllipse(-7, -7, 20, 20);

    if(params->only_selected_mode && !selected)
        return;

    bool if_any_visible_edge = false;
    for(int i = 0; i < edgeList.size(); i++) {
        if(!params->IsBelowWeight(edgeList[i]->weight)) {
            if_any_visible_edge = true;
            break;
        }
    }
    if(!if_any_visible_edge)
        return;

    QRadialGradient gradient(-3, -3, 10);
    if(selected) {
        gradient.setColorAt(0, Qt::blue);
        gradient.setColorAt(1, Qt::darkBlue);
    } else {
        gradient.setColorAt(0, Qt::green);
        gradient.setColorAt(1, Qt::darkGreen);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

    if(layout == TLayout::SQUARE) {
        QFont font = painter->font();
        font.setPointSize(2);
        painter->setFont(font);
        painter->setPen(Qt::red);
        painter->drawText(-10, -1, QString::fromStdString(category));
        painter->setPen(Qt::yellow);
        painter->drawText(-10, 5, QString::fromStdString(value));
    }
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QString s = "NODE: [" + QString::fromStdString(category) + "] [" + QString::fromStdString(value) + "]" + "  Number of edges: " + QString::number(edgeList.size());
    infoLabel->setText(s);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    selected = !selected;
    update();
}
