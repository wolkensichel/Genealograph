#ifndef SETUPSHEETDIALOG_H
#define SETUPSHEETDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>

#include "data.h"

class SetupSheetDialog : public QDialog
{
    Q_OBJECT

public:
    SetupSheetDialog(QWidget *parent = nullptr);
    sheet fetchFormInputs();

private:
    QLabel *label_width;
    QLabel *label_height;

    QSpinBox *form_width;
    QSpinBox *form_height;

    QDialogButtonBox *buttonbox;

};

#endif // SETUPSHEETDIALOG_H