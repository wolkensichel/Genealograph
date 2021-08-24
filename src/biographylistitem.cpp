#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "biographylistitem.h"


BiographyListItem::BiographyListItem(QString &text, QString caption)
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
    form->setDisabled(true);
    form->setStyleSheet("background: white; color: #565656");
    layout->addWidget(form);

    checkbox = new QCheckBox;
    layout->addWidget(checkbox);
}
