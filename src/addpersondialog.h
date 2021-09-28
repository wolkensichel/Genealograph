#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
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

    QList<std::tuple<QString, QString, bool>> input_cfg;
    QMap<QString, input_form> forms;

    QFormLayout *layout;

    QDialogButtonBox *buttonbox;
};

#endif // ADDPERSONDIALOG_H
