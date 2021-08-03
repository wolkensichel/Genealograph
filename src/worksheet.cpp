#include <QPainter>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QPushButton>

#include "worksheet.h"
#include "treeobject.h"


WorkSheet::WorkSheet(QMenu *menuCreate, QObject *parent)
    : QGraphicsScene(parent)
{
    current_mode = MoveCard;
    hline = nullptr;
    vline1 = nullptr;
    vline2 = nullptr;
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
}


void WorkSheet::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    QGraphicsScene::mousePressEvent(mouseEvent);
}


void WorkSheet::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (current_mode == AddCard) {
        //QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        //line->setLine(newLine);
    } else if (current_mode == MoveCard) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
