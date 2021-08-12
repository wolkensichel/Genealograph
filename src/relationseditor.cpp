#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QDockWidget>

#include <QTextStream>
#include <iostream>

#include "relationseditor.h"
#include "relation.h"
#include "treeobject.h"

RelationsEditor::RelationsEditor(QDockWidget *dock)
{
    parent = dock;

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QLabel *label_enable_edit = new QLabel(tr("Lock Relations"));
    QCheckBox *checkbox_enable_edit = new QCheckBox;

    groupbox_parents = new QGroupBox(tr("Parents:"));
    createGroupBox(groupbox_parents);
    groupbox_partners = new QGroupBox(tr("Partners:"));
    createGroupBox(groupbox_partners);
    groupbox_children = new QGroupBox(tr("Children:"));
    createGroupBox(groupbox_children);

    layout->addWidget(label_enable_edit, 0, 0, 1, 9, Qt::AlignRight);
    layout->addWidget(checkbox_enable_edit, 0, 9, Qt::AlignRight);
    layout->addWidget(groupbox_parents, 1, 0, 2, 10, Qt::AlignTop);
    layout->addWidget(groupbox_partners, 3, 0, 2, 10, Qt::AlignTop);
    layout->addWidget(groupbox_children, 5, 0, 10, 10, Qt::AlignTop);
    setLayout(layout);

}


void RelationsEditor::createGroupBox(QGroupBox *box)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(2, 2, 2, 2);
    box->setLayout(layout);

    QLabel *editlabel_parents[2];
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);

    for (int i = 0; i < 2; ++i) {
        editlabel_parents[i] = new QLabel(tr("Person %1").arg(i + 1));
        editlabel_parents[i]->setAutoFillBackground(true);
        editlabel_parents[i]->setPalette(palette);
        layout->addWidget(editlabel_parents[i]);
    }
}


void RelationsEditor::populateGroupBox(QLayout* layout, QList<TreeObject *> treecards)
{
    QLabel *labels[treecards.size()];
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);

    for(int i = 0; i < treecards.size(); i++)
    {
        labels[i] = new QLabel(treecards[i]->getName());
        labels[i]->setAutoFillBackground(true);
        labels[i]->setPalette(palette);
        layout->addWidget(labels[i]);
    }
}


void RelationsEditor::cleanGroupBox(QLayout* layout)
{
    while(!layout->isEmpty())
    {
        delete layout->takeAt(0)->widget();
        delete layout->takeAt(0);
    }
}


void RelationsEditor::update(TreeObject* treecard, QList<Relation *> relations)
{
    parent->raise();
    QTextStream cout(stdout);

    cleanGroupBox(groupbox_parents->layout());
    cleanGroupBox(groupbox_partners->layout());
    cleanGroupBox(groupbox_children->layout());

    foreach(Relation *relation, relations)
    {
        // insert parents
        if (relation->parents != nullptr) {
            populateGroupBox(groupbox_parents->layout(), relation->parents->getTreeObjects());
        }

        // insert partners
        QList<TreeObject *> partners;
        if (relation->tree_objects.size() == 2)
        {
            if (relation->tree_objects[0] == treecard)
                partners.append(relation->tree_objects[1]);
            else
                partners.append(relation->tree_objects[0]);
        }
        populateGroupBox(groupbox_partners->layout(), partners);

        // insert children
        QList<TreeObject *> children;
        foreach(Relation* child, relation->children)
            children.append(child->tree_objects[0]);
        populateGroupBox(groupbox_children->layout(), children);
    }

}
