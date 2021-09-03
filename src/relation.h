#ifndef RELATION_H
#define RELATION_H


#include <QGraphicsPathItem>


class TreeObject;
class WorkSheet;

class Relation : public QGraphicsPathItem
{
public:
    Relation(TreeObject*, TreeObject*, QGraphicsScene*);
    Relation(Relation*, TreeObject*, QGraphicsScene*);
    void updatePosition();
    QList<TreeObject *>getTreeObjects();
    Relation* getParentsRelation();
    QList<Relation *>getDescentRelations();
    void removeDescentRelation();
    void removePartnershipRelation();

    QList<TreeObject *> tree_objects;
    Relation* parents = nullptr;
    QList<Relation *> descents;

private:
    enum Mode {Upper, Lower};
    quint32 computePartnershipYOffset(Relation*);
    quint32 computeCombinedEdgeParents(Relation*, Mode);
    quint32 computeHoriztonalBranchYPos(quint32, Mode);

    QPainterPath path;
};

#endif // RELATION_H
