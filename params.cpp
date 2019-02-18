
#include "params.h"

Qt::Key Params::GetKeyFromLayout(TLayout l)
{
    if(l == SQUARE)
        return Qt::Key_1;
    else if(l == CATEGORIES)
        return Qt::Key_2;
}
