#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

#include "data.h"


class AddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    AddPersonDialog(QList<std::tuple<QString, QString, bool>>, QWidget *parent = nullptr);
    person fetchFormInputs();

private:
    void initializeInputs();

    QList<std::tuple<QString, QString, bool>> form_types;
    QMap<QString, input_form> forms;

    QFormLayout *layout;

    QLabel *label_firstname;
    QLabel *label_lastname;

    QLineEdit *form_firstname;
    QLineEdit *form_lastname;

    QDialogButtonBox *buttonbox;
};

#endif // ADDPERSONDIALOG_H
