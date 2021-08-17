#ifndef RELATION_H
#define RELATION_H


#include <QGraphicsPathItem>


class TreeObject;

class Relation : public QGraphicsPathItem
{
public:
    Relation(TreeObject*, TreeObject*, QGraphicsScene*);
    Relation(Relation*, TreeObject*, QGraphicsScene*);
    void updatePosition();
    QList<TreeObject *>getTreeObjects();
    Relation* getParentsRelation();
    QList<Relation *>getDescentRelations();

    QList<TreeObject *> tree_objects;
    Relation* parents = nullptr;
    QList<Relation *> descents;

private:
    QPainterPath path;
};

#endif // RELATION_H
