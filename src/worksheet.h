#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QGraphicsScene>
#include <QMenu>

#include "data.h"
#include "treeobject.h"

class WorkSheet : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {AddCard, MoveCard};
    explicit WorkSheet(QMenu *menuCreate, QObject *parent = nullptr);
    void setMode(Mode mode);
    void createTreeCard(person);
    void createPartnershipConnection(int*);
    QList<TreeObject *> getTreeObjectList();

private:
    QList<TreeObject *> tree_objects;
    Mode current_mode;
    QPen pen;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // WORKSHEET_H
