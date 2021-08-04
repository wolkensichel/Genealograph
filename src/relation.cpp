#include <QPen>
#include <QPainter>

#include "relation.h"
#include "treeobject.h"


Relation::Relation(TreeObject* treecard1, TreeObject* treecard2, QGraphicsScene *scene)
{
    tree_objects.append(treecard1);
    tree_objects.append(treecard2);

    setPen(QPen(Qt::black, 2));
    setZValue(-1);
    updatePosition();

    treecard1->addRelation(this);
    treecard2->addRelation(this);
    scene->addItem(this);
}


void Relation::updatePosition()
{
    QLineF line(tree_objects[0]->pos()+tree_objects[0]->boundingRect().center(), \
                tree_objects[1]->pos()+tree_objects[1]->boundingRect().center());
    setLine(line);
}
