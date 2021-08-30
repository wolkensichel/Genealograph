#include <QFormLayout>

#include "setupsheetdialog.h"
#include "mainwindow.h"


SetupSheetDialog::SetupSheetDialog(quint16 min_width, quint16 min_height, QString title, QWidget *parent) : QDialog(parent)
{
    form_width = new QSpinBox;
    form_width->setRange(min_width, 65535);
    form_width->setSuffix("px");
    form_width->setSingleStep(10);
    form_width->setValue(min_width);
    form_height = new QSpinBox;
    form_height->setRange(min_height, 65535);
    form_height->setSuffix("px");
    form_height->setSingleStep(10);
    form_height->setValue(min_height);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Width:"), form_width);
    layout->addRow(tr("Height:"), form_height);
    layout->addRow(buttonbox);
    setLayout(layout);

    setWindowTitle(title);
}


sheet SetupSheetDialog::fetchFormInputs()
{
    sheet worksheet;
    worksheet.width = form_width->value();
    worksheet.height = form_height->value();

    return worksheet;
}
