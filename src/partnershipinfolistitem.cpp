#include "partnershipinfolistitem.h"
#include "partnershipinfo.h"
#include "relation.h"


PartnershipInfoListItem::PartnershipInfoListItem(QString item_key, bool lock_status, PartnershipInfo *info_card)
    : key(item_key), enable_form_editing(lock_status), owner(info_card)
{
    form_type = owner->content.items[key].form_type;

    layout = new QHBoxLayout();
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(layout);

    label = new QLabel;
    label->setText(key + ":");
    label->setFixedWidth(120);
    layout->addWidget(label);

    fillField(key, owner->content.items[key]);
    enableForm();

    checkbox = new QCheckBox;
    checkbox->setChecked(owner->content.items[key].show);
    checkbox->setEnabled(true);
    layout->addWidget(checkbox);
    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(changePartnershipInfoShowStatus(bool)));
}


void PartnershipInfoListItem::fillField(QString key, container_item item)
{
    if (form_type == "QLineEdit")
    {
        form_object.line_edit = new QLineEdit;
        form_object.line_edit->setText(item.value.toString());
        layout->addWidget(form_object.line_edit);
        connect(form_object.line_edit, SIGNAL(textEdited(QString)), this, SLOT(updatePartnershipInfo(QString)));
    }
    else if (form_type == "QDateEdit")
    {
        form_object.date_edit = new QDateEdit;
        form_object.date_edit->setDisplayFormat("dd.MM.yyyy");
        form_object.date_edit->setMinimumDate(QDate(100, 1, 1));
        form_object.date_edit->setMaximumDate(QDate(9999, 12, 31));
        form_object.date_edit->setDate(item.value.toDate());
        layout->addWidget(form_object.date_edit);
        layout->addStretch();
        connect(form_object.date_edit, SIGNAL(dateChanged(QDate)), this, SLOT(prepareDateAndUpdatePartnershipInfo(QDate)));
    }
    else if (form_type == "QComboBox")
    {
        form_object.box_edit = new QComboBox;
        if (key == "Type")
        {
            form_object.box_edit->addItem("");
            form_object.box_edit->addItem("Married");
        }
        form_object.box_edit->setCurrentText(item.value.toByteArray());
        layout->addWidget(form_object.box_edit);
        layout->addStretch();
        connect(form_object.box_edit, SIGNAL(currentTextChanged(QString)), this, SLOT(updatePartnershipInfo(QString)));
    }
    else if (form_type == "QTextEdit")
    {
        form_object.text_edit = new QTextEdit;
        form_object.text_edit->setText(item.value.toString());
        layout->addWidget(form_object.text_edit);
        connect(form_object.text_edit, SIGNAL(textEdited(QString)), this, SLOT(updatePartnershipInfo(QString)));
    }
}


void PartnershipInfoListItem::enableForm()
{
    if (form_type == "QLineEdit")
        form_object.line_edit->setEnabled(enable_form_editing);
    else if (form_type == "QDateEdit")
        form_object.date_edit->setEnabled(enable_form_editing);
    else if (form_type == "QComboBox")
        form_object.box_edit->setEnabled(enable_form_editing);
    else if (form_type == "QTextEdit")
        form_object.text_edit->setEnabled(enable_form_editing);

    if (enable_form_editing)
    {
        if (form_type == "QLineEdit")
            form_object.line_edit->setStyleSheet(styleSheet());
        else if (form_type == "QDateEdit")
            form_object.date_edit->setStyleSheet(styleSheet());
        else if (form_type == "QComboBox")
            form_object.box_edit->setStyleSheet(styleSheet());
        else if (form_type == "QTextEdit")
            form_object.date_edit->setStyleSheet(styleSheet());
    }
    else
    {
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


void PartnershipInfoListItem::enableFormEditing(bool lock_status)
{
    enable_form_editing = !lock_status;
    enableForm();
}


void PartnershipInfoListItem::enableEditing(bool ph_status)
{
    checkbox->setEnabled(!ph_status);
}


void PartnershipInfoListItem::updatePartnershipInfo(QString text)
{
    owner->updatePartnershipInfo(key, text);
}


void PartnershipInfoListItem::prepareDateAndUpdatePartnershipInfo(QDate date)
{
    updatePartnershipInfo(date.toString(Qt::DateFormat::ISODate));
}


void PartnershipInfoListItem::changePartnershipInfoShowStatus(bool status)
{
    owner->changeShowStatus(key, status);
}
