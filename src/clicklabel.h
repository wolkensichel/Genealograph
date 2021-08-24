#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include "relationseditor.h"

class TreeObject;

class ClickLabel : public QLabel
{
public:
    enum Mode {Reference, Remover};
    ClickLabel(TreeObject*, TreeObject*, Mode, RelationsEditor::Relationship);

private:
    int label_mode;
    RelationsEditor::Relationship relationship;
    QList<TreeObject *> tree_objects;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CLICKLABEL_H
