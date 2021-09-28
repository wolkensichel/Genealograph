#include <QCheckBox>
#include <QGroupBox>
#include <QDockWidget>
#include <QScrollArea>

#include "relationseditor.h"
#include "relation.h"
#include "relationslistitem.h"
#include "clicklabel.h"
#include "treeobject.h"
#include "worksheet.h"

RelationsEditor::RelationsEditor()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);

    QWidget *enable_edit = new QWidget;
    enable_edit->setFixedHeight(20);
    QLabel *label_enable_edit = new QLabel(tr("Lock Relations"));
    checkbox_enable_edit = new QCheckBox;
    checkbox_enable_edit->setEnabled(false);
    checkbox_enable_edit->setChecked(false);
    connect(checkbox_enable_edit, SIGNAL(clicked(bool)), this, SLOT(changeLockStatus(bool)));

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
    box_layout[id] = new QVBoxLayout;
    box_layout[id]->setContentsMargins(0, 0, 0, 0);
    box->setLayout(box_layout[id]);

    scrollarea[id] = new QScrollArea;
    scrollarea[id]->setWidgetResizable(true);
    box_layout[id]->addWidget(scrollarea[id]);

    widget_layout[id] = new QVBoxLayout;
    widget_layout[id]->setSizeConstraint(QLayout::SetMinAndMaxSize);
    widget_layout[id]->setContentsMargins(0, 0, 0, 0);
    widget_layout[id]->setAlignment(Qt::AlignTop);

    widget[id] = new QWidget;
    widget[id]->setLayout(widget_layout[id]);
    scrollarea[id]->setWidget(widget[id]);

    palette.setColor(QPalette::Window, Qt::white);
}


void RelationsEditor::populateGroupBox(QLayout* layout, QList<TreeObject *> treecards, Relationship type)
{
    RelationsListItem *items[treecards.size()];

    for(int i = 0; i < treecards.size(); i++)
    {
        items[i] = new RelationsListItem(current_owner, treecards[i], type, checkbox_enable_edit->isChecked());
        layout->addWidget(items[i]);
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
        cleanGroupBox(widget_layout[i]);
    checkbox_enable_edit->setEnabled(false);
    checkbox_enable_edit->setChecked(false);
}


void RelationsEditor::update(TreeObject* treecard)
{
    current_owner = treecard;
    checkbox_enable_edit->setEnabled(true);
    checkbox_enable_edit->setChecked(current_owner->content.relations_dock_lock);

    // set parents
    if(current_owner->descent != nullptr)
        populateGroupBox(widget_layout[0], current_owner->descent->parents->getTreeObjects(), Parents);

    QList<TreeObject *> partners = QList<TreeObject *>();
    QList<TreeObject *> children = QList<TreeObject *>();

    foreach(Relation *partnership, current_owner->partnerships)
    {
        // set partners
        if (partnership->tree_objects[0] == current_owner)
            partners.append(partnership->tree_objects[1]);
        else
            partners.append(partnership->tree_objects[0]);

        // set children
        foreach(Relation* child, partnership->descents)
            children.append(child->tree_objects[0]);
    }

    populateGroupBox(widget_layout[1], partners, Partner);
    populateGroupBox(widget_layout[2], children, Child);
}


void RelationsEditor::changeLockStatus(bool status)
{
    for (int i = 0; i <= 2; i++)
        foreach (RelationsListItem *item, widget[i]->findChildren<RelationsListItem *>())
            item->enableRemover(status);

    current_owner->updateRelationLockStatus(status);
}
