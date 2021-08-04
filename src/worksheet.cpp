#include <QPainter>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QTextStream>
#include <iostream>

#include "worksheet.h"
#include "treeobject.h"
#include "relation.h"


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
    TreeObject *treecard = new TreeObject(new_person, this);
    tree_objects.append(treecard);
    //setMode(MoveCard);
}


void WorkSheet::createPartnershipRelation(int* partnership)
{
    if (*partnership != -1 and *(partnership+1) != -1)
    {
        TreeObject* partner1 = tree_objects.at(*partnership);
        TreeObject* partner2 = tree_objects.at(*(partnership+1));

        Relation *relation = new Relation(partner1, partner2, this);
        relations.append(relation);
        //setMode(MoveCard);
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
