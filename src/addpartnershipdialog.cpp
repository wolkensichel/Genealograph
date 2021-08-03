#include <QGridLayout>

#include "addpartnershipdialog.h"
#include "mainwindow.h"
#include "worksheet.h"


AddPartnershipDialog::AddPartnershipDialog(QWidget *parent) : QDialog(parent)
{
    label_partner1 = new QLabel(tr("Partner 1:"));
    label_partner2 = new QLabel(tr("Partner 2:"));

    form_partner1 = new QComboBox;
    form_partner2 = new QComboBox;

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label_partner1, 0, 0);
    layout->addWidget(form_partner1, 0, 1);
    layout->addWidget(label_partner2, 1, 0);
    layout->addWidget(form_partner2, 1, 1);
    layout->addWidget(buttonbox, 3, 0, 1, 3);
    setLayout(layout);

    setWindowTitle("Add Partnership");
}


void AddPartnershipDialog::populateDropDownMenus(QList<TreeObject *> tree_objects)
{  
    form_partner1->addItem(tr("Select"));
    form_partner2->addItem(tr("Select"));

    foreach(TreeObject *obj, tree_objects)
    {
        form_partner1->addItem(obj->getName());
        form_partner2->addItem(obj->getName());
    }
}


int * AddPartnershipDialog::fetchFormInputs()
{
    static int partnership[2];
    partnership[0] = form_partner1->currentIndex()-1;
    partnership[1] = form_partner2->currentIndex()-1;

    return partnership;
}
