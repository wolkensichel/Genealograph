#ifndef RELATIONSEDITOR_H
#define RELATIONSEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>

class Relation;
class TreeObject;
class QDockWidget;


class RelationsEditor : public QWidget
{
    Q_OBJECT

public:
    enum Relationship {Parents, Partner, Child};
    RelationsEditor(QDockWidget*);
    void update(TreeObject*, QList<Relation *>);
    void clear();

private:
    void createGroupBox(QGroupBox*, int);
    void populateGroupBox(QLayout*, TreeObject*, QList<TreeObject *>, Relationship);
    void cleanGroupBox(QLayout*);

    QGroupBox *groupbox_parents;
    QGroupBox *groupbox_partners;
    QGroupBox *groupbox_children;

    QVBoxLayout *widget_layout[3];
    QVBoxLayout *box_layout[3];
    QScrollArea *scrollarea[3];
    QWidget *widget[3];

    QDockWidget *parent;

    QPalette palette;
};

#endif // RELATIONSEDITOR_H
