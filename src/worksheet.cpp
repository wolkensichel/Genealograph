#include <QPainter>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QWidget>
#include <QTextStream>
#include <iostream>

#include "worksheet.h"
#include "treeobject.h"
#include "relation.h"


WorkSheet::WorkSheet(QMenu *menuCreate, BiographyEditor *biography_dock, RelationsEditor *relations_dock, QObject *parent)
    : QGraphicsScene(parent)
{
    id_counter = 1;
    grid_size = 20;
    current_mode = Default;
    biography_editor = biography_dock;
    relations_editor = relations_dock;
}


void WorkSheet::setMode(Mode mode)
{
    current_mode = mode;
}


void WorkSheet::createTreeCard(person new_person, quint16 id, QPointF pos)
{
    if (id == quint16(0))
    {
        TreeObject *treecard = new TreeObject(new_person, biography_editor, relations_editor, id_counter);
        tree_objects.append(treecard);
        addItem(treecard);
        id_counter++;
        setMode(NewCard);
    }
    else
    {
        TreeObject *treecard = new TreeObject(new_person, biography_editor, relations_editor, id);
        tree_objects.append(treecard);
        addItem(treecard);
        treecard->setPos(pos);
        if (id_counter < id)
            id_counter = ++id;
    }
}


void WorkSheet::createPartnershipRelation(int* partnership)
{
    if (*partnership != -1 and *(partnership+1) != -1) // 3rd parameter for marriage/open partnership ...
    {
        TreeObject* partner1 = tree_objects.at(*partnership);
        TreeObject* partner2 = tree_objects.at(*(partnership+1));

        Relation *relation = new Relation(partner1, partner2, this);
        partnership_relations.append(relation);
    }
}


void WorkSheet::createDescentRelation(int* descent)
{
    if (*descent != -1 and *(descent+1) != -1)
    {
        Relation* partnership = partnership_relations.at(*descent);
        TreeObject* child = tree_objects.at(*(descent+1));

        Relation *relation = new Relation(partnership, child, this);
        descent_relations.append(relation);
    }
}


void WorkSheet::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    foreach (TreeObject *treecard, tree_objects)
    {
        treecard->setPen(QPen(Qt::black, 1));
        treecard->setZValue(0);
    }

    QGraphicsScene::mousePressEvent(event);
}


void WorkSheet::outOfScopeCorrection()
{
    if (current_pos_x < 0)
        current_pos_x = 0;
    else if (current_pos_x > width()-item->boundingRect().width())
        current_pos_x = width()-item->boundingRect().width();

    if (current_pos_y < 0)
        current_pos_y = 0;
    else if (current_pos_y > height()-item->boundingRect().height())
        current_pos_y = height()-item->boundingRect().height();
}


void WorkSheet::snapToGrid()
{
    rest_x = current_pos_x % grid_size;
    rest_y = current_pos_y % grid_size;

    if (rest_x <= grid_size/2)
        item->setX(current_pos_x-rest_x);
    else if (rest_x > grid_size/2)
        item->setX(current_pos_x+grid_size-rest_x);

    if (rest_y <= grid_size/2)
        item->setY(current_pos_y-rest_y);
    else if (rest_y > grid_size/2)
        item->setY(current_pos_y+grid_size-rest_y);
}


void WorkSheet::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setMode(Default);

    if (!selectedItems().isEmpty()) {
        item = selectedItems()[0];

        current_pos_x = static_cast<int>(item->pos().x());
        current_pos_y = static_cast<int>(item->pos().y());

        outOfScopeCorrection();
        snapToGrid();

        foreach (Relation *partnership, partnership_relations)
            partnership->updatePosition();
        foreach (Relation *descent, descent_relations)
            descent->updatePosition();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}


void WorkSheet::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (current_mode == NewCard)
        tree_objects.last()->setPos(event->scenePos()-QPointF(tree_objects.last()->boundingRect().width()/2,
                                                              tree_objects.last()->boundingRect().height()/2));
    QGraphicsScene::mouseMoveEvent(event);
}


QList<TreeObject *> WorkSheet::getTreeObjectList()
{
    return tree_objects;
}


QList<Relation *> WorkSheet::getPartnershipRelationList()
{
    return partnership_relations;
}


QList<Relation *> WorkSheet::getDescentRelationList()
{
    return descent_relations;
}


void WorkSheet::createTreeFromFile(load_data &data)
{
    QListIterator<object_data *> it_od(data.objects);
    while (it_od.hasNext())
    {
        object_data *current_object = it_od.next();
        createTreeCard(current_object->bio, current_object->id, current_object->pos);
    }

    int reference_ids[2];
    QListIterator<partnership_data *> it_ps(data.partnerships);
    while (it_ps.hasNext())
    {
        partnership_data *current_object = it_ps.next();
        reference_ids[0] = getTreeObjectListPosition(current_object->id_partner1);
        reference_ids[1] = getTreeObjectListPosition(current_object->id_partner2);
        createPartnershipRelation(reference_ids);
    }

    QListIterator<descent_data *> it_d(data.descents);
    while (it_d.hasNext())
    {
        descent_data *current_object = it_d.next();
        reference_ids[0] = getPartnershipRelationListPosition(
                    current_object->id_parent1, current_object->id_parent2);
        reference_ids[1] = getTreeObjectListPosition(current_object->id_child);
        createDescentRelation(reference_ids);
    }
}


int WorkSheet::getTreeObjectListPosition(quint16 id)
{
    auto predicate = [id](TreeObject *tree_object) { return tree_object->id == id; };
    return std::find_if(std::begin(tree_objects), std::end(tree_objects), predicate)
            - std::begin(tree_objects);

}


int WorkSheet::getPartnershipRelationListPosition(quint16 id_parent1, quint16 id_parent2)
{
    auto predicate = [id_parent1, id_parent2](Relation *partnership) {
        return (partnership->tree_objects.first()->id == id_parent1
                && partnership->tree_objects.last()->id == id_parent2);
        };
    return std::find_if(std::begin(partnership_relations), std::end(partnership_relations), predicate)
            - std::begin(partnership_relations);
}


void WorkSheet::clean()
{
    tree_objects.clear();
    partnership_relations.clear();
    descent_relations.clear();
    this->clear();
}
