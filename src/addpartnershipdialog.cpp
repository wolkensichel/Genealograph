#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

#include "addpartnershipdialog.h"
#include "mainwindow.h"
#include "worksheet.h"


AddPartnershipDialog::AddPartnershipDialog(QWidget *parent) : QDialog(parent)
{
    form_partnership_type = new QComboBox();
    form_partnership_start_date = new QLineEdit();
    form_partnership_start_place = new QLineEdit();
    form_partnership_end_date = new QLineEdit();

    form_partner1 = new QComboBox();
    form_partner1->setEditable(true);

    form_partner2 = new QComboBox();
    form_partner2->setEditable(true);

    info = new QLabel("");
    QPalette palette = info->palette();
    palette.setColor(info->foregroundRole(), Qt::red);
    info->setPalette(palette);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Form of Partnership:"), form_partnership_type);
    layout->addRow(tr("Partner 1:"), form_partner1);
    layout->addRow(tr("Partner 2:"), form_partner2);
    layout->addRow(tr("From:"), form_partnership_start_date);
    layout->addRow(tr("Place:"), form_partnership_start_place);
    layout->addRow(tr("Until:"), form_partnership_end_date);
    layout->addRow(info);
    layout->addRow(buttonbox);
    setLayout(layout);

    setWindowTitle("Add Partnership");
}


void AddPartnershipDialog::populateDropDownMenus(QList<TreeObject *> tree_objects)
{  
    treecards = tree_objects;

    form_partner1->lineEdit()->setPlaceholderText(tr("Select"));
    form_partner2->lineEdit()->setPlaceholderText(tr("Select"));

    int i = 0;
    foreach(TreeObject *treecard, tree_objects) {
        persons_in_dropdown.insert(treecard->getName(), i++);
        form_partner1->addItem(treecard->getName());
        form_partner2->addItem(treecard->getName());
    }

    form_partner1->model()->sort(0);
    form_partner1->setCurrentIndex(-1);
    connect(form_partner1, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));

    form_partner2->model()->sort(0);
    form_partner2->setCurrentIndex(-1);
    connect(form_partner2, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));

    form_partnership_type->addItem("");
    form_partnership_type->addItem(tr("Married"));
}


partnership AddPartnershipDialog::fetchFormInputs()
{
    partnership new_partnership;

    static int persons_indices[2];
    persons_indices[0] = persons_in_dropdown[form_partner1->currentText()];
    persons_indices[1] = persons_in_dropdown[form_partner2->currentText()];
    new_partnership.persons = persons_indices;

    new_partnership.type = form_partnership_type->currentIndex();
    new_partnership.from = form_partnership_start_date->text();
    new_partnership.until = form_partnership_end_date->text();
    new_partnership.place = form_partnership_start_place->text();

    return new_partnership;
}


void AddPartnershipDialog::analyzeInputPairs()
{
    if (form_partner1->currentIndex() >= 0 && form_partner2->currentIndex() >= 0) {

        if (form_partner1->currentIndex() == form_partner2->currentIndex()) {
            info->setText("Partners selected are the same person.");
            buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
        else {
            info->setText("");
            buttonbox->button(QDialogButtonBox::Ok)->setEnabled(true);

            TreeObject *partner1 = treecards[persons_in_dropdown[form_partner1->currentText()]];
            TreeObject *partner2 = treecards[persons_in_dropdown[form_partner2->currentText()]];

            foreach (Relation *partnership, partner1->partnerships)
                if (partnership->tree_objects[0] == partner2 || partnership->tree_objects[1] == partner2) {
                    info->setText("Partnership already exists.");
                    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
                    break;
                }
        }
    }
}
