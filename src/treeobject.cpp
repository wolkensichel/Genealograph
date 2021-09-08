#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "treeobject.h"
#include "relation.h"
#include "worksheet.h"
#include "relationseditor.h"
#include "biographyeditor.h"


TreeObject::TreeObject(person new_person, QList<std::tuple<QString, QString, bool>> data_types)
    : form_types(data_types)
{
    individual = new_person;

    widget = new QWidget();
    layout = new QVBoxLayout;
    widget->setLayout(layout);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);

    fillFields();

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
    biography_editor->update(this, individual, form_types);
}


void TreeObject::updateRelationsEditor()
{
    RelationsEditor *relations_editor =
            qobject_cast<RelationsEditor *>(scene()->parent()->findChild<RelationsEditor *>());
    relations_editor->clear();
    relations_editor->update(this, partnerships, descent, individual.relations_dock_lock);
}


void TreeObject::fillFields()
{
    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = form_types.begin(); iter != form_types.end(); ++iter) {
        QString key = std::get<0>(*iter);

        QString value;
        if (individual.bio[key].form_type == "QDateEdit")
            value = convertDateFormatForDisplay(individual.bio[key].value.toString());
        else
            value = individual.bio[key].value.toString();

        QLabel *label = new QLabel(value);
        label->setFixedSize(100, 20);
        layout->addWidget(label);

        if (individual.bio[key].show)
            label->show();
        else
            label->hide();

        labels.insert(key, label);
    }
    updateBiographyPlaceholderStatus(individual.placeholder);
}


QString TreeObject::convertDateFormatForDisplay(QString value)
{
    QList<QString> value_components = value.split("-");
    value = value_components[2].remove(QRegularExpression("^[0]*")) + "." +
            value_components[1].remove(QRegularExpression("^[0]*")) + "." +
            value_components[0].remove(QRegularExpression("^[0]*"));
    return value;
}


QString TreeObject::getName()
{
    return individual.bio["Last Name"].value.toString() + ", " + individual.bio["First Name"].value.toString();
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
    individual.relations_dock_lock = status;
}


void TreeObject::updateBiographyLockStatus(bool status)
{
    individual.biography_dock_lock = status;
}


void TreeObject::updateBiography(QString key, QVariant datum)
{
    individual.bio[key].value = datum;

    QString value;
    if (individual.bio[key].form_type == "QDateEdit")
        value = convertDateFormatForDisplay(individual.bio[key].value.toString());
    else
        value = individual.bio[key].value.toString();

    labels[key]->setText(value);
}


void TreeObject::changeBioShowStatus(QString key, bool status)
{
    individual.bio[key].show = status;
    if (status)
        labels[key]->show();
    else
        labels[key]->hide();

    widget->adjustSize();
    setRect(-1, -1, widget->width()+1, widget->height()+1);

    updateRelations();
}


void TreeObject::updateBiographyPlaceholderStatus(bool status)
{
    individual.placeholder = status;

    QMap<QString, QLabel*>::const_iterator it;
    if (status)
        for (it = labels.cbegin(); it != labels.cend(); ++it)
            it.value()->hide();
    else
        for (it = labels.cbegin(); it != labels.cend(); ++it)
            if (individual.bio[it.key()].show)
                it.value()->show();
            else
                it.value()->hide();
}
