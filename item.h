#ifndef ITEM_H
#define ITEM_H
#include <QString>

class item
{
public:
    // if youre adding a new type of data to be stores in an item obviously put it here
    int id;
    QString name,
        category;
    float value;
    item(int i, QString n, float v, QString category);
};

#endif // ITEM_H
