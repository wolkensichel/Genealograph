#include "clicklabel.h"
#include "treeobject.h"
#include "relation.h"
#include "worksheet.h"
#include "mainwindow.h"
#include "relationslistitem.h"


ClickLabel::ClickLabel(TreeObject *person, TreeObject *referenced_person, RelationsEditor::Relationship relation, bool clickable = false, Type type = Content, RelationsListItem *parent = nullptr)
    : enabled(clickable), relation_type(relation), label_type(type), owner(parent)
{
    tree_objects = QList<TreeObject *>();
    tree_objects.append(person);
    tree_objects.append(referenced_person);

    adjustColor();
}


void ClickLabel::adjustColor()
{
    if (enabled && label_type == Delete)
        setStyleSheet("color: red");
    else if (!enabled && label_type == Delete)
        setStyleSheet("color: grey");
}


void ClickLabel::enable(bool clickable)
{
    enabled = clickable;
    adjustColor();
}


void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || !enabled)
        return;

    if (label_type == Delete)
    {
        switch(relation_type)
        {
            case RelationsEditor::RelationsEditor::Parents:
                tree_objects.first()->descent->removeDescentRelation();
                break;
            case RelationsEditor::RelationsEditor::Partner:
                foreach (Relation *partnership, tree_objects.first()->partnerships)
                {
                    if (partnership->tree_objects.first() == tree_objects.last() ||
                        partnership->tree_objects.last() == tree_objects.last())
                        partnership->removePartnershipRelation();
                }
                break;
            case RelationsEditor::RelationsEditor::Child:
                tree_objects.last()->descent->removeDescentRelation();
                break;
        }
        tree_objects.first()->updateRelationsEditor();
    }
    else if (label_type == Content)
    {
        /*tree_objects.first()->scene()->clearSelection();
        tree_objects.first()->setSelected(true);
        tree_objects.first()->updateBiographyEditor();
        tree_objects.first()->updateRelationsEditor();*/
        foreach (Relation *partnership, tree_objects.first()->partnerships)
            if (partnership->tree_objects.first() == tree_objects.last() ||
                partnership->tree_objects.last() == tree_objects.last())
            {
                owner->showHidePartnershipInfo();
                break;
            }
    }
}
