
#include "params.h"

Qt::Key Params::GetKeyFromLayout(TLayout l)
{
    if(l == SQUARE)
        return Qt::Key_1;
    else if(l == CATEGORIES)
        return Qt::Key_2;
    else if(l == CIRCLE)
        return Qt::Key_3;
    else if(l == COORDINATES)
        return Qt::Key_4;
}

bool Params::IsBelowWeight(int weight)
{
    if(edge_weight >= 0) {
        if((21 - edge_weight) < weight)
            return true;
    } else {
        if(weight < abs(edge_weight))
            return true;
    }
    return false;
}
