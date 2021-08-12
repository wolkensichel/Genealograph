#ifndef TREEOBJECT_H
#define TREEOBJECT_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"


class Relation;
class DescentRelation;
class RelationsEditor;
class BiographyEditor;


class TreeObject : public QGraphicsRectItem
{
public:
    TreeObject(person, BiographyEditor*, RelationsEditor*, QGraphicsScene*);
    QString getName();
    void addRelation(Relation*);

private:
    void fillFields(person);

    QGraphicsProxyWidget* proxy;
    QVBoxLayout *layout;

    QLabel* first_name;
    QLabel* last_name;

    QList<Relation *> relations;
    DescentRelation *descent_relation = nullptr;

    BiographyEditor *biography_editor;
    RelationsEditor *relations_editor;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // TREEOBJECT_H
