#include <QSizePolicy>
#include <QTextStream>
#include <iostream>

#include "biographylistitem.h"
#include "treeobject.h"


BiographyListItem::BiographyListItem(QString item_key, bio_item &item, bool lock_status, bool ph_status, TreeObject *treecard)
    : key(item_key), form_type(item.form_type), enable_form_editing(!lock_status), owner(treecard)
{
    layout = new QHBoxLayout();
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(layout);

    label = new QLabel;
    label->setText(key + ":");
    label->setFixedWidth(100);
    layout->addWidget(label);

    fillField(key, item);
    enableForm();
    layout->addStretch();

    checkbox = new QCheckBox;
    checkbox->setChecked(item.show);
    checkbox->setEnabled(!ph_status);
    layout->addWidget(checkbox);
    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(changeBioShowStatus(bool)));
}


void BiographyListItem::fillField(QString key, bio_item item)
{
    if (form_type == "QLineEdit") {
        form_object.line_edit = new QLineEdit;
        form_object.line_edit->setText(item.value.toString());
        layout->addWidget(form_object.line_edit);
        connect(form_object.line_edit, SIGNAL(textEdited(QString)), this, SLOT(updateTreeObjectBio(QString)));
    }
    else if (form_type == "QDateEdit") {
        form_object.date_edit = new QDateEdit;
        form_object.date_edit->setDisplayFormat("dd.MM.yyyy");
        form_object.date_edit->setMinimumDate(QDate(100, 1, 1));
        form_object.date_edit->setMaximumDate(QDate(9999, 12, 31));
        form_object.date_edit->setDate(item.value.toDate());
        layout->addWidget(form_object.date_edit);
        connect(form_object.date_edit, SIGNAL(dateChanged(QDate)), this, SLOT(prepareDateAndUpdateTreeObjectBio(QDate)));
    }
    else if (form_type == "QComboBox") {
        form_object.box_edit = new QComboBox;
        if (key == "Sex") {
            form_object.box_edit->addItem("");
            form_object.box_edit->addItem("M");
            form_object.box_edit->addItem("F");
            form_object.box_edit->addItem("X");
        }
        form_object.box_edit->setCurrentText(item.value.toByteArray());
        layout->addWidget(form_object.box_edit);
        connect(form_object.box_edit, SIGNAL(currentTextChanged(QString)), this, SLOT(updateTreeObjectBio(QString)));
    }
    else if (form_type == "QTextEdit") {
        form_object.text_edit = new QTextEdit;
        form_object.text_edit->setText(item.value.toString());
        layout->addWidget(form_object.text_edit);
        connect(form_object.text_edit, SIGNAL(textEdited(QString)), this, SLOT(updateTreeObjectBio(QString)));
    }
}


void BiographyListItem::enableForm()
{
    if (form_type == "QLineEdit")
        form_object.line_edit->setEnabled(enable_form_editing);
    else if (form_type == "QDateEdit")
        form_object.date_edit->setEnabled(enable_form_editing);
    else if (form_type == "QComboBox")
        form_object.box_edit->setEnabled(enable_form_editing);
    else if (form_type == "QTextEdit")
        form_object.text_edit->setEnabled(enable_form_editing);

    if (enable_form_editing) {
        if (form_type == "QLineEdit")
            form_object.line_edit->setStyleSheet(styleSheet());
        else if (form_type == "QDateEdit")
            form_object.date_edit->setStyleSheet(styleSheet());
        else if (form_type == "QComboBox")
            form_object.box_edit->setStyleSheet(styleSheet());
        else if (form_type == "QTextEdit")
            form_object.date_edit->setStyleSheet(styleSheet());
    }
    else {
        if (form_type == "QLineEdit")
            form_object.text_edit->setStyleSheet("background: white; color: #565656");
        else if (form_type == "QDateEdit")
            form_object.date_edit->setStyleSheet("background: white; color: #565656");
        else if (form_type == "QComboBox")
            form_object.box_edit->setStyleSheet("background: white; color: #565656");
        else if (form_type == "QTextEdit")
            form_object.date_edit->setStyleSheet("background: white; color: #565656");
    }
}


void BiographyListItem::enableFormEditing(bool lock_status)
{
    enable_form_editing = !lock_status;
    enableForm();
}


void BiographyListItem::updateTreeObjectBio(QString text)
{
    owner->updateBiography(key, text);
}


void BiographyListItem::prepareDateAndUpdateTreeObjectBio(QDate date)
{
    updateTreeObjectBio(date.toString(Qt::DateFormat::ISODate));
}


void BiographyListItem::changeBioShowStatus(bool status)
{
    owner->changeBioShowStatus(key, status);
}
