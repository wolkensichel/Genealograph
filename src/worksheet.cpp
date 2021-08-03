#include <QPainter>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QTextStream>
#include <iostream>

#include "worksheet.h"
#include "treeobject.h"


WorkSheet::WorkSheet(QMenu *menuCreate, QObject *parent)
    : QGraphicsScene(parent)
{
    current_mode = MoveCard;
}


void WorkSheet::setMode(Mode mode)
{
    current_mode = mode;
}


void WorkSheet::createTreeCard(person new_person)
{
    TreeObject *treecard = new TreeObject(new_person);
    treecard->setPos(this->width()/2-40, this->height()/2-50);
    addItem(treecard);
    setMode(MoveCard);
    tree_objects.append(treecard);
}


void WorkSheet::createPartnershipConnection(int* partnership)
{
    // get tree objects
    if (*partnership != -1 and *(partnership+1) != -1)
    {
        //TreeObject *treecard_partner1 = tree_objects.at(*partnership);
        //TreeObject *treecard_partner2 = tree_objects.at(*(partnership+1));

        //line_partner = new QGraphicsItem(QLineF);
    }
    // draw single hline
}


void WorkSheet::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    foreach (TreeObject *treecard, tree_objects)
    {
        pen = QPen(Qt::black);
        treecard->setPen(pen);
        treecard->setZValue(0);
    }

    QGraphicsScene::mousePressEvent(event);
}


void WorkSheet::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (current_mode == AddCard) {
        //QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        //line->setLine(newLine);
    } else if (current_mode == MoveCard) {
        QGraphicsScene::mouseMoveEvent(event);
    }
}


QList<TreeObject *> WorkSheet::getTreeObjectList()
{
    return tree_objects;
}
