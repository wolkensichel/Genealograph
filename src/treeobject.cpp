#include <QPen>

#include "treeobject.h"

TreeObject::TreeObject(person new_person)
{
    setRect(0, 0, 79, 100);
    setFlags(QGraphicsItem::ItemIsMovable); //QGraphicsItem::ItemIsSelectable
    setBrush(Qt::lightGray);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);

    QWidget *widget = new QWidget();
    layout = new QVBoxLayout;
    widget->setLayout(layout);

    fillFields(new_person);

    proxy->setWidget(widget);
}


void TreeObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QColor highlight_color;
    highlight_color.setRgb(30, 200, 255, 255);
    QPen pen(highlight_color);
    pen.setWidth(2);
    setPen(pen);
    setZValue(1);

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
    return first_name->text();
}
