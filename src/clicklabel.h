#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>

#include "relationseditor.h"

class TreeObject;
class RelationsListItem;

class ClickLabel : public QLabel
{
    Q_OBJECT

public:
    enum Type {Content, Delete};
    ClickLabel(TreeObject*, TreeObject*, RelationsEditor::Relationship, bool, Type, RelationsListItem*);
    ClickLabel(TreeObject*, TreeObject*, bool);
    void enable(bool);

private:
    void adjustColor();
    bool enabled;
    int label_mode;

    RelationsEditor::Relationship relation_type;
    ClickLabel::Type label_type;
    RelationsListItem *owner;
    QList<TreeObject *> tree_objects;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CLICKLABEL_H
