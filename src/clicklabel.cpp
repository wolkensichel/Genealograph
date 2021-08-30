#include "clicklabel.h"
#include "treeobject.h"
#include "relation.h"
#include "worksheet.h"
#include "mainwindow.h"

#include <QTextStream>
#include <iostream>


ClickLabel::ClickLabel(TreeObject *person, TreeObject *referenced_person, RelationsEditor::Relationship type)
{
    tree_objects = QList<TreeObject *>();
    tree_objects.append(person);
    tree_objects.append(referenced_person);
    relationship = type;
}


ClickLabel::ClickLabel(TreeObject *referenced_person)
{
    tree_objects = QList<TreeObject *>();
    tree_objects.append(referenced_person);
}


void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (tree_objects.length() == 2)
    {
        switch(relationship)
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
    else if (tree_objects.length() == 1)
    {
        tree_objects.first()->scene()->clearSelection();
        tree_objects.first()->setSelected(true);
        tree_objects.first()->updateBiographyEditor();
        tree_objects.first()->updateRelationsEditor();
    }
}
