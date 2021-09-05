#ifndef ADDPARTNERSHIPDIALOG_H
#define ADDPARTNERSHIPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QDialogButtonBox>

#include "data.h"
#include "treeobject.h"

class AddPartnershipDialog : public QDialog
{
    Q_OBJECT

public:
    AddPartnershipDialog(QWidget *parent = nullptr);
    void populateDropDownMenus(QList<TreeObject *>);
    int * fetchFormInputs();

private:
    QLabel *label_partner1;
    QLabel *label_partner2;

    QLabel *info;

    QComboBox *form_partner1;
    QComboBox *form_partner2;

    QDialogButtonBox *buttonbox;

    QList<TreeObject *> treecards;

    QMap<QString, int> persons_in_dropdown = {};

private slots:
    void analyzeInputPairs();
};

#endif // ADDPARTNERSHIPDIALOG_H
