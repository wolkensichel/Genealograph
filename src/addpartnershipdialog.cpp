#include <QGridLayout>

#include "addpartnershipdialog.h"
#include "mainwindow.h"
#include <QObject>


AddPartnershipDialog::AddPartnershipDialog(QWidget *parent) : QDialog(parent)
{
    label_firstname = new QLabel(tr("First Name:"));
    label_lastname = new QLabel(tr("Last Name:"));

    form_firstname = new QLineEdit;
    form_lastname = new QLineEdit;

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label_firstname, 0, 0);
    layout->addWidget(form_firstname, 0, 1);
    layout->addWidget(label_lastname, 1, 0);
    layout->addWidget(form_lastname, 1, 1);
    layout->addWidget(buttonbox, 3, 0, 1, 3);
    setLayout(layout);

    setWindowTitle("Add Person");
}


person AddPartnershipDialog::getFormInputs()
{
    person new_person;
    //new_person.firstname = form_firstname->text();
    //new_person.lastname = form_lastname->text();

    new_person.firstname = "First Name";
    new_person.lastname = "Last Name";

    return new_person;
}