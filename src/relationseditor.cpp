#include <QCheckBox>
#include <QGroupBox>
#include <QDockWidget>
#include <QScrollArea>

#include "relationseditor.h"
#include "relation.h"
#include "treeobject.h"

RelationsEditor::RelationsEditor(QDockWidget *dock)
{
    parent = dock;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);

    QWidget *enable_edit = new QWidget;
    enable_edit->setFixedHeight(20);
    QLabel *label_enable_edit = new QLabel(tr("Lock Relations"));
    QCheckBox *checkbox_enable_edit = new QCheckBox;

    hlayout->addStretch();
    hlayout->addWidget(label_enable_edit);
    hlayout->addWidget(checkbox_enable_edit);
    hlayout->setAlignment(label_enable_edit, Qt::AlignRight);
    hlayout->setAlignment(checkbox_enable_edit, Qt::AlignRight);
    enable_edit->setLayout(hlayout);

    groupbox_parents = new QGroupBox(tr("Parents:"));
    createGroupBox(groupbox_parents, 0);
    groupbox_partners = new QGroupBox(tr("Partners:"));
    createGroupBox(groupbox_partners, 1);
    groupbox_children = new QGroupBox(tr("Children:"));
    createGroupBox(groupbox_children, 2);

    layout->addWidget(enable_edit);
    layout->addWidget(groupbox_parents);
    layout->addWidget(groupbox_partners);
    layout->addWidget(groupbox_children);
    setLayout(layout);
}


void RelationsEditor::createGroupBox(QGroupBox *box, int id)
{
    QVBoxLayout *box_layout = new QVBoxLayout;
    box_layout->setContentsMargins(0, 0, 0, 0);
    box->setLayout(box_layout);

    QScrollArea *scrollarea = new QScrollArea;
    scrollarea->setWidgetResizable(true);
    box_layout->addWidget(scrollarea);

    QWidget *widget = new QWidget;
    scrollarea->setWidget(widget);

    widget_layout[id] = new QVBoxLayout;
    widget_layout[id]->setContentsMargins(0, 0, 0, 0);
    widget_layout[id]->setAlignment(Qt::AlignTop);
    widget->setLayout(widget_layout[id]);

    palette.setColor(QPalette::Window, Qt::white);
}


void RelationsEditor::populateGroupBox(QLayout* scroll_layout, QList<TreeObject *> treecards)
{
    QLabel *labels[treecards.size()];

    for(int i = 0; i < treecards.size(); i++)
    {
        labels[i] = new QLabel(treecards[i]->getName());
        labels[i]->setAutoFillBackground(true);
        labels[i]->setPalette(palette);
        labels[i]->setFixedHeight(40);
        scroll_layout->addWidget(labels[i]);
    }
}


void RelationsEditor::cleanGroupBox(QLayout* layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }
}


void RelationsEditor::clear()
{
    for (int i = 0; i <= 2; i++)
        cleanGroupBox(widget_layout[i]->layout());
}


void RelationsEditor::update(TreeObject* treecard, QList<Relation *> relations)
{
    // set parents
    if(relations.last()->parents != nullptr)
    {
        populateGroupBox(widget_layout[0]->layout(), relations.last()->parents->getTreeObjects());
        relations.removeLast();
    }

    QList<TreeObject *> partners = QList<TreeObject *>();
    QList<TreeObject *> children = QList<TreeObject *>();

    foreach(Relation *relation, relations)
    {
        // set partners
        if (relation->tree_objects[0] == treecard)
            partners.append(relation->tree_objects[1]);
        else
            partners.append(relation->tree_objects[0]);

        // set children
        foreach(Relation* child, relation->descents)
            children.append(child->tree_objects[0]);
    }

    populateGroupBox(widget_layout[1]->layout(), partners);
    populateGroupBox(widget_layout[2]->layout(), children);
}
