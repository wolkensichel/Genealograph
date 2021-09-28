#ifndef PARTNERSHIPINFOLISTITEM_H
#define PARTNERSHIPINFOLISTITEM_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>

#include "data.h"


class PartnershipInfo;

class PartnershipInfoListItem : public QWidget
{
    Q_OBJECT

public:
    PartnershipInfoListItem(QString, bool, PartnershipInfo*);
    void enableFormEditing(bool);
    void enableEditing(bool);

private:
    void fillField(QString, container_item);
    void enableForm();

    QString key;
    QString form_type;
    bool enable_form_editing;
    PartnershipInfo *owner;

    QHBoxLayout *layout;

    QLabel *label;
    input_form form_object;
    QCheckBox *checkbox;

private slots:
    void updatePartnershipInfo(QString);
    void prepareDateAndUpdatePartnershipInfo(QDate);
    void changePartnershipInfoShowStatus(bool);
};

#endif // PARTNERSHIPINFOLISTITEM_H
