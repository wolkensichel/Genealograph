#ifndef ADDDESCENTDIALOG_H
#define ADDDESCENTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QDialogButtonBox>

#include "data.h"
#include "treeobject.h"

class AddDescentDialog : public QDialog
{
    Q_OBJECT

public:
    AddDescentDialog(QWidget *parent = nullptr);
    void populateDropDownMenus(QList<TreeObject *>, QList<Relation *>);
    int * fetchFormInputs();

private:
    QLabel *label_parents;
    QLabel *label_child;

    QComboBox *form_parents;
    QComboBox *form_child;

    QDialogButtonBox *buttonbox;

};

#endif // ADDDESCENTDIALOG_H