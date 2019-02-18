#ifndef PARAMS_H
#define PARAMS_H

#include <qnamespace.h>
#include "math.h"

const int NODE_step = 60;
const int NODE_margin = NODE_step;
const int NODE_count = 6;
const int NODE_minx = - (NODE_count * NODE_step);
const int NODE_maxx = NODE_count * NODE_step;
const int NODE_miny = - (NODE_count * NODE_step);
const int NODE_maxy = NODE_count * NODE_step;

const int WIN_SIZE_X = (int)(1.5 * (abs(NODE_minx) + NODE_maxx));
const int WIN_SIZE_Y = (int)(1.2 * (abs(NODE_miny) + NODE_maxy));

typedef enum {
    SQUARE = 1,
    CATEGORIES = 2,
    REPAINT = 100
} TLayout;

class Params
{
public:
    void Reset() { edge_weight = 0; }

    int edge_weight {0};
    TLayout layout {CATEGORIES};

    Qt::Key GetKeyFromLayout(TLayout l);
};

#endif // PARAMS_H
