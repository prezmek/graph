
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
#include <QKeyEvent>

#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "params.h"

static int x_square = NODE_minx;
static int y_square = NODE_miny;

static std::pair<int, int> GetNextPos()
{
    auto p = std::make_pair(x_square, y_square);
    x_square += NODE_step;
    if(x_square > NODE_maxx) {
        x_square = NODE_minx;
        y_square += NODE_step;
    }
    return p;
}

static void GetPointsOnCircle(int r, int no, int xp, int yp, std::vector<int>& x, std::vector<int>& y)
{
    for(int i = 0; i < no; i++) {
        double t = i * 2 * 3.14159 / no;
        x.push_back(r * cos(t) + xp);
        y.push_back(r * sin(t) + yp);
    }
}
void GraphWidget::SetItemsLayout(TLayout layout)
{
    // calculate

    if(layout == TLayout::CATEGORIES) {
        params->layout = layout;

        for(auto& i : items()) {
            i->hide();
        }

        struct Item {
            int i;  // item number
            std::string value;
            int x,y;
        };

        std::map<std::string, std::vector<Item>> categories;

        for(int i = 0; i < soddata.GetNodes().size(); i++) {
            auto& n = soddata.GetNodes()[i];
            Item it;
            it.i = i;
            it.value = n.value;
            categories[n.category].push_back(it);
        }

#if 0
        for(auto& m : categories) {
            std::cout << "==>" << m.first << ":" << std::endl;
            for(auto& v : m.second) {
                std::cout << v.value << " ";
            }
            std::cout << std::endl;
        }
#endif
        int cats = categories.size();
        std::vector<int> x;
        std::vector<int> y;
        GetPointsOnCircle(330, cats, 0, 0, x, y);
        int c = 0;
        for(auto& m : categories) {
            int no_nodes = m.second.size();
            std::vector<int> xx;
            std::vector<int> yy;
            GetPointsOnCircle(80, no_nodes, x[c], y[c], xx, yy);
            for(int i = 0; i < no_nodes; i++) {
                items()[m.second[i].i]->setPos(xx[i], yy[i]);
            }
            c++;
        }

        for(auto& it : items()) {
            it->show();
        }
    } else if (layout == TLayout::SQUARE) {
        params->layout = layout;

        x_square = NODE_minx;
        y_square = NODE_miny;
        for(auto& it : items()) {
            it->hide();
        }
        for(int i = 0; i < soddata.GetNodes().size(); i++) {
            auto p = GetNextPos();
            items()[i]->setPos(p.first, p.second);
        }
        for(auto& it : items()) {
            it->show();
        }
    } else {

        for(auto& it : items()) {
            it->update();
        }

    }

}

GraphWidget::GraphWidget(char* filename, Params* params, QLabel* infoLabel, QWidget *parent)
    : QGraphicsView(parent)
    , timerId(0)
    , params(params)
    , infoLabel(infoLabel)
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
        Node* n = new Node(this, sodn.category, sodn.value, TLayout::SQUARE, infoLabel);
        nodes.push_back(n);
        scene->addItem(n);
    }

    SetItemsLayout(params->layout);

    for(auto e : soddata.GetEdges()) {
        Node* n1 = nodes[e.l];
        Node* n2 = nodes[e.r];
        scene->addItem(new Edge(n1, n2, params, infoLabel, e.w));
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
    case Qt::Key_0:
        SetItemsLayout(TLayout::REPAINT);
        break;
    case Qt::Key_1:
        SetItemsLayout(TLayout::SQUARE);
        break;
    case Qt::Key_2:
        SetItemsLayout(TLayout::CATEGORIES);
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

/*    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);*/
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
