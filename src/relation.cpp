#include <QPen>
#include <QPainter>

#include "relation.h"
#include "treeobject.h"
#include "worksheet.h"


Relation::Relation(TreeObject* treecard1, TreeObject* treecard2, PartnershipInfo *partnership_info)
{
    id = partnership_info->content.id;

    descents = QList<Relation *>();
    tree_objects = QList<TreeObject *>();
    tree_objects.append(treecard1);
    tree_objects.append(treecard2);

    info_card = partnership_info;
    info_card->connectPartnershipRelation(this);

    treecard1->addPartnershipRelation(this);
    treecard2->addPartnershipRelation(this);

    setPen(QPen(Qt::black, 1));
    setZValue(-2);
    updatePosition();
}


Relation::Relation(Relation* partnership, TreeObject* child, descent descent_info)
{
    id = descent_info.id;

    descents = QList<Relation *>();
    tree_objects = QList<TreeObject *>();
    tree_objects.append(child);
    parents = partnership;

    info_descent = descent_info;

    child->setDescentRelation(this);
    partnership->descents.append(this);

    setPen(QPen(Qt::black, 1));
    setZValue(-2);
    updatePosition();
}


void Relation::updatePosition()
{
    path.clear();

    if (parents == nullptr)
    {
        qint32 y_off = computePartnershipYOffset(this);

        path.moveTo(tree_objects[0]->pos().x() + tree_objects[0]->rect().center().x(),
                    tree_objects[0]->pos().y() + y_off - 2);
        path.lineTo(tree_objects[1]->pos().x() + tree_objects[1]->rect().center().x(),
                    tree_objects[1]->pos().y() + y_off - 2);

        if (info_card->content.items["Type"].value == "Married" ||
            info_card->content.items["Type"].value == "Divorced") {
            path.moveTo(tree_objects[1]->pos().x() + tree_objects[1]->rect().center().x(),
                        tree_objects[1]->pos().y() + y_off + 2);
            path.lineTo(tree_objects[0]->pos().x() + tree_objects[0]->rect().center().x(),
                        tree_objects[0]->pos().y() + y_off + 2);
        }

        info_card->updatePosition(path.boundingRect().center());
    }
    else
    {
        qint32 x_offset = tree_objects[0]->pos().x() + tree_objects[0]->boundingRect().center().x();
        qint32 y_offset = tree_objects[0]->pos().y() + tree_objects[0]->boundingRect().center().y();

        qint32 parents_edge = 0;
        qint32 y_hrz = 0;
        if (y_offset >= parents->boundingRect().center().y())
        {
            parents_edge = computeCombinedEdgeParents(parents, Lower);
            y_hrz = computeHoriztonalBranchYPos(parents_edge, Lower);
        }
        else
        {
            parents_edge = computeCombinedEdgeParents(parents, Upper);
            y_hrz = computeHoriztonalBranchYPos(parents_edge, Upper);
        }

        path.moveTo(parents->boundingRect().center());
        path.lineTo(QPointF(parents->boundingRect().center().x(), y_hrz));
        path.lineTo(QPointF(x_offset, y_hrz));
        path.lineTo(QPointF(x_offset, y_offset));
    }
    setPath(path);
}


quint32 Relation::computePartnershipYOffset(Relation* partnership)
{
    if (partnership->tree_objects[0]->widget->height() <= partnership->tree_objects[1]->widget->height())
        return partnership->tree_objects[0]->widget->height()/2;
    else
        return partnership->tree_objects[1]->widget->height()/2;
}


quint32 Relation::computeCombinedEdgeParents(Relation *partnership, Mode mode)
{
    quint32 edge = 0;
    if (mode == Lower) {
        int parent1_lower_edge = partnership->tree_objects[0]->pos().y()
                + partnership->tree_objects[0]->boundingRect().height();
        int parent2_lower_edge = partnership->tree_objects[1]->pos().y()
                + partnership->tree_objects[1]->boundingRect().height();

        if (parent1_lower_edge >= parent2_lower_edge)
            edge = parent1_lower_edge;
        else
            edge = parent2_lower_edge;
    }
    else {
        int parent1_upper_edge = partnership->tree_objects[0]->pos().y();
        int parent2_upper_edge = partnership->tree_objects[1]->pos().y();

        if (parent1_upper_edge <= parent2_upper_edge)
            edge = parent1_upper_edge;
        else
            edge = parent2_upper_edge;
    }
    return edge;
}


quint32 Relation::computeHoriztonalBranchYPos(quint32 edge, Mode mode)
{
    if (mode == Lower)
        edge += 40;
    else if (mode == Upper)
        edge -= 40;
    return edge;
}


QList<TreeObject *> Relation::getTreeObjects()
{
    return tree_objects;
}


Relation* Relation::getParentsRelation()
{
    return parents;
}


QList<Relation *> Relation::getDescentRelations()
{
    return descents;
}


void Relation::removeDescentRelation()
{
    tree_objects.first()->descent = nullptr;
    parents->descents.removeOne(this);
    qobject_cast<WorkSheet *>(scene())->removeDescentRelationFromMap(this);
    scene()->removeItem(this);
    delete this;
}


void Relation::removePartnershipRelation()
{
    tree_objects.first()->partnerships.removeOne(this);
    tree_objects.last()->partnerships.removeOne(this);
    foreach (Relation *descent, descents)
        descent->removeDescentRelation();
    info_card->removePartnershipInfo();
    qobject_cast<WorkSheet *>(scene())->removePartnershipRelationFromMap(this);
    scene()->removeItem(this);
    delete this;
}
