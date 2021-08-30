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
    enum Mode {Default, MoveCard};
    quint16 id_counter;
    explicit WorkSheet(QMenu*, QObject *parent = nullptr);
    void setMode(Mode mode);
    void createTreeCard(person, quint16 = 0, QPointF = QPointF(0, 0));
    void createPartnershipRelation(int*);
    void createDescentRelation(int*);
    void createTreeFromFile(load_data&);
    void clean();

    void removeTreeObjectFromList(TreeObject*);
    void removePartnershipRelationFromList(Relation*);
    void removeDescentRelationFromList(Relation*);

    QList<TreeObject *> getTreeObjectList();
    QList<Relation *> getPartnershipRelationList();
    QList<Relation *> getDescentRelationList();

private:
    int getTreeObjectListPosition(quint16);
    int getPartnershipRelationListPosition(quint16, quint16);
    void outOfScopeCorrection();
    void snapToGrid();

    void keepItemOnScene(QGraphicsSceneMouseEvent*);
    void removeTreeObjectDialog(int);
    void removeTreeObject(int);

    QGraphicsItem *item;
    QList<QGraphicsItem *> item_list;
    QList<TreeObject *> tree_objects;
    QList<Relation *> partnership_relations;
    QList<Relation *> descent_relations;

    Mode active_mode;

    int grid_size;
    int current_pos_x;
    int current_pos_y;
    int rest_x;
    int rest_y;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // WORKSHEET_H
