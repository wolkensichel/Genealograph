#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "treeobject.h"
#include "relation.h"
#include "worksheet.h"
#include "relationseditor.h"
#include "biographyeditor.h"


TreeObject::TreeObject(person new_person, QList<std::tuple<QString, QString, bool>> input_cfg_persons)
    : input_cfg(input_cfg_persons)
{
    content = new_person;

    layout = new QVBoxLayout();

    widget = new QWidget();
    widget->setLayout(layout);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);

    fillFields();

    setRect(-1, -1, widget->width()+1, widget->height()+1);
    //setBrush(Qt::lightGray);
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsGeometryChanges|
             QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsFocusable);
}


void TreeObject::fillFields()
{
    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter)
    {
        QString key = std::get<0>(*iter);
        createLabel(key);
    }

    updateBiographyPlaceholderStatus(content.placeholder);
}


QString TreeObject::convertDateFormatForDisplay(QString value)
{
    QList<QString> value_components = value.split("-");
    value = value_components[2].remove(QRegularExpression("^[0]*")) + "." +
            value_components[1].remove(QRegularExpression("^[0]*")) + "." +
            value_components[0].remove(QRegularExpression("^[0]*"));
    return value;
}


void TreeObject::createLabel(QString &key)
{
    QString value = getValue(content.items[key]);
    if (!value.isEmpty())
        value = appendices(key, value);

    QLabel *label = new QLabel(value);
    //label->setFixedSize(198, 15);
    label->setAlignment(Qt::AlignCenter);
    if (bold_font.contains(key))
    {
        QFont font = label->font();
        font.setWeight(QFont::Bold);
        label->setFont(font);
    }
    layout->addWidget(label);

    labels.insert(key, label);

    toggleShowHide(key);
}


void TreeObject::toggleShowHide(QString &key)
{
    if (content.items[key].show)
        labels[key]->show();
    else
        labels[key]->hide();
}


QString TreeObject::getValue(container_item &item)
{
    QString value;
    if (item.form_type == "QDateEdit")
        value = convertDateFormatForDisplay(item.value.toString());
    else
        value = item.value.toString();
    return value;
}


QString TreeObject::appendices(QString &key, QString value)
{
    if (key == "Birth name")
        value = "née " + value;
    else if (key == "Date of birth")
        value = QString(QChar(0x002A)) + " " + value;
    else if (key == "Place of birth")
    {
        value = "in " + value;
        if (getValue(content.items["Date of birth"]).isEmpty())
            value = QString(QChar(0x002A)) + " " + value;
    }
    else if (key == "Date of death")
        value = QString(QChar(0x2020)) + " " + value;
    else if (key == "Place of death")
    {
        value = "in " + value;
        if (getValue(content.items["Date of death"]).isEmpty())
            value = QString(QChar(0x2020)) + " " + value;
    }

    return value;
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
    biography_editor->update(this);
}


void TreeObject::updateRelationsEditor()
{
    RelationsEditor *relations_editor =
            qobject_cast<RelationsEditor *>(scene()->parent()->findChild<RelationsEditor *>());
    relations_editor->clear();
    relations_editor->update(this);
}


QString TreeObject::getName()
{
    return content.items["Last name"].value.toString() + ", " + content.items["First name"].value.toString();
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

    for (Relation *partnership : qAsConst(partnerships))
    {
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
    content.relations_dock_lock = status;
}


void TreeObject::updateBiographyLockStatus(bool status)
{
    content.biography_dock_lock = status;
}


void TreeObject::updateBiography(QString key, QVariant datum)
{
    content.items[key].value = datum;

    QString value = getValue(content.items[key]);
    if (!value.isEmpty())
        value = appendices(key, value);
    labels[key]->setText(value);

    updateDependantLabel(key);

    widget->adjustSize();
    setRect(-1, -1, widget->width()+1, widget->height()+1);
}


void TreeObject::updateDependantLabel(QString &key)
{
    if (dependant_labels.contains(key))
    {
        key = dependant_labels[key];
        QString value = getValue(content.items[key]);
        if (!value.isEmpty())
        {
            value = appendices(key, value);
            labels[key]->setText(value);
        }
    }
}


void TreeObject::changeBioShowStatus(QString key, bool status)
{
    content.items[key].show = status;
    toggleShowHide(key);

    widget->adjustSize();
    setRect(-1, -1, widget->width()+1, widget->height()+1);

    updateRelations();
}


void TreeObject::updateBiographyPlaceholderStatus(bool status)
{
    content.placeholder = status;

    QMap<QString, QLabel*>::const_iterator it;
    if (status)
        for (it = labels.cbegin(); it != labels.cend(); ++it)
            it.value()->hide();
    else
        for (it = labels.cbegin(); it != labels.cend(); ++it)
            if (content.items[it.key()].show)
                it.value()->show();
            else
                it.value()->hide();
}
