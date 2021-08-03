#include "treeobject.h"

TreeObject::TreeObject(person new_person)
{
    setRect(0, 0, 79, 100);
    setFlag(QGraphicsItem::ItemIsMovable);
    setBrush(Qt::lightGray);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);

    QWidget *widget = new QWidget();
    layout = new QVBoxLayout;
    widget->setLayout(layout);

    fillFields(new_person);

    proxy->setWidget(widget);
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