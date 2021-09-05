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
    bool detectCycle(Relation*, TreeObject*);

    QLabel *label_parents;
    QLabel *label_child;

    QComboBox *form_parents;
    QComboBox *form_child;

    QLabel *info;

    QDialogButtonBox *buttonbox;

    QList<TreeObject *> treecards;
    QList<Relation *> partnerships;

    QMap<QString, int> partnerships_in_dropdown = {};
    QMap<QString, int> children_in_dropdown = {};

private slots:
    void analyzeInputPairs();
};

#endif // ADDDESCENTDIALOG_H
