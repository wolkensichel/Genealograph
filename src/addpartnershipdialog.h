#ifndef ADDPARTNERSHIPDIALOG_H
#define ADDPARTNERSHIPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

#include "data.h"

class AddPartnershipDialog : public QDialog
{
    Q_OBJECT

public:
    AddPartnershipDialog(QWidget *parent = nullptr);
    person getFormInputs();

private:
    QLabel *label_firstname;
    QLabel *label_lastname;

    QLineEdit *form_firstname;
    QLineEdit *form_lastname;

    QDialogButtonBox *buttonbox;

};

#endif // ADDPARTNERSHIPDIALOG_H