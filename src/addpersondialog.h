#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

#include "data.h"

class AddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    AddPersonDialog(QWidget *parent = nullptr);
    person getData();

private:
    QLabel *label_firstname;
    QLabel *label_lastname;

    QLineEdit *field_firstname;
    QLineEdit *field_lastname;

    QDialogButtonBox *buttonbox;

};

#endif // ADDPERSONDIALOG_H