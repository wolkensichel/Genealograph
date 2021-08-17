#include <QPen>

#include "treeobject.h"
#include "relation.h"
#include "relationseditor.h"
#include "biographyeditor.h"

#include <QTextStream>


TreeObject::TreeObject(person new_person, BiographyEditor *biography_dock, RelationsEditor *relations_dock, QGraphicsScene *scene)
{
    biography_editor = biography_dock;
    relations_editor = relations_dock;

    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsGeometryChanges); //QGraphicsItem::ItemIsSelectable
    setRect(0, 0, 79, 99);
    setBrush(Qt::lightGray);

    proxy = new QGraphicsProxyWidget(this);
    //proxy->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);

    QWidget *widget = new QWidget();
    layout = new QVBoxLayout;
    widget->setLayout(layout);

    fillFields(new_person);

    proxy->setWidget(widget);

    setPos(scene->width()/2-40, scene->height()/2-50);
    scene->addItem(this);
}


void TreeObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QColor highlight_color;
    highlight_color.setRgb(30, 200, 255, 255);
    QPen pen(highlight_color);
    pen.setWidth(2);
    setPen(pen);
    setZValue(1);

    biography_editor->clear();
    biography_editor->update(this);

    relations_editor->clear();
    QList<Relation *> relations = mergeRelations(partnerships, descent);
    if (relations.isEmpty() == false)
        relations_editor->update(this, relations);

    QGraphicsItem::mousePressEvent(event);
}


void TreeObject::fillFields(person person)
{
    first_name = new QLabel;
    first_name->setText(person.firstname);
    //first_name->setGeometry(0, 0, 80, 25);
    layout->addWidget(first_name);

    last_name = new QLabel;
    last_name->setText(person.lastname);
    //last_name->setGeometry(0, 0, 80, 25);
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
