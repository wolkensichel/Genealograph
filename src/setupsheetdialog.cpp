#include <QFormLayout>

#include "setupsheetdialog.h"
#include "mainwindow.h"


SetupSheetDialog::SetupSheetDialog(QWidget *parent) : QDialog(parent)
{
    form_width = new QSpinBox;
    form_width->setRange(1, 65535);
    form_width->setSuffix("px");
    form_height = new QSpinBox;
    form_height->setRange(1, 65535);
    form_height->setSuffix("px");

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Width:"), form_width);
    layout->addRow(tr("Height:"), form_height);
    layout->addRow(buttonbox);
    setLayout(layout);

    setWindowTitle("Setup Worksheet");
}


sheet SetupSheetDialog::fetchFormInputs()
{
    sheet worksheet;
    worksheet.width = form_width->value();
    worksheet.height = form_height->value();

    return worksheet;
}