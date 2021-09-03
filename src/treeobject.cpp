#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "treeobject.h"
#include "relation.h"
#include "worksheet.h"
#include "relationseditor.h"
#include "biographyeditor.h"


TreeObject::TreeObject(person new_person, quint16 current_id)
{
    individual = new_person;
    id = current_id;
    relations_dock_lock = true;
    biography_dock_lock = true;

    widget = new QWidget();
    layout = new QVBoxLayout;
    widget->setLayout(layout);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);

    fillFields(individual);

    setRect(-1, -1, widget->width()+1, widget->height()+1);
    setBrush(Qt::lightGray);
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsGeometryChanges|
             QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsFocusable);
}


void TreeObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /*QColor highlight_color;
    highlight_color.setRgb(30, 200, 255, 255);
    QPen pen(highlight_color);
    pen.setWidth(2);
    setPen(pen);*/
    setZValue(1);

    updateBiographyEditor();
    updateRelationsEditor();

    QGraphicsItem::mousePressEvent(event);
}


void TreeObject::updateBiographyEditor()
{
    BiographyEditor *biography_editor =
            qobject_cast<BiographyEditor *>(scene()->parent()->findChild<BiographyEditor *>());
    biography_editor->clear();
    biography_editor->update(this, individual, biography_dock_lock, labels_map);
}


void TreeObject::updateRelationsEditor()
{
    RelationsEditor *relations_editor =
            qobject_cast<RelationsEditor *>(scene()->parent()->findChild<RelationsEditor *>());
    relations_editor->clear();
    relations_editor->update(this, partnerships, descent, relations_dock_lock);
}


void TreeObject::fillFields(person individual)
{
    foreach (QString key, keys) {
        QLabel *label = new QLabel(individual.bio[key].toString());
        label->setFixedSize(100,20);
        layout->addWidget(label);

        label_config label_param;
        label_param.object = label;
        if (default_show_status.contains(key)) {
            bool status = default_show_status[key];
            label_param.show = status;
            if (status)
               label->show();
            else
               label->hide();
        }
        else {
            label_param.show = false;
            label->hide();
        }
        labels_map.insert(key, label_param);
    }
}


QString TreeObject::getName()
{
    return individual.bio["Last Name"].toString() + ", " + individual.bio["First Name"].toString();
}


void TreeObject::addPartnershipRelation(Relation* partnership)
{
    partnerships.append(partnership);
}


void TreeObject::setDescentRelation(Relation* child)
{
    descent = child;
}


QVariant TreeObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
        updateRelations();

    return value;
}


void TreeObject::updateRelations()
{
    if (descent != nullptr)
        descent->updatePosition();

    for (Relation *partnership : qAsConst(partnerships)) {
        partnership->updatePosition();
        for (Relation *child : partnership->getDescentRelations())
            child->updatePosition();
    }
}


void TreeObject::removeTreeObject()
{
    qobject_cast<WorkSheet *>(scene())->removeTreeObjectFromList(this);
    scene()->removeItem(this);
    delete this;
}


void TreeObject::updateRelationLockStatus(bool status)
{
    relations_dock_lock = status;
}


void TreeObject::updateBiographyLockStatus(bool status)
{
    biography_dock_lock = status;
}


void TreeObject::updateBiography(QString key, QVariant value)
{
    individual.bio[key] = value;
    QLabel *label = labels_map[key].object;
    label->setText(individual.bio[key].toString());
}


void TreeObject::changeBioShowStatus(QString key, bool status)
{
    labels_map[key].show = status;
    if (status)
        labels_map[key].object->show();
    else
        labels_map[key].object->hide();

    widget->adjustSize();
    setRect(-1, -1, widget->width()+1, widget->height()+1);

    updateRelations();
}
