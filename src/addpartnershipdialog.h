#ifndef ADDPARTNERSHIPDIALOG_H
#define ADDPARTNERSHIPDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>

#include "data.h"
#include "treeobject.h"

class AddPartnershipDialog : public QDialog
{
    Q_OBJECT

public:
    AddPartnershipDialog(QList<std::tuple<QString, QString, bool>>, QList<TreeObject *>, QWidget *parent = nullptr);
    partnership fetchFormInputs();

private:
    void initializeInputs();
    void populateDropDownMenus(QList<TreeObject *>);

    QList<std::tuple<QString, QString, bool>> input_cfg;
    QMap <QString, input_form> forms;

    QFormLayout *layout;

    QDialogButtonBox *buttonbox;

    QLabel *info;

    QList<TreeObject *> treecards;
    QMap<QString, int> persons_in_dropdown = {};

private slots:
    void analyzeInputPairs();
};

#endif // ADDPARTNERSHIPDIALOG_H
