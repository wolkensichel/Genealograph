#include <QFormLayout>

#include "addpartnershipdialog.h"
#include "mainwindow.h"
#include "worksheet.h"


AddPartnershipDialog::AddPartnershipDialog(QWidget *parent) : QDialog(parent)
{
    form_partner1 = new QComboBox();
    form_partner2 = new QComboBox();

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Partner 1:"), form_partner1);
    layout->addRow(tr("Partner 2:"), form_partner2);
    layout->addRow(buttonbox);
    setLayout(layout);

    setWindowTitle("Add Partnership");
}


void AddPartnershipDialog::populateDropDownMenus(QList<TreeObject *> tree_objects)
{  
    form_partner1->addItem(tr("Select"));
    form_partner2->addItem(tr("Select"));

    foreach(TreeObject *treecard, tree_objects)
    {
        form_partner1->addItem(treecard->getName());
        form_partner2->addItem(treecard->getName());
    }
}


int * AddPartnershipDialog::fetchFormInputs()
{
    static int partnership[2];
    partnership[0] = form_partner1->currentIndex()-1;
    partnership[1] = form_partner2->currentIndex()-1;

    return partnership;
}
