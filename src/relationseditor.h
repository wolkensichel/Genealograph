#ifndef RELATIONSEDITOR_H
#define RELATIONSEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>

class Relation;
class TreeObject;
class QDockWidget;


class RelationsEditor : public QWidget
{
    Q_OBJECT

public:
    RelationsEditor(QDockWidget*);
    void update(TreeObject*, QList<Relation *>);
    void clear();

private:
    void createGroupBox(QGroupBox*, int);
    void populateGroupBox(QLayout*, QList<TreeObject *>);
    void cleanGroupBox(QLayout*);

    QGroupBox *groupbox_parents;
    QGroupBox *groupbox_partners;
    QGroupBox *groupbox_children;

    QVBoxLayout *widget_layout[3];

    QDockWidget *parent;

    QPalette palette;
};

#endif // RELATIONSEDITOR_H
