#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "relationslistitem.h"
#include "clicklabel.h"
#include "treeobject.h"

RelationsListItem::RelationsListItem(TreeObject *person, TreeObject *referenced_person, RelationsEditor::Relationship type)
{
    layout = new QHBoxLayout();
    //layout->setSizeConstraint(QLayout::SetMaximumSize);
    layout->setContentsMargins(2, 2, 2, 2);
    setLayout(layout);

    label = new ClickLabel(person, referenced_person, ClickLabel::Reference, type);
    label->setText(referenced_person->getName());
    layout->addWidget(label);

    remover = new QLabel("x");
    remover->setStyleSheet("color: red");
    remover->setFixedWidth(20);
    layout->addWidget(remover);
    layout->setAlignment(remover, Qt::AlignRight);

    setAutoFillBackground(true);
}
