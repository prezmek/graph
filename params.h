#ifndef PARAMS_H
#define PARAMS_H

#include "math.h"

const int NODE_step = 60;
const int NODE_margin = NODE_step;
const int NODE_count = 6;
const int NODE_minx = - (NODE_count * NODE_step);
const int NODE_maxx = NODE_count * NODE_step;
const int NODE_miny = - (NODE_count * NODE_step);
const int NODE_maxy = NODE_count * NODE_step;

const int WIN_SIZE_X = 1.5 * (abs(NODE_minx) + NODE_maxx);
const int WIN_SIZE_Y = 1.2 * (abs(NODE_miny) + NODE_maxy);

typedef enum {
    SQUARE = 1,
    CATEGORIES = 2
} TLayout;

#endif // PARAMS_H
