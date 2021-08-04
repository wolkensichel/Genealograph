#ifndef RELATION_H
#define RELATION_H


#include <QGraphicsLineItem>


class TreeObject;

class Relation : public QGraphicsLineItem
{
public:
    Relation(TreeObject*, TreeObject*, QGraphicsScene*);
    void updatePosition();

private:
    QGraphicsLineItem *line;
    QList<TreeObject *> tree_objects;
};

#endif // RELATION_H
