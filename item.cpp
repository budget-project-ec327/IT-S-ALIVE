#include "item.h"
// if youre adding a new type of data to be stores in an item obviously put it here
item::item(int i, QString n, float v, QString c)
{
    id = i;
    name = n;
    value = v;
    category = c;
}
