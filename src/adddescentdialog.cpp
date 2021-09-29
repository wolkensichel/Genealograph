#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

#include "adddescentdialog.h"
#include "mainwindow.h"
#include "worksheet.h"


AddDescentDialog::AddDescentDialog(QList<std::tuple<QString, QString, bool>> input_cfg_descents, QList<TreeObject *> tree_objects, QList<Relation *> partnership_relations, QWidget *parent)
    : QDialog(parent), input_cfg(input_cfg_descents)
{
    layout = new QFormLayout;

    initializeInputs();
    populateDropDownMenus(tree_objects, partnership_relations);

    info = new QLabel("");
    QPalette palette = info->palette();
    palette.setColor(info->foregroundRole(), Qt::red);
    info->setPalette(palette);
    layout->addRow(info);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addRow(buttonbox);

    setLayout(layout);
    setWindowTitle("Add Descent");
}


void AddDescentDialog::initializeInputs()
{
    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter) {
        QString key = std::get<0>(*iter);
        QString form_type = std::get<1>(*iter);

        input_form form_object;
        if (form_type == "QLineEdit") {
            form_object.line_edit = new QLineEdit;
            layout->addRow(key + ":", form_object.line_edit);
        }
        else if (form_type == "QDateEdit") {
            // use QSpinBoxes instead?
            form_object.date_edit = new QDateEdit;
            form_object.date_edit->setDisplayFormat("dd.MM.yyyy");
            form_object.date_edit->setMinimumDate(QDate(100, 1, 1));
            form_object.date_edit->setMaximumDate(QDate(9999, 12, 31));
            layout->addRow(key + ":", form_object.date_edit);
        }
        else if (form_type == "QComboBox") {
            form_object.box_edit = new QComboBox;
            layout->addRow(key + ":", form_object.box_edit);
        }
        else if (form_type == "QTextEdit") {
            form_object.text_edit = new QTextEdit;
            layout->addRow(key + ":", form_object.text_edit);
        }
        forms.insert(key, form_object);
    }
}


void AddDescentDialog::populateDropDownMenus(QList<TreeObject *> tree_objects, QList<Relation *> partnership_relations)
{
    treecards = tree_objects;
    partnerships = partnership_relations;

    forms["Parents"].box_edit->setEditable(true);
    forms["Child"].box_edit->setEditable(true);

    forms["Parents"].box_edit->lineEdit()->setPlaceholderText(tr("Select"));
    forms["Child"].box_edit->lineEdit()->setPlaceholderText(tr("Select"));

    int i = 0;
    foreach(Relation *partnership, partnerships)
    {
        QList<TreeObject *> treecards = partnership->getTreeObjects();
        QString partner1 = createDropDownPerson(treecards[0]);
        QString partner2 = createDropDownPerson(treecards[1]);
        QString value = partner1 + " and " + partner2;
        partnerships_in_dropdown.insert(value, i++);
        forms["Parents"].box_edit->addItem(value);
    }

    i = 0;
    foreach(TreeObject *treecard, treecards)
    {
        if (treecard->descent == nullptr)
        {
            QString value = createDropDownPerson(treecard);
            children_in_dropdown.insert(value, i);
            forms["Child"].box_edit->addItem(value);
        }
        i++;
    }

    forms["Parents"].box_edit->model()->sort(0);
    forms["Parents"].box_edit->setCurrentIndex(-1);
    connect(forms["Parents"].box_edit, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));

    forms["Child"].box_edit->model()->sort(0);
    forms["Child"].box_edit->setCurrentIndex(-1);
    connect(forms["Child"].box_edit, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));
}


QString AddDescentDialog::createDropDownPerson(TreeObject *treecard)
{
    QString birth_date = treecard->content.items["Date of birth"].value.toString();
    birth_date = (!birth_date.isEmpty()) ? ", b. " + birth_date : "";
    QString death_date = treecard->content.items["Date of death"].value.toString();
    death_date = (!death_date.isEmpty()) ? ", d. " + death_date : "";
    QString first_name = treecard->content.items["First name"].value.toString();
    first_name = (!first_name.isEmpty()) ? ", " + first_name : "";
    QString last_name = treecard->content.items["Last name"].value.toString();
    QString value = last_name + first_name + birth_date + death_date;
    if (!value.isEmpty() && value.startsWith(", "))
        value.remove(0, 2);

    return value;
}


descent AddDescentDialog::fetchFormInputs()
{
    /*static int descent[2];
    descent[0] = partnerships_in_dropdown[form_parents->currentText()];
    descent[1] = children_in_dropdown[form_child->currentText()];

    return descent;*/

    descent new_descent;

    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter) {
        QString key = std::get<0>(*iter);
        QString form = std::get<1>(*iter);

        container_item item;
        item.form_type = std::get<1>(*iter);
        item.show = std::get<2>(*iter);

        if (form == "QLineEdit")
            item.value = forms[key].line_edit->text();
        else if (form == "QDateEdit")
            item.value = forms[key].date_edit->date();
        else if (form == "QComboBox")
            if (key == "Parents")
                item.value = partnerships_in_dropdown[forms[key].box_edit->currentText()];
            else if (key == "Child")
                item.value = children_in_dropdown[forms[key].box_edit->currentText()];
            else
                item.value = forms[key].box_edit->currentText();
        else if (form == "QTextEdit")
            item.value = forms[key].text_edit->toPlainText();

        new_descent.items.insert(key, item);
    }

    return new_descent;
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
    if (forms["Parents"].box_edit->currentIndex() >= 0 && forms["Child"].box_edit->currentIndex() >= 0) {
        Relation *parents = partnerships[partnerships_in_dropdown[forms["Parents"].box_edit->currentText()]];
        TreeObject *child = treecards[children_in_dropdown[forms["Child"].box_edit->currentText()]];

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
