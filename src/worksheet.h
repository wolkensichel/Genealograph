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
    void createPartnershipRelation(partnership, QList<std::tuple<QString, QString, bool>>);
    void createDescentRelation(descent, QList<std::tuple<QString, QString, bool>>);
    void createTreeFromFile(load_data&, QList<QList<std::tuple<QString, QString, bool>>>);
    void clean();

    void removeTreeObjectFromMap(TreeObject*);
    void removePartnershipRelationFromMap(Relation*);
    void removeDescentRelationFromMap(Relation*);

    QMap<quint16, TreeObject *> getTreeObjectMap();
    QMap<quint16, Relation *> getPartnershipRelationMap();
    QMap<quint16, Relation *> getDescentRelationMap();

private:
    void outOfScopeCorrection(QGraphicsItem*);
    void snapToGrid(QGraphicsItem*);

    void keepItemOnScene(QGraphicsSceneMouseEvent*);
    void removeTreeObjectDialog(QList<quint16>);
    void removeTreeObjects(QList<quint16>);

    QList<QGraphicsItem *> item_list;
    QMap<quint16, TreeObject *> tree_objects;
    QMap<quint16, Relation *> partnership_relations;
    QMap<quint16, Relation *> descent_relations;

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
