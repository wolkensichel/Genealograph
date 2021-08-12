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
    new_person.firstname = form_firstname->text();
    new_person.lastname = form_lastname->text();

    //new_person.firstname = "First Name";
    //new_person.lastname = "Last Name";

    return new_person;
}
