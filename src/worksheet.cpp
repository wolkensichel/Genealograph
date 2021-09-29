#include <QPainter>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QWidget>

#include "worksheet.h"
#include "treeobject.h"
#include "relation.h"
#include "mainwindow.h"
#include "biographyeditor.h"
#include "relationseditor.h"
#include "partnershipinfo.h"


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


void WorkSheet::createTreeCard(person new_person, QList<std::tuple<QString, QString, bool>> input_cfg_persons)
{
    clearSelection();
    new_person.id = id_counter;
    new_person.biography_dock_lock = false;
    new_person.relations_dock_lock = true;
    new_person.placeholder = false;

    TreeObject *treecard = new TreeObject(new_person, input_cfg_persons);
    tree_objects.append(treecard);
    addItem(treecard);
    id_counter++;
    treecard->setSelected(true);
    setMode(InsertCard);
}


void WorkSheet::createTreeCardFromFile(person new_person, QList<std::tuple<QString, QString, bool>> input_cfg_persons)
{
    clearSelection();

    TreeObject *treecard = new TreeObject(new_person, input_cfg_persons);
    tree_objects.append(treecard);
    addItem(treecard);
    if (id_counter < new_person.id)
        id_counter = new_person.id+1;
    treecard->setPos(new_person.pos);
}


void WorkSheet::createPartnershipRelation(partnership new_partnership, QList<std::tuple<QString, QString, bool>> input_cfg_partnerships)
{
    TreeObject* partner1 = tree_objects.at(new_partnership.items["Partner 1"].value.toInt());
    TreeObject* partner2 = tree_objects.at(new_partnership.items["Partner 2"].value.toInt());

    PartnershipInfo *partnership_info = new PartnershipInfo(new_partnership, input_cfg_partnerships);
    addItem(partnership_info);
    Relation *relation = new Relation(partner1, partner2, partnership_info);
    addItem(relation);
    partnership_relations.append(relation);

    if (!selectedItems().isEmpty())
        parent()->findChild<RelationsEditor *>()->current_owner->updateRelationsEditor();
}


void WorkSheet::createDescentRelation(descent new_descent, QList<std::tuple<QString, QString, bool>> input_cfg_descents)
{
    Relation* partnership = partnership_relations.at(new_descent.items["Parents"].value.toInt());
    TreeObject* child = tree_objects.at(new_descent.items["Child"].value.toInt());

    Relation *relation = new Relation(partnership, child, new_descent);
    addItem(relation);
    descent_relations.append(relation);

    if (!selectedItems().isEmpty())
        parent()->findChild<RelationsEditor *>()->current_owner->updateRelationsEditor();
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

    if (mouseGrabberItem() == nullptr) {
        parent()->findChild<BiographyEditor *>()->clear();
        parent()->findChild<RelationsEditor *>()->clear();
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


void WorkSheet::createTreeFromFile(load_data &data, QList<QList<std::tuple<QString, QString, bool>>> input_cfg)
{
    QListIterator<person *> it_od(data.persons);
    while (it_od.hasNext())
        createTreeCardFromFile(*it_od.next(), input_cfg[0]);

    QListIterator<partnership *> it_ps(data.partnerships);
    while (it_ps.hasNext())
        createPartnershipRelation(*it_ps.next(), input_cfg[1]);

    QListIterator<descent *> it_d(data.descents);
    while (it_d.hasNext())
        createDescentRelation(*it_d.next(), input_cfg[2]);
}


void WorkSheet::clean()
{
    QList<TreeObject *> tree_objects_for_removal = tree_objects;
    removeTreeObject(tree_objects_for_removal);
}
