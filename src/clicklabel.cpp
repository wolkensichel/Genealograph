#include "clicklabel.h"
#include "treeobject.h"
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
                qobject_cast<WorkSheet *>(tree_objects[0]->scene())->removeParentsRelation(tree_objects[0]->descent);
                tree_objects[0]->descent = nullptr;
                break;
            case RelationsEditor::RelationsEditor::Partner:
                foreach (Relation* partnership, tree_objects[0]->partnerships) {
                    if (partnership->tree_objects[0] == tree_objects[1] ||
                        partnership->tree_objects[1] == tree_objects[1]) {
                        tree_objects[0]->partnerships.removeOne(partnership);
                        QList<Relation *> relation_list = {partnership};
                        qobject_cast<WorkSheet *>(tree_objects[0]->scene())->removePartnershipRelations(relation_list);
                    }
                }
                break;
            case RelationsEditor::RelationsEditor::Child:
                Relation *descent = tree_objects[1]->descent;
                descent->parents->descents.removeOne(tree_objects[1]->descent);
                QList<Relation *> relation_list = {descent};
                qobject_cast<WorkSheet *>(tree_objects[0]->scene())->removeChildRelations(relation_list);
                break;
        }
    }
    tree_objects[0]->updateRelationsEditor();
}
