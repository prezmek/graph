
#include <iostream>
#include <qmath.h>
#include <QPainter>

#include "edge.h"
#include "node.h"

Edge::Edge(Node *sourceNode, Node *destNode, Params* params, QLabel* infoLabel, int weight)
    : arrowSize(10)
    , infoLabel(infoLabel)
    , weight(weight <= 0 ? 1 : weight)
    , params(params)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(!source || !dest)
        return;

    if(!params->NoOfEdgesOK(source->edgeList.size()) && !params->NoOfEdgesOK(dest->edgeList.size()))
        return;

    if(params->only_selected_mode)
        if(!source->selected && !dest->selected)
            return;

    if(params->IsBelowWeight(weight))
        return;

    QLineF line(sourcePoint, destPoint);
    if(qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    int w = weight * 9;
    painter->setPen(QPen(QBrush(QColor(w, w, w)), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrows
/*
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
*/
}

void Edge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString s = "EDGE: [" + QString::fromStdString(source->category) + "] [" + QString::fromStdString(source->value) + "]" +
            " [" + QString::fromStdString(dest->category) + "] -> [" + QString::fromStdString(dest->value) + "]" +
            "  Weight: " + QString::number(weight);
    infoLabel->setText(s);
}
