#include <QFormLayout>

#include "addpersondialog.h"
#include "mainwindow.h"


AddPersonDialog::AddPersonDialog(QList<std::tuple<QString, QString, bool>> input_cfg_persons, QWidget *parent)
    : QDialog(parent), input_cfg(input_cfg_persons)
{
    layout = new QFormLayout;

    initializeInputs();

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addRow(buttonbox);

    setLayout(layout);
    setWindowTitle("Add Person");
}


void AddPersonDialog::initializeInputs()
{
    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter) {
        QString key = std::get<0>(*iter);
        QString form_type = std::get<1>(*iter);

        input_form form_object;
        if (form_type == "QLineEdit") {
            form_object.line_edit = new QLineEdit;
            layout->addRow(key + ":", form_object.line_edit);
        }
        else if (form_type == "QDateEdit") {
            // use QSpinBoxes instead?
            form_object.date_edit = new QDateEdit;
            form_object.date_edit->setDisplayFormat("dd.MM.yyyy");
            form_object.date_edit->setMinimumDate(QDate(100, 1, 1));
            form_object.date_edit->setMaximumDate(QDate(9999, 12, 31));
            if (key == "Date of death")
                form_object.date_edit->setDate(QDate(9999, 12, 31));
            layout->addRow(key + ":", form_object.date_edit);
        }
        else if (form_type == "QComboBox") {
            form_object.box_edit = new QComboBox;
            if (key == "Sex") {
                form_object.box_edit->addItem("");
                form_object.box_edit->addItem("M");
                form_object.box_edit->addItem("F");
                form_object.box_edit->addItem("X");
            }
            layout->addRow(key + ":", form_object.box_edit);
        }
        else if (form_type == "QTextEdit") {
            form_object.text_edit = new QTextEdit;
            layout->addRow(key + ":", form_object.text_edit);
        }
        forms.insert(key, form_object);
    }
}


person AddPersonDialog::fetchFormInputs()
{
    person new_person;
    new_person.id = 0;

    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter) {
        QString key = std::get<0>(*iter);
        QString form = std::get<1>(*iter);

        container_item item;
        item.form_type = std::get<1>(*iter);
        item.show = std::get<2>(*iter);

        if (form == "QLineEdit")
            item.value = forms[key].line_edit->text();
        else if (form == "QDateEdit")
            item.value = forms[key].date_edit->date();
        else if (form == "QComboBox")
            item.value = forms[key].box_edit->currentText();
        else if (form == "QTextEdit")
            item.value = forms[key].text_edit->toPlainText();

        new_person.items.insert(key, item);
    }

    return new_person;
}
