#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "relationslistitem.h"
#include "clicklabel.h"
#include "treeobject.h"

RelationsListItem::RelationsListItem(TreeObject *person, TreeObject *referenced_person, RelationsEditor::Relationship type, bool lock_status)
{
    layout = new QHBoxLayout();
    //layout->setSizeConstraint(QLayout::SetMaximumSize);
    layout->setContentsMargins(2, 2, 2, 2);
    setLayout(layout);

    label = new ClickLabel(referenced_person, true);
    label->setText(referenced_person->getName());
    layout->addWidget(label);

    remover = new ClickLabel(person, referenced_person, type, !lock_status);
    remover->setText("x");
    remover->setFixedWidth(20);
    layout->addWidget(remover);
    layout->setAlignment(remover, Qt::AlignRight);

    setAutoFillBackground(true);
}


void RelationsListItem::enableRemover(bool lock_status)
{
    if (lock_status == true) {
        qobject_cast<ClickLabel *>(remover)->enable(false);
    }
    else {
        qobject_cast<ClickLabel *>(remover)->enable(true);
    }
}
