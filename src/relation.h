#ifndef RELATION_H
#define RELATION_H

#include <QGraphicsPathItem>
#include <QLabel>

#include "partnershipinfo.h"
#include "data.h"


class TreeObject;
class WorkSheet;

class Relation : public QGraphicsPathItem
{
public:
    Relation(TreeObject*, TreeObject*, PartnershipInfo*);
    Relation(Relation*, TreeObject*, descent);
    void fillInfoCard();
    void updatePosition();
    QList<TreeObject *>getTreeObjects();
    Relation* getParentsRelation();
    QList<Relation *>getDescentRelations();
    void removeDescentRelation();
    void removePartnershipRelation();

    quint16 id;

    QList<TreeObject *> tree_objects;
    Relation* parents = nullptr;
    QList<Relation *> descents;

    PartnershipInfo *info_card;
    descent info_descent;

    QPainterPath path;

private:
    enum Mode {Upper, Lower};
    quint32 computePartnershipYOffset(Relation*);
    quint32 computeCombinedEdgeParents(Relation*, Mode);
    quint32 computeHoriztonalBranchYPos(quint32, Mode);
};

#endif // RELATION_H
