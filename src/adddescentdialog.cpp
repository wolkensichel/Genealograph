#include <QGridLayout>

#include "adddescentdialog.h"
#include "mainwindow.h"
#include "worksheet.h"


AddDescentDialog::AddDescentDialog(QWidget *parent) : QDialog(parent)
{
    label_parents = new QLabel(tr("Parents:"));
    label_child = new QLabel(tr("Child:"));

    form_parents = new QComboBox();
    form_child = new QComboBox();

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label_parents, 0, 0);
    layout->addWidget(form_parents, 0, 1);
    layout->addWidget(label_child, 1, 0);
    layout->addWidget(form_child, 1, 1);
    layout->addWidget(buttonbox, 3, 0, 1, 3);
    setLayout(layout);

    setWindowTitle("Add Descent");
}


void AddDescentDialog::populateDropDownMenus(QList<TreeObject *> tree_objects, QList<Relation *> partnership_relations)
{
    form_parents->addItem(tr("Select"));
    form_child->addItem(tr("Select"));

    foreach(Relation *partnership, partnership_relations)
    {
        QList<TreeObject *> treecards = partnership->getTreeObjects();
        form_parents->addItem(treecards[0]->getName()+", "+treecards[1]->getName());
    }

    foreach(TreeObject *treecard, tree_objects)
        form_child->addItem(treecard->getName());
}


int * AddDescentDialog::fetchFormInputs()
{
    static int descent[2];
    descent[0] = form_parents->currentIndex()-1;
    descent[1] = form_child->currentIndex()-1;

    return descent;
}
