#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "biographylistitem.h"
#include "treeobject.h"


BiographyListItem::BiographyListItem(QVariant &text, QString caption, bool lock_status, bool show_status, TreeObject *owner)
    : enabled(!lock_status), current_owner(owner)
{
    layout = new QHBoxLayout();
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(layout);

    label = new QLabel;
    label->setText(caption+":");
    label->setFixedWidth(80);
    layout->addWidget(label);

    form = new QLineEdit;
    form->setText(text.toString());
    layout->addWidget(form);
    connect(form, SIGNAL(textEdited(QString)), this, SLOT(updateTreeObjectBio(QString)));

    adjustStyle();

    checkbox = new QCheckBox;
    checkbox->setChecked(show_status);
    layout->addWidget(checkbox);
    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(changeBioShowStatus(bool)));
}


void BiographyListItem::adjustStyle()
{
    form->setEnabled(enabled);
    if (enabled)
        form->setStyleSheet(styleSheet());
    else
        form->setStyleSheet("background: white; color: #565656");
}


void BiographyListItem::enableEditing(bool lock_status)
{
    enabled = !lock_status;
    adjustStyle();
}


void BiographyListItem::updateTreeObjectBio(QString text)
{
    QString caption = label->text().remove(label->text().length()-1, 1);
    current_owner->updateBiography(caption, text);
}


void BiographyListItem::changeBioShowStatus(bool status)
{
    QString caption = label->text().remove(label->text().length()-1, 1);
    current_owner->changeBioShowStatus(caption, status);
}
