#include <QFormLayout>

#include "addpersondialog.h"
#include "mainwindow.h"


AddPersonDialog::AddPersonDialog(QWidget *parent) : QDialog(parent)
{
    form_firstname = new QLineEdit;
    form_lastname = new QLineEdit;

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("First Name:"), form_firstname);
    layout->addRow(tr("Last Name:"), form_lastname);
    layout->addRow(buttonbox);
    setLayout(layout);

    setWindowTitle("Add Person");
}


person AddPersonDialog::fetchFormInputs()
{
    person new_person;
    //new_person.first_name = form_firstname->text();
    //new_person.last_name = form_lastname->text();

    QString key = "First Name";
    new_person.bio.insert(key, form_firstname->text());
    key = "Last Name";
    new_person.bio.insert(key, form_lastname->text());

    return new_person;
}
