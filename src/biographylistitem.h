#ifndef BIOGRAPHYLISTITEM_H
#define BIOGRAPHYLISTITEM_H

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>

#include "data.h"


class TreeObject;


class BiographyListItem : public QWidget// : public QLabel
{
    Q_OBJECT

public:
    BiographyListItem(QVariant&, QString, bool, bool, bool, TreeObject*);
    void enableTextEditing(bool);
    void enableEditing(bool);

private:
    void adjustStyle();

    bool enable_text_editing;

    TreeObject *current_owner;
    QHBoxLayout *layout;
    QLabel *label;
    QLineEdit *form;
    QCheckBox *checkbox;

private slots:
    void updateTreeObjectBio(QString);
    void changeBioShowStatus(bool);
};

#endif // BIOGRAPHYLISTITEM_H
