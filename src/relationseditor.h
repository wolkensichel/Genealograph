#ifndef RELATIONSEDITOR_H
#define RELATIONSEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QCheckBox>

class Relation;
class TreeObject;
class QDockWidget;


class RelationsEditor : public QWidget
{
    Q_OBJECT

public:
    enum Relationship {Parents, Partner, Child};
    RelationsEditor();
    void update(TreeObject*, QList<Relation *>, Relation*, bool);
    void clear();

private:
    void createGroupBox(QGroupBox*, int);
    void populateGroupBox(QLayout*, QList<TreeObject *>, Relationship);
    void cleanGroupBox(QLayout*);

    QGroupBox *groupbox_parents;
    QGroupBox *groupbox_partners;
    QGroupBox *groupbox_children;

    QVBoxLayout *widget_layout[3];
    QVBoxLayout *box_layout[3];
    QScrollArea *scrollarea[3];
    QWidget *widget[3];

    TreeObject *current_owner = nullptr;
    QCheckBox *checkbox_enable_edit;

    QPalette palette;

public slots:
    void changeLockStatus(bool);
};

#endif // RELATIONSEDITOR_H
