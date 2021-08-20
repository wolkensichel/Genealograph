#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "listlabel.h"


ListLabel::ListLabel(QString &text, QString caption)
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


void ListLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTextStream cout(stdout);
    cout << "this is some text\n";
}
