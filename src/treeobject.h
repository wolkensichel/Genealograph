#ifndef TREEOBJECT_H
#define TREEOBJECT_H

#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"


class Relation;


class TreeObject : public QGraphicsRectItem
{
    QList<QString> bold_font = {"First Name", "Last Name"};
    QMap<QString, QString> dependant_labels = {
        {"Date of birth", "Place of birth"},
        {"Date of death", "Place of death"}
    };

public:
    TreeObject(person, QList<std::tuple<QString, QString, bool>>);
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

    QList<Relation *> partnerships;
    Relation* descent = nullptr;

    QWidget *widget;

private:
    void fillFields();
    void createLabel(QString&);
    QString getValue(bio_item&);
    QString appendices(QString&, QString);
    void toggleShowHide(QString&);
    void updateDependantBiographyLabel(QString&);
    QString convertDateFormatForDisplay(QString);

    QGraphicsProxyWidget* proxy;
    QVBoxLayout *layout;

    QList<std::tuple<QString, QString, bool>> form_types;
    QMap<QString, QLabel*> labels;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // TREEOBJECT_H
