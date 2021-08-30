#include "clicklabel.h"
#include "treeobject.h"
#include "relation.h"
#include "worksheet.h"

#include <QTextStream>
#include <iostream>


ClickLabel::ClickLabel(TreeObject *person, TreeObject *referenced_person, Mode mode, RelationsEditor::Relationship type)
{
    tree_objects = QList<TreeObject *>();
    tree_objects.append(person);
    tree_objects.append(referenced_person);
    label_mode = mode;
    relationship = type;
}


void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (label_mode == Reference) {
        switch(relationship) {
            case RelationsEditor::RelationsEditor::Parents:
                tree_objects[0]->descent->removeDescentRelation();
                break;
            case RelationsEditor::RelationsEditor::Partner:
                foreach (Relation *partnership, tree_objects[0]->partnerships)
                {
                    if (partnership->tree_objects[0] == tree_objects[1] ||
                        partnership->tree_objects[1] == tree_objects[1])
                        partnership->removePartnershipRelation();
                }
                break;
            case RelationsEditor::RelationsEditor::Child:
                tree_objects[1]->descent->removeDescentRelation();
                break;
        }
    }
    tree_objects[0]->updateRelationsEditor();
}
