#include <QPainter>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QWidget>
#include <QTextStream>
#include <iostream>

#include "worksheet.h"
#include "treeobject.h"
#include "relation.h"
#include "mainwindow.h"


WorkSheet::WorkSheet(QMenu *menuCreate, QObject *parent)
    : QGraphicsScene(parent)
{
    id_counter = 1;
    grid_size = 20;
    active_mode = Default;
}


void WorkSheet::setMode(Mode mode)
{
    active_mode = mode;
}


void WorkSheet::createTreeCard(person new_person, quint16 id, QPointF pos)
{
    clearSelection();
    if (id == quint16(0))
    {
        TreeObject *treecard = new TreeObject(new_person, id_counter);
        tree_objects.append(treecard);
        addItem(treecard);
        id_counter++;
        treecard->setSelected(true);
        setMode(InsertCard);
    }
    else
    {
        TreeObject *treecard = new TreeObject(new_person, id);
        tree_objects.append(treecard);
        addItem(treecard);
        if (id_counter < id)
            id_counter = ++id;
        treecard->setPos(pos);
    }
}


void WorkSheet::createPartnershipRelation(int* partnership)
{
    if (*partnership != -1 and *(partnership+1) != -1) // 3rd parameter for marriage/open partnership ...
    {
        TreeObject* partner1 = tree_objects.at(*partnership);
        TreeObject* partner2 = tree_objects.at(*(partnership+1));

        Relation *relation = new Relation(partner1, partner2, this);
        addItem(relation);
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
        addItem(relation);
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


void WorkSheet::outOfScopeCorrection(QGraphicsItem *item)
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


void WorkSheet::snapToGrid(QGraphicsItem *item)
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

    if (!selectedItems().isEmpty())
    {
        foreach (QGraphicsItem *item, selectedItems())
        {
            current_pos_x = static_cast<int>(item->pos().x());
            current_pos_y = static_cast<int>(item->pos().y());

            outOfScopeCorrection(item);
            snapToGrid(item);
        }

        foreach (Relation *partnership, partnership_relations)
            partnership->updatePosition();
        foreach (Relation *descent, descent_relations)
            descent->updatePosition();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}


void WorkSheet::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (active_mode == InsertCard)
        keepItemOnScene(event);

    QGraphicsScene::mouseMoveEvent(event);
}


void WorkSheet::keepItemOnScene(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = selectedItems().first();

    if (event->scenePos().x() > width()-item->boundingRect().width()/2)
        item->setX(width()-item->boundingRect().width());
    else if (event->scenePos().x() < item->boundingRect().width()/2)
        item->setX(0);
    else
        item->setX(event->scenePos().x()-item->boundingRect().width()/2);

    if (event->scenePos().y() > height()-item->boundingRect().height()/2)
        item->setY(height()-item->boundingRect().height());
    else if (event->scenePos().y() < item->boundingRect().height()/2)
        item->setY(0);
    else
        item->setY(event->scenePos().y()-item->boundingRect().height()/2);
}


void WorkSheet::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete && !selectedItems().isEmpty())
    {
        QList<TreeObject *> tree_objects_for_removal;
        foreach (QGraphicsItem *item, selectedItems())
            if (item->type() == TreeObject::Type)
                tree_objects_for_removal.append(qgraphicsitem_cast<TreeObject *>(item));
        removeTreeObjectDialog(tree_objects_for_removal);
    }
    else if (event->key() == Qt::Key_A)
    {
        foreach (TreeObject *treecard, tree_objects)
            treecard->setSelected(true);
    }
    else if (event->key() == Qt::Key_Escape)
    {
        clearSelection();
        // send signal to break removeTreeObjectDialog loop
    }

    QGraphicsScene::keyPressEvent(event);
}


void WorkSheet::removeTreeObjectDialog(QList<TreeObject *> objects)
{
    QString names;
    foreach (TreeObject *object, objects)
        names += object->getName() + "\n";

    QMessageBox msg_box;
    msg_box.setText(tr("Delete Tree Card"));
    msg_box.setInformativeText(tr("Are you sure that you want to remove\n")+ names +tr("and all connected relations?"));
    msg_box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg_box.setDefaultButton(QMessageBox::Cancel);

    if (msg_box.exec() == QMessageBox::Ok)
        removeTreeObject(objects);
}


void WorkSheet::removeTreeObject(QList<TreeObject *> objects)
{
    foreach (TreeObject *object, objects)
    {
        if (object->descent != nullptr)
            object->descent->removeDescentRelation();
        foreach(Relation *partnership, object->partnerships)
            partnership->removePartnershipRelation();
        object->removeTreeObject();
    }
}


void WorkSheet::removeTreeObjectFromList(TreeObject *tree_object)
{
    tree_objects.removeOne(tree_object);
}


void WorkSheet::removePartnershipRelationFromList(Relation *partnership)
{
    partnership_relations.removeOne(partnership);
}


void WorkSheet::removeDescentRelationFromList(Relation *descent)
{
    descent_relations.removeOne(descent);
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
        reference_ids[0] = getPartnershipRelationListPosition(current_object->id_parent1,
                                                              current_object->id_parent2);
        reference_ids[1] = getTreeObjectListPosition(current_object->id_child);
        createDescentRelation(reference_ids);
    }
}


int WorkSheet::getTreeObjectListPosition(quint16 id)
{
    auto predicate = [id](TreeObject *tree_object) { return tree_object->id == id; };
    return std::find_if(tree_objects.begin(), tree_objects.end(), predicate)
            - tree_objects.begin();
}


int WorkSheet::getPartnershipRelationListPosition(quint16 id_parent1, quint16 id_parent2)
{
    auto predicate = [id_parent1, id_parent2](Relation *partnership) {
        return (partnership->tree_objects.first()->id == id_parent1
                && partnership->tree_objects.last()->id == id_parent2);
        };
    return std::find_if(partnership_relations.begin(), partnership_relations.end(), predicate)
            - partnership_relations.begin();
}


void WorkSheet::changeLockStatus(bool status)
{

}


void WorkSheet::clean()
{
    QList<TreeObject *> tree_objects_for_removal = tree_objects;
    removeTreeObject(tree_objects_for_removal);
}
