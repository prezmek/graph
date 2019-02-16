
#include <math.h>
#include <vector>
#include <QKeyEvent>

#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "params.h"


static std::pair<int, int> GetNextPos()
{
    static int x = NODE_minx;
    static int y = NODE_miny;

    auto p = std::make_pair(x, y);

    x += NODE_step;
    if(x > NODE_maxx) {
        x = NODE_minx;
        y += NODE_step;
    }

    return p;
}

GraphWidget::GraphWidget(char* filename, QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    // Read data from file

    soddata.ReadFile(filename);

    // create scene:

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(NODE_minx - NODE_margin, NODE_miny - NODE_margin, abs(NODE_minx) + NODE_maxx + 2 * NODE_margin, abs(NODE_miny) + NODE_maxy + 2 * NODE_margin);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(800, 500);
    setWindowTitle(tr("GRAPH"));

    // create nodes:

    std::vector<Node*> nodes;
    for(auto sodn : soddata.GetNodes()) {
        Node* n = new Node(this);
        nodes.push_back(n);
        auto p = GetNextPos();
        n->setPos(p.first, p.second);
        scene->addItem(n);
    }

    for(auto e : soddata.GetEdges()) {
        Node* n1 = nodes[e.l];
        Node* n2 = nodes[e.r];
        scene->addItem(new Edge(n1, n2));
    }
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // shadow:

    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // fill:

    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // text:
/*
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4, sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("You may:\n 1) click and drag the nodes around\n 2) zoom with the mouse wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(12);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
*/
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
