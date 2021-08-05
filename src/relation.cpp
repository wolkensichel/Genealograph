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


Relation::Relation(Relation* partnership, TreeObject* child, QGraphicsScene *scene)
{
    tree_objects.append(child);
    parents = partnership;
    partnership->children.append(this);

    setPen(QPen(Qt::black, 2));
    setZValue(-1);
    updatePosition();

    child->addRelation(this);
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


QList<Relation *> Relation::getChildRelations()
{
    return children;
}
