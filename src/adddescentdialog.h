#ifndef ADDDESCENTDIALOG_H
#define ADDDESCENTDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QDialogButtonBox>

#include "data.h"
#include "treeobject.h"

class AddDescentDialog : public QDialog
{
    Q_OBJECT

public:
    AddDescentDialog(QList<std::tuple<QString, QString, bool>>, QMap<quint16, TreeObject *>, QMap<quint16, Relation *>, QWidget *parent = nullptr);
    descent fetchFormInputs();

private:
    void initializeInputs();
    void populateDropDownMenus(QMap<quint16, TreeObject *>, QMap<quint16, Relation *>);
    QString createDropDownPerson(TreeObject*);
    bool detectCycle(Relation*, TreeObject*);

    QList<std::tuple<QString, QString, bool>> input_cfg;
    QMap <QString, input_form> forms;

    QFormLayout *layout;
    QDialogButtonBox *buttonbox;

    QLabel *info;

    QMap<quint16, TreeObject *> treecards;
    QMap<quint16, Relation *> partnerships;
    QMap<QString, int> partnerships_in_dropdown = {};
    QMap<QString, int> children_in_dropdown = {};

private slots:
    void analyzeInputPairs();
};

#endif // ADDDESCENTDIALOG_H
