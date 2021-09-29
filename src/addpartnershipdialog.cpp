#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

#include "addpartnershipdialog.h"
#include "mainwindow.h"
#include "worksheet.h"
#include "treeobject.h"


AddPartnershipDialog::AddPartnershipDialog(QList<std::tuple<QString, QString, bool>> input_cfg_partnerships, QMap<quint16, TreeObject *> tree_objects, QWidget *parent)
    : QDialog(parent), input_cfg(input_cfg_partnerships)
{
    layout = new QFormLayout;

    initializeInputs();
    populateDropDownMenus(tree_objects);

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
    setWindowTitle("Add Partnership");
}


void AddPartnershipDialog::initializeInputs()
{
    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter)
    {
        QString key = std::get<0>(*iter);
        QString form_type = std::get<1>(*iter);

        input_form form_object;
        if (form_type == "QLineEdit")
        {
            form_object.line_edit = new QLineEdit;
            layout->addRow(key + ":", form_object.line_edit);
        }
        else if (form_type == "QDateEdit")
        {
            // use QSpinBoxes instead?
            form_object.date_edit = new QDateEdit;
            form_object.date_edit->setDisplayFormat("dd.MM.yyyy");
            form_object.date_edit->setMinimumDate(QDate(100, 1, 1));
            form_object.date_edit->setMaximumDate(QDate(9999, 12, 31));
            if (key == "Date ended")
                form_object.date_edit->setDate(QDate(9999, 12, 31));
            layout->addRow(key + ":", form_object.date_edit);
        }
        else if (form_type == "QComboBox")
        {
            form_object.box_edit = new QComboBox;
            if (key == "Type")
            {
                form_object.box_edit->addItem("");
                form_object.box_edit->addItem("Married");
            }
            layout->addRow(key + ":", form_object.box_edit);
        }
        else if (form_type == "QTextEdit")
        {
            form_object.text_edit = new QTextEdit;
            layout->addRow(key + ":", form_object.text_edit);
        }
        forms.insert(key, form_object);
    }
}


void AddPartnershipDialog::populateDropDownMenus(QMap<quint16, TreeObject *> tree_objects)
{  
    treecards = tree_objects;

    forms["Partner 1"].box_edit->setEditable(true);
    forms["Partner 2"].box_edit->setEditable(true);

    forms["Partner 1"].box_edit->lineEdit()->setPlaceholderText(tr("Select"));
    forms["Partner 2"].box_edit->lineEdit()->setPlaceholderText(tr("Select"));

    QMapIterator<quint16, TreeObject *> iter(tree_objects);
    while (iter.hasNext())
    {
        TreeObject *treecard = iter.next().value();
        QString value = createDropDownPerson(treecard);
        persons_in_dropdown.insert(value, treecard->content.id);
        forms["Partner 1"].box_edit->addItem(value);
        forms["Partner 2"].box_edit->addItem(value);
    }

    forms["Partner 1"].box_edit->model()->sort(0);
    forms["Partner 1"].box_edit->setCurrentIndex(-1);
    connect(forms["Partner 1"].box_edit, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));

    forms["Partner 2"].box_edit->model()->sort(0);
    forms["Partner 2"].box_edit->setCurrentIndex(-1);
    connect(forms["Partner 2"].box_edit, SIGNAL(currentIndexChanged(int)), this, SLOT(analyzeInputPairs()));
}


QString AddPartnershipDialog::createDropDownPerson(TreeObject *treecard)
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


partnership AddPartnershipDialog::fetchFormInputs()
{
    partnership new_partnership;
    new_partnership.id = 0;

    QList<std::tuple<QString, QString, bool>>::iterator iter;
    for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter)
    {
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
            if (key == "Partner 1" || key == "Partner 2")
                item.value = persons_in_dropdown[forms[key].box_edit->currentText()];
            else
                item.value = forms[key].box_edit->currentText();
        else if (form == "QTextEdit")
            item.value = forms[key].text_edit->toPlainText();

        if (item.value.toString().isEmpty())
            item.show = false;

        new_partnership.items.insert(key, item);
    }

    return new_partnership;
}


void AddPartnershipDialog::analyzeInputPairs()
{
    if (forms["Partner 1"].box_edit->currentIndex() >= 0 && forms["Partner 2"].box_edit->currentIndex() >= 0)
    {

        if (forms["Partner 1"].box_edit->currentIndex() == forms["Partner 2"].box_edit->currentIndex())
        {
            info->setText("Partners selected are the same person.");
            buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
        else
        {
            info->setText("");
            buttonbox->button(QDialogButtonBox::Ok)->setEnabled(true);

            TreeObject *partner1 = treecards[persons_in_dropdown[forms["Partner 1"].box_edit->currentText()]];
            TreeObject *partner2 = treecards[persons_in_dropdown[forms["Partner 2"].box_edit->currentText()]];

            foreach (Relation *partnership, partner1->partnerships)
                if (partnership->tree_objects[0] == partner2 || partnership->tree_objects[1] == partner2)
                {
                    info->setText("Partnership already exists.");
                    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);
                    break;
                }
        }
    }
}
