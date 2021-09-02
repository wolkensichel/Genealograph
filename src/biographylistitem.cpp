#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "biographylistitem.h"


BiographyListItem::BiographyListItem(QString &text, QString caption, bool lock_status)
    : enabled(!lock_status)
{
    layout = new QHBoxLayout();
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(layout);

    label = new QLabel;
    label->setText(caption);
    label->setFixedWidth(80);
    layout->addWidget(label);

    form = new QLineEdit;
    form->setText(text);
    layout->addWidget(form);

    adjustStyle();

    checkbox = new QCheckBox;
    layout->addWidget(checkbox);
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
