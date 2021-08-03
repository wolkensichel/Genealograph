#include <QGridLayout>

#include "addpersondialog.h"
#include "mainwindow.h"
#include <QObject>


AddPersonDialog::AddPersonDialog(QWidget *parent) : QDialog(parent)
{
    label_firstname = new QLabel(tr("First Name:"));
    label_lastname = new QLabel(tr("Last Name:"));

    field_firstname = new QLineEdit;
    field_lastname = new QLineEdit;

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label_firstname, 0, 0);
    layout->addWidget(field_firstname, 0, 1);
    layout->addWidget(label_lastname, 1, 0);
    layout->addWidget(field_lastname, 1, 1);
    layout->addWidget(buttonbox, 3, 0, 1, 3);
    setLayout(layout);

    setWindowTitle("Add Person");
}


person AddPersonDialog::getData()
{
    person new_person;
    //new_person.firstname = field_firstname->text();
    //new_person.lastname = field_lastname->text();

    new_person.firstname = "First Name";
    new_person.lastname = "Last Name";

    return new_person;
}