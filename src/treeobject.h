#ifndef TREEOBJECT_H
#define TREEOBJECT_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"


class Relation;


class TreeObject : public QGraphicsRectItem
{
    QList<QString> keys = {"First Name", "Last Name"};

    QMap<QString, bool> default_show_status = {
        {"First Name", true},
        {"Last Name", true}
    };

public:
    TreeObject(person, quint16);
    QString getName();
    void addPartnershipRelation(Relation*);
    void setDescentRelation(Relation*);
    QList<Relation *> getPartnershipRelations();
    Relation* getDescentRelation();
    void updateRelations();
    void addLines();
    void updateBiographyEditor();
    void updateRelationsEditor();
    void removeTreeObject();
    void updateRelationLockStatus(bool);
    void updateBiographyLockStatus(bool);
    void updateBiography(QString, QVariant);
    void changeBioShowStatus(QString, bool);
    void updateBiographyPlaceholderStatus(bool);

    person individual;
    quint16 id;
    bool relations_dock_lock;
    bool biography_dock_lock;

    QList<Relation *> partnerships;
    Relation* descent = nullptr;

    QWidget *widget;

private:
    void fillFields(person);

    QGraphicsProxyWidget* proxy;
    QVBoxLayout *layout;

    QMap<QString, QLabel*> labels_map;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // TREEOBJECT_H
