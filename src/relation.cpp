#include <QPen>
#include <QPainter>

#include "relation.h"
#include "treeobject.h"
#include "worksheet.h"


Relation::Relation(TreeObject* treecard1, TreeObject* treecard2, QGraphicsScene *scene)
{
    descents = QList<Relation *>();
    tree_objects = QList<TreeObject *>();
    tree_objects.append(treecard1);
    tree_objects.append(treecard2);

    treecard1->addPartnershipRelation(this);
    treecard2->addPartnershipRelation(this);

    setPen(QPen(Qt::black, 1));
    setZValue(-1);
    updatePosition();

    scene->addItem(this);
}


Relation::Relation(Relation* partnership, TreeObject* child, QGraphicsScene *scene)
{
    descents = QList<Relation *>();
    tree_objects = QList<TreeObject *>();
    tree_objects.append(child);
    parents = partnership;

    child->setDescentRelation(this);
    partnership->descents.append(this);

    setPen(QPen(Qt::black, 1));
    setZValue(-1);
    updatePosition();

    scene->addItem(this);
}


void Relation::updatePosition()
{
    path.clear();
    if (parents == nullptr)
    {
        path.moveTo(tree_objects[0]->pos()+tree_objects[0]->boundingRect().center());
        path.lineTo(tree_objects[1]->pos()+tree_objects[1]->boundingRect().center());
    }
    else
    {
        qreal y_diff = tree_objects[0]->pos().y() + tree_objects[0]->boundingRect().center().y() - parents->boundingRect().center().y();
        qreal x_offset = tree_objects[0]->pos().x() + tree_objects[0]->boundingRect().center().x();

        path.moveTo(parents->boundingRect().center());
        path.lineTo(parents->boundingRect().center() + QPointF(0, y_diff/2));
        path.lineTo(QPointF(x_offset, parents->boundingRect().center().y() + y_diff/2));
        path.lineTo(QPointF(x_offset, parents->boundingRect().center().y() + y_diff));
    }
    setPath(path);
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
    qobject_cast<WorkSheet *>(scene())->removeDescentRelationFromList(this);
    scene()->removeItem(this);
    delete this;
}


void Relation::removePartnershipRelation()
{
    tree_objects.first()->partnerships.removeOne(this);
    tree_objects.last()->partnerships.removeOne(this);
    foreach (Relation *descent, descents)
        descent->removeDescentRelation();
    qobject_cast<WorkSheet *>(scene())->removePartnershipRelationFromList(this);
    scene()->removeItem(this);
    delete this;
}
