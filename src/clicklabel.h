#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include "relationseditor.h"

class TreeObject;

class ClickLabel : public QLabel
{
    Q_OBJECT

public:
    ClickLabel(TreeObject*, TreeObject*, RelationsEditor::Relationship, bool);
    ClickLabel(TreeObject*, bool);
    void enable(bool);

private:
    void adjustColor();
    bool enabled;
    int label_mode;
    RelationsEditor::Relationship relationship;
    QList<TreeObject *> tree_objects;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CLICKLABEL_H
