#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QGraphicsScene>
#include <QMenu>

#include "data.h"
#include "treeobject.h"
#include "relation.h"


class WorkSheet : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {AddCard, MoveCard};
    explicit WorkSheet(QMenu *menuCreate, QObject *parent = nullptr);
    void setMode(Mode mode);
    void createTreeCard(person);
    void createPartnershipRelation(int*);
    QList<TreeObject *> getTreeObjectList();

private:
    QList<TreeObject *> tree_objects;
    QList<Relation *> relations;
    Mode current_mode;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // WORKSHEET_H
