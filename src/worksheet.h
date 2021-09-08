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
    enum Mode {Default, InsertCard};
    quint16 id_counter;
    explicit WorkSheet(QMenu*, QObject *parent = nullptr);
    void setMode(Mode mode);
    void createTreeCard(person, QList<std::tuple<QString, QString, bool>>);
    void createTreeCardFromFile(person, QList<std::tuple<QString, QString, bool>>);
    void createPartnershipRelation(int*);
    void createDescentRelation(int*);
    void createTreeFromFile(load_data&, QList<std::tuple<QString, QString, bool>>);
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
    void outOfScopeCorrection(QGraphicsItem*);
    void snapToGrid(QGraphicsItem*);

    void keepItemOnScene(QGraphicsSceneMouseEvent*);
    void removeTreeObjectDialog(QList<TreeObject *>);
    void removeTreeObject(QList<TreeObject *>);

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
