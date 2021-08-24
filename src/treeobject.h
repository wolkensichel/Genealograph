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
    TreeObject(person, BiographyEditor*, RelationsEditor*, quint16);
    QString getName();
    void addPartnershipRelation(Relation*);
    void setDescentRelation(Relation*);
    QList<Relation *> getPartnershipRelations();
    Relation* getDescentRelation();
    void addLines();
    person bio;
    quint16 id;

    QList<Relation *> partnerships;
    Relation* descent = nullptr;

private:
    void fillFields(person);
    QList<Relation *> mergeRelations(QList<Relation *>, Relation*);

    QGraphicsProxyWidget* proxy;
    QWidget *widget;
    QVBoxLayout *layout;

    QLabel* first_name;
    QLabel* last_name;

    BiographyEditor *biography_editor;
    RelationsEditor *relations_editor;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // TREEOBJECT_H
