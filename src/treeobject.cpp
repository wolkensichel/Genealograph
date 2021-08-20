#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "treeobject.h"
#include "relation.h"
#include "relationseditor.h"
#include "biographyeditor.h"

#include <QTextStream>


TreeObject::TreeObject(person new_person, BiographyEditor *biography_dock, RelationsEditor *relations_dock, quint16 current_id)
{
    biography_editor = biography_dock;
    relations_editor = relations_dock;
    bio = new_person;
    id = current_id;

    widget = new QWidget();
    layout = new QVBoxLayout;
    widget->setLayout(layout);

    fillFields(bio);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);

    setRect(2, 2, widget->width()-4, widget->height()-4);
    setBrush(Qt::lightGray);
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsSelectable);
}


void TreeObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /*QColor highlight_color;
    highlight_color.setRgb(30, 200, 255, 255);
    QPen pen(highlight_color);
    pen.setWidth(2);
    setPen(pen);*/
    setZValue(1);

    biography_editor->clear();
    biography_editor->update(bio);

    relations_editor->clear();
    QList<Relation *> relations = mergeRelations(partnerships, descent);
    if (!relations.isEmpty())
        relations_editor->update(this, relations);

    QGraphicsItem::mousePressEvent(event);
}


void TreeObject::fillFields(person person)
{
    first_name = new QLabel;
    first_name->setText(person.first_name);
    //first_name->setGeometry(0, 0, 100, 20);
    first_name->setFixedSize(100,20);
    layout->addWidget(first_name);

    last_name = new QLabel;
    last_name->setText(person.last_name);
    //last_name->setGeometry(0, 0, 100, 20);
    last_name->setFixedSize(100,20);
    layout->addWidget(last_name);
}


QString TreeObject::getName()
{
    return last_name->text() + ", " + first_name->text();
}


QList<Relation *> TreeObject::mergeRelations(QList<Relation *> partners, Relation *child)
{
    QList<Relation *> relations = QList<Relation *>();
    relations = partners;
    if (child != nullptr)
        relations.append(child);

    return relations;
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
    QList<Relation *> relations = mergeRelations(partnerships, descent);

    if (change == QGraphicsItem::ItemPositionChange && relations.isEmpty() == false)
    {
        for (Relation *relation : qAsConst(relations))
        {
            relation->updatePosition();
            for (Relation *child : relation->getDescentRelations())
                child->updatePosition();
        }
    }

    return value;
}
