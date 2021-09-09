#ifndef PARTNERSHIPINFO_H
#define PARTNERSHIPINFO_H

#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"


class PartnershipInfo : public QGraphicsRectItem
{
public:
    PartnershipInfo(partnership);
    void updatePosition(QPointF);

    QWidget *widget;

    int relation_type;

private:
    void fillFields();

    QGraphicsProxyWidget *proxy;
    QVBoxLayout *layout;

    QString from;
    QString until;
    QString place;
};

#endif // PARTNERSHIPINFO_H
