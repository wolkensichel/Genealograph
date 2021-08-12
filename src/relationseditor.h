#ifndef RELATIONSEDITOR_H
#define RELATIONSEDITOR_H

#include <QWidget>
#include <QGroupBox>

class Relation;
class TreeObject;
class QDockWidget;


class RelationsEditor : public QWidget
{
    Q_OBJECT

public:
    RelationsEditor(QDockWidget*);
    void update(TreeObject*, QList<Relation *>);

private:
    void createGroupBox(QGroupBox*);
    void populateGroupBox(QLayout*, QList<TreeObject *>);
    void cleanGroupBox(QLayout*);

    QGroupBox *groupbox_parents;
    QGroupBox *groupbox_partners;
    QGroupBox *groupbox_children;

    QDockWidget *parent;
};

#endif // RELATIONSEDITOR_H
