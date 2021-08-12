#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QGraphicsScene>
#include <QMenu>

#include "data.h"
#include "treeobject.h"
#include "relation.h"


class BiographyEditor;
class RelationsEditor;


class WorkSheet : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {AddCard, MoveCard};
    explicit WorkSheet(QMenu*, BiographyEditor*, RelationsEditor*, QObject *parent = nullptr);
    void setMode(Mode mode);
    void createTreeCard(person);
    void createPartnershipRelation(int*);
    void createDescentRelation(int*);
    QList<TreeObject *> getTreeObjectList();
    QList<Relation *> getPartnershipRelationList();

private:
    QList<TreeObject *> tree_objects;
    QList<Relation *> partnership_relations;
    QList<Relation *> descent_relations;
    Mode current_mode;
    BiographyEditor *biography_editor;
    RelationsEditor *relations_editor;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // WORKSHEET_H
