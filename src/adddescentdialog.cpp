#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

#include "adddescentdialog.h"
#include "mainwindow.h"
#include "worksheet.h"


AddDescentDialog::AddDescentDialog(QWidget *parent) : QDialog(parent)
{
    form_parents = new QComboBox();
    form_parents->setEditable(true);

    form_child = new QComboBox();
    form_child->setEditable(true);

    info = new QLabel("");
    QPalette palette = info->palette();
    palette.setColor(info->foregroundRole(), Qt::red);
    info->setPalette(palette);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Parents:"), form_parents);
    layout->addRow(tr("Child:"), form_child);
    layout->addRow(info);
    layout->addRow(buttonbox);
    setLayout(layout);

    setWindowTitle("Add Descent");
}


void AddDescentDialog::populateDropDownMenus(QList<TreeObject *> tree_objects, QList<Relation *> partnership_relations)
{
    treecards = tree_objects;
    partnerships = partnership_relations;

    form_parents->lineEdit()->setPlaceholderText(tr("Select"));
    form_child->lineEdit()->setPlaceholderText(tr("Select"));

    int i = 0;
    foreach(Relation *partnership, partnerships)
    {
        QList<TreeObject *> treecards = partnership->getTreeObjects();
        partnerships_in_dropdown.insert(treecards[0]->getName()+", "+treecards[1]->getName(), i++);
        form_parents->addItem(treecards[0]->getName()+", "+treecards[1]->getName());
    }

    i = 0;
    foreach(TreeObject *treecard, treecards)
    {
        if (treecard->descent == nullptr)
        {
            children_in_dropdown.insert(treecard->getName(), i);
            form_child->addItem(treecard->getName());
        }
        i++;
    }

    form_parents->model()->sort(0);
    form_parents->setCurrentIndex(-1);
    connect(form_parents, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));

    form_child->model()->sort(0);
    form_child->setCurrentIndex(-1);
    connect(form_child, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));
}


int* AddDescentDialog::fetchFormInputs()
{
    static int descent[2];
    descent[0] = partnerships_in_dropdown[form_parents->currentText()];
    descent[1] = children_in_dropdown[form_child->currentText()];

    return descent;
}


bool AddDescentDialog::detectCycle(Relation* parents, TreeObject* child)
{
    foreach (Relation *partnership, child->partnerships)
        foreach(Relation *descent, partnership->descents)
            if (descent->tree_objects[0] == parents->tree_objects[0] ||
                descent->tree_objects[0] == parents->tree_objects[1])
                return true;
            else
                if (detectCycle(parents, descent->tree_objects[0]))
                    return true;

    return false;
}


void AddDescentDialog::analyzeInputPairs()
{
    if (form_parents->currentIndex() >= 0 && form_child->currentIndex() >= 0) {
        Relation *parents = partnerships[partnerships_in_dropdown[form_parents->currentText()]];
        TreeObject *child = treecards[children_in_dropdown[form_child->currentText()]];

        if (parents->tree_objects[0] == child || parents->tree_objects[1] == child) {
            info->setText("Child and parent are the same person.");
            buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
        else if (parents->tree_objects[0]->descent == nullptr && parents->tree_objects[1]->descent == nullptr) {
            info->setText("");
            buttonbox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
        else {
            if (detectCycle(parents, child)) {
                info->setText("Cycle detected. At least one parent is a descendant of the selected child.");
                buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
            }
            else {
                info->setText("");
                buttonbox->button(QDialogButtonBox::Ok)->setEnabled(true);
            }
        }
    }
}
