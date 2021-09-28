#ifndef BIOGRAPHYLISTITEM_H
#define BIOGRAPHYLISTITEM_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>

#include "data.h"


class TreeObject;


class BiographyListItem : public QWidget
{
    Q_OBJECT

public:
    BiographyListItem(QString, bool, bool, TreeObject*);
    void enableFormEditing(bool);
    void enableEditing(bool);

private:
    void fillField(QString, container_item);
    void enableForm();

    QString key;
    QString form_type;
    bool enable_form_editing;
    TreeObject *owner;

    QHBoxLayout *layout;

    QLabel *label;
    input_form form_object;
    QCheckBox *checkbox;

private slots:
    void updateTreeObjectBio(QString);
    void prepareDateAndUpdateTreeObjectBio(QDate);
    void changeBioShowStatus(bool);
};

#endif // BIOGRAPHYLISTITEM_H
